/**
  ******************************************************************************
  * @file    led_button_switch.h
  * @version V0.0.0
  * @date    2017/11/17
  * @brief
  *
  * @copyright 2017 DJI. All right reserved.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DEMO_RTOS_RTTHREAD_LED_BUTTON_SWITCH_H
#define DEMO_RTOS_RTTHREAD_LED_BUTTON_SWITCH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <dji_typedef.h>

/* Defines, configurable -----------------------------------------------------*/

/* Defines, fixed ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef enum {
    LED1_GREEN = 0,
    LED2_RED,
    LED3_BLUE,
} E_LED;

typedef enum {
    LED_OPT_ON = 0,
    LED_OPT_OFF,
    LED_OPT_TOGGLE,
} E_LEDOption;

typedef enum {
    BUTTON1 = 0,
    BUTTON2,
} E_Button;

typedef void (*ButtonPressCallbackFunc)(E_Button button);

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

void LED_Init(void);
void LED_Control(E_LED led, E_LEDOption ledOption);

void UART_SW_Init(void);
void UART_SW_On(void);
void UART_SW_Off(void);

void CAN_SW_Init(void);
void CAN_SW_On(void);
void CAN_SW_Off(void);

void Button_Init(void);
void Button_SetDownPressCallback(ButtonPressCallbackFunc callbackFunc);
void Button_StartUpdate(void);

#ifdef __cplusplus
}
#endif

#endif //DEMO_RTOS_RTTHREAD_LED_BUTTON_SWITCH_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
