/**
 * @file    mxc_sys.h
 * @brief   System level header file.
 */

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

#ifndef LIBRARIES_PERIPHDRIVERS_INCLUDE_MAX32672_MXC_SYS_H_
#define LIBRARIES_PERIPHDRIVERS_INCLUDE_MAX32672_MXC_SYS_H_

#include "mxc_device.h"
#include "gcr_regs.h"
#include "mcr_regs.h"
#include "trimsir_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mxc_sys System Configuration (MXC_SYS)
 * @ingroup syscfg
 * @details API for system configuration including clock source selection and entering critical sections of code.
 * @{
 */

/** @brief System reset0 and reset1 enumeration. Used in MXC_SYS_PeriphReset0 function */
typedef enum {
    MXC_SYS_RESET0_DMA = MXC_F_GCR_RST0_DMA_POS, /**< Reset DMA */
    MXC_SYS_RESET0_WDT0 = MXC_F_GCR_RST0_WDT0_POS, /**< Reset WDT */
    MXC_SYS_RESET0_GPIO0 = MXC_F_GCR_RST0_GPIO0_POS, /**< Reset GPIO0 */
    MXC_SYS_RESET0_GPIO1 = MXC_F_GCR_RST0_GPIO1_POS, /**< Reset GPIO1 */
    MXC_SYS_RESET0_TMR0 = MXC_F_GCR_RST0_TMR0_POS, /**< Reset TIMER0 */
    MXC_SYS_RESET0_TMR1 = MXC_F_GCR_RST0_TMR1_POS, /**< Reset TIMER1 */
    MXC_SYS_RESET0_TMR2 = MXC_F_GCR_RST0_TMR2_POS, /**< Reset TIMER2 */
    MXC_SYS_RESET0_TMR3 = MXC_F_GCR_RST0_TMR3_POS, /**< Reset TIMER3 */
    MXC_SYS_RESET0_UART0 = MXC_F_GCR_RST0_UART0_POS, /**< Reset UART0 */
    MXC_SYS_RESET0_UART1 = MXC_F_GCR_RST0_UART1_POS, /**< Reset UART1 */
    MXC_SYS_RESET0_SPI0 = MXC_F_GCR_RST0_SPI0_POS, /**< Reset SPI0 */
    MXC_SYS_RESET0_SPI1 = MXC_F_GCR_RST0_SPI1_POS, /**< Reset SPI1 */
    MXC_SYS_RESET0_SPI2 = MXC_F_GCR_RST0_SPI2_POS, /**< Reset SPI2 */
    MXC_SYS_RESET0_I2C0 = MXC_F_GCR_RST0_I2C0_POS, /**< Reset I2C0 */
    MXC_SYS_RESET0_RTC = MXC_F_MCR_RST_RTC_POS, /**< Reset RTC */
    MXC_SYS_RESET0_CTB = MXC_F_GCR_RST0_CTB_POS, /**< Reset CTB */
    MXC_SYS_RESET0_TRNG = MXC_F_GCR_RST0_TRNG_POS, /**< Reset TRNG */
    MXC_SYS_RESET0_ADC = MXC_F_GCR_RST0_ADC_POS, /**< Reset ADC */
    MXC_SYS_RESET0_UART2 = MXC_F_GCR_RST0_UART2_POS, /**< Reset UART2 */
    MXC_SYS_RESET0_SRST = MXC_F_GCR_RST0_SOFT_POS, /**< Soft reset */
    MXC_SYS_RESET0_PRST = MXC_F_GCR_RST0_PERIPH_POS, /**< Peripheral reset */
    MXC_SYS_RESET0_SYS = MXC_F_GCR_RST0_SYS_POS, /**< System reset */
    /* RESET1 Below this line we add 32 to separate RESET0 and RESET1 */
    MXC_SYS_RESET1_I2C1 = (MXC_F_GCR_RST1_I2C1_POS + 32), /**< Reset I2C1 */
    MXC_SYS_RESET1_WDT1 = (MXC_F_GCR_RST1_WDT1_POS + 32), /**< Reset WDT1 */
    MXC_SYS_RESET1_AES = (MXC_F_GCR_RST1_AES_POS + 32), /**< Reset AES */
    MXC_SYS_RESET1_I2C2 = (MXC_F_GCR_RST1_I2C2_POS + 32), /**< Reset I2C2*/
    MXC_SYS_RESET1_I2S = (MXC_F_GCR_RST1_I2S_POS + 32), /**< Reset I2S*/
    MXC_SYS_RESET1_QDEC = (MXC_F_GCR_RST1_QDEC_POS + 32), /**< Reset QDEC*/
    /* LPGCR RESET Below this line we add 64 to separate LPGCR and GCR */
    MXC_SYS_RESET_TMR4 = (MXC_F_MCR_RST_LPTMR0_POS + 64), /**< Reset TMR4 */
    MXC_SYS_RESET_TMR5 = (MXC_F_MCR_RST_LPTMR1_POS + 64), /**< Reset TMR5 */
    MXC_SYS_RESET_UART3 = (MXC_F_MCR_RST_LPUART0_POS + 64), /**< Reset UART3 */
} mxc_sys_reset_t;

/** @brief System clock disable enumeration. Used in MXC_SYS_ClockDisable and MXC_SYS_ClockEnable functions */
typedef enum {
    MXC_SYS_PERIPH_CLOCK_GPIO0 =
        MXC_F_GCR_PCLKDIS0_GPIO0_POS, /**< Disable MXC_F_GCR_PCLKDIS0_GPIO0 clock */
    MXC_SYS_PERIPH_CLOCK_GPIO1 =
        MXC_F_GCR_PCLKDIS0_GPIO1_POS, /**< Disable MXC_F_GCR_PCLKDIS0_GPIO1 clock */
    MXC_SYS_PERIPH_CLOCK_DMA =
        MXC_F_GCR_PCLKDIS0_DMA_POS, /**< Disable MXC_F_GCR_PCLKDIS0_DMA clock */
    MXC_SYS_PERIPH_CLOCK_SPI0 =
        MXC_F_GCR_PCLKDIS0_SPI0_POS, /**< Disable MXC_F_GCR_PCLKDIS0_SPI0 clock */
    MXC_SYS_PERIPH_CLOCK_SPI1 =
        MXC_F_GCR_PCLKDIS0_SPI1_POS, /**< Disable MXC_F_GCR_PCLKDIS0_SPI1 clock */
    MXC_SYS_PERIPH_CLOCK_SPI2 =
        MXC_F_GCR_PCLKDIS0_SPI2_POS, /**< Disable MXC_F_GCR_PCLKDIS0_SPI2 clock */
    MXC_SYS_PERIPH_CLOCK_UART0 =
        MXC_F_GCR_PCLKDIS0_UART0_POS, /**< Disable MXC_F_GCR_PCLKDIS0_UART0 clock */
    MXC_SYS_PERIPH_CLOCK_UART1 =
        MXC_F_GCR_PCLKDIS0_UART1_POS, /**< Disable MXC_F_GCR_PCLKDIS0_UART1 clock */
    MXC_SYS_PERIPH_CLOCK_I2C0 =
        MXC_F_GCR_PCLKDIS0_I2C0_POS, /**< Disable MXC_F_GCR_PCLKDIS0_I2C0 clock */
    MXC_SYS_PERIPH_CLOCK_TMR0 =
        MXC_F_GCR_PCLKDIS0_TMR0_POS, /**< Disable MXC_F_GCR_PCLKDIS0_TMR0 clock */
    MXC_SYS_PERIPH_CLOCK_TMR1 =
        MXC_F_GCR_PCLKDIS0_TMR1_POS, /**< Disable MXC_F_GCR_PCLKDIS0_TMR1 clock */
    MXC_SYS_PERIPH_CLOCK_TMR2 =
        MXC_F_GCR_PCLKDIS0_TMR2_POS, /**< Disable MXC_F_GCR_PCLKDIS0_TMR2 clock */
    MXC_SYS_PERIPH_CLOCK_TMR3 =
        MXC_F_GCR_PCLKDIS0_TMR3_POS, /**< Disable MXC_F_GCR_PCLKDIS0_TMR3 clock */
    MXC_SYS_PERIPH_CLOCK_ADC =
        MXC_F_GCR_PCLKDIS0_ADC_POS, /**< Disable MXC_F_GCR_PCLKDIS0_ADC clock */
    MXC_SYS_PERIPH_CLOCK_I2C1 =
        MXC_F_GCR_PCLKDIS0_I2C1_POS, /**< Disable MXC_F_GCR_PCLKDIS0_I2C1 clock */
    MXC_SYS_PERIPH_CLOCK_CTB =
        MXC_F_GCR_PCLKDIS0_CTB_POS, /**< Disable MXC_F_GCR_PCLKDIS0_CTB clock */
    /* PCLKDIS1 Below this line we add 32 to separate PCLKDIS0 and PCLKDIS1 */
    MXC_SYS_PERIPH_CLOCK_UART2 =
        (MXC_F_GCR_PCLKDIS1_UART2_POS + 32), /**< Disable MXC_F_GCR_PCLKDIS1_UART2 clock */
    MXC_SYS_PERIPH_CLOCK_TRNG =
        (MXC_F_GCR_PCLKDIS1_TRNG_POS + 32), /**< Disable MXC_F_GCR_PCLKDIS1_TRNG clock */
    MXC_SYS_PERIPH_CLOCK_WDT0 =
        (MXC_F_GCR_PCLKDIS1_WDT0_POS + 32), /**< Disable MXC_F_GCR_PCLKDIS1_WDT0 clock */
    MXC_SYS_PERIPH_CLOCK_WDT1 =
        (MXC_F_GCR_PCLKDIS1_WDT1_POS + 32), /**< Disable MXC_F_GCR_PCLKDIS1_WDT1 clock */
    MXC_SYS_PERIPH_CLOCK_ICACHE =
        (MXC_F_GCR_PCLKDIS1_ICC0_POS + 32), /**< Disable MXC_F_GCR_PCLKDIS1_ICACHE clock */
    MXC_SYS_PERIPH_CLOCK_AES =
        (MXC_F_GCR_PCLKDIS1_AES_POS + 32), /**< Disable MXC_F_GCR_PCLKDIS1_AES clock */
    MXC_SYS_PERIPH_CLOCK_I2C2 =
        (MXC_F_GCR_PCLKDIS1_I2C2_POS + 32), /**< Disable MXC_F_GCR_PCLKDIS1_I2C2 clock */
    MXC_SYS_PERIPH_CLOCK_I2S =
        (MXC_F_GCR_PCLKDIS1_I2S_POS + 32), /**< Disable MXC_F_GCR_PCLKDIS1_I2S clock */
    MXC_SYS_PERIPH_CLOCK_QDEC =
        (MXC_F_GCR_PCLKDIS1_QDEC_POS + 32), /**< Disable MXC_F_GCR_PCLKDIS1_QDEC clock */
    /* LPGCR PCLKDIS Below this line we add 64 to seperate GCR and LPGCR registers */
    MXC_SYS_PERIPH_CLOCK_TMR4 =
        (MXC_F_MCR_PCLKDIS_LPTMR0_POS + 64), /**< Disable MXC_F_LPGCR_PCLKDIS_TMR4 clock */
    MXC_SYS_PERIPH_CLOCK_TMR5 =
        (MXC_F_MCR_PCLKDIS_LPTMR1_POS + 64), /**< Disable MXC_F_LPGCR_PCLKDIS_TMR5 clock */
    MXC_SYS_PERIPH_CLOCK_UART3 =
        (MXC_F_MCR_PCLKDIS_LPUART0_POS + 64), /**< Disable MXC_F_LPGCR_PCLKDIS_UART3 clock */
} mxc_sys_periph_clock_t;

/** @brief Enumeration to select System Clock source */
typedef enum {
    MXC_SYS_CLOCK_IPO =
        MXC_V_GCR_CLKCTRL_SYSCLK_SEL_IPO, /**< Select the Internal Primary Oscillator (IPO) */
    MXC_SYS_CLOCK_IBRO =
        MXC_V_GCR_CLKCTRL_SYSCLK_SEL_IBRO, /**< Select the Internal Baud Rate Oscillator (IBRO) */
    MXC_SYS_CLOCK_ERFO =
        MXC_V_GCR_CLKCTRL_SYSCLK_SEL_ERFO, /**< Select the External RF Crystal Oscillator */
    MXC_SYS_CLOCK_INRO =
        MXC_V_GCR_CLKCTRL_SYSCLK_SEL_INRO, /**< Select the Internal Nanoring Oscillator (INRO) */
    MXC_SYS_CLOCK_ERTCO =
        MXC_V_GCR_CLKCTRL_SYSCLK_SEL_ERTCO, /**< Select the External RTC Crystal Oscillator */
    MXC_SYS_CLOCK_EXTCLK =
        MXC_V_GCR_CLKCTRL_SYSCLK_SEL_EXTCLK /**< Use the external system clock input */
} mxc_sys_system_clock_t;

/** @brief Enumeration to enable/disable ECCs on various memory banks */
typedef enum {
    MXC_SYS_ECCEN_RAM01 = MXC_F_TRIMSIR_BB_SIR2_RAM0_1ECCEN, /**< Select ECC for RAM0/1 */
    MXC_SYS_ECCEN_RAM2 = MXC_F_TRIMSIR_BB_SIR2_RAM2ECCEN, /**< Select ECC for RAM2 */
    MXC_SYS_ECCEN_RAM3 = MXC_F_TRIMSIR_BB_SIR2_RAM3ECCEN, /**< Select ECC for RAM3 */
    MXC_SYS_ECCEN_ICC0 = MXC_F_TRIMSIR_BB_SIR2_ICC0ECCEN, /**< Select ECC for ICC0 */
    MXC_SYS_ECCEN_FLASH0 = MXC_F_TRIMSIR_BB_SIR2_FL0ECCEN, /**< Select ECC for Flash 0 */
    MXC_SYS_ECCEN_FLASH1 = MXC_F_TRIMSIR_BB_SIR2_FL1ECCEN, /**< Select ECC for Flash 1 */
} mxc_sys_eccen_t;

#define MXC_SYS_USN_CHECKSUM_LEN 16 // Length of the USN + padding for checksum compute
#define MXC_SYS_USN_CSUM_FIELD_LEN 2 // Size of the checksum field in the USN
#define MXC_SYS_USN_LEN 13 // Size of the USN including the checksum

/***** Function Prototypes *****/

typedef struct {
    int ie_status;
    int in_critical;
} mxc_crit_state_t;

static mxc_crit_state_t _state = { .ie_status = (int)0xFFFFFFFF, .in_critical = 0 };

static inline void _mxc_crit_get_state()
{
#ifndef __riscv
    /*
        On ARM M the 0th bit of the Priority Mask register indicates
        whether interrupts are enabled or not.

        0 = enabled
        1 = disabled
    */
    uint32_t primask = __get_PRIMASK();
    _state.ie_status = (primask == 0);
#else
    /*
        On RISC-V bit position 3 (Machine Interrupt Enable) of the
        mstatus register indicates whether interrupts are enabled.

        0 = disabled
        1 = enabled
    */
    uint32_t mstatus = get_mstatus();
    _state.ie_status = ((mstatus & (1 << 3)) != 0);
#endif
}

/**
 * @brief Enter a critical section of code that cannot be interrupted.  Call @ref MXC_SYS_Crit_Exit to exit the critical section.
 * @details Ex:
 * @code
 * MXC_SYS_Crit_Enter();
 * printf("Hello critical section!\n");
 * MXC_SYS_Crit_Exit();
 * @endcode
 * The @ref MXC_CRITICAL macro is also provided as a convencience macro for wrapping a code section in this way.
 * @returns None
 */
static inline void MXC_SYS_Crit_Enter(void)
{
    _mxc_crit_get_state();
    if (_state.ie_status)
        __disable_irq();
    _state.in_critical = 1;
}

/**
 * @brief Exit a critical section of code from @ref MXC_SYS_Crit_Enter
 * @returns None
 */
static inline void MXC_SYS_Crit_Exit(void)
{
    if (_state.ie_status) {
        __enable_irq();
    }
    _state.in_critical = 0;
    _mxc_crit_get_state();
    /*
        ^ Reset the state again to prevent edge case
        where interrupts get disabled, then Crit_Exit() gets
        called, which would inadvertently re-enable interrupts
        from old state.
    */
}

/**
 * @brief Polls whether code is currently executing from a critical section.
 * @returns 1 if code is currently in a critical section (interrupts are disabled).
 *          0 if code is not in a critical section.
 */
static inline int MXC_SYS_In_Crit_Section(void)
{
    return _state.in_critical;
}

// clang-format off
/**
 * @brief Macro for wrapping a section of code to make it critical (interrupts disabled).  Note: this macro
 * does not support nesting.
 * @details
 * Ex:
 * \code
 * MXC_CRITICAL(
 *      printf("Hello critical section!\n");
 * )
 * \endcode
 * This macro places a call to @ref MXC_SYS_Crit_Enter before the code, and a call to @ref MXC_SYS_Crit_Exit after.
 * @param code The code section to wrap.
 */
#define MXC_CRITICAL(code) {\
    MXC_SYS_Crit_Enter();\
    code;\
    MXC_SYS_Crit_Exit();\
}
// clang-format on

