#ifndef M4_TANSFERRING_OS_UTIL_H
#define M4_TANSFERRING_OS_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cmsis_os.h>
#include <FreeRTOS.h>

#define OS_GET_TIME_MS  (osKernelSysTick() * 1000 / osKernelSysTickFrequency)
#define OS_MALLOC       pvPortMalloc
#define OS_FREE         vPortFree
#define OS_DELAY        osDelay
    
#ifdef __cplusplus
}
#endif

#endif //M4_TANSFERRING_OS_UTIL_H

/****************** (C) COPYRIGHT DJI Innovations *****END OF FILE****/
