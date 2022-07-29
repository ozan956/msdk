/**
 * @file        main.c
 * @brief       I2S Transmitter Example
 * @details
 * @note
 */

/*******************************************************************************
 * Copyright (C) Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 ******************************************************************************/

/***** Includes *****/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "dma.h"
#include "i2s.h"
#include "i2s_regs.h"
#include "icc.h"
#include "led.h"
#include "max9867.h"
#include "mxc_delay.h"
#include "mxc_device.h"
#include "mxc_sys.h"
#include "nvic_table.h"
#include "pb.h"
#include "Ext_Flash.h"

/***** Definitions *****/
#if defined(BOARD_FTHR_APPS_P1)
#define I2C_MASTER  MXC_I2C1 // SCL P0_16; SDA P0_17
#define CONNECT_NUM 2
#else
#define I2C_MASTER  MXC_I2C2 // SCL P0_30; SDA P0_31
#define CONNECT_NUM 3
#endif

#define BUF_SIZE                     16000
#define SMPL_RATE                    48000
#define BUF_SEL(CUR_BUF, BUF1, BUF2) ((CUR_BUF == BUF1) ? BUF2 : BUF1)

/***** Global Data *****/
Ext_Flash_Unblk_t free_flash;
mxc_i2s_req_t i2s_req;
volatile uint8_t i2s_done = 0;
int16_t buf0[BUF_SIZE];
int16_t buf1[BUF_SIZE];

/*****************************************************************/
void i2s_dma_cb(int handle, int error)
{
    i2s_done = 1;
}

/*****************************************************************/
void DMA_IRQHandler(void)
{
    MXC_DMA_Handler();
}

/*****************************************************************/
int i2s_init(void)
{
    int err = E_NO_ERROR;

    i2s_req.wordSize    = MXC_I2S_DATASIZE_HALFWORD; // Configure I2S interface parameters
    i2s_req.sampleSize  = MXC_I2S_SAMPLESIZE_SIXTEEN;
    i2s_req.justify     = MXC_I2S_LSB_JUSTIFY;
    i2s_req.wsPolarity  = MXC_I2S_POL_NORMAL;
    i2s_req.channelMode = MXC_I2S_EXTERNAL_SCK_EXTERNAL_WS; // BLCK & LRCLK generated by codec
    i2s_req.stereoMode  = MXC_I2S_MONO_RIGHT_CH; // Receive only right channel data from codec.
    i2s_req.bitOrder    = MXC_I2S_LSB_FIRST;
    i2s_req.clkdiv      = MXC_I2S_CalculateClockDiv(SMPL_RATE, i2s_req.wordSize) + 1;
    i2s_req.rawData     = NULL;
    i2s_req.txData      = NULL;
    i2s_req.rxData      = buf0;
    i2s_req.length      = sizeof(buf0);

    err = MXC_I2S_Init(&i2s_req); // Initialize I2S
    if (err != E_NO_ERROR) {
        return err;
    }

    MXC_I2S_RegisterDMACallback(i2s_dma_cb);
    MXC_NVIC_SetVector(DMA0_IRQn, DMA_IRQHandler);

    return err;
}

/*****************************************************************/
int ext_flash_init(void)
{
    int err;

    err = Ext_Flash_Init();
    if (err != E_NO_ERROR) {
        return err;
    }

    printf("\nErasing external flash. This will take a moment...\n");
    err = Ext_Flash_Bulk_Erase();
    if (err == E_NO_ERROR) {
        printf("Erase complete.\n");
    } else {
        printf("Erase failed with error: %d", err);
    }

    return err;
}

