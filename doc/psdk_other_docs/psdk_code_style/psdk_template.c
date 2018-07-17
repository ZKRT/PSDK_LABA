/**
  ******************************************************************************
  * @file    psdk_template.c
  * @version V0.0.0
  * @date    10-August-2017
  * @brief   This file to indicate psdk coding style and comment style.
  *
  * @copyright 2017 DJI. All right reserved.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "psdk_template.h"


/* Private define ------------------------------------------------------------*/
#define MAX_PACKAGE_LEN  256

/* Private variables ---------------------------------------------------------*/
uint8_t s_SendBuffer[PSDK_TEMPLATE_MAX_BUFFER_SIZE];

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
static int PsdkTemplate_PrivateSend(const uint8_t *buffer, uint16_t len)
{
    return len;
}

/* Exported functions --------------------------------------------------------*/
void PsdkTemplate_Init(void)
{
}

int PsdkTemplate_Send(const uint8_t *buffer, uint16_t len)
{
    uint16_t realLen;

    if (len > MAX_PACKAGE_LEN) {
        realLen = MAX_PACKAGE_LEN;
    }

    PsdkTemplate_PrivateSend(buffer, len);
    return realLen;
}

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
