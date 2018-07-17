
#ifndef __USART_H__
#define __USART_H__

#include "stm32f4xx.h"

#define USING_UART_PORT_1
#define USING_UART_PORT_2
#define USING_UART_PORT_3

#define UART_ERROR  -1

typedef enum {
    UART_NUM_1  = 1,
    UART_NUM_2  = 2,
    UART_NUM_3  = 3,
} E_UartNum;

void UART_Init(E_UartNum uartNum, uint32_t baudRate);
int UART_Read(E_UartNum uartNum, uint8_t *buf, uint16_t readSize);
int UART_Write(E_UartNum uartNum, const uint8_t *buf, uint16_t writeSize);

#endif
