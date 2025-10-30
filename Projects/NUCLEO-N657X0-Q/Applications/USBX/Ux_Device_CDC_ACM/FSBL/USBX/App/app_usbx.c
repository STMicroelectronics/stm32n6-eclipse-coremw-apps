/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_usbx.c
  * @brief   USBX applicative file
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
#include "app_usbx.h"

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN UX_Pool_Buffer */
#if defined ( __ICCARM__ ) /* IAR Compiler */
#pragma location = ".UsbxPoolSection"
#else /* GNU and AC6 Compiler */
__attribute__((section(".UsbxPoolSection")))
#endif
/* USER CODE END UX_Pool_Buffer */
#if defined ( __ICCARM__ )
#pragma data_alignment=4
#endif
static __ALIGNED(4) UCHAR ux_device_memory_buffer[USBX_MEMORY_STACK_SIZE];

/**
  * @brief  Application USBX Initialization.
  * @param  memory_ptr: memory pointer
  * @retval status
  */
UINT MX_USBX_Init(VOID)
{
  UINT ret = UX_SUCCESS;

  UCHAR *pointer;
  pointer = ux_device_memory_buffer;

  /* USER CODE BEGIN MX_USBX_Init0 */

  /* USER CODE END MX_USBX_Init0 */

  /* Initialize USBX Memory */
  if (ux_system_initialize(pointer, USBX_MEMORY_STACK_SIZE, UX_NULL, 0) != UX_SUCCESS)
  {
    /* USER CODE BEGIN USBX_SYSTEM_INITIALIZE_ERROR */
    return UX_ERROR;
    /* USER CODE END USBX_SYSTEM_INITIALIZE_ERROR */
  }

  ret = MX_USBX_Device_Init();
  if(ret != UX_SUCCESS)
  {
  /* USER CODE BEGIN MX_USBX_Device_Init_Error */
    while(1)
    {
    }
  /* USER CODE END MX_USBX_Device_Init_Error */
  }

  /* USER CODE BEGIN MX_USBX_Init1 */

  /* USER CODE END MX_USBX_Init1 */

  return ret;
}
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
