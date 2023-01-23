/**
 * @file    tmr.h
 * @brief   Timer (TMR) function prototypes and data types.
 */

/******************************************************************************
 * Copyright (C) 2023 Maxim Integrated Products, Inc., All rights Reserved.
 * 
 * This software is protected by copyright laws of the United States and
 * of foreign countries. This material may also be protected by patent laws
 * and technology transfer regulations of the United States and of foreign
 * countries. This software is furnished under a license agreement and/or a
 * nondisclosure agreement and may only be used or reproduced in accordance
 * with the terms of those agreements. Dissemination of this information to
 * any party or parties not specified in the license agreement and/or
 * nondisclosure agreement is expressly prohibited.
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

/* Define to prevent redundant inclusion */
#ifndef LIBRARIES_PERIPHDRIVERS_INCLUDE_MAX32570_TMR_H_
#define LIBRARIES_PERIPHDRIVERS_INCLUDE_MAX32570_TMR_H_

/* **** Includes **** */
#include <stdint.h>
#include "mxc_device.h"
#include "tmr_regs.h"
#include "mxc_sys.h"
#include "gcr_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup tmr Timer (TMR)
 * @ingroup periphlibs
 * @{
 */

/**
 * @brief      Timer prescaler values
 */
typedef enum {
    MXC_TMR_PRES_1 = MXC_S_TMR_CTRL_CLKDIV_DIV1, ///< Divide input clock by 1
    MXC_TMR_PRES_2 = MXC_S_TMR_CTRL_CLKDIV_DIV2, ///< Divide input clock by 2
    MXC_TMR_PRES_4 = MXC_S_TMR_CTRL_CLKDIV_DIV4, ///< Divide input clock by 4
    MXC_TMR_PRES_8 = MXC_S_TMR_CTRL_CLKDIV_DIV8, ///< Divide input clock by 8
    MXC_TMR_PRES_16 = MXC_S_TMR_CTRL_CLKDIV_DIV16, ///< Divide input clock by 16
    MXC_TMR_PRES_32 = MXC_S_TMR_CTRL_CLKDIV_DIV32, ///< Divide input clock by 32
    MXC_TMR_PRES_64 = MXC_S_TMR_CTRL_CLKDIV_DIV64, ///< Divide input clock by 64
    MXC_TMR_PRES_128 = MXC_S_TMR_CTRL_CLKDIV_DIV128, ///< Divide input clock by 128
    MXC_TMR_PRES_256 = MXC_F_TMR_CTRL_CLKDIV3 | MXC_S_TMR_CTRL_CLKDIV_DIV1, ///< Divide input clock by 256
    MXC_TMR_PRES_512 = MXC_F_TMR_CTRL_CLKDIV3 | MXC_S_TMR_CTRL_CLKDIV_DIV4, ///< Divide input clock by 512
    MXC_TMR_PRES_1024 = MXC_F_TMR_CTRL_CLKDIV3 | MXC_S_TMR_CTRL_CLKDIV_DIV8, ///< Divide input clock by 1024
    MXC_TMR_PRES_2048 = MXC_F_TMR_CTRL_CLKDIV3 | MXC_S_TMR_CTRL_CLKDIV_DIV16, ///< Divide input clock by 2048
    MXC_TMR_PRES_4096 = MXC_F_TMR_CTRL_CLKDIV3 | MXC_S_TMR_CTRL_CLKDIV_DIV32 ///< Divide input clock by 4096
} mxc_tmr_pres_t;

/**
 * @brief      Timer modes
 */
typedef enum {
    MXC_TMR_MODE_ONESHOT = MXC_V_TMR_CTRL_MODE_ONESHOT, ///< Timer Mode ONESHOT
    MXC_TMR_MODE_CONTINUOUS = MXC_V_TMR_CTRL_MODE_CONTINUOUS, ///< Timer Mode CONTINUOUS
    MXC_TMR_MODE_COUNTER = MXC_V_TMR_CTRL_MODE_COUNTER, ///< Timer Mode COUNTER
    MXC_TMR_MODE_PWM = MXC_V_TMR_CTRL_MODE_PWM, ///< Timer Mode PWM
    MXC_TMR_MODE_CAPTURE = MXC_V_TMR_CTRL_MODE_CAPTURE, ///< Timer Mode CAPTURE
    MXC_TMR_MODE_COMPARE = MXC_V_TMR_CTRL_MODE_COMPARE, ///< Timer Mode COMPARE
    MXC_TMR_MODE_GATED = MXC_V_TMR_CTRL_MODE_GATED, ///< Timer Mode GATED
    MXC_TMR_MODE_CAPTURE_COMPARE = MXC_V_TMR_CTRL_MODE_CAPTURECOMPARE ///< Timer Mode CAPTURECOMPARE
} mxc_tmr_mode_t;

/**
 * @brief      Timer units of time enumeration
 */
typedef enum {
    MXC_TMR_UNIT_NANOSEC = 0, ///< Nanosecond Unit Indicator
    MXC_TMR_UNIT_MICROSEC, ///< Microsecond Unit Indicator
    MXC_TMR_UNIT_MILLISEC, ///< Millisecond Unit Indicator
    MXC_TMR_UNIT_SEC, ///< Second Unit Indicator
} mxc_tmr_unit_t;

/**
 * @brief      Timer Configuration
 */
typedef struct {
    mxc_tmr_pres_t pres; ///< Desired timer prescaler
    mxc_tmr_mode_t mode; ///< Desired timer mode
    uint32_t cmp_cnt; ///< Compare register value in timer ticks
    unsigned pol; ///< Polarity (0 or 1)
    mxc_gpio_cfg_t *pins; ///< Timer pins
} mxc_tmr_cfg_t;

/* **** Definitions **** */
typedef void (*mxc_tmr_complete_t)(int error);

/* **** Function Prototypes **** */

/**
 * @brief      Initialize timer module clock.
 * @param      tmr        Pointer to timer module to initialize.
 * @param      cfg        configuration object
 */
void MXC_TMR_Init(mxc_tmr_regs_t *tmr, mxc_tmr_cfg_t *cfg);

/**
 * @brief      Shutdown timer module clock.
 * @param      tmr  Pointer to timer module to initialize.
 */
void MXC_TMR_Shutdown(mxc_tmr_regs_t *tmr);

/**
 * @brief      Start the timer counting.
 * @param      tmr  Pointer to timer module to initialize.
 */
void MXC_TMR_Start(mxc_tmr_regs_t *tmr);

/**
 * @brief      Stop the timer.
 * @param      tmr  Pointer to timer module to initialize.
 */
void MXC_TMR_Stop(mxc_tmr_regs_t *tmr);

/**
 * @brief      Set the value of the first transition in PWM mode
 * @param      tmr     Pointer to timer module to initialize.
 * @param      pwm     New pwm count.
 * @note       Will block until safe to change the period count.
 * @return     E_BAD_PARAM if pwm > cnt.
 */
int MXC_TMR_SetPWM(mxc_tmr_regs_t *tmr, uint32_t pwm);

/**
 * @brief      Get the timer compare count.
 * @param      tmr     Pointer to timer module to initialize.
 * @return     Returns the current compare count.
 */
uint32_t MXC_TMR_GetCompare(mxc_tmr_regs_t *tmr);

/**
 * @brief      Get the timer capture count.
 * @param      tmr     Pointer to timer module to initialize.
 * @return     Returns the most recent capture count.
 */
uint32_t MXC_TMR_GetCapture(mxc_tmr_regs_t *tmr);

/**
 * @brief      Get the timer count.
 * @param      tmr     Pointer to timer module to initialize.
 * @return     Returns the current count.
 */
uint32_t MXC_TMR_GetCount(mxc_tmr_regs_t *tmr);

/**
 * @brief      Clear the timer interrupt.
 * @param      tmr     Pointer to timer module to initialize.
 */
void MXC_TMR_ClearFlags(mxc_tmr_regs_t *tmr);

/**
 * @brief      Get the timer interrupt status.
 * @param      tmr     Pointer to timer module to initialize.
 * @return     Returns the interrupt status. 1 if interrupt has occured.
 */
uint32_t MXC_TMR_GetFlags(mxc_tmr_regs_t *tmr);

/**
 * @brief      enable interupt
 *
 * @param      tmr   The timer
 */
void MXC_TMR_EnableInt(mxc_tmr_regs_t *tmr);

/**
 * @brief      disable interupt
 *
 * @param      tmr   The timer
 */
void MXC_TMR_DisableInt(mxc_tmr_regs_t *tmr);

/**
 * @brief      Set the timer compare count.
 * @param      tmr     Pointer to timer module to initialize.
 * @param      cmp_cnt New compare count.
 * @note       In PWM Mode use this to set the value of the second transition.
 */
void MXC_TMR_SetCompare(mxc_tmr_regs_t *tmr, uint32_t cmp_cnt);

/**
 * @brief      Set the timer count.
 * @param      tmr     Pointer to timer module to initialize.
 * @param      cnt     New count.
 */
void MXC_TMR_SetCount(mxc_tmr_regs_t *tmr, uint32_t cnt);

/**
 * @brief      Dealay for a set periord of time measured in microseconds
 *
 * @param      tmr   The timer
 * @param[in]  us    microseconds to delay for
 */
void MXC_TMR_Delay(mxc_tmr_regs_t *tmr, uint32_t us);

/**
 * @brief      Start a timer that will time out after a certain number of microseconds
 *
 * @param      tmr   The timer
 * @param[in]  us    microseconds to time out after
 */
void MXC_TMR_TO_Start(mxc_tmr_regs_t *tmr, uint32_t us);

/**
 * @brief      Check on time out timer
 *
 * @param      tmr   The timer
 *
 * @return     Returns E_TIMEOUT if timer timed out or E_NO_ERROR if it has not timed out
 */
int MXC_TMR_TO_Check(mxc_tmr_regs_t *tmr);

/**
 * @brief      Stop the Timeout timer
 *
 * @param      tmr   The timer
 */
void MXC_TMR_TO_Stop(mxc_tmr_regs_t *tmr);

/**
 * @brief      Clear timeout timer back to zero
 *
 * @param      tmr   The timer
 */
void MXC_TMR_TO_Clear(mxc_tmr_regs_t *tmr);

/**
 * @brief      Get elapsed time of timeout timer
 *
 * @param      tmr   The timer
 *
 * @return     Time that has elapsed in timeout timer
 */
unsigned int MXC_TMR_TO_Elapsed(mxc_tmr_regs_t *tmr);

/**
 * @brief      Amount of time remaining until timeour
 *
 * @param      tmr   The timer
 *
 * @return     Time that is left until timeout
 */
unsigned int MXC_TMR_TO_Remaining(mxc_tmr_regs_t *tmr);

/**
 * @brief      Start stopwatch
 *
 * @param      tmr      The timer
 */
void MXC_TMR_SW_Start(mxc_tmr_regs_t *tmr);

/**
 * @brief      Stopwatch stop
 *
 * @param      tmr   The timer
 *
 * @return     the time when the stopwatch is stopped.
 */
unsigned int MXC_TMR_SW_Stop(mxc_tmr_regs_t *tmr);

/**
 * @brief      Get time from timer
 *
 * @param      tmr    The timer
 * @param[in]  ticks  The ticks
 * @param      time   The time
 * @param      units  The units
 *
 * @return     E_NO_ERROR or error check mxc_errors.
 */
int MXC_TMR_GetTime(mxc_tmr_regs_t *tmr, uint32_t ticks, uint32_t *time, mxc_tmr_unit_t *units);

/**@} end of group tmr */

#ifdef __cplusplus
}
#endif

#endif // LIBRARIES_PERIPHDRIVERS_INCLUDE_MAX32570_TMR_H_
