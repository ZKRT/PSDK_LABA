/**
  ******************************************************************************
  * @file    app_config.h
  * @version V0.0.0
  * @date    2017/11/20
  * @brief   
  *
  * @copyright 2017 DJI. All right reserved.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DEMO_RTOS_RTTHREAD_APP_CONFIG_H
#define DEMO_RTOS_RTTHREAD_APP_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/


/* Defines, fixed ------------------------------------------------------------*/

#define PSDK_CHANNEL_UART       0
#define PSDK_CHANNEL_CAN        1

/* Defines, configurable -----------------------------------------------------*/

#define PSDK_DEMO_CHANNEL_USE   PSDK_CHANNEL_UART

#define PSDK_UART_REC_BUF_LEN       1024
#define PSDK_CAN_RX_REC_BUF_LEN     100

#define PSDK_UART_NUM               UART_NUM_2
    
/* Exported types ------------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif //DEMO_RTOS_RTTHREAD_APP_CONFIG_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
