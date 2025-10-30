/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_usbx_host.h
  * @brief   USBX Host applicative header file
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
#ifndef __APP_USBX_HOST_H__
#define __APP_USBX_HOST_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ux_api.h"
#include "main.h"
#include "ux_host_mouse.h"
#include "ux_host_keyboard.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ux_hcd_stm32.h"
#if defined(_TRACE)
#include "usbpd_trace.h"
#endif /* _TRACE */
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/

/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#if defined(_TRACE)
#define DPM_USER_DEBUG_TRACE_SIZE       50u

#define USBH_UsrLog(...)  do {                                                             \
    char _str[DPM_USER_DEBUG_TRACE_SIZE];                                                  \
    uint8_t _size = snprintf(_str, DPM_USER_DEBUG_TRACE_SIZE, __VA_ARGS__);                \
    if (_size < DPM_USER_DEBUG_TRACE_SIZE)                                                 \
      USBPD_TRACE_Add(USBPD_TRACE_DEBUG, 0, 0, (uint8_t*)_str, strlen(_str));              \
    else                                                                                   \
      USBPD_TRACE_Add(USBPD_TRACE_DEBUG, 0, 0, (uint8_t*)_str, DPM_USER_DEBUG_TRACE_SIZE); \
  } while(0)

#define  USBH_ErrLog(...)   do {                                                           \
    char _str[DPM_USER_DEBUG_TRACE_SIZE];                                                  \
    uint8_t _size = snprintf(_str, DPM_USER_DEBUG_TRACE_SIZE, __VA_ARGS__);                \
    if (_size < DPM_USER_DEBUG_TRACE_SIZE)                                                 \
      USBPD_TRACE_Add(USBPD_TRACE_DEBUG, 0, 0, (uint8_t*)_str, strlen(_str));              \
    else                                                                                   \
      USBPD_TRACE_Add(USBPD_TRACE_DEBUG, 0, 0, (uint8_t*)_str, DPM_USER_DEBUG_TRACE_SIZE); \
  } while(0)
#else
#define USBH_UsrLog(...)   printf(__VA_ARGS__);\
                           printf("\n");

#define USBH_ErrLog(...)   printf("ERROR: ") ;\
                           printf(__VA_ARGS__);\
                           printf("\n");
#endif /* _TRACE */
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
UINT MX_USBX_Host_Init(VOID);
UINT MX_USBX_Host_Stack_Init(VOID);
UINT MX_USBX_Host_Stack_DeInit(VOID);

/* USER CODE BEGIN EFP */
VOID USBX_APP_Host_Init(VOID);
VOID USBX_Host_Process(VOID *arg);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */


/* USER CODE BEGIN 1 */
typedef enum
{
  STOP_USB_HOST = 1,
  START_USB_HOST,
} USB_MODE_STATE;
/* USER CODE END 1 */

#ifdef __cplusplus
}
#endif
#endif /* __APP_USBX_HOST_H__ */
