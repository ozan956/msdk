/**
 * @file    sir_regs.h
 * @brief   Registers, Bit Masks and Bit Positions for the SIR Peripheral Module.
 * @note    This file is @generated.
 * @ingroup sir_registers
 */

/******************************************************************************
 *
 * Copyright (C) 2022-2023 Maxim Integrated Products, Inc. All Rights Reserved.
 * (now owned by Analog Devices, Inc.),
 * Copyright (C) 2023 Analog Devices, Inc. All Rights Reserved. This software
 * is proprietary to Analog Devices, Inc. and its licensors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

#ifndef LIBRARIES_CMSIS_DEVICE_MAXIM_MAX32570_INCLUDE_SIR_REGS_H_
#define LIBRARIES_CMSIS_DEVICE_MAXIM_MAX32570_INCLUDE_SIR_REGS_H_

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
 * @ingroup     sir
 * @defgroup    sir_registers SIR_Registers
 * @brief       Registers, Bit Masks and Bit Positions for the SIR Peripheral Module.
 * @details     System Initialization Registers.
 */

/**
 * @ingroup sir_registers
 * Structure type to access the SIR Registers.
 */
typedef struct {
    __I  uint32_t sistat;               /**< <tt>\b 0x000:</tt> SIR SISTAT Register */
    __I  uint32_t siaddr;               /**< <tt>\b 0x004:</tt> SIR SIADDR Register */
    __R  uint32_t rsv_0x8_0xff[62];
    __I  uint32_t fstat;                /**< <tt>\b 0x100:</tt> SIR FSTAT Register */
    __I  uint32_t sfdis;                /**< <tt>\b 0x104:</tt> SIR SFDIS Register */
} mxc_sir_regs_t;

/* Register offsets for module SIR */
/**
 * @ingroup    sir_registers
 * @defgroup   SIR_Register_Offsets Register Offsets
 * @brief      SIR Peripheral Register Offsets from the SIR Base Peripheral Address.
 * @{
 */
#define MXC_R_SIR_SISTAT                   ((uint32_t)0x00000000UL) /**< Offset from SIR Base Address: <tt> 0x0000</tt> */
#define MXC_R_SIR_SIADDR                   ((uint32_t)0x00000004UL) /**< Offset from SIR Base Address: <tt> 0x0004</tt> */
#define MXC_R_SIR_FSTAT                    ((uint32_t)0x00000100UL) /**< Offset from SIR Base Address: <tt> 0x0100</tt> */
#define MXC_R_SIR_SFDIS                    ((uint32_t)0x00000104UL) /**< Offset from SIR Base Address: <tt> 0x0104</tt> */
/**@} end of group sir_registers */

/**
 * @ingroup  sir_registers
 * @defgroup SIR_SISTAT SIR_SISTAT
 * @brief    System Initialization Status Register.
 * @{
 */
#define MXC_F_SIR_SISTAT_MAGIC_POS                     0 /**< SISTAT_MAGIC Position */
#define MXC_F_SIR_SISTAT_MAGIC                         ((uint32_t)(0x1UL << MXC_F_SIR_SISTAT_MAGIC_POS)) /**< SISTAT_MAGIC Mask */

#define MXC_F_SIR_SISTAT_CRCERR_POS                    1 /**< SISTAT_CRCERR Position */
#define MXC_F_SIR_SISTAT_CRCERR                        ((uint32_t)(0x1UL << MXC_F_SIR_SISTAT_CRCERR_POS)) /**< SISTAT_CRCERR Mask */

/**@} end of group SIR_SISTAT_Register */

/**
 * @ingroup  sir_registers
 * @defgroup SIR_SIADDR SIR_SIADDR
 * @brief    System Initializartion Address Register.
 * @{
 */
#define MXC_F_SIR_SIADDR_ERRADDR_POS                   0 /**< SIADDR_ERRADDR Position */
#define MXC_F_SIR_SIADDR_ERRADDR                       ((uint32_t)(0xFFFFFFFFUL << MXC_F_SIR_SIADDR_ERRADDR_POS)) /**< SIADDR_ERRADDR Mask */

/**@} end of group SIR_SIADDR_Register */

/**
 * @ingroup  sir_registers
 * @defgroup SIR_FSTAT SIR_FSTAT
 * @brief    Function Status Register.
 * @{
 */
#define MXC_F_SIR_FSTAT_FPU_POS                        0 /**< FSTAT_FPU Position */
#define MXC_F_SIR_FSTAT_FPU                            ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_FPU_POS)) /**< FSTAT_FPU Mask */

#define MXC_F_SIR_FSTAT_USB_POS                        1 /**< FSTAT_USB Position */
#define MXC_F_SIR_FSTAT_USB                            ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_USB_POS)) /**< FSTAT_USB Mask */

