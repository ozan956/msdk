/**
 * @file    gpio_regs.h
 * @brief   Registers, Bit Masks and Bit Positions for the GPIO Peripheral Module.
 * @note    This file is @generated.
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

#ifndef LIBRARIES_CMSIS_DEVICE_MAXIM_MAX32572_INCLUDE_GPIO_REGS_H_
#define LIBRARIES_CMSIS_DEVICE_MAXIM_MAX32572_INCLUDE_GPIO_REGS_H_

/* **** Includes **** */
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__ICCARM__)
  #pragma system_include
#endif

#if defined (__CC_ARM)
  #pragma anon_unions
#endif
/// @cond
/*
    If types are not defined elsewhere (CMSIS) define them here
*/
#ifndef __IO
#define __IO volatile
#endif
#ifndef __I
#define __I  volatile const
#endif
#ifndef __O
#define __O  volatile
#endif
#ifndef __R
#define __R  volatile const
#endif
/// @endcond

/* **** Definitions **** */

/**
 * @ingroup     gpio
 * @defgroup    gpio_registers GPIO_Registers
 * @brief       Registers, Bit Masks and Bit Positions for the GPIO Peripheral Module.
 * @details     Individual I/O for each GPIO
 */

/**
 * @ingroup gpio_registers
 * Structure type to access the GPIO Registers.
 */
typedef struct {
    __IO uint32_t en0;                  /**< <tt>\b 0x00:</tt> GPIO EN0 Register */
    __IO uint32_t en0_set;              /**< <tt>\b 0x04:</tt> GPIO EN0_SET Register */
    __IO uint32_t en0_clr;              /**< <tt>\b 0x08:</tt> GPIO EN0_CLR Register */
    __IO uint32_t outen;                /**< <tt>\b 0x0C:</tt> GPIO OUTEN Register */
    __IO uint32_t outen_set;            /**< <tt>\b 0x10:</tt> GPIO OUTEN_SET Register */
    __IO uint32_t outen_clr;            /**< <tt>\b 0x14:</tt> GPIO OUTEN_CLR Register */
    __IO uint32_t out;                  /**< <tt>\b 0x18:</tt> GPIO OUT Register */
    __O  uint32_t out_set;              /**< <tt>\b 0x1C:</tt> GPIO OUT_SET Register */
    __O  uint32_t out_clr;              /**< <tt>\b 0x20:</tt> GPIO OUT_CLR Register */
    __I  uint32_t in;                   /**< <tt>\b 0x24:</tt> GPIO IN Register */
    __IO uint32_t intmode;              /**< <tt>\b 0x28:</tt> GPIO INTMODE Register */
    __IO uint32_t intpol;               /**< <tt>\b 0x2C:</tt> GPIO INTPOL Register */
    __IO uint32_t inen;                 /**< <tt>\b 0x30:</tt> GPIO INEN Register */
    __IO uint32_t inten;                /**< <tt>\b 0x34:</tt> GPIO INTEN Register */
    __IO uint32_t inten_set;            /**< <tt>\b 0x38:</tt> GPIO INTEN_SET Register */
    __IO uint32_t inten_clr;            /**< <tt>\b 0x3C:</tt> GPIO INTEN_CLR Register */
    __I  uint32_t intfl;                /**< <tt>\b 0x40:</tt> GPIO INTFL Register */
    __R  uint32_t rsv_0x44;
    __IO uint32_t intfl_clr;            /**< <tt>\b 0x48:</tt> GPIO INTFL_CLR Register */
    __IO uint32_t wken;                 /**< <tt>\b 0x4C:</tt> GPIO WKEN Register */
    __IO uint32_t wken_set;             /**< <tt>\b 0x50:</tt> GPIO WKEN_SET Register */
    __IO uint32_t wken_clr;             /**< <tt>\b 0x54:</tt> GPIO WKEN_CLR Register */
    __R  uint32_t rsv_0x58;
    __IO uint32_t dualedge;             /**< <tt>\b 0x5C:</tt> GPIO DUALEDGE Register */
    __IO uint32_t padctrl0;             /**< <tt>\b 0x60:</tt> GPIO PADCTRL0 Register */
    __IO uint32_t padctrl1;             /**< <tt>\b 0x64:</tt> GPIO PADCTRL1 Register */
    __IO uint32_t en1;                  /**< <tt>\b 0x68:</tt> GPIO EN1 Register */
    __IO uint32_t en1_set;              /**< <tt>\b 0x6C:</tt> GPIO EN1_SET Register */
    __IO uint32_t en1_clr;              /**< <tt>\b 0x70:</tt> GPIO EN1_CLR Register */
    __IO uint32_t en2;                  /**< <tt>\b 0x74:</tt> GPIO EN2 Register */
    __IO uint32_t en2_set;              /**< <tt>\b 0x78:</tt> GPIO EN2_SET Register */
    __IO uint32_t en2_clr;              /**< <tt>\b 0x7C:</tt> GPIO EN2_CLR Register */
    __R  uint32_t rsv_0x80_0xa7[10];
    __IO uint32_t hysen;                /**< <tt>\b 0xA8:</tt> GPIO HYSEN Register */
    __IO uint32_t srsel;                /**< <tt>\b 0xAC:</tt> GPIO SRSEL Register */
    __IO uint32_t ds0;                  /**< <tt>\b 0xB0:</tt> GPIO DS0 Register */
    __IO uint32_t ds1;                  /**< <tt>\b 0xB4:</tt> GPIO DS1 Register */
    __IO uint32_t pssel;                /**< <tt>\b 0xB8:</tt> GPIO PSSEL Register */
    __R  uint32_t rsv_0xbc;
    __IO uint32_t vssel;                /**< <tt>\b 0xC0:</tt> GPIO VSSEL Register */
} mxc_gpio_regs_t;

