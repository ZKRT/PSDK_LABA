#ifndef __LOG_PRINTF_H
#define __LOG_PRINTF_H

#include <dji_typedef.h>
#include "uart.h"

#define LOG_STR_LEN_MAX             128


extern void UART_Printf(const char *fmt, ...);

#define LOG(fmt, ...)       UART_Printf("[%s]" fmt "\r\n",__FUNCTION__,##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) UART_Printf("[Debug][%s]" fmt "\r\n", __FUNCTION__, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)  UART_Printf("[INFO][%s]" fmt "\r\n", __FUNCTION__, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  UART_Printf("[WARN][%s]" fmt "\r\n", __FUNCTION__, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) UART_Printf("[ERROR][%s]" fmt "\r\n", __FUNCTION__, ##__VA_ARGS__)

void LOG_Init(void);

#endif

/************************** (C) COPYRIGHT DJI Innovations************ END OF FILE ***/
