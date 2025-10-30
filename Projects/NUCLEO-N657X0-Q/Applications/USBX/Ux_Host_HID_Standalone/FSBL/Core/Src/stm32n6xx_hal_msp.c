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

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/**
* @brief UART MSP Initialization
* This function configures the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
    PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_IC9;
    PeriphClkInitStruct.ICSelection[RCC_IC9].ClockSelection = RCC_ICCLKSOURCE_PLL2;
    PeriphClkInitStruct.ICSelection[RCC_IC9].ClockDivider = 16;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PE5     ------> USART1_TX
    PE6     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

/**
* @brief UART MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PE5     ------> USART1_TX
    PE6     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_5|GPIO_PIN_6);

  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/**
* @brief HCD MSP Initialization
* This function configures the hardware resources used in this example
* @param hhcd: HCD handle pointer
* @retval None
*/
void HAL_HCD_MspInit(HCD_HandleTypeDef* hcdHandle)
{

  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(hcdHandle->Instance==USB1_OTG_HS)
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
    /* Peripheral clock enable */
    __HAL_RCC_USB1_OTG_HS_CLK_ENABLE();

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
* @brief HCD MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hhcd: HCD handle pointer
* @retval None
*/
void HAL_HCD_MspDeInit(HCD_HandleTypeDef* hcdHandle)
{

  if(hcdHandle->Instance==USB1_OTG_HS)
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
