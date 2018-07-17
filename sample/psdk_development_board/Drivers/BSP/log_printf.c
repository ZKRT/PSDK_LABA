#include <stdio.h>
#include "log_printf.h"
#include <string.h>
#include <stdarg.h>

static uint8_t isLogInit = 0;

void LOG_Init(void)
{
    UART_Init(UART_NUM_1, 115200);
    isLogInit = 1;
}

void UART_Printf(const char *fmt, ...)
{
    if (isLogInit) {
        char buffer[LOG_STR_LEN_MAX];
        va_list args;
        va_start (args, fmt);
        vsnprintf(buffer, sizeof(buffer), fmt, args);
        UART_Write(UART_NUM_1, (uint8_t *)buffer, strlen(buffer) + 1);
        va_end(args);
    }
}

/************************** (C) COPYRIGHT DJI Innovations************ END OF FILE ***/