/**
 * @brief Reads the device USN and verifies the checksum.
 * @param usn       Pointer to store the USN. Array must be at least MXC_SYS_USN_LEN bytes long.
 * @param checksum  Optional pointer to store the AES checksum. If not NULL, checksum is verified with AES engine.
 * @returns         E_NO_ERROR if everything is successful.
 */
int MXC_SYS_GetUSN(uint8_t *usn, uint8_t *checksum);

/**
 * @brief Gets design revision of the chip.
 * 
 * @return Design revision.
 */
int MXC_SYS_GetRevision(void);

/**
 * @brief Determines if the selected peripheral clock is enabled.
 * @param clock   Enumeration for desired clock.
 * @returns       0 is the clock is disabled, non 0 if the clock is enabled.
 */
int MXC_SYS_IsClockEnabled(mxc_sys_periph_clock_t clock);

/**
 * @brief Disables the selected peripheral clock.
 * @param clock   Enumeration for desired clock.
 */
void MXC_SYS_ClockDisable(mxc_sys_periph_clock_t clock);

/**
 * @brief Enables the selected peripheral clock.
 * @param clock   Enumeration for desired clock.
 */
void MXC_SYS_ClockEnable(mxc_sys_periph_clock_t clock);

/**
 * @brief Enables the 32kHz oscillator
 * @param mxc_sys_cfg   Not used, may be NULL.
 */
