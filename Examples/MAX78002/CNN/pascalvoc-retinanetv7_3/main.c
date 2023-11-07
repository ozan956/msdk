/******************************************************************************
 * Copyright (C) 2023 Maxim Integrated Products, Inc., All Rights Reserved.
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

// pascalvoc-retinanetv7_3
// This file was @generated by ai8xize.py --test-dir sdk/Examples/MAX78002/CNN --prefix pascalvoc-retinanetv7_3 --checkpoint-file retinanet_v7_test/ai87_ssd_retinanetv7_256_320_pascalvoc_loss_2.961_ep388_qat_best_q_altered.pth.tar --config-file retinanet_v7_test/pascalvoc-retinanetv7-wideout-fail.yaml --sample-input retinanet_v7_test/sample_pascalvoc_256_320.npy --overlap-data --device MAX78002 --display-checkpoint --verbose --overwrite --fifo --no-unload --no-kat

// This file was also modified to implement the load_input function, which depends on
// other software modules in this project to capture image data from an OV5640 CSI2
// camera, buffer it to the external APS6404 SRAM on the MAX78002EVKIT, and feed it
// to the CNN accelerator in the expected format.

// All manual modifications are marked with "MODIFICATION:"

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "mxc.h"
#include "cnn.h"
#include "sampledata.h"
// MODIFICATION: Add project includes
// ---
#include "src/sram/fastspi.h"
#include "src/tft/tft_utils.h"
#include "src/camera/camera.h"
#include "nms.h"
// ---

volatile uint32_t cnn_time; // Stopwatch

void fail(void)
{
    printf("\n*** FAIL ***\n\n");
    while (1) {}
}

// MODIFICATION: Implement load_input for OV5640 CSI2 camera
// Data input: HWC 3x256x320 (245760 bytes total / 81920 bytes per channel):
// static const uint32_t input_0[] = SAMPLE_INPUT_0;
void load_input(void)
{
    camera_capture_and_load_cnn();
}

int main(void)
{
    printf("\n*** Object Detection Demo (pascalvoc-retinanetv7_3) ***\n");
    MXC_ICC_Enable(MXC_ICC0); // Enable cache

    // Switch to 120 MHz clock
    MXC_SYS_Clock_Select(MXC_SYS_CLOCK_IPO);
    MXC_GCR->ipll_ctrl |= MXC_F_GCR_IPLL_CTRL_EN; // Enable IPLL
    SystemCoreClockUpdate();
    MXC_TFT_SetFont((int)&Liberation_Sans16x16[0]);
    TFT_Print("Initializing...\n", 0, 0);

    printf("Waiting...\n");

    // DO NOT DELETE THIS LINE:
    MXC_Delay(SEC(3)); // Let debugger interrupt if needed

    // MODIFICATION: console, camera, and TFT initialization
    // --- MODS START

    if (!camera_init()) {
        printf("Camera initialization failed!\n");
        return E_FAIL;
    }
    // --- MODS END

    // Enable peripheral, enable CNN interrupt, turn on CNN clock
    // CNN clock: PLL (200 MHz) div 4
    cnn_enable(MXC_S_GCR_PCLKDIV_CNNCLKSEL_IPLL, MXC_S_GCR_PCLKDIV_CNNCLKDIV_DIV4);

    cnn_init(); // Bring state machine into consistent state
    cnn_load_weights(); // Load kernels
    cnn_load_bias();

    // MODIFICATION: Add while(1) loop
    while (1) {
        cnn_configure(); // Configure state machine
        // CNN clock: PLL (200 MHz) div 1
        MXC_GCR->pclkdiv =
            (MXC_GCR->pclkdiv & ~(MXC_F_GCR_PCLKDIV_CNNCLKDIV | MXC_F_GCR_PCLKDIV_CNNCLKSEL)) |
            MXC_S_GCR_PCLKDIV_CNNCLKDIV_DIV1 | MXC_S_GCR_PCLKDIV_CNNCLKSEL_IPLL;
        cnn_start(); // Start CNN processing
        load_input(); // Load data input via FIFO

        // MODIFICATION: Display captured image on TFT
        camera_display_last_image();

        while (cnn_time == 0) MXC_LP_EnterSleepMode(); // Wait for CNN

        // Switch CNN clock to PLL (200 MHz) div 4

        MXC_GCR->pclkdiv =
            (MXC_GCR->pclkdiv & ~(MXC_F_GCR_PCLKDIV_CNNCLKDIV | MXC_F_GCR_PCLKDIV_CNNCLKSEL)) |
            MXC_S_GCR_PCLKDIV_CNNCLKDIV_DIV4 | MXC_S_GCR_PCLKDIV_CNNCLKSEL_IPLL;

#ifdef CNN_INFERENCE_TIMER
        printf("Inference complete!  Approximate data loading and inference time: %u us\n",
               cnn_time);
#endif

        // MODIFICATION: Run Non-Maximal Suppression (NMS) to filter and display results
        // --- MODS START
        printf("Starting NMS... \n");
        MXC_TMR_SW_Start(MXC_TMR1);
        nms_localize_objects();
        unsigned int elapsed = MXC_TMR_SW_Stop(MXC_TMR1);
        printf("Done!  (Took %i us)\n", elapsed);

        // Drawing bounding boxes is excluded from NMS calculation because all of the
        // overhead is TFT communication
        nms_draw_boxes();
        // -- MODS END

        printf("\n");
    }
    cnn_disable(); // Shut down CNN clock, disable peripheral

    MXC_GCR->ipll_ctrl &= ~MXC_F_GCR_IPLL_CTRL_EN; // Disable IPLL

    return 0;
}

/*
  SUMMARY OF OPS
  Hardware: 7,830,828,800 ops (7,804,270,080 macc; 25,245,440 comp; 1,313,280 add; 0 mul; 0 bitwise)
    Layer 0 (preprocess_layer_1): 146,800,640 ops (141,557,760 macc; 5,242,880 comp; 0 add; 0 mul; 0 bitwise)
    Layer 1 (preprocess_layer_2): 3,025,141,760 ops (3,019,898,880 macc; 5,242,880 comp; 0 add; 0 mul; 0 bitwise)
    Layer 2 (BB0_preprocess): 761,528,320 ops (754,974,720 macc; 6,553,600 comp; 0 add; 0 mul; 0 bitwise)
    Layer 3: 756,285,440 ops (754,974,720 macc; 1,310,720 comp; 0 add; 0 mul; 0 bitwise)
    Layer 4 (BB0_conv2): 756,285,440 ops (754,974,720 macc; 1,310,720 comp; 0 add; 0 mul; 0 bitwise)
    Layer 5 (BB1_preprocess): 190,382,080 ops (188,743,680 macc; 1,638,400 comp; 0 add; 0 mul; 0 bitwise)
    Layer 6: 189,071,360 ops (188,743,680 macc; 327,680 comp; 0 add; 0 mul; 0 bitwise)
    Layer 7 (BB1_conv2): 189,071,360 ops (188,743,680 macc; 327,680 comp; 0 add; 0 mul; 0 bitwise)
    Layer 8 (enc_64_80): 327,680 ops (0 macc; 0 comp; 327,680 add; 0 mul; 0 bitwise)
    Layer 9 (BB2_preprocess): 189,071,360 ops (188,743,680 macc; 327,680 comp; 0 add; 0 mul; 0 bitwise)
    Layer 10: 189,071,360 ops (188,743,680 macc; 327,680 comp; 0 add; 0 mul; 0 bitwise)
    Layer 11 (BB2_conv2): 189,071,360 ops (188,743,680 macc; 327,680 comp; 0 add; 0 mul; 0 bitwise)
    Layer 12 (enc_64_80_2): 327,680 ops (0 macc; 0 comp; 327,680 add; 0 mul; 0 bitwise)
    Layer 13 (BB3_preprocess): 47,595,520 ops (47,185,920 macc; 409,600 comp; 0 add; 0 mul; 0 bitwise)
    Layer 14: 47,267,840 ops (47,185,920 macc; 81,920 comp; 0 add; 0 mul; 0 bitwise)
    Layer 15 (BB3_conv2): 47,267,840 ops (47,185,920 macc; 81,920 comp; 0 add; 0 mul; 0 bitwise)
    Layer 16 (enc_32_40): 81,920 ops (0 macc; 0 comp; 81,920 add; 0 mul; 0 bitwise)
    Layer 17 (BB4_preprocess): 11,898,880 ops (11,796,480 macc; 102,400 comp; 0 add; 0 mul; 0 bitwise)
    Layer 18: 11,816,960 ops (11,796,480 macc; 20,480 comp; 0 add; 0 mul; 0 bitwise)
    Layer 19 (BB4_conv2): 11,816,960 ops (11,796,480 macc; 20,480 comp; 0 add; 0 mul; 0 bitwise)
    Layer 20 (enc_16_20): 20,480 ops (0 macc; 0 comp; 20,480 add; 0 mul; 0 bitwise)
    Layer 21 (BB5_preprocess): 5,928,960 ops (5,898,240 macc; 30,720 comp; 0 add; 0 mul; 0 bitwise)
    Layer 22 (BB5_conv1): 11,806,720 ops (11,796,480 macc; 10,240 comp; 0 add; 0 mul; 0 bitwise)
    Layer 23 (BB5_preprocess_gapped): 0 ops (0 macc; 0 comp; 0 add; 0 mul; 0 bitwise)
    Layer 24 (BB5_conv2): 11,806,720 ops (11,796,480 macc; 10,240 comp; 0 add; 0 mul; 0 bitwise)
    Layer 25 (enc_8_10): 10,240 ops (0 macc; 0 comp; 10,240 add; 0 mul; 0 bitwise)
    Layer 26 (BB6_preprocess): 2,961,920 ops (2,949,120 macc; 12,800 comp; 0 add; 0 mul; 0 bitwise)
    Layer 27 (BB6_conv1): 2,951,680 ops (2,949,120 macc; 2,560 comp; 0 add; 0 mul; 0 bitwise)
    Layer 28 (BB6_preprocess_gapped): 0 ops (0 macc; 0 comp; 0 add; 0 mul; 0 bitwise)
    Layer 29 (BB6_conv2): 2,951,680 ops (2,949,120 macc; 2,560 comp; 0 add; 0 mul; 0 bitwise)
    Layer 30 (enc_4_5): 2,560 ops (0 macc; 0 comp; 2,560 add; 0 mul; 0 bitwise)
    Layer 31 (skip_32_40): 5,324,800 ops (5,242,880 macc; 81,920 comp; 0 add; 0 mul; 0 bitwise)
    Layer 32 (skip_16_20): 1,331,200 ops (1,310,720 macc; 20,480 comp; 0 add; 0 mul; 0 bitwise)
    Layer 33 (skip_8_10): 660,480 ops (655,360 macc; 5,120 comp; 0 add; 0 mul; 0 bitwise)
    Layer 34 (FPN_out_4_5): 165,120 ops (163,840 macc; 1,280 comp; 0 add; 0 mul; 0 bitwise)
    Layer 35 (up_conv_4_5): 2,949,120 ops (2,949,120 macc; 0 comp; 0 add; 0 mul; 0 bitwise)
    Layer 36 (out_8_10): 5,120 ops (0 macc; 0 comp; 5,120 add; 0 mul; 0 bitwise)
    Layer 37 (FPN_out_8_10): 2,954,240 ops (2,949,120 macc; 5,120 comp; 0 add; 0 mul; 0 bitwise)
    Layer 38 (upconv_8_10): 11,796,480 ops (11,796,480 macc; 0 comp; 0 add; 0 mul; 0 bitwise)
    Layer 39 (out_16_20): 20,480 ops (0 macc; 0 comp; 20,480 add; 0 mul; 0 bitwise)
    Layer 40 (FPN_out_16_20): 11,816,960 ops (11,796,480 macc; 20,480 comp; 0 add; 0 mul; 0 bitwise)
    Layer 41 (upconv_16_20): 47,185,920 ops (47,185,920 macc; 0 comp; 0 add; 0 mul; 0 bitwise)
    Layer 42 (out_32_40): 81,920 ops (0 macc; 0 comp; 81,920 add; 0 mul; 0 bitwise)
    Layer 43 (FPN_out_32_40): 47,267,840 ops (47,185,920 macc; 81,920 comp; 0 add; 0 mul; 0 bitwise)
    Layer 44 (class_32_40_res0_preprocess): 47,267,840 ops (47,185,920 macc; 81,920 comp; 0 add; 0 mul; 0 bitwise)
    Layer 45 (class_32_40_res0_conv1): 47,267,840 ops (47,185,920 macc; 81,920 comp; 0 add; 0 mul; 0 bitwise)
    Layer 46 (class_32_40_res0_conv2): 47,267,840 ops (47,185,920 macc; 81,920 comp; 0 add; 0 mul; 0 bitwise)
    Layer 47 (class_32_40_res0): 81,920 ops (0 macc; 0 comp; 81,920 add; 0 mul; 0 bitwise)
    Layer 48 (class_32_40_res1_preprocess): 47,267,840 ops (47,185,920 macc; 81,920 comp; 0 add; 0 mul; 0 bitwise)
    Layer 49 (class_32_40_res1_conv1): 47,267,840 ops (47,185,920 macc; 81,920 comp; 0 add; 0 mul; 0 bitwise)
    Layer 50 (class_32_40_res1_conv2): 47,267,840 ops (47,185,920 macc; 81,920 comp; 0 add; 0 mul; 0 bitwise)
    Layer 51 (class_32_40_res1): 81,920 ops (0 macc; 0 comp; 81,920 add; 0 mul; 0 bitwise)
    Layer 52 (class_preds_from_32_40): 92,897,280 ops (92,897,280 macc; 0 comp; 0 add; 0 mul; 0 bitwise)
    Layer 53 (class_16_20_res0_preprocess): 11,816,960 ops (11,796,480 macc; 20,480 comp; 0 add; 0 mul; 0 bitwise)
    Layer 54: 11,816,960 ops (11,796,480 macc; 20,480 comp; 0 add; 0 mul; 0 bitwise)
    Layer 55 (class_16_20_res0_conv2): 11,816,960 ops (11,796,480 macc; 20,480 comp; 0 add; 0 mul; 0 bitwise)
    Layer 56 (class_16_20_res0): 20,480 ops (0 macc; 0 comp; 20,480 add; 0 mul; 0 bitwise)
    Layer 57 (class_16_20_res1_preprocess): 11,816,960 ops (11,796,480 macc; 20,480 comp; 0 add; 0 mul; 0 bitwise)
    Layer 58: 11,816,960 ops (11,796,480 macc; 20,480 comp; 0 add; 0 mul; 0 bitwise)
    Layer 59 (class_16_20_res1_conv2): 11,816,960 ops (11,796,480 macc; 20,480 comp; 0 add; 0 mul; 0 bitwise)
    Layer 60 (class_16_20_res1): 20,480 ops (0 macc; 0 comp; 20,480 add; 0 mul; 0 bitwise)
    Layer 61 (class_preds_from_16_20): 23,224,320 ops (23,224,320 macc; 0 comp; 0 add; 0 mul; 0 bitwise)
    Layer 62 (class_8_10_res0_preprocess): 2,954,240 ops (2,949,120 macc; 5,120 comp; 0 add; 0 mul; 0 bitwise)
    Layer 63: 2,954,240 ops (2,949,120 macc; 5,120 comp; 0 add; 0 mul; 0 bitwise)
    Layer 64 (class_8_10_res0_conv2): 2,954,240 ops (2,949,120 macc; 5,120 comp; 0 add; 0 mul; 0 bitwise)
    Layer 65 (class_8_10_res0): 5,120 ops (0 macc; 0 comp; 5,120 add; 0 mul; 0 bitwise)
    Layer 66 (class_8_10_res1_preprocess): 2,954,240 ops (2,949,120 macc; 5,120 comp; 0 add; 0 mul; 0 bitwise)
    Layer 67: 2,954,240 ops (2,949,120 macc; 5,120 comp; 0 add; 0 mul; 0 bitwise)
    Layer 68 (class_8_10_res1_conv2): 2,954,240 ops (2,949,120 macc; 5,120 comp; 0 add; 0 mul; 0 bitwise)
    Layer 69 (class_8_10_res1): 5,120 ops (0 macc; 0 comp; 5,120 add; 0 mul; 0 bitwise)
    Layer 70 (class_preds_from_8_10): 5,806,080 ops (5,806,080 macc; 0 comp; 0 add; 0 mul; 0 bitwise)
    Layer 71 (class_4_5_res0_preprocess): 738,560 ops (737,280 macc; 1,280 comp; 0 add; 0 mul; 0 bitwise)
    Layer 72: 738,560 ops (737,280 macc; 1,280 comp; 0 add; 0 mul; 0 bitwise)
    Layer 73 (class_4_5_res0_conv2): 738,560 ops (737,280 macc; 1,280 comp; 0 add; 0 mul; 0 bitwise)
    Layer 74 (class_4_5_res0): 1,280 ops (0 macc; 0 comp; 1,280 add; 0 mul; 0 bitwise)
    Layer 75 (class_4_5_res1_preprocess): 738,560 ops (737,280 macc; 1,280 comp; 0 add; 0 mul; 0 bitwise)
    Layer 76: 738,560 ops (737,280 macc; 1,280 comp; 0 add; 0 mul; 0 bitwise)
    Layer 77 (class_4_5_res1_conv2): 738,560 ops (737,280 macc; 1,280 comp; 0 add; 0 mul; 0 bitwise)
    Layer 78 (class_4_5_res1): 1,280 ops (0 macc; 0 comp; 1,280 add; 0 mul; 0 bitwise)
    Layer 79 (class_preds_from_4_5): 1,451,520 ops (1,451,520 macc; 0 comp; 0 add; 0 mul; 0 bitwise)
    Layer 80 (loc_32_40_res0_preprocess): 47,267,840 ops (47,185,920 macc; 81,920 comp; 0 add; 0 mul; 0 bitwise)
    Layer 81 (loc_32_40_res0_conv1): 47,267,840 ops (47,185,920 macc; 81,920 comp; 0 add; 0 mul; 0 bitwise)
    Layer 82 (loc_32_40_res0_conv2): 47,267,840 ops (47,185,920 macc; 81,920 comp; 0 add; 0 mul; 0 bitwise)
    Layer 83 (loc_32_40_res0): 81,920 ops (0 macc; 0 comp; 81,920 add; 0 mul; 0 bitwise)
    Layer 84 (loc_32_40_res1_preprocess): 47,267,840 ops (47,185,920 macc; 81,920 comp; 0 add; 0 mul; 0 bitwise)
    Layer 85 (loc_32_40_res1_conv1): 47,267,840 ops (47,185,920 macc; 81,920 comp; 0 add; 0 mul; 0 bitwise)
    Layer 86 (loc_32_40_res1_conv2): 47,267,840 ops (47,185,920 macc; 81,920 comp; 0 add; 0 mul; 0 bitwise)
    Layer 87 (loc_32_40_res1): 81,920 ops (0 macc; 0 comp; 81,920 add; 0 mul; 0 bitwise)
    Layer 88 (loc_preds_from_32_40): 17,694,720 ops (17,694,720 macc; 0 comp; 0 add; 0 mul; 0 bitwise)
    Layer 89 (loc_16_20_res0_preprocess): 11,816,960 ops (11,796,480 macc; 20,480 comp; 0 add; 0 mul; 0 bitwise)
    Layer 90 (loc_16_20_res0_conv1): 11,816,960 ops (11,796,480 macc; 20,480 comp; 0 add; 0 mul; 0 bitwise)
    Layer 91 (loc_16_20_res0_conv2): 11,816,960 ops (11,796,480 macc; 20,480 comp; 0 add; 0 mul; 0 bitwise)
    Layer 92 (loc_16_20_res0): 20,480 ops (0 macc; 0 comp; 20,480 add; 0 mul; 0 bitwise)
    Layer 93 (loc_16_20_res1_preprocess): 11,816,960 ops (11,796,480 macc; 20,480 comp; 0 add; 0 mul; 0 bitwise)
    Layer 94 (loc_16_20_res1_conv1): 11,816,960 ops (11,796,480 macc; 20,480 comp; 0 add; 0 mul; 0 bitwise)
    Layer 95 (loc_16_20_res1_conv2): 11,816,960 ops (11,796,480 macc; 20,480 comp; 0 add; 0 mul; 0 bitwise)
    Layer 96 (loc_16_20_res1): 20,480 ops (0 macc; 0 comp; 20,480 add; 0 mul; 0 bitwise)
    Layer 97 (loc_preds_from_16_20): 4,423,680 ops (4,423,680 macc; 0 comp; 0 add; 0 mul; 0 bitwise)
    Layer 98 (loc_8_10_res0_preprocess): 2,954,240 ops (2,949,120 macc; 5,120 comp; 0 add; 0 mul; 0 bitwise)
    Layer 99 (loc_8_10_res0_conv1): 2,954,240 ops (2,949,120 macc; 5,120 comp; 0 add; 0 mul; 0 bitwise)
    Layer 100 (loc_8_10_res0_conv2): 2,954,240 ops (2,949,120 macc; 5,120 comp; 0 add; 0 mul; 0 bitwise)
    Layer 101 (loc_8_10_res0): 5,120 ops (0 macc; 0 comp; 5,120 add; 0 mul; 0 bitwise)
    Layer 102 (loc_8_10_res1_preprocess): 2,954,240 ops (2,949,120 macc; 5,120 comp; 0 add; 0 mul; 0 bitwise)
    Layer 103 (loc_8_10_res1_conv1): 2,954,240 ops (2,949,120 macc; 5,120 comp; 0 add; 0 mul; 0 bitwise)
    Layer 104 (loc_8_10_res1_conv2): 2,954,240 ops (2,949,120 macc; 5,120 comp; 0 add; 0 mul; 0 bitwise)
    Layer 105 (loc_8_10_res1): 5,120 ops (0 macc; 0 comp; 5,120 add; 0 mul; 0 bitwise)
    Layer 106 (loc_preds_from_8_10): 1,105,920 ops (1,105,920 macc; 0 comp; 0 add; 0 mul; 0 bitwise)
    Layer 107 (loc_4_5_res0_preprocess): 738,560 ops (737,280 macc; 1,280 comp; 0 add; 0 mul; 0 bitwise)
    Layer 108 (loc_4_5_res0_conv1): 738,560 ops (737,280 macc; 1,280 comp; 0 add; 0 mul; 0 bitwise)
    Layer 109 (loc_4_5_res0_conv2): 738,560 ops (737,280 macc; 1,280 comp; 0 add; 0 mul; 0 bitwise)
    Layer 110 (loc_4_5_res0): 1,280 ops (0 macc; 0 comp; 1,280 add; 0 mul; 0 bitwise)
    Layer 111 (loc_4_5_res1_preprocess): 738,560 ops (737,280 macc; 1,280 comp; 0 add; 0 mul; 0 bitwise)
    Layer 112 (loc_4_5_res1_conv1): 738,560 ops (737,280 macc; 1,280 comp; 0 add; 0 mul; 0 bitwise)
    Layer 113 (loc_4_5_res1_conv2): 738,560 ops (737,280 macc; 1,280 comp; 0 add; 0 mul; 0 bitwise)
    Layer 114 (loc_4_5_res1): 1,280 ops (0 macc; 0 comp; 1,280 add; 0 mul; 0 bitwise)
    Layer 115 (loc_preds_from_4_5): 276,480 ops (276,480 macc; 0 comp; 0 add; 0 mul; 0 bitwise)

  RESOURCE USAGE
  Weight memory: 2,177,088 bytes out of 2,396,160 bytes total (90.9%)
  Bias memory:   3,414 bytes out of 8,192 bytes total (41.7%)
*/
