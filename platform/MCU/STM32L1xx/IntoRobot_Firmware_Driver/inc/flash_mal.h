/**
 ******************************************************************************
 * @file    flash_mal.h
 * @author  Satish Nair
 * @version V1.0.0
 * @date    30-Jan-2015
 * @brief   Header for flash media access layer
 ******************************************************************************
 Copyright (c) 2015 Particle Industries, Inc.  All rights reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation, either
 version 3 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_MAL_H
#define __FLASH_MAL_H

#include "hw_config.h"
#include "flash_device_hal.h"

/* Includes ------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macros ------------------------------------------------------------*/
#ifndef INTERNAL_FLASH_SIZE
#   error "INTERNAL_FLASH_SIZE not defined"
#endif

/* Internal Flash memory address where various firmwares are located */
#ifndef INTERNAL_FLASH_START
#define INTERNAL_FLASH_START        ((uint32_t)0x08000000)
#endif
/* Internal Flash End Address */
#define INTERNAL_FLASH_END      ((uint32_t)INTERNAL_FLASH_START+INTERNAL_FLASH_SIZE)	//For 512KB Internal Flash

//Bootloader firmware at the start of internal flash
#define USB_DFU_ADDRESS             INTERNAL_FLASH_START
//Main firmware begin address after 20KB (5 x 4K) from start of flash
#define CORE_FW_ADDRESS             ((uint32_t)0x08006000)
#define APP_START_MASK              ((uint32_t)0x2FFFC000)

/* Internal Flash page size */
#define INTERNAL_FLASH_PAGE_SIZE      ((uint32_t)256)         //256Byte
#define INTERNAL_FLASH_SECTOR_SIZE    ((uint32_t)0x1000)      //4k Byte

#define USER_FIRMWARE_IMAGE_LOCATION CORE_FW_ADDRESS
#define FIRMWARE_IMAGE_SIZE           0x1A000      //104K (firmware size)
#define BOOTLOADER_IMAGE_SIZE         0x5000       //20K (bootloader size)

#ifdef USE_SERIAL_FLASH
/* External Flash memory address where Factory programmed core firmware is located */
#define EXTERNAL_FLASH_FAC_ADDRESS  ((uint32_t)0x00)
/* External Flash memory address where OTA upgraded core firmware will be saved */
#define EXTERNAL_FLASH_OTA_ADDRESS  ((uint32_t)(EXTERNAL_FLASH_FAC_ADDRESS + FIRMWARE_IMAGE_SIZE))
/* External Flash memory address where OTA upgraded bootloader will be saved */
#define EXTERNAL_FLASH_OTA_BOOTLOADER_ADDRESS  ((uint32_t)(EXTERNAL_FLASH_OTA_ADDRESS + FIRMWARE_IMAGE_SIZE))
#endif

#if FIRMWARE_IMAGE_SIZE > INTERNAL_FLASH_SIZE
#   error "FIRMWARE_IMAGE_SIZE too large to fit into internal flash"
#endif

/* Bootloader Flash regions that needs to be protected: 0x08000000 - 0x08004FFF */
#define BOOTLOADER_FLASH_PAGES      (OB_WRP1_PAGES0TO15|OB_WRP1_PAGES16TO31|OB_WRP1_PAGES32TO47|OB_WRP1_PAGES48TO63|OB_WRP1_PAGES64TO79)


void FLASH_WriteProtection_Enable(uint32_t FLASH_WRP_Sectors);
void FLASH_WriteProtection_Disable(uint32_t FLASH_WRP_Sectors);
uint32_t FLASH_PagesMask(uint32_t imageSize, uint32_t pageSize);


#include "flash_access.h"

#ifdef __cplusplus
}
#endif


#endif  /*__FLASH_MAL_H*/