void MXC_SYS_RTCClockEnable(void);

/**
 * @brief Disables the 32kHz oscillator
 * @returns         E_NO_ERROR if everything is successful
 */
int MXC_SYS_RTCClockDisable();

/**
 * @brief Enable System Clock Source without switching to it
 * @param      clock The clock to enable
 * @return     E_NO_ERROR if everything is successful
 */
int MXC_SYS_ClockSourceEnable(mxc_sys_system_clock_t clock);

/**
 * @brief Disable System Clock Source
 * @param      clock The clock to disable
 * @return     E_NO_ERROR if everything is successful
 */
int MXC_SYS_ClockSourceDisable(mxc_sys_system_clock_t clock);

/**
 * @brief Select the system clock.
 * @param clock     Enumeration for desired clock.  Note:  If using the external clock input be sure to define EXTCLK_FREQ correctly.
 *                  The default EXTCLK_FREQ value is defined in the system_max32672.h file and can be overridden at compile time.
 * @returns         E_NO_ERROR if everything is successful.
 */
int MXC_SYS_Clock_Select(mxc_sys_system_clock_t clock);

/**
 * @brief Wait for a clock to enable with timeout
 * @param      ready The clock to wait for
 * @return     E_NO_ERROR if ready, E_TIME_OUT if timeout
 */
