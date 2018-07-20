/**
  ******************************************************************************
  * @file    main.c
  * @version V0.0.0
  * @date    March 2018
  * @brief   
  * Main program body.
  * @copyright 2018 DJI. All right reserved.
  ******************************************************************************
  */


#include <psdk.h>
#include "sys.h"
#include "application.h"

osThreadId runIndicateTaskHandle;
osThreadId processRecDataTaskHandle;
osThreadId psdkTestTaskHandle;

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Init */ 
    Sys_Init();

    application_init();

    /* definition of Threads  */
    osThreadDef(n_indicateTask, RunIndicateTask, osPriorityNormal, 0, 128);
    osThreadDef(n_psdkRecTask, PrcocessPsdkRecTask, osPriorityNormal, 0, 1024);
    osThreadDef(n_psdkTestTask, PsdkTestTask, osPriorityAboveNormal, 0, 1024);

    /* Start threads */
    runIndicateTaskHandle = osThreadCreate(osThread(n_indicateTask), NULL);
    processRecDataTaskHandle = osThreadCreate(osThread(n_psdkRecTask), NULL);
    psdkTestTaskHandle = osThreadCreate(osThread(n_psdkTestTask), NULL);

    /* Start scheduler */
    osKernelStart();

    /*Taken by the scheduler */
    for (;;);

}



