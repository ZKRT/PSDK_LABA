/**
 ******************************************************************************
 * @file    psdk_msg_subcribe.c
 * @version V0.0.0
 * @date    2017/11/10
 * @brief
 * This file provides the API functions for receiving the push data from 
 * PSDK port, as well handling callback functions.
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

/* Includes ------------------------------------------------------------------*/
#include "psdk_msg_subcribe.h"
#include <string.h>

/* Private define ------------------------------------------------------------*/

/*!Private function prototypes 
 */
static E_PsdkStat
MsgPushCmd_PushBandWidth(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData);
static E_PsdkStat
MsgPushCmd_PushAttitude(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData);	
static E_PsdkStat
MsgPushCmd_PushBatteryInfo(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData);
static E_PsdkStat
MsgPushCmd_PushGpsInfo(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData);
static E_PsdkStat
MsgPushCmd_PushUavState(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData);
static E_PsdkStat
MsgPushCmd_PushAppDateTime(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData);


/*!Private variables
 */
static T_PsdkPushDataMsgCallbackList s_PushDataMsgCallbackList;
//@formatter:off
static const T_PsdkProtCmdItem s_PushDataMsgSubProtCmdList[] =
{
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_DATA_PUSH, PSDK_DATAPUSH_CMD_ID_PUSH_BANDWIDTH, MsgPushCmd_PushBandWidth),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_DATA_PUSH, PSDK_DATAPUSH_CMD_ID_PUSH_ATTITUDE, MsgPushCmd_PushAttitude),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_DATA_PUSH, PSDK_DATAPUSH_CMD_ID_PUSH_BATTERY_INFO, MsgPushCmd_PushBatteryInfo),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_DATA_PUSH, PSDK_DATAPUSH_CMD_ID_PUSH_GPS_INFO, MsgPushCmd_PushGpsInfo),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_DATA_PUSH, PSDK_DATAPUSH_CMD_ID_PUSH_UAV_STATE, MsgPushCmd_PushUavState),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_DATA_PUSH, PSDK_DATAPUSH_CMD_ID_PUSH_APP_DATETIME, MsgPushCmd_PushAppDateTime),
};
//@formatter:on

/* Exported functions --------------------------------------------------------*/
/** @brief Initialize the psdk's push data functionality
 *
 * @param psdkUpper:  pointer to the toplevel psdk struct
 * 
 * @return an enum that represents a status of PSDK
 */
E_PsdkStat PsdkMsgSub_Init(T_PsdkUpper *psdkUpper)
{
    T_PsdkProtCmdSetHandle cmdSetHandle;

    memset(&s_PushDataMsgCallbackList, 0x00, sizeof(s_PushDataMsgCallbackList));
    cmdSetHandle.cmdSet = PSDK_CMDSET_DATA_PUSH;
    cmdSetHandle.cmdList = s_PushDataMsgSubProtCmdList;
    cmdSetHandle.cmdCount = sizeof(s_PushDataMsgSubProtCmdList) / sizeof(T_PsdkProtCmdItem);

    return PsdkProto_RegCmdSetHandler(&(psdkUpper->protHandle), &cmdSetHandle);
}

/** @brief Register the callback functions for push data
 * by the user
 *
 * @param psdkUpper:  pointer to the top-level psdk struct
 * 
 * @param PushDataMsgCallbackList: pointer to user's callback functions list
 *
 * @return an enum that represents a status of PSDK
 */
E_PsdkStat PsdkMsgSub_RegMsgCallbackList(T_PsdkUpper *psdkUpper, const T_PsdkPushDataMsgCallbackList *PushDataMsgCallbackList)
{
    memcpy(&s_PushDataMsgCallbackList, PushDataMsgCallbackList, sizeof(T_PsdkPushDataMsgCallbackList));

    return PSDK_STAT_OK;
}

/* Private functions ---------------------------------------------------------*/
static E_PsdkStat
MsgPushCmd_PushBandWidth(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)
{
    if (s_PushDataMsgCallbackList.bandWidthMsgCallback != NULL) {
        s_PushDataMsgCallbackList.bandWidthMsgCallback((const T_BandWidthMsg *) inProtData);
    }
    return PSDK_STAT_OK;
}

static E_PsdkStat
MsgPushCmd_PushAttitude(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)
{
    if (s_PushDataMsgCallbackList.uavAttitudeMsgCallback != NULL) {
        s_PushDataMsgCallbackList.uavAttitudeMsgCallback((const T_UavAttitudeMsg *) inProtData);
    }
    return PSDK_STAT_OK;
}

static E_PsdkStat
MsgPushCmd_PushBatteryInfo(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)
{
    if (s_PushDataMsgCallbackList.batteryInfoMsgCallback != NULL) {
        s_PushDataMsgCallbackList.batteryInfoMsgCallback((const T_BatteryInfoMsg *) inProtData);
    }
    return PSDK_STAT_OK;
}

static E_PsdkStat
MsgPushCmd_PushGpsInfo(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)
{
    if (s_PushDataMsgCallbackList.gpsInfoMsgCallback != NULL) {
        s_PushDataMsgCallbackList.gpsInfoMsgCallback((const T_GPSInfoMsg *) inProtData);
    }
    return PSDK_STAT_OK;
}

static E_PsdkStat
MsgPushCmd_PushUavState(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)
{
    if (s_PushDataMsgCallbackList.uavStateMsgCallback != NULL) {
        s_PushDataMsgCallbackList.uavStateMsgCallback((const T_UavStateMsg *) inProtData);
    }
    return PSDK_STAT_OK;
}

static E_PsdkStat
MsgPushCmd_PushAppDateTime(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)
{
    if (s_PushDataMsgCallbackList.appDateTimeMsgCallback != NULL) {
        s_PushDataMsgCallbackList.appDateTimeMsgCallback((const T_AppDateTimeMsg *) inProtData);
    }
    return PSDK_STAT_OK;
}

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