int MXC_SYS_Clock_Timeout(uint32_t ready);

/**
 * @brief Reset the peripherals and/or CPU in the rstr0 or rstr1 register.
 * @param           Enumeration for what to reset. Can reset multiple items at once.
 */
void MXC_SYS_Reset_Periph(mxc_sys_reset_t reset);

/**
 * @brief   Enable ECCs. Select which ECCs to enable by masking together the
 *          appropriate mxc_sys_eccen_t options.
 * 
 * @param ecc_mask   Mask of mxc_sys_eccen_t to select which ECCs to enable
 */
void MXC_SYS_ECC_Enable(uint32_t ecc_mask);

/**
 * @brief   Disable ECCs. Select which ECCs to disable by masking together the
 *          appropriate mxc_sys_eccen_t options.
 * 
 * @param ecc_mask   Mask of mxc_sys_eccen_t to select which ECCs to disable
 */
void MXC_SYS_ECC_Disable(uint32_t ecc_mask);

/**
 * @brief   Checks whether the selected ECC instance is enabled.
 * 
 * @param ecc   Selects which ECC to check the enabled status of
 * 
 * @return  0 - ECC not enabled, 1 - ECC enabled, or an error code if an invalid
 *          parameter was passed to function.
 */
int MXC_SYS_ECC_GetEnabled(mxc_sys_eccen_t ecc);

