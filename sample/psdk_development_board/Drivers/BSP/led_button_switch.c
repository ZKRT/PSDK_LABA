/**
  ******************************************************************************
  * @file    led_button_switch.c
  * @version V0.0.0
  * @date    2017/11/17
  * @brief
  *
  * @copyright 2017 DJI. All right reserved.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "led_button_switch.h"
#include <stm32f4xx.h>
#include "log_printf.h"
#include "flash.h"
#include <os_util.h>


/* Private define ------------------------------------------------------------*/
#define LED1_RCC    RCC_AHB1Periph_GPIOB //run
#define LED1_PORT   GPIOB
#define LED1_PIN    GPIO_Pin_1

#define LED2_RCC    RCC_AHB1Periph_GPIOB //uart api
#define LED2_PORT   GPIOB
#define LED2_PIN    GPIO_Pin_0

#define LED3_RCC    RCC_AHB1Periph_GPIOB //can
#define LED3_PORT   GPIOB
#define LED3_PIN    GPIO_Pin_0

#define UART_SW_RCC         RCC_AHB1Periph_GPIOE
#define UART_SW_PORT        GPIOE
#define UART_SW_PIN         GPIO_Pin_7

#define CAN_SW_RCC          RCC_AHB1Periph_GPIOE
#define CAN_SW_PORT         GPIOE
#define CAN_SW_PIN          GPIO_Pin_10

#define BUTTON1_RCC         RCC_AHB1Periph_GPIOA
#define BUTTON1_PORT        GPIOA
#define BUTTON1_PIN         GPIO_Pin_0
#define BUTTON1_EXITPORT    EXTI_PortSourceGPIOA
#define BUTTON1_EXITPIN     EXTI_PinSource0
#define BUTTON1_EXITLINE    EXTI_Line0

#define BUTTON2_RCC         RCC_AHB1Periph_GPIOA
#define BUTTON2_PORT        GPIOA
#define BUTTON2_PIN         GPIO_Pin_1
#define BUTTON2_EXITPORT    EXTI_PortSourceGPIOA
#define BUTTON2_EXITPIN     EXTI_PinSource1
#define BUTTON2_EXITLINE    EXTI_Line1

#define BUTTTON_IRQn0        EXTI0_IRQn
#define BUTTON_IRQHandler0   EXTI0_IRQHandler

#define BUTTTON_IRQn1        EXTI1_IRQn
#define BUTTON_IRQHandler1   EXTI1_IRQHandler

#define DEFAULT_SETTINGS    0xFFFFFFFF
/* Private variables ---------------------------------------------------------*/
static ButtonPressCallbackFunc s_btPressCallback = NULL;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
extern uint32_t can_uart_sw_settings;

void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIO Periph clock enable */
    RCC_AHB1PeriphClockCmd(LED1_RCC, ENABLE);
    RCC_AHB1PeriphClockCmd(LED2_RCC, ENABLE);
    RCC_AHB1PeriphClockCmd(LED3_RCC, ENABLE);

    /* Configure GPIO_InitStructure */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_InitStructure.GPIO_Pin = LED1_PIN;
    GPIO_Init(LED1_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LED2_PIN;
    GPIO_Init(LED2_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LED3_PIN;
    GPIO_Init(LED3_PORT, &GPIO_InitStructure);
}

void LED_Control(E_LED led, E_LEDOption eLedOption)
{
    GPIO_TypeDef *ledPort;
    uint16_t ledPin;

    if (led == LED1_GREEN) {
        ledPort = LED1_PORT;
        ledPin = LED1_PIN;
    } else if (led == LED2_RED) {
        ledPort = LED2_PORT;
        ledPin = LED2_PIN;
    } else if (led == LED3_BLUE) {
        ledPort = LED3_PORT;
        ledPin = LED3_PIN;
    } else {
        return;
    }

    if (eLedOption == LED_OPT_ON) {
        GPIO_ResetBits(ledPort, ledPin);
    } else if (eLedOption == LED_OPT_OFF){
        GPIO_SetBits(ledPort, ledPin);
    } else if (eLedOption == LED_OPT_TOGGLE) {
        if (GPIO_ReadOutputDataBit(ledPort, ledPin) == 1) {
            GPIO_ResetBits(ledPort, ledPin);
        } else {
            GPIO_SetBits(ledPort, ledPin);
        }
    }
}

void UART_SW_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIO Periph clock enable */
    RCC_AHB1PeriphClockCmd(UART_SW_RCC, ENABLE);

    /* Configure GPIO_InitStructure */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin = UART_SW_PIN;

    GPIO_Init(UART_SW_PORT, &GPIO_InitStructure);
}

