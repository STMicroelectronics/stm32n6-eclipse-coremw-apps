/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32n6xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32n6xx_nucleo_usbpd_pwr.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/

/* USER CODE BEGIN ET */
extern HCD_HandleTypeDef hhcd_USB_OTG_HS1;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
#define RESET_USB_MACRO() do { \
    LL_AHB5_GRP1_ForceReset(0x00800000); \
    __HAL_RCC_USB1_OTG_HS_FORCE_RESET(); \
    __HAL_RCC_USB1_OTG_HS_PHY_FORCE_RESET(); \
    LL_RCC_HSE_SelectHSEDiv2AsDiv2Clock(); \
    LL_AHB5_GRP1_ReleaseReset(0x00800000); \
} while(0)
/* USER CODE END Private defines */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void MX_USB1_OTG_HS_HCD_Init(void);
void MX_GPDMA1_Init(void);
void MX_UCPD1_Init(void);
void MX_USART1_Init(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
