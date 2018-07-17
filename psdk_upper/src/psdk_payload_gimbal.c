/**
 *********************************************************************
 * @file    psdk_payload_gimbal.c
 * @brief
 * This file provides the API functions for handling the gimbal 
 * commands from the mobile app (ground) via PSDK port.
 * @history
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
 *********************************************************************
 */

/*********************************************************************
*       Includes
**********************************************************************
*/

#include <psdk.h>
#include <psdk_cmdset_define/psdk_cmdset_gimbal.h>

/*********************************************************************
*       Defines, configurable
**********************************************************************
*/


/*********************************************************************
*       Defines, fixed
**********************************************************************
*/

#define MODLE_FUNC_GIMCMD(name) \
static E_PsdkStat \
GimbalCmd_##name(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)\
{\
    T_PsdkGimbal##name##Ack ack;\
    ack.ackCode = PSDK_CMD_ACK_CODE_UNSUPPORT;\
    if (s_gimbalHandler.name != NULL) {\
        s_gimbalHandler.name((const T_PsdkGimbal##name##Req *) inProtData, &ack);\
    }\
    PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *) &ack, sizeof(T_PsdkGimbal##name##Ack));\
    return PSDK_STAT_OK;\
}

#define GIMCMD(name)    GimbalCmd_##name

/*********************************************************************
*       Types, local
**********************************************************************
*/


/*********************************************************************
*       Static data
**********************************************************************
*/

static T_PsdkGimbalHandler s_gimbalHandler;
static uint8_t s_isSupportGimbal = 0;

/*********************************************************************
*       Static functions`
**********************************************************************
*/

MODLE_FUNC_GIMCMD(GetGimbalState)

MODLE_FUNC_GIMCMD(SetGimbalMode)

MODLE_FUNC_GIMCMD(ReturnHead)

MODLE_FUNC_GIMCMD(ControlSpeed)

MODLE_FUNC_GIMCMD(StartCalibration)

//support state
static E_PsdkStat
GimbalCmd_SupportState(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)
{
    T_PsdkGimbalSupportStateAck ack;
    ack.ackCode = PSDK_CMD_ACK_CODE_OK;
    ack.isGimbalCmdSetSupport = s_isSupportGimbal;

    PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *) &ack, sizeof(T_PsdkGimbalSupportStateAck));
    return PSDK_STAT_OK;
}

//@formatter:off
static const T_PsdkProtCmdItem s_PayloadGimbalCmdList[] =
{
//support state
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_GIMBAL, PSDK_CAMERA_CMD_ID_SUPPORT_STATE, GIMCMD(SupportState)),

PSDK_PROT_CMD_ITEM(PSDK_CMDSET_GIMBAL, PSDK_GIMBAL_CMD_ID_GET_GIMBAL_PARAM, GIMCMD(GetGimbalState)),

PSDK_PROT_CMD_ITEM(PSDK_CMDSET_GIMBAL, PSDK_GIMBAL_CMD_ID_SET_GIMBAL_MODE, GIMCMD(SetGimbalMode)),

PSDK_PROT_CMD_ITEM(PSDK_CMDSET_GIMBAL, PSDK_GIMBAL_CMD_ID_RETURN_HEAD, GIMCMD(ReturnHead)),

PSDK_PROT_CMD_ITEM(PSDK_CMDSET_GIMBAL, PSDK_GIMBAL_CMD_ID_CONTROL_SPEED, GIMCMD(ControlSpeed)),

PSDK_PROT_CMD_ITEM(PSDK_CMDSET_GIMBAL, PSDK_GIMBAL_CMD_ID_START_CALIBRATION, GIMCMD(StartCalibration)),
};
//@formatter:on

/*********************************************************************
*       Export functions
**********************************************************************
*/
/** @brief Initialize PSDK's gimbal commands handling.
 *
 * @param psdkUpper:  pointer to the toplevel psdk struct
 * 
 * @param cameraHandler: pointer to the gimbal handler structure.
 *
 * @return an enum that represents a status of PSDK
 */
E_PsdkStat PsdkGimbal_Init(T_PsdkUpper *psdkUpper, const T_PsdkGimbalHandler *gimbalHandler)
{
    T_PsdkProtCmdSetHandle cmdSetHandle;

    s_gimbalHandler = *gimbalHandler;
    cmdSetHandle.cmdSet = PSDK_CMDSET_GIMBAL;
    cmdSetHandle.cmdList = s_PayloadGimbalCmdList;
    cmdSetHandle.cmdCount = sizeof(s_PayloadGimbalCmdList) / sizeof(T_PsdkProtCmdItem);

    s_isSupportGimbal = 1;

    return PsdkProto_RegCmdSetHandler(&(psdkUpper->protHandle), &cmdSetHandle);
}

/****************** (C) COPYRIGHT DJI Innovations *****END OF FILE****/
