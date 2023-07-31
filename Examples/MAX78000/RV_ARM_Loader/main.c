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

/**
 * @file    main.c
 * @brief   A basic getting started program for the RISCV, run from the ARM core.
 * @details RV_ARM_Loader runs on the ARM core to load the RISCV code space, setup the RISCV debugger pins,
            and start the RISCV core.
 */

/***** Includes *****/
#include <stdio.h>
#include <stdint.h>
#include "mxc_device.h"
#include "mxc_delay.h"
#include "mxc_sys.h"
#include "sema.h"
#include "led.h"
#include "nvic_table.h"

/***** Definitions *****/

/***** Globals *****/


/***** Functions *****/

void WakeISR(void)
{
    MXC_SEMA->irq0 = MXC_F_SEMA_IRQ0_EN & ~MXC_F_SEMA_IRQ0_CM4_IRQ;
    printf("Hello RISC-V!\n");
}

// *****************************************************************************
int main(void)
{
    printf("ARM: RV_ARM_Loader\n");

    MXC_Delay(MXC_DELAY_SEC(2));

    // printf("_riscv_boot: 0x%x\n", (uint32_t)&_riscv_boot);

    // Switch to 100 MHz clock
    // MXC_SYS_Clock_Select(MXC_SYS_CLOCK_IPO);
    SystemCoreClockUpdate();

    MXC_SYS_ClockEnable(MXC_SYS_PERIPH_CLOCK_SMPHR); // Enable Sempahore clock
    NVIC_EnableIRQ(RISCV_IRQn);
    MXC_NVIC_SetVector(RISCV_IRQn, WakeISR); // Set wakeup ISR

    /* Enable RISCV debugger GPIO */
    MXC_GPIO_Config(&gpio_cfg_rv_jtag);

    /* Start the RISCV core */
    MXC_SYS_RISCVRun();

    /* Enter LPM */
    while (1) {}
}