void UART_SW_On(void)
{
    GPIO_SetBits(UART_SW_PORT, UART_SW_PIN);
}

void UART_SW_Off(void)
{
    GPIO_ResetBits(UART_SW_PORT, UART_SW_PIN);
}

void CAN_SW_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIO Periph clock enable */
    RCC_AHB1PeriphClockCmd(CAN_SW_RCC, ENABLE);

    /* Configure GPIO_InitStructure */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin = CAN_SW_PIN;

    GPIO_Init(CAN_SW_PORT, &GPIO_InitStructure);
}

void CAN_SW_On(void)
{
    GPIO_SetBits(CAN_SW_PORT, CAN_SW_PIN);
}

void CAN_SW_Off(void)
{
    GPIO_ResetBits(CAN_SW_PORT, CAN_SW_PIN);
}

void Button_StartUpdate(void)
{
    // if (can_uart_sw_settings == DEFAULT_SETTINGS)
    // {
    //     UART_SW_On();
    //     CAN_SW_On();
    // }
    // else
    // {
    //     UART_SW_Off();
    //     CAN_SW_Off();
    // }
}

void Button_PressCallback(E_Button button)
{
    static uint32_t lastButtion2Time = 0;
    
    if (button == BUTTON1)
    {
        //reserved
    }
    else if (button == BUTTON2)
    {
        if (OS_GET_TIME_MS - lastButtion2Time < 50) {
            return ;
        } else {
            lastButtion2Time = OS_GET_TIME_MS;
        }
        
        can_uart_sw_settings = ~can_uart_sw_settings;
    }
}

void Button_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    s_btPressCallback = Button_PressCallback;

    /* GPIO Periph clock enable */
    RCC_AHB1PeriphClockCmd(BUTTON1_RCC, ENABLE);
    RCC_AHB1PeriphClockCmd(BUTTON2_RCC, ENABLE);
    /* Enable SYSCFG clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    /* Configure PA0 pin as input floating */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

    GPIO_InitStructure.GPIO_Pin = BUTTON1_PIN;
    GPIO_Init(BUTTON1_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BUTTON2_PIN;
    GPIO_Init(BUTTON2_PORT, &GPIO_InitStructure);

    /* Connect EXTI pin */
    SYSCFG_EXTILineConfig(BUTTON1_EXITPORT, BUTTON1_EXITPIN);
    SYSCFG_EXTILineConfig(BUTTON2_EXITPORT, BUTTON2_EXITPIN);

    /* Configure EXTI Line */
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;

    EXTI_InitStructure.EXTI_Line = BUTTON1_EXITLINE;
    EXTI_Init(&EXTI_InitStructure);

    EXTI_InitStructure.EXTI_Line = BUTTON2_EXITLINE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable and set EXTI Line0 Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = BUTTTON_IRQn0;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = BUTTTON_IRQn1;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0E;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0E;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void Button_SetDownPressCallback(ButtonPressCallbackFunc callbackFunc)
{
    s_btPressCallback = callbackFunc;
}

// void BUTTON_IRQHandler(void)
// {
//     if (EXTI_GetITStatus(BUTTON1_EXITLINE) != RESET)
//     {
//         /* button1 */
//         if(NULL != s_btPressCallback)
//             s_btPressCallback(BUTTON1);

//         /* Clear the EXTI line pending bit */
//         EXTI_ClearITPendingBit(BUTTON1_EXITLINE);
//     }
//     else if (EXTI_GetITStatus(BUTTON2_EXITLINE) != RESET)
//     {
//         /* button2 */
//         if(NULL != s_btPressCallback)
//             s_btPressCallback(BUTTON2);

//         /* Clear the EXTI line pending bit */
//         EXTI_ClearITPendingBit(BUTTON2_EXITLINE);
//     }
// }

void BUTTON_IRQHandler0(void)
{
    if (EXTI_GetITStatus(BUTTON1_EXITLINE) != RESET)
    {
        /* button1 */
        if(NULL != s_btPressCallback)
            s_btPressCallback(BUTTON1);

        /* Clear the EXTI line pending bit */
        EXTI_ClearITPendingBit(BUTTON1_EXITLINE);
    }
}
void BUTTON_IRQHandler1(void)
{
    if (EXTI_GetITStatus(BUTTON2_EXITLINE) != RESET)
    {
        /* button2 */
        if(NULL != s_btPressCallback)
            s_btPressCallback(BUTTON2);

        /* Clear the EXTI line pending bit */
        EXTI_ClearITPendingBit(BUTTON2_EXITLINE);
    }
}
/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