/**
 * @brief Enable ECC interrupt sources.
 * 
 * @param flags  Mask of flags to enable in the ECC interrupt enable register.
 */
void MXC_SYS_ECC_EnableInt(unsigned int flags);

/**
 * @brief Disable ECC interrupt sources.
 * 
 * @param flags  Mask of flags to disable in the ECC interrupt enable register.
 */
void MXC_SYS_ECC_DisableInt(unsigned int flags);

/**
 * @brief Get the value of the interrupt flags in the ECC interrupt register.
 * 
 * @param err_flags  Pointer to variable to store the value of ECC interrupt flag register.
 * @param ced_flags  Pointer to variable to store the value of correctable error flag register.
 */
void MXC_SYS_ECC_GetFlags(unsigned int *err_flags, unsigned int *ced_flags);

/**
 * @brief Clears flags in the ECC interrupt register
 *
 * @param err_flags  Mask of flags to clear in the ECC interrupt flag register.
 * @param ced_flags  Mask of flags to clear in correctable error flag register
 */
void MXC_SYS_ECC_ClearFlags(unsigned int err_flags, unsigned int ced_flags);

/**
 * @brief  Get the memory address of the most recent error detected by ECC.
 * 
 * @returns The address of the the last detected ECC error.
 */
int MXC_SYS_ECC_GetErrorAddress(void);

#ifdef __cplusplus
}
#endif

#endif // LIBRARIES_PERIPHDRIVERS_INCLUDE_MAX32672_MXC_SYS_H_
