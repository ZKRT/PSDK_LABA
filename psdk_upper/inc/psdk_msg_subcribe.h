/**
 ******************************************************************************
 * @file    psdk_msg_subcribe.h
 * @version V0.0.0
 * @date    2017/11/10
 * @brief
 * This is the header file for "psdk_msg_subcribe.c", defining the struct and 
 * (exported) function prototypes. 
 *
 * @Copyright (c) 2017-2018 DJI. All rights reserved.
 *
 * All information contained herein is, and remains, the property of DJI.
 * The intellectual and technical concepts contained herein are proprietary
 * to DJI and may be covered by U.S. and foreign patents, patents in process,
 * and protected by trade secret or copyright law.  Dissemination of this
 * information, including but not limited to data and other proprietary
 * material(s) incorporated within the information, in any form, is strictly
 * prohibited without the express written consent of DJI.
 *
 * If you receive this source code without DJI’s authorization, you may not
 * further disseminate the information, and you must immediately remove the
 * source code and notify DJI of its removal. DJI reserves the right to pursue
 * legal actions against you for any loss(es) or damage(s) caused by your
 * failure to do so.
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PSDK_MSG_SUBCRIBE_H
#define PSDK_MSG_SUBCRIBE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "psdk_upper.h"
#include "psdk_cmdset.h"

/* Defines, configurable -----------------------------------------------------*/

/* Defines, fixed ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/*! @brief callback function list for receiving push data.
 *
 * @details This struct type is used to define a list structure that 
 * includes all the callback functions that you can design for the push data:
 * 1. PSDK communication status
 * 2. Vehicle attitude
 * 3. Battery information
 * 4. GPS information
 * 5. UAV state
   6. APP time and date  
 *
 * @note You must specify the message rate through DJI Assistant 2 for the push 
 * data.
 */
typedef struct _PsdkPushDataMsgCallbackList {
    void (*bandWidthMsgCallback)(const T_BandWidthMsg *);
    void (*uavAttitudeMsgCallback)(const T_UavAttitudeMsg *);
    void (*batteryInfoMsgCallback)(const T_BatteryInfoMsg *);
    void (*gpsInfoMsgCallback)(const T_GPSInfoMsg *);
    void (*uavStateMsgCallback)(const T_UavStateMsg *);
    void (*appDateTimeMsgCallback)(const T_AppDateTimeMsg *);
} T_PsdkPushDataMsgCallbackList;

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
E_PsdkStat PsdkMsgSub_Init(T_PsdkUpper *psdkUpper);
E_PsdkStat PsdkMsgSub_RegMsgCallbackList(T_PsdkUpper *psdkUpper, const T_PsdkPushDataMsgCallbackList *PushDataMsgCallbackList);

#ifdef __cplusplus
}
#endif

#endif //PSDK_MSG_SUBCRIBE_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/