/* Register offsets for module GPIO */
/**
 * @ingroup    gpio_registers
 * @defgroup   GPIO_Register_Offsets Register Offsets
 * @brief      GPIO Peripheral Register Offsets from the GPIO Base Peripheral Address.
 * @{
 */
#define MXC_R_GPIO_EN0                     ((uint32_t)0x00000000UL) /**< Offset from GPIO Base Address: <tt> 0x0000</tt> */
#define MXC_R_GPIO_EN0_SET                 ((uint32_t)0x00000004UL) /**< Offset from GPIO Base Address: <tt> 0x0004</tt> */
#define MXC_R_GPIO_EN0_CLR                 ((uint32_t)0x00000008UL) /**< Offset from GPIO Base Address: <tt> 0x0008</tt> */
#define MXC_R_GPIO_OUTEN                   ((uint32_t)0x0000000CUL) /**< Offset from GPIO Base Address: <tt> 0x000C</tt> */
#define MXC_R_GPIO_OUTEN_SET               ((uint32_t)0x00000010UL) /**< Offset from GPIO Base Address: <tt> 0x0010</tt> */
#define MXC_R_GPIO_OUTEN_CLR               ((uint32_t)0x00000014UL) /**< Offset from GPIO Base Address: <tt> 0x0014</tt> */
#define MXC_R_GPIO_OUT                     ((uint32_t)0x00000018UL) /**< Offset from GPIO Base Address: <tt> 0x0018</tt> */
#define MXC_R_GPIO_OUT_SET                 ((uint32_t)0x0000001CUL) /**< Offset from GPIO Base Address: <tt> 0x001C</tt> */
#define MXC_R_GPIO_OUT_CLR                 ((uint32_t)0x00000020UL) /**< Offset from GPIO Base Address: <tt> 0x0020</tt> */
#define MXC_R_GPIO_IN                      ((uint32_t)0x00000024UL) /**< Offset from GPIO Base Address: <tt> 0x0024</tt> */
#define MXC_R_GPIO_INTMODE                 ((uint32_t)0x00000028UL) /**< Offset from GPIO Base Address: <tt> 0x0028</tt> */
#define MXC_R_GPIO_INTPOL                  ((uint32_t)0x0000002CUL) /**< Offset from GPIO Base Address: <tt> 0x002C</tt> */
#define MXC_R_GPIO_INEN                    ((uint32_t)0x00000030UL) /**< Offset from GPIO Base Address: <tt> 0x0030</tt> */
#define MXC_R_GPIO_INTEN                   ((uint32_t)0x00000034UL) /**< Offset from GPIO Base Address: <tt> 0x0034</tt> */
#define MXC_R_GPIO_INTEN_SET               ((uint32_t)0x00000038UL) /**< Offset from GPIO Base Address: <tt> 0x0038</tt> */
#define MXC_R_GPIO_INTEN_CLR               ((uint32_t)0x0000003CUL) /**< Offset from GPIO Base Address: <tt> 0x003C</tt> */
#define MXC_R_GPIO_INTFL                   ((uint32_t)0x00000040UL) /**< Offset from GPIO Base Address: <tt> 0x0040</tt> */
#define MXC_R_GPIO_INTFL_CLR               ((uint32_t)0x00000048UL) /**< Offset from GPIO Base Address: <tt> 0x0048</tt> */
#define MXC_R_GPIO_WKEN                    ((uint32_t)0x0000004CUL) /**< Offset from GPIO Base Address: <tt> 0x004C</tt> */
#define MXC_R_GPIO_WKEN_SET                ((uint32_t)0x00000050UL) /**< Offset from GPIO Base Address: <tt> 0x0050</tt> */
#define MXC_R_GPIO_WKEN_CLR                ((uint32_t)0x00000054UL) /**< Offset from GPIO Base Address: <tt> 0x0054</tt> */
#define MXC_R_GPIO_DUALEDGE                ((uint32_t)0x0000005CUL) /**< Offset from GPIO Base Address: <tt> 0x005C</tt> */
#define MXC_R_GPIO_PADCTRL0                ((uint32_t)0x00000060UL) /**< Offset from GPIO Base Address: <tt> 0x0060</tt> */
#define MXC_R_GPIO_PADCTRL1                ((uint32_t)0x00000064UL) /**< Offset from GPIO Base Address: <tt> 0x0064</tt> */
#define MXC_R_GPIO_EN1                     ((uint32_t)0x00000068UL) /**< Offset from GPIO Base Address: <tt> 0x0068</tt> */
#define MXC_R_GPIO_EN1_SET                 ((uint32_t)0x0000006CUL) /**< Offset from GPIO Base Address: <tt> 0x006C</tt> */
#define MXC_R_GPIO_EN1_CLR                 ((uint32_t)0x00000070UL) /**< Offset from GPIO Base Address: <tt> 0x0070</tt> */
#define MXC_R_GPIO_EN2                     ((uint32_t)0x00000074UL) /**< Offset from GPIO Base Address: <tt> 0x0074</tt> */
#define MXC_R_GPIO_EN2_SET                 ((uint32_t)0x00000078UL) /**< Offset from GPIO Base Address: <tt> 0x0078</tt> */
#define MXC_R_GPIO_EN2_CLR                 ((uint32_t)0x0000007CUL) /**< Offset from GPIO Base Address: <tt> 0x007C</tt> */
#define MXC_R_GPIO_HYSEN                   ((uint32_t)0x000000A8UL) /**< Offset from GPIO Base Address: <tt> 0x00A8</tt> */
#define MXC_R_GPIO_SRSEL                   ((uint32_t)0x000000ACUL) /**< Offset from GPIO Base Address: <tt> 0x00AC</tt> */
#define MXC_R_GPIO_DS0                     ((uint32_t)0x000000B0UL) /**< Offset from GPIO Base Address: <tt> 0x00B0</tt> */
#define MXC_R_GPIO_DS1                     ((uint32_t)0x000000B4UL) /**< Offset from GPIO Base Address: <tt> 0x00B4</tt> */
#define MXC_R_GPIO_PSSEL                   ((uint32_t)0x000000B8UL) /**< Offset from GPIO Base Address: <tt> 0x00B8</tt> */
#define MXC_R_GPIO_VSSEL                   ((uint32_t)0x000000C0UL) /**< Offset from GPIO Base Address: <tt> 0x00C0</tt> */
/**@} end of group gpio_registers */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_EN0 GPIO_EN0
 * @brief    GPIO Function Enable Register. Each bit controls the GPIO_EN setting for one
 *           GPIO pin on the associated port.
 * @{
 */
#define MXC_F_GPIO_EN0_ALL_POS                         0 /**< EN0_ALL Position */
#define MXC_F_GPIO_EN0_ALL                             ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_EN0_ALL_POS)) /**< EN0_ALL Mask */
#define MXC_V_GPIO_EN0_ALL_ALTERNATE                   ((uint32_t)0x0UL) /**< EN0_ALL_ALTERNATE Value */
#define MXC_S_GPIO_EN0_ALL_ALTERNATE                   (MXC_V_GPIO_EN0_ALL_ALTERNATE << MXC_F_GPIO_EN0_ALL_POS) /**< EN0_ALL_ALTERNATE Setting */
#define MXC_V_GPIO_EN0_ALL_GPIO                        ((uint32_t)0x1UL) /**< EN0_ALL_GPIO Value */
#define MXC_S_GPIO_EN0_ALL_GPIO                        (MXC_V_GPIO_EN0_ALL_GPIO << MXC_F_GPIO_EN0_ALL_POS) /**< EN0_ALL_GPIO Setting */

/**@} end of group GPIO_EN0_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_EN0_SET GPIO_EN0_SET
 * @brief    GPIO Set Function Enable Register. Writing a 1 to one or more bits in this
 *           register sets the bits in the same positions in GPIO_EN to 1, without affecting
 *           other bits in that register.
 * @{
 */
#define MXC_F_GPIO_EN0_SET_ALL_POS                     0 /**< EN0_SET_ALL Position */
#define MXC_F_GPIO_EN0_SET_ALL                         ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_EN0_SET_ALL_POS)) /**< EN0_SET_ALL Mask */

/**@} end of group GPIO_EN0_SET_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_EN0_CLR GPIO_EN0_CLR
 * @brief    GPIO Clear Function Enable Register. Writing a 1 to one or more bits in this
 *           register clears the bits in the same positions in GPIO_EN to 0, without
 *           affecting other bits in that register.
 * @{
 */
#define MXC_F_GPIO_EN0_CLR_ALL_POS                     0 /**< EN0_CLR_ALL Position */
#define MXC_F_GPIO_EN0_CLR_ALL                         ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_EN0_CLR_ALL_POS)) /**< EN0_CLR_ALL Mask */

/**@} end of group GPIO_EN0_CLR_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_OUTEN GPIO_OUTEN
 * @brief    GPIO Output Enable Register. Each bit controls the GPIO_OUT_EN setting for one
 *           GPIO pin in the associated port.
 * @{
 */
#define MXC_F_GPIO_OUTEN_ALL_POS                       0 /**< OUTEN_ALL Position */
#define MXC_F_GPIO_OUTEN_ALL                           ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_OUTEN_ALL_POS)) /**< OUTEN_ALL Mask */
#define MXC_V_GPIO_OUTEN_ALL_DIS                       ((uint32_t)0x0UL) /**< OUTEN_ALL_DIS Value */
#define MXC_S_GPIO_OUTEN_ALL_DIS                       (MXC_V_GPIO_OUTEN_ALL_DIS << MXC_F_GPIO_OUTEN_ALL_POS) /**< OUTEN_ALL_DIS Setting */
#define MXC_V_GPIO_OUTEN_ALL_EN                        ((uint32_t)0x1UL) /**< OUTEN_ALL_EN Value */
#define MXC_S_GPIO_OUTEN_ALL_EN                        (MXC_V_GPIO_OUTEN_ALL_EN << MXC_F_GPIO_OUTEN_ALL_POS) /**< OUTEN_ALL_EN Setting */

/**@} end of group GPIO_OUTEN_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_OUTEN_SET GPIO_OUTEN_SET
 * @brief    GPIO Output Enable Set Function Enable Register. Writing a 1 to one or more bits
 *           in this register sets the bits in the same positions in GPIO_OUT_EN to 1,
 *           without affecting other bits in that register.
 * @{
 */
#define MXC_F_GPIO_OUTEN_SET_ALL_POS                   0 /**< OUTEN_SET_ALL Position */
#define MXC_F_GPIO_OUTEN_SET_ALL                       ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_OUTEN_SET_ALL_POS)) /**< OUTEN_SET_ALL Mask */

/**@} end of group GPIO_OUTEN_SET_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_OUTEN_CLR GPIO_OUTEN_CLR
 * @brief    GPIO Output Enable Clear Function Enable Register. Writing a 1 to one or more
 *           bits in this register clears the bits in the same positions in GPIO_OUT_EN to 0,
 *           without affecting other bits in that register.
 * @{
 */
#define MXC_F_GPIO_OUTEN_CLR_ALL_POS                   0 /**< OUTEN_CLR_ALL Position */
#define MXC_F_GPIO_OUTEN_CLR_ALL                       ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_OUTEN_CLR_ALL_POS)) /**< OUTEN_CLR_ALL Mask */

/**@} end of group GPIO_OUTEN_CLR_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_OUT GPIO_OUT
 * @brief    GPIO Output Register. Each bit controls the GPIO_OUT setting for one pin in the
 *           associated port.  This register can be written either directly, or by using the
 *           GPIO_OUT_SET and GPIO_OUT_CLR registers.
 * @{
 */
#define MXC_F_GPIO_OUT_ALL_POS                         0 /**< OUT_ALL Position */
#define MXC_F_GPIO_OUT_ALL                             ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_OUT_ALL_POS)) /**< OUT_ALL Mask */
#define MXC_V_GPIO_OUT_ALL_LOW                         ((uint32_t)0x0UL) /**< OUT_ALL_LOW Value */
#define MXC_S_GPIO_OUT_ALL_LOW                         (MXC_V_GPIO_OUT_ALL_LOW << MXC_F_GPIO_OUT_ALL_POS) /**< OUT_ALL_LOW Setting */
#define MXC_V_GPIO_OUT_ALL_HIGH                        ((uint32_t)0x1UL) /**< OUT_ALL_HIGH Value */
#define MXC_S_GPIO_OUT_ALL_HIGH                        (MXC_V_GPIO_OUT_ALL_HIGH << MXC_F_GPIO_OUT_ALL_POS) /**< OUT_ALL_HIGH Setting */

/**@} end of group GPIO_OUT_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_OUT_SET GPIO_OUT_SET
 * @brief    GPIO Output Set. Writing a 1 to one or more bits in this register sets the bits
 *           in the same positions in GPIO_OUT to 1, without affecting other bits in that
 *           register.
 * @{
 */
#define MXC_F_GPIO_OUT_SET_ALL_POS                     0 /**< OUT_SET_ALL Position */
#define MXC_F_GPIO_OUT_SET_ALL                         ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_OUT_SET_ALL_POS)) /**< OUT_SET_ALL Mask */
#define MXC_V_GPIO_OUT_SET_ALL_NO                      ((uint32_t)0x0UL) /**< OUT_SET_ALL_NO Value */
#define MXC_S_GPIO_OUT_SET_ALL_NO                      (MXC_V_GPIO_OUT_SET_ALL_NO << MXC_F_GPIO_OUT_SET_ALL_POS) /**< OUT_SET_ALL_NO Setting */
#define MXC_V_GPIO_OUT_SET_ALL_SET                     ((uint32_t)0x1UL) /**< OUT_SET_ALL_SET Value */
#define MXC_S_GPIO_OUT_SET_ALL_SET                     (MXC_V_GPIO_OUT_SET_ALL_SET << MXC_F_GPIO_OUT_SET_ALL_POS) /**< OUT_SET_ALL_SET Setting */

/**@} end of group GPIO_OUT_SET_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_OUT_CLR GPIO_OUT_CLR
 * @brief    GPIO Output Clear. Writing a 1 to one or more bits in this register clears the
 *           bits in the same positions in GPIO_OUT to 0, without affecting other bits in
 *           that register.
 * @{
 */
#define MXC_F_GPIO_OUT_CLR_ALL_POS                     0 /**< OUT_CLR_ALL Position */
#define MXC_F_GPIO_OUT_CLR_ALL                         ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_OUT_CLR_ALL_POS)) /**< OUT_CLR_ALL Mask */

/**@} end of group GPIO_OUT_CLR_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_IN GPIO_IN
 * @brief    GPIO Input Register. Read-only register to read from the logic states of the
 *           GPIO pins on this port.
 * @{
 */
#define MXC_F_GPIO_IN_ALL_POS                          0 /**< IN_ALL Position */
#define MXC_F_GPIO_IN_ALL                              ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_IN_ALL_POS)) /**< IN_ALL Mask */

/**@} end of group GPIO_IN_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_INTMODE GPIO_INTMODE
 * @brief    GPIO Interrupt Mode Register. Each bit in this register controls the interrupt
 *           mode setting for the associated GPIO pin on this port.
 * @{
 */
#define MXC_F_GPIO_INTMODE_ALL_POS                     0 /**< INTMODE_ALL Position */
#define MXC_F_GPIO_INTMODE_ALL                         ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_INTMODE_ALL_POS)) /**< INTMODE_ALL Mask */
#define MXC_V_GPIO_INTMODE_ALL_LEVEL                   ((uint32_t)0x0UL) /**< INTMODE_ALL_LEVEL Value */
#define MXC_S_GPIO_INTMODE_ALL_LEVEL                   (MXC_V_GPIO_INTMODE_ALL_LEVEL << MXC_F_GPIO_INTMODE_ALL_POS) /**< INTMODE_ALL_LEVEL Setting */
#define MXC_V_GPIO_INTMODE_ALL_EDGE                    ((uint32_t)0x1UL) /**< INTMODE_ALL_EDGE Value */
#define MXC_S_GPIO_INTMODE_ALL_EDGE                    (MXC_V_GPIO_INTMODE_ALL_EDGE << MXC_F_GPIO_INTMODE_ALL_POS) /**< INTMODE_ALL_EDGE Setting */

/**@} end of group GPIO_INTMODE_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_INTPOL GPIO_INTPOL
 * @brief    GPIO Interrupt Polarity Register. Each bit in this register controls the
 *           interrupt polarity setting for one GPIO pin in the associated port.
 * @{
 */
#define MXC_F_GPIO_INTPOL_ALL_POS                      0 /**< INTPOL_ALL Position */
#define MXC_F_GPIO_INTPOL_ALL                          ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_INTPOL_ALL_POS)) /**< INTPOL_ALL Mask */
#define MXC_V_GPIO_INTPOL_ALL_FALLING                  ((uint32_t)0x0UL) /**< INTPOL_ALL_FALLING Value */
#define MXC_S_GPIO_INTPOL_ALL_FALLING                  (MXC_V_GPIO_INTPOL_ALL_FALLING << MXC_F_GPIO_INTPOL_ALL_POS) /**< INTPOL_ALL_FALLING Setting */
#define MXC_V_GPIO_INTPOL_ALL_RISING                   ((uint32_t)0x1UL) /**< INTPOL_ALL_RISING Value */
#define MXC_S_GPIO_INTPOL_ALL_RISING                   (MXC_V_GPIO_INTPOL_ALL_RISING << MXC_F_GPIO_INTPOL_ALL_POS) /**< INTPOL_ALL_RISING Setting */

/**@} end of group GPIO_INTPOL_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_INTEN GPIO_INTEN
 * @brief    GPIO Interrupt Enable Register. Each bit in this register controls the GPIO
 *           interrupt enable for the associated pin on the GPIO port.
 * @{
 */
#define MXC_F_GPIO_INTEN_ALL_POS                       0 /**< INTEN_ALL Position */
#define MXC_F_GPIO_INTEN_ALL                           ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_INTEN_ALL_POS)) /**< INTEN_ALL Mask */
#define MXC_V_GPIO_INTEN_ALL_DIS                       ((uint32_t)0x0UL) /**< INTEN_ALL_DIS Value */
#define MXC_S_GPIO_INTEN_ALL_DIS                       (MXC_V_GPIO_INTEN_ALL_DIS << MXC_F_GPIO_INTEN_ALL_POS) /**< INTEN_ALL_DIS Setting */
#define MXC_V_GPIO_INTEN_ALL_EN                        ((uint32_t)0x1UL) /**< INTEN_ALL_EN Value */
#define MXC_S_GPIO_INTEN_ALL_EN                        (MXC_V_GPIO_INTEN_ALL_EN << MXC_F_GPIO_INTEN_ALL_POS) /**< INTEN_ALL_EN Setting */

/**@} end of group GPIO_INTEN_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_INTEN_SET GPIO_INTEN_SET
 * @brief    GPIO Interrupt Enable Set. Writing a 1 to one or more bits in this register sets
 *           the bits in the same positions in GPIO_INT_EN to 1, without affecting other bits
 *           in that register.
 * @{
 */
#define MXC_F_GPIO_INTEN_SET_ALL_POS                   0 /**< INTEN_SET_ALL Position */
#define MXC_F_GPIO_INTEN_SET_ALL                       ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_INTEN_SET_ALL_POS)) /**< INTEN_SET_ALL Mask */
#define MXC_V_GPIO_INTEN_SET_ALL_NO                    ((uint32_t)0x0UL) /**< INTEN_SET_ALL_NO Value */
#define MXC_S_GPIO_INTEN_SET_ALL_NO                    (MXC_V_GPIO_INTEN_SET_ALL_NO << MXC_F_GPIO_INTEN_SET_ALL_POS) /**< INTEN_SET_ALL_NO Setting */
#define MXC_V_GPIO_INTEN_SET_ALL_SET                   ((uint32_t)0x1UL) /**< INTEN_SET_ALL_SET Value */
#define MXC_S_GPIO_INTEN_SET_ALL_SET                   (MXC_V_GPIO_INTEN_SET_ALL_SET << MXC_F_GPIO_INTEN_SET_ALL_POS) /**< INTEN_SET_ALL_SET Setting */

/**@} end of group GPIO_INTEN_SET_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_INTEN_CLR GPIO_INTEN_CLR
 * @brief    GPIO Interrupt Enable Clear. Writing a 1 to one or more bits in this register
 *           clears the bits in the same positions in GPIO_INT_EN to 0, without affecting
 *           other bits in that register.
 * @{
 */
#define MXC_F_GPIO_INTEN_CLR_ALL_POS                   0 /**< INTEN_CLR_ALL Position */
#define MXC_F_GPIO_INTEN_CLR_ALL                       ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_INTEN_CLR_ALL_POS)) /**< INTEN_CLR_ALL Mask */
#define MXC_V_GPIO_INTEN_CLR_ALL_NO                    ((uint32_t)0x0UL) /**< INTEN_CLR_ALL_NO Value */
#define MXC_S_GPIO_INTEN_CLR_ALL_NO                    (MXC_V_GPIO_INTEN_CLR_ALL_NO << MXC_F_GPIO_INTEN_CLR_ALL_POS) /**< INTEN_CLR_ALL_NO Setting */
#define MXC_V_GPIO_INTEN_CLR_ALL_CLEAR                 ((uint32_t)0x1UL) /**< INTEN_CLR_ALL_CLEAR Value */
#define MXC_S_GPIO_INTEN_CLR_ALL_CLEAR                 (MXC_V_GPIO_INTEN_CLR_ALL_CLEAR << MXC_F_GPIO_INTEN_CLR_ALL_POS) /**< INTEN_CLR_ALL_CLEAR Setting */

/**@} end of group GPIO_INTEN_CLR_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_INTFL GPIO_INTFL
 * @brief    GPIO Interrupt Status Register. Each bit in this register contains the pending
 *           interrupt status for the associated GPIO pin in this port.
 * @{
 */
#define MXC_F_GPIO_INTFL_ALL_POS                       0 /**< INTFL_ALL Position */
#define MXC_F_GPIO_INTFL_ALL                           ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_INTFL_ALL_POS)) /**< INTFL_ALL Mask */
#define MXC_V_GPIO_INTFL_ALL_NO                        ((uint32_t)0x0UL) /**< INTFL_ALL_NO Value */
#define MXC_S_GPIO_INTFL_ALL_NO                        (MXC_V_GPIO_INTFL_ALL_NO << MXC_F_GPIO_INTFL_ALL_POS) /**< INTFL_ALL_NO Setting */
#define MXC_V_GPIO_INTFL_ALL_PENDING                   ((uint32_t)0x1UL) /**< INTFL_ALL_PENDING Value */
#define MXC_S_GPIO_INTFL_ALL_PENDING                   (MXC_V_GPIO_INTFL_ALL_PENDING << MXC_F_GPIO_INTFL_ALL_POS) /**< INTFL_ALL_PENDING Setting */

/**@} end of group GPIO_INTFL_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_INTFL_CLR GPIO_INTFL_CLR
 * @brief    GPIO Status Clear. Writing a 1 to one or more bits in this register clears the
 *           bits in the same positions in GPIO_INT_STAT to 0, without affecting other bits
 *           in that register.
 * @{
 */
#define MXC_F_GPIO_INTFL_CLR_ALL_POS                   0 /**< INTFL_CLR_ALL Position */
#define MXC_F_GPIO_INTFL_CLR_ALL                       ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_INTFL_CLR_ALL_POS)) /**< INTFL_CLR_ALL Mask */

/**@} end of group GPIO_INTFL_CLR_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_WKEN GPIO_WKEN
 * @brief    GPIO Wake Enable Register. Each bit in this register controls the PMU wakeup
 *           enable for the associated GPIO pin in this port.
 * @{
 */
#define MXC_F_GPIO_WKEN_ALL_POS                        0 /**< WKEN_ALL Position */
#define MXC_F_GPIO_WKEN_ALL                            ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_WKEN_ALL_POS)) /**< WKEN_ALL Mask */
#define MXC_V_GPIO_WKEN_ALL_DIS                        ((uint32_t)0x0UL) /**< WKEN_ALL_DIS Value */
#define MXC_S_GPIO_WKEN_ALL_DIS                        (MXC_V_GPIO_WKEN_ALL_DIS << MXC_F_GPIO_WKEN_ALL_POS) /**< WKEN_ALL_DIS Setting */
#define MXC_V_GPIO_WKEN_ALL_EN                         ((uint32_t)0x1UL) /**< WKEN_ALL_EN Value */
#define MXC_S_GPIO_WKEN_ALL_EN                         (MXC_V_GPIO_WKEN_ALL_EN << MXC_F_GPIO_WKEN_ALL_POS) /**< WKEN_ALL_EN Setting */

/**@} end of group GPIO_WKEN_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_WKEN_SET GPIO_WKEN_SET
 * @brief    GPIO Wake Enable Set. Writing a 1 to one or more bits in this register sets the
 *           bits in the same positions in GPIO_WAKE_EN to 1, without affecting other bits in
 *           that register.
 * @{
 */
#define MXC_F_GPIO_WKEN_SET_ALL_POS                    0 /**< WKEN_SET_ALL Position */
#define MXC_F_GPIO_WKEN_SET_ALL                        ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_WKEN_SET_ALL_POS)) /**< WKEN_SET_ALL Mask */

/**@} end of group GPIO_WKEN_SET_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_WKEN_CLR GPIO_WKEN_CLR
 * @brief    GPIO Wake Enable Clear. Writing a 1 to one or more bits in this register clears
 *           the bits in the same positions in GPIO_WAKE_EN to 0, without affecting other
 *           bits in that register.
 * @{
 */
#define MXC_F_GPIO_WKEN_CLR_ALL_POS                    0 /**< WKEN_CLR_ALL Position */
#define MXC_F_GPIO_WKEN_CLR_ALL                        ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_WKEN_CLR_ALL_POS)) /**< WKEN_CLR_ALL Mask */

/**@} end of group GPIO_WKEN_CLR_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_DUALEDGE GPIO_DUALEDGE
 * @brief    GPIO Interrupt Dual Edge Mode Register. Each bit in this register selects dual
 *           edge mode for the associated GPIO pin in this port.
 * @{
 */
#define MXC_F_GPIO_DUALEDGE_ALL_POS                    0 /**< DUALEDGE_ALL Position */
#define MXC_F_GPIO_DUALEDGE_ALL                        ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_DUALEDGE_ALL_POS)) /**< DUALEDGE_ALL Mask */
#define MXC_V_GPIO_DUALEDGE_ALL_NO                     ((uint32_t)0x0UL) /**< DUALEDGE_ALL_NO Value */
#define MXC_S_GPIO_DUALEDGE_ALL_NO                     (MXC_V_GPIO_DUALEDGE_ALL_NO << MXC_F_GPIO_DUALEDGE_ALL_POS) /**< DUALEDGE_ALL_NO Setting */
#define MXC_V_GPIO_DUALEDGE_ALL_EN                     ((uint32_t)0x1UL) /**< DUALEDGE_ALL_EN Value */
#define MXC_S_GPIO_DUALEDGE_ALL_EN                     (MXC_V_GPIO_DUALEDGE_ALL_EN << MXC_F_GPIO_DUALEDGE_ALL_POS) /**< DUALEDGE_ALL_EN Setting */

/**@} end of group GPIO_DUALEDGE_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_PADCTRL0 GPIO_PADCTRL0
 * @brief    GPIO Input Mode Config 0. Each bit in this register enables the weak pull-up for
 *           the associated GPIO pin in this port.
 * @{
 */
#define MXC_F_GPIO_PADCTRL0_ALL_POS                    0 /**< PADCTRL0_ALL Position */
#define MXC_F_GPIO_PADCTRL0_ALL                        ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_PADCTRL0_ALL_POS)) /**< PADCTRL0_ALL Mask */
#define MXC_V_GPIO_PADCTRL0_ALL_IMPEDANCE              ((uint32_t)0x0UL) /**< PADCTRL0_ALL_IMPEDANCE Value */
#define MXC_S_GPIO_PADCTRL0_ALL_IMPEDANCE              (MXC_V_GPIO_PADCTRL0_ALL_IMPEDANCE << MXC_F_GPIO_PADCTRL0_ALL_POS) /**< PADCTRL0_ALL_IMPEDANCE Setting */
#define MXC_V_GPIO_PADCTRL0_ALL_PU                     ((uint32_t)0x1UL) /**< PADCTRL0_ALL_PU Value */
#define MXC_S_GPIO_PADCTRL0_ALL_PU                     (MXC_V_GPIO_PADCTRL0_ALL_PU << MXC_F_GPIO_PADCTRL0_ALL_POS) /**< PADCTRL0_ALL_PU Setting */
#define MXC_V_GPIO_PADCTRL0_ALL_PD                     ((uint32_t)0x2UL) /**< PADCTRL0_ALL_PD Value */
#define MXC_S_GPIO_PADCTRL0_ALL_PD                     (MXC_V_GPIO_PADCTRL0_ALL_PD << MXC_F_GPIO_PADCTRL0_ALL_POS) /**< PADCTRL0_ALL_PD Setting */

/**@} end of group GPIO_PADCTRL0_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_PADCTRL1 GPIO_PADCTRL1
 * @brief    GPIO Input Mode Config 1. Each bit in this register enables the weak pull-up for
 *           the associated GPIO pin in this port.
 * @{
 */
#define MXC_F_GPIO_PADCTRL1_ALL_POS                    0 /**< PADCTRL1_ALL Position */
#define MXC_F_GPIO_PADCTRL1_ALL                        ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_PADCTRL1_ALL_POS)) /**< PADCTRL1_ALL Mask */
#define MXC_V_GPIO_PADCTRL1_ALL_IMPEDANCE              ((uint32_t)0x0UL) /**< PADCTRL1_ALL_IMPEDANCE Value */
#define MXC_S_GPIO_PADCTRL1_ALL_IMPEDANCE              (MXC_V_GPIO_PADCTRL1_ALL_IMPEDANCE << MXC_F_GPIO_PADCTRL1_ALL_POS) /**< PADCTRL1_ALL_IMPEDANCE Setting */
#define MXC_V_GPIO_PADCTRL1_ALL_PU                     ((uint32_t)0x1UL) /**< PADCTRL1_ALL_PU Value */
#define MXC_S_GPIO_PADCTRL1_ALL_PU                     (MXC_V_GPIO_PADCTRL1_ALL_PU << MXC_F_GPIO_PADCTRL1_ALL_POS) /**< PADCTRL1_ALL_PU Setting */
#define MXC_V_GPIO_PADCTRL1_ALL_PD                     ((uint32_t)0x2UL) /**< PADCTRL1_ALL_PD Value */
#define MXC_S_GPIO_PADCTRL1_ALL_PD                     (MXC_V_GPIO_PADCTRL1_ALL_PD << MXC_F_GPIO_PADCTRL1_ALL_POS) /**< PADCTRL1_ALL_PD Setting */

/**@} end of group GPIO_PADCTRL1_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_EN1 GPIO_EN1
 * @brief    GPIO Alternate Function Enable Register. Each bit in this register selects
 *           between primary/secondary functions for the associated GPIO pin in this port.
 * @{
 */
#define MXC_F_GPIO_EN1_ALL_POS                         0 /**< EN1_ALL Position */
#define MXC_F_GPIO_EN1_ALL                             ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_EN1_ALL_POS)) /**< EN1_ALL Mask */
#define MXC_V_GPIO_EN1_ALL_PRIMARY                     ((uint32_t)0x0UL) /**< EN1_ALL_PRIMARY Value */
#define MXC_S_GPIO_EN1_ALL_PRIMARY                     (MXC_V_GPIO_EN1_ALL_PRIMARY << MXC_F_GPIO_EN1_ALL_POS) /**< EN1_ALL_PRIMARY Setting */
#define MXC_V_GPIO_EN1_ALL_SECONDARY                   ((uint32_t)0x1UL) /**< EN1_ALL_SECONDARY Value */
#define MXC_S_GPIO_EN1_ALL_SECONDARY                   (MXC_V_GPIO_EN1_ALL_SECONDARY << MXC_F_GPIO_EN1_ALL_POS) /**< EN1_ALL_SECONDARY Setting */

/**@} end of group GPIO_EN1_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_EN1_SET GPIO_EN1_SET
 * @brief    GPIO Alternate Function Set. Writing a 1 to one or more bits in this register
 *           sets the bits in the same positions in GPIO_EN1 to 1, without affecting other
 *           bits in that register.
 * @{
 */
#define MXC_F_GPIO_EN1_SET_ALL_POS                     0 /**< EN1_SET_ALL Position */
#define MXC_F_GPIO_EN1_SET_ALL                         ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_EN1_SET_ALL_POS)) /**< EN1_SET_ALL Mask */

/**@} end of group GPIO_EN1_SET_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_EN1_CLR GPIO_EN1_CLR
 * @brief    GPIO Alternate Function Clear. Writing a 1 to one or more bits in this register
 *           clears the bits in the same positions in GPIO_EN1 to 0, without affecting other
 *           bits in that register.
 * @{
 */
#define MXC_F_GPIO_EN1_CLR_ALL_POS                     0 /**< EN1_CLR_ALL Position */
#define MXC_F_GPIO_EN1_CLR_ALL                         ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_EN1_CLR_ALL_POS)) /**< EN1_CLR_ALL Mask */

/**@} end of group GPIO_EN1_CLR_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_EN2 GPIO_EN2
 * @brief    GPIO Alternate Function Enable Register. Each bit in this register selects
 *           between primary/secondary functions for the associated GPIO pin in this port.
 * @{
 */
#define MXC_F_GPIO_EN2_ALL_POS                         0 /**< EN2_ALL Position */
#define MXC_F_GPIO_EN2_ALL                             ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_EN2_ALL_POS)) /**< EN2_ALL Mask */
#define MXC_V_GPIO_EN2_ALL_PRIMARY                     ((uint32_t)0x0UL) /**< EN2_ALL_PRIMARY Value */
#define MXC_S_GPIO_EN2_ALL_PRIMARY                     (MXC_V_GPIO_EN2_ALL_PRIMARY << MXC_F_GPIO_EN2_ALL_POS) /**< EN2_ALL_PRIMARY Setting */
#define MXC_V_GPIO_EN2_ALL_SECONDARY                   ((uint32_t)0x1UL) /**< EN2_ALL_SECONDARY Value */
#define MXC_S_GPIO_EN2_ALL_SECONDARY                   (MXC_V_GPIO_EN2_ALL_SECONDARY << MXC_F_GPIO_EN2_ALL_POS) /**< EN2_ALL_SECONDARY Setting */

/**@} end of group GPIO_EN2_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_EN2_SET GPIO_EN2_SET
 * @brief    GPIO Alternate Function 2 Set. Writing a 1 to one or more bits in this register
 *           sets the bits in the same positions in GPIO_EN2 to 1, without affecting other
 *           bits in that register.
 * @{
 */
#define MXC_F_GPIO_EN2_SET_ALL_POS                     0 /**< EN2_SET_ALL Position */
#define MXC_F_GPIO_EN2_SET_ALL                         ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_EN2_SET_ALL_POS)) /**< EN2_SET_ALL Mask */

/**@} end of group GPIO_EN2_SET_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_EN2_CLR GPIO_EN2_CLR
 * @brief    GPIO Wake Alternate Function Clear. Writing a 1 to one or more bits in this
 *           register clears the bits in the same positions in GPIO_EN2 to 0, without
 *           affecting other bits in that register.
 * @{
 */
#define MXC_F_GPIO_EN2_CLR_ALL_POS                     0 /**< EN2_CLR_ALL Position */
#define MXC_F_GPIO_EN2_CLR_ALL                         ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_EN2_CLR_ALL_POS)) /**< EN2_CLR_ALL Mask */

/**@} end of group GPIO_EN2_CLR_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_HYSEN GPIO_HYSEN
 * @brief    GPIO Input Hysteresis Enable.
 * @{
 */
#define MXC_F_GPIO_HYSEN_ALL_POS                       0 /**< HYSEN_ALL Position */
#define MXC_F_GPIO_HYSEN_ALL                           ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_HYSEN_ALL_POS)) /**< HYSEN_ALL Mask */

/**@} end of group GPIO_HYSEN_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_SRSEL GPIO_SRSEL
 * @brief    GPIO Slew Rate Enable Register.
 * @{
 */
#define MXC_F_GPIO_SRSEL_ALL_POS                       0 /**< SRSEL_ALL Position */
#define MXC_F_GPIO_SRSEL_ALL                           ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_SRSEL_ALL_POS)) /**< SRSEL_ALL Mask */
#define MXC_V_GPIO_SRSEL_ALL_FAST                      ((uint32_t)0x0UL) /**< SRSEL_ALL_FAST Value */
#define MXC_S_GPIO_SRSEL_ALL_FAST                      (MXC_V_GPIO_SRSEL_ALL_FAST << MXC_F_GPIO_SRSEL_ALL_POS) /**< SRSEL_ALL_FAST Setting */
#define MXC_V_GPIO_SRSEL_ALL_SLOW                      ((uint32_t)0x1UL) /**< SRSEL_ALL_SLOW Value */
#define MXC_S_GPIO_SRSEL_ALL_SLOW                      (MXC_V_GPIO_SRSEL_ALL_SLOW << MXC_F_GPIO_SRSEL_ALL_POS) /**< SRSEL_ALL_SLOW Setting */

/**@} end of group GPIO_SRSEL_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_DS0 GPIO_DS0
 * @brief    GPIO Drive Strength 0 Register. Each bit in this register selects the drive
 *           strength for the associated GPIO pin in this port. Refer to the Datasheet for
 *           sink/source current of GPIO pins in each mode.
 * @{
 */
#define MXC_F_GPIO_DS0_ALL_POS                         0 /**< DS0_ALL Position */
#define MXC_F_GPIO_DS0_ALL                             ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_DS0_ALL_POS)) /**< DS0_ALL Mask */
#define MXC_V_GPIO_DS0_ALL_LD                          ((uint32_t)0x0UL) /**< DS0_ALL_LD Value */
#define MXC_S_GPIO_DS0_ALL_LD                          (MXC_V_GPIO_DS0_ALL_LD << MXC_F_GPIO_DS0_ALL_POS) /**< DS0_ALL_LD Setting */
#define MXC_V_GPIO_DS0_ALL_HD                          ((uint32_t)0x1UL) /**< DS0_ALL_HD Value */
#define MXC_S_GPIO_DS0_ALL_HD                          (MXC_V_GPIO_DS0_ALL_HD << MXC_F_GPIO_DS0_ALL_POS) /**< DS0_ALL_HD Setting */

/**@} end of group GPIO_DS0_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_DS1 GPIO_DS1
 * @brief    GPIO Drive Strength 1 Register. Each bit in this register selects the drive
 *           strength for the associated GPIO pin in this port. Refer to the Datasheet for
 *           sink/source current of GPIO pins in each mode.
 * @{
 */
#define MXC_F_GPIO_DS1_ALL_POS                         0 /**< DS1_ALL Position */
#define MXC_F_GPIO_DS1_ALL                             ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_DS1_ALL_POS)) /**< DS1_ALL Mask */

/**@} end of group GPIO_DS1_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_PSSEL GPIO_PSSEL
 * @brief    GPIO Pull Select Mode.
 * @{
 */
#define MXC_F_GPIO_PSSEL_ALL_POS                       0 /**< PSSEL_ALL Position */
#define MXC_F_GPIO_PSSEL_ALL                           ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_PSSEL_ALL_POS)) /**< PSSEL_ALL Mask */

/**@} end of group GPIO_PSSEL_Register */

/**
 * @ingroup  gpio_registers
 * @defgroup GPIO_VSSEL GPIO_VSSEL
 * @brief    GPIO Voltage Select.
 * @{
 */
#define MXC_F_GPIO_VSSEL_ALL_POS                       0 /**< VSSEL_ALL Position */
#define MXC_F_GPIO_VSSEL_ALL                           ((uint32_t)(0xFFFFFFFFUL << MXC_F_GPIO_VSSEL_ALL_POS)) /**< VSSEL_ALL Mask */

/**@} end of group GPIO_VSSEL_Register */

#ifdef __cplusplus
}
#endif

#endif // LIBRARIES_CMSIS_DEVICE_MAXIM_MAX32572_INCLUDE_GPIO_REGS_H_