/*****************************************************************/
uint32_t record_audio(void)
{
    void* flash_buf = buf0;
    void* i2s_buf   = buf0;

    uint32_t flash_addr = free_flash.start_addr;

    i2s_done = 0;
    MXC_DMA_ReleaseChannel(0);
    LED_On(0);
    MXC_I2S_RXDMAConfig(i2s_buf, sizeof(buf0)); // Start collecting first set of I2S samples

    while (PB_Get(0) && flash_addr < free_flash.end_addr) {
        while (!i2s_done)
            ; // Wait for I2S transaction to finish

        flash_buf = i2s_buf;
        i2s_buf   = BUF_SEL(i2s_buf, buf0, buf1); // Select sample buffer

        i2s_done = 0; // Receive next set of audio samples
        MXC_DMA_ReleaseChannel(0);
        MXC_I2S_RXDMAConfig(i2s_buf, sizeof(buf0));

        Ext_Flash_Program_Page(flash_addr, (uint8_t*)flash_buf, sizeof(buf0),
                               Ext_Flash_DataLine_Quad); // Store received audio samples
        flash_addr += sizeof(buf0);
    }
    LED_Off(0);

    return flash_addr; // Return flash address where the recording ended
}

/*****************************************************************/
void playback_audio(uint32_t eor_addr)
{
    void* flash_buf = buf0;
    void* i2s_buf   = buf0;

    LED_Off(0);
    LED_On(1);

    Ext_Flash_Read(free_flash.start_addr, (uint8_t*)flash_buf, sizeof(buf0),
                   Ext_Flash_DataLine_Quad); // Get first set of audio samples

    for (int i = free_flash.start_addr; i < eor_addr; i += sizeof(buf0)) {
        LED_Toggle(0);
        LED_Toggle(1);

        i2s_buf = flash_buf;

        i2s_done = 0; // Start transmission of audio samples
        MXC_DMA_ReleaseChannel(0);
        MXC_I2S_TXDMAConfig(i2s_buf, sizeof(buf0));

        flash_buf = BUF_SEL(flash_buf, buf0, buf1); // Get next set of audio samples
        Ext_Flash_Read(i, (uint8_t*)flash_buf, sizeof(buf0), Ext_Flash_DataLine_Quad);

        while (!i2s_done)
            ;
    }

    LED_Off(0);
    LED_Off(1);
}

/*****************************************************************/
int main()
{
    int err;
    uint32_t eor_addr;

    MXC_ICC_Enable(MXC_ICC0); // Enable cache

    MXC_SYS_Clock_Select(MXC_SYS_CLOCK_IPO); // Set system clock to 100 MHz
    SystemCoreClockUpdate();

    printf("\n******************* I2S Record/Playback Example *******************\n");

    printf("\nThis example demonstrates how to record audio from the on-board\n");
    printf("digital microphone and play the recorded audio back out through\n");
    printf("the headphone jack.\n");

    printf("\nOnce the green LED is illiuminated the system is ready to begin\n");
    printf("recording. Recording will start when button SW3 is pressed and will\n");
    printf("continue until the button is released or the external memory is\n");
    printf("full.\n");

    printf("\nAfter the recording has finished the audio will begin playing after\n");
    printf("a 3 second delay.\n");

    err = i2s_init(); // Initialize I2S interface
    if (err != E_NO_ERROR) {
        printf("Error configuring Audio Codec I2S interface.\n");
        while (1)
            ;
    }

    err = max9867_init(I2C_MASTER, 12288000, SMPL_RATE); // Initialize audio codec
    if (err != E_NO_ERROR) {
        printf("Error configuring audio codec: %i", err);
        while (1)
            ;
    }

    err = ext_flash_init(); // Initialize external flash chip used to store audio samples
    if (err != E_NO_ERROR) {
        printf("Error initializing external flash.\n");
        while (1)
            ;
    }
    free_flash = Ext_Flash_GetAvailableFlash();

    printf("\nPress and hold SW3 to start recording.\n");
    LED_On(1);
    while (!PB_Get(0))
        ;                           // Wait for button press
    MXC_Delay(MXC_DELAY_MSEC(500)); // Button debounce

    printf("\nRecording started.\n");
    eor_addr = record_audio(); // Record audio samples
    printf("Recording ended.\n");

    MXC_Delay(MXC_DELAY_SEC(5));

    printf("\nPlayback starting.\n");
    playback_audio(eor_addr); // Playback audio recording
    printf("Playback ended.\n");

    return E_NO_ERROR;
}
