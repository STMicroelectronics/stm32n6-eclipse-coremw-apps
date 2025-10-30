/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file         stm32n6xx_hal_msp.c
  * @brief        This file provides code for the MSP Initialization
  *               and de-Initialization codes.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{

  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  /* System interrupt init*/

  HAL_PWREx_EnableVddIO4();

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/**
* @brief PCD MSP Initialization
* This function configures the hardware resources used in this example
* @param hhcd: PCD handle pointer
* @retval None
*/
void HAL_PCD_MspInit(PCD_HandleTypeDef* pcdHandle)
{

  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(pcdHandle->Instance==USB1_OTG_HS)
  {
  /* USER CODE BEGIN USB1_OTG_HS_MspInit 0 */

  /* USER CODE END USB1_OTG_HS_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USBOTGHS1;
    PeriphClkInitStruct.UsbOtgHs1ClockSelection = RCC_USBPHY1REFCLKSOURCE_HSE_DIRECT;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* Enable VDDUSB */
    HAL_PWREx_EnableVddUSB();

    /* USB1_OTG_HS clock enable */
    __HAL_RCC_USB1_OTG_HS_CLK_ENABLE();
    __HAL_RCC_USB1_OTG_HS_PHY_CLK_ENABLE();

    /* USB1_OTG_HS interrupt Init */
    HAL_NVIC_SetPriority(USB1_OTG_HS_IRQn, 7, 0);
    HAL_NVIC_EnableIRQ(USB1_OTG_HS_IRQn);
  /* USER CODE BEGIN USB1_OTG_HS_MspInit 1 */
    /* Reset USB peripherals and configure the HSE clock */
    RESET_USB_MACRO();

    /* Required few clock cycles before accessing USB PHY Controller Registers */
    HAL_Delay(1);

    USB1_HS_PHYC->USBPHYC_CR &= ~(0x7 << 0x4);

    USB1_HS_PHYC->USBPHYC_CR |= (0x1 << 16) |
                                (0x2 << 4)  |
                                (0x1 << 2)  |
                                 0x1U;

    __HAL_RCC_USB1_OTG_HS_PHY_RELEASE_RESET();

    /* Required few clock cycles before Releasing Reset */
    HAL_Delay(1);

    __HAL_RCC_USB1_OTG_HS_RELEASE_RESET();
  /* USER CODE END USB1_OTG_HS_MspInit 1 */
  }
}

/**
* @brief PCD MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hhcd: PCD handle pointer
* @retval None
*/
void HAL_PCD_MspDeInit(PCD_HandleTypeDef* pcdHandle)
{

  if(pcdHandle->Instance==USB1_OTG_HS)
  {
  /* USER CODE BEGIN USB1_OTG_HS_MspDeInit 0 */

  /* USER CODE END USB1_OTG_HS_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USB1_OTG_HS_CLK_DISABLE();
    __HAL_RCC_USB1_OTG_HS_PHY_CLK_DISABLE();

    /* Disable VDDUSB */
    HAL_PWREx_DisableVddUSB();

    /* USB1_OTG_HS interrupt Deinit */
    HAL_NVIC_DisableIRQ(USB1_OTG_HS_IRQn);
  /* USER CODE BEGIN USB1_OTG_HS_MspDeInit 1 */

  /* USER CODE END USB1_OTG_HS_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
