/**
 * @file    trng_regs.h
 * @brief   Registers, Bit Masks and Bit Positions for the TRNG Peripheral Module.
 * @note    This file is @generated.
 */

/******************************************************************************
 * Copyright (C) 2022 Maxim Integrated Products, Inc., All rights Reserved.
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

#ifndef LIBRARIES_CMSIS_DEVICE_MAXIM_MAX32570_INCLUDE_TRNG_REGS_H_
#define LIBRARIES_CMSIS_DEVICE_MAXIM_MAX32570_INCLUDE_TRNG_REGS_H_

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
 * @ingroup     trng
 * @defgroup    trng_registers TRNG_Registers
 * @brief       Registers, Bit Masks and Bit Positions for the TRNG Peripheral Module.
 * @details     Random Number Generator.
 */

/**
 * @ingroup trng_registers
 * Structure type to access the TRNG Registers.
 */
typedef struct {
    __IO uint32_t ctrl;                 /**< <tt>\b 0x00:</tt> TRNG CTRL Register */
    __I  uint32_t status;               /**< <tt>\b 0x04:</tt> TRNG STATUS Register */
    __I  uint32_t data;                 /**< <tt>\b 0x08:</tt> TRNG DATA Register */
} mxc_trng_regs_t;

/* Register offsets for module TRNG */
/**
 * @ingroup    trng_registers
 * @defgroup   TRNG_Register_Offsets Register Offsets
 * @brief      TRNG Peripheral Register Offsets from the TRNG Base Peripheral Address.
 * @{
 */
#define MXC_R_TRNG_CTRL                    ((uint32_t)0x00000000UL) /**< Offset from TRNG Base Address: <tt> 0x0000</tt> */
#define MXC_R_TRNG_STATUS                  ((uint32_t)0x00000004UL) /**< Offset from TRNG Base Address: <tt> 0x0004</tt> */
#define MXC_R_TRNG_DATA                    ((uint32_t)0x00000008UL) /**< Offset from TRNG Base Address: <tt> 0x0008</tt> */
/**@} end of group trng_registers */

/**
 * @ingroup  trng_registers
 * @defgroup TRNG_CTRL TRNG_CTRL
 * @brief    TRNG Control Register.
 * @{
 */
#define MXC_F_TRNG_CTRL_RND_IE_POS                     1 /**< CTRL_RND_IE Position */
#define MXC_F_TRNG_CTRL_RND_IE                         ((uint32_t)(0x1UL << MXC_F_TRNG_CTRL_RND_IE_POS)) /**< CTRL_RND_IE Mask */

#define MXC_F_TRNG_CTRL_AESKG_MEMPROTE_POS             4 /**< CTRL_AESKG_MEMPROTE Position */
#define MXC_F_TRNG_CTRL_AESKG_MEMPROTE                 ((uint32_t)(0x1UL << MXC_F_TRNG_CTRL_AESKG_MEMPROTE_POS)) /**< CTRL_AESKG_MEMPROTE Mask */

/**@} end of group TRNG_CTRL_Register */

/**
 * @ingroup  trng_registers
 * @defgroup TRNG_STATUS TRNG_STATUS
 * @brief    Data. The content of this register is valid only when RNG_IS = 1. When TRNG is
 *           disabled, read returns 0x0000 0000.
 * @{
 */
#define MXC_F_TRNG_STATUS_RND_RDY_POS                  0 /**< STATUS_RND_RDY Position */
#define MXC_F_TRNG_STATUS_RND_RDY                      ((uint32_t)(0x1UL << MXC_F_TRNG_STATUS_RND_RDY_POS)) /**< STATUS_RND_RDY Mask */

#define MXC_F_TRNG_STATUS_AESKGD_MEU_POS               4 /**< STATUS_AESKGD_MEU Position */
#define MXC_F_TRNG_STATUS_AESKGD_MEU                   ((uint32_t)(0x1UL << MXC_F_TRNG_STATUS_AESKGD_MEU_POS)) /**< STATUS_AESKGD_MEU Mask */

/**@} end of group TRNG_STATUS_Register */

/**
 * @ingroup  trng_registers
 * @defgroup TRNG_DATA TRNG_DATA
 * @brief    Data. The content of this register is valid only when RNG_IS = 1. When TRNG is
 *           disabled, read returns 0x0000 0000.
 * @{
 */
#define MXC_F_TRNG_DATA_DATA_POS                       0 /**< DATA_DATA Position */
#define MXC_F_TRNG_DATA_DATA                           ((uint32_t)(0xFFFFFFFFUL << MXC_F_TRNG_DATA_DATA_POS)) /**< DATA_DATA Mask */

/**@} end of group TRNG_DATA_Register */

#ifdef __cplusplus
}
#endif

#endif // LIBRARIES_CMSIS_DEVICE_MAXIM_MAX32570_INCLUDE_TRNG_REGS_H_
