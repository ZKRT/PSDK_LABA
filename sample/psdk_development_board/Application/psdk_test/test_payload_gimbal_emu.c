/*********************************************************************
*       Includes
**********************************************************************
*/
#include <psdk.h>
#include "test_payload_gimbal_emu.h"

/*********************************************************************
*       Static data
**********************************************************************
*/

static uint8_t gimbalMode = PSDK_GIMBAL_GIMBAL_MODE_FPV;

static uint8_t isYawLimit = 0;
static uint8_t isRollLimit = 0;
static uint8_t isPitchLimit = 0;

static int16_t pitch = 0;
static int16_t roll = 0;
static int16_t yaw = 0;

/*********************************************************************
*       Static functions
**********************************************************************
*/

/*********************************************************************
*       Export functions
**********************************************************************
*/

void GimbalEmu_GetGimbalParam(const T_PsdkGimbalGetGimbalStateReq *req, T_PsdkGimbalGetGimbalStateAck *ack)
{
//    PSDK_LOG_DEBUG("Get Gimbal Param");

    //get gimbal param
    ack->gimbalMode = gimbalMode;
    ack->isMountedUpwards = 0;
    ack->isPitchLimit = isPitchLimit;
    ack->isRollLimit = isRollLimit;
    ack->isYawLimit = isYawLimit;

    ack->pitch = pitch;
    ack->roll = roll;
    ack->yaw = yaw;

    //ack code
    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void GimbalEmu_SetGimbalMode(const T_PsdkGimbalSetGimbalModeReq *req, T_PsdkGimbalSetGimbalModeAck *ack)
{
    PSDK_LOG_DEBUG("Set Gimbal Mode");

    gimbalMode = req->gimbalMode;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void GimbalEmu_ReturnHead(const T_PsdkGimbalReturnHeadReq *req, T_PsdkGimbalReturnHeadAck *ack)
{
    PSDK_LOG_DEBUG("Return Head");

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void GimbalEmu_ControlSpeed(const T_PsdkGimbalControlSpeedReq *req, T_PsdkGimbalControlSpeedAck *ack)
{
    PSDK_LOG_DEBUG("Control Speed");

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

const T_PsdkGimbalHandler g_testGimbalHandler = {
        .GetGimbalState = GimbalEmu_GetGimbalParam,
        .SetGimbalMode = GimbalEmu_SetGimbalMode,
        .ReturnHead = GimbalEmu_ReturnHead,
        .ControlSpeed = GimbalEmu_ControlSpeed,
};

/****************** (C) COPYRIGHT DJI Innovations *****END OF FILE****/