#define MXC_F_SIR_FSTAT_ADC_POS                        2 /**< FSTAT_ADC Position */
#define MXC_F_SIR_FSTAT_ADC                            ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_ADC_POS)) /**< FSTAT_ADC Mask */

#define MXC_F_SIR_FSTAT_SPIXIP_POS                     3 /**< FSTAT_SPIXIP Position */
#define MXC_F_SIR_FSTAT_SPIXIP                         ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_SPIXIP_POS)) /**< FSTAT_SPIXIP Mask */

#define MXC_F_SIR_FSTAT_SDHC_POS                       6 /**< FSTAT_SDHC Position */
#define MXC_F_SIR_FSTAT_SDHC                           ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_SDHC_POS)) /**< FSTAT_SDHC Mask */

#define MXC_F_SIR_FSTAT_SEMA_POS                       7 /**< FSTAT_SEMA Position */
#define MXC_F_SIR_FSTAT_SEMA                           ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_SEMA_POS)) /**< FSTAT_SEMA Mask */

#define MXC_F_SIR_FSTAT_SRCC_POS                       8 /**< FSTAT_SRCC Position */
#define MXC_F_SIR_FSTAT_SRCC                           ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_SRCC_POS)) /**< FSTAT_SRCC Mask */

#define MXC_F_SIR_FSTAT_MSRADC_POS                     9 /**< FSTAT_MSRADC Position */
#define MXC_F_SIR_FSTAT_MSRADC                         ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_MSRADC_POS)) /**< FSTAT_MSRADC Mask */

#define MXC_F_SIR_FSTAT_SC_POS                         10 /**< FSTAT_SC Position */
#define MXC_F_SIR_FSTAT_SC                             ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_SC_POS)) /**< FSTAT_SC Mask */

#define MXC_F_SIR_FSTAT_NFC_POS                        11 /**< FSTAT_NFC Position */
#define MXC_F_SIR_FSTAT_NFC                            ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_NFC_POS)) /**< FSTAT_NFC Mask */

#define MXC_F_SIR_FSTAT_NMI_POS                        12 /**< FSTAT_NMI Position */
#define MXC_F_SIR_FSTAT_NMI                            ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_NMI_POS)) /**< FSTAT_NMI Mask */

/**@} end of group SIR_FSTAT_Register */

/**
 * @ingroup  sir_registers
 * @defgroup SIR_SFDIS SIR_SFDIS
 * @brief    Security Function Status Register.
 * @{
 */
#define MXC_F_SIR_SFDIS_SECBOOT_POS                    0 /**< SFDIS_SECBOOT Position */
#define MXC_F_SIR_SFDIS_SECBOOT                        ((uint32_t)(0x1UL << MXC_F_SIR_SFDIS_SECBOOT_POS)) /**< SFDIS_SECBOOT Mask */

#define MXC_F_SIR_SFDIS_SERLOAD_POS                    1 /**< SFDIS_SERLOAD Position */
#define MXC_F_SIR_SFDIS_SERLOAD                        ((uint32_t)(0x1UL << MXC_F_SIR_SFDIS_SERLOAD_POS)) /**< SFDIS_SERLOAD Mask */

#define MXC_F_SIR_SFDIS_TRNG_POS                       2 /**< SFDIS_TRNG Position */
#define MXC_F_SIR_SFDIS_TRNG                           ((uint32_t)(0x1UL << MXC_F_SIR_SFDIS_TRNG_POS)) /**< SFDIS_TRNG Mask */

#define MXC_F_SIR_SFDIS_AES_POS                        3 /**< SFDIS_AES Position */
#define MXC_F_SIR_SFDIS_AES                            ((uint32_t)(0x1UL << MXC_F_SIR_SFDIS_AES_POS)) /**< SFDIS_AES Mask */

#define MXC_F_SIR_SFDIS_SHA_POS                        4 /**< SFDIS_SHA Position */
#define MXC_F_SIR_SFDIS_SHA                            ((uint32_t)(0x1UL << MXC_F_SIR_SFDIS_SHA_POS)) /**< SFDIS_SHA Mask */

#define MXC_F_SIR_SFDIS_MAA_POS                        5 /**< SFDIS_MAA Position */
#define MXC_F_SIR_SFDIS_MAA                            ((uint32_t)(0x1UL << MXC_F_SIR_SFDIS_MAA_POS)) /**< SFDIS_MAA Mask */

#define MXC_F_SIR_SFDIS_SECMODE_POS                    7 /**< SFDIS_SECMODE Position */
#define MXC_F_SIR_SFDIS_SECMODE                        ((uint32_t)(0x1UL << MXC_F_SIR_SFDIS_SECMODE_POS)) /**< SFDIS_SECMODE Mask */

/**@} end of group SIR_SFDIS_Register */

#ifdef __cplusplus
}
#endif

#endif // LIBRARIES_CMSIS_DEVICE_MAXIM_MAX32570_INCLUDE_SIR_REGS_H_
