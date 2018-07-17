/**
 ********************************************************************
 * @file    psdk_payload_camera.c
 * @brief
 * This file provides the API functions  for handling the camera 
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

#include "psdk_payload_camera.h"
#include "string.h"
#include <psdk_ack_code.h>
#include <psdk.h>
#include <psdk_cmdset_define/psdk_cmdset_camera.h>

/*********************************************************************
*       Defines, configurable
**********************************************************************
*/


/*********************************************************************
*       Defines, fixed
**********************************************************************
*/

#define MODLE_FUNC_CAMCMD(name) \
static E_PsdkStat \
CameraCmd_##name(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)\
{\
    T_PsdkCamera##name##Ack ack;\
    ack.ackCode = PSDK_CMD_ACK_CODE_UNSUPPORT;\
    if (s_cameraHandler.name != NULL) {\
        s_cameraHandler.name((const T_PsdkCamera##name##Req *) inProtData, &ack);\
    }\
    PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *) &ack, sizeof(T_PsdkCamera##name##Ack));\
    return PSDK_STAT_OK;\
}

#define CAMCMD(name)    CameraCmd_##name

/*********************************************************************
*       Types, local
**********************************************************************
*/

/*********************************************************************
*       Static data
**********************************************************************
*/

static T_PsdkCameraHandler s_cameraHandler;
static uint8_t s_isSupportCamera = 0;


/*********************************************************************
*       Static functions
**********************************************************************
*/
MODLE_FUNC_CAMCMD(SetMode)

MODLE_FUNC_CAMCMD(GetMode)

MODLE_FUNC_CAMCMD(ShootPhoto)

MODLE_FUNC_CAMCMD(GetShootPhotoState)

MODLE_FUNC_CAMCMD(SetShootPhotoMode)

MODLE_FUNC_CAMCMD(GetShootPhotoMode)

MODLE_FUNC_CAMCMD(RecordVideo)

MODLE_FUNC_CAMCMD(GetRecordVideoState)

MODLE_FUNC_CAMCMD(GetSDCardState)

MODLE_FUNC_CAMCMD(FormatSDCard)

MODLE_FUNC_CAMCMD(SetMeteringMode)

MODLE_FUNC_CAMCMD(GetMeteringMode)

MODLE_FUNC_CAMCMD(SetSpotMetering)

MODLE_FUNC_CAMCMD(GetSpotMetering)

MODLE_FUNC_CAMCMD(SetFocusMode)

MODLE_FUNC_CAMCMD(GetFocusMode)

MODLE_FUNC_CAMCMD(SetFocusZone)

MODLE_FUNC_CAMCMD(GetFocusZone)

//zoom
MODLE_FUNC_CAMCMD(GetDigitalZoomSpec)

MODLE_FUNC_CAMCMD(SetDigitalZoomFactor)

MODLE_FUNC_CAMCMD(GetDigitalZoomFactor)

MODLE_FUNC_CAMCMD(GetOpticalZoomSpec)

MODLE_FUNC_CAMCMD(SetOpticalZoomFocalLength)

MODLE_FUNC_CAMCMD(GetOpticalZoomFocalLength)

MODLE_FUNC_CAMCMD(GetOpticalZoomFactor)

MODLE_FUNC_CAMCMD(StartContinuousOpticalZoom)

MODLE_FUNC_CAMCMD(StopContinuousOpticalZoom)

MODLE_FUNC_CAMCMD(SetFocusAssistantSettings)

MODLE_FUNC_CAMCMD(GetFocusAssistantSettings)

MODLE_FUNC_CAMCMD(GetFocusRingValueUpperBound)

MODLE_FUNC_CAMCMD(SetFocusRingValue)

MODLE_FUNC_CAMCMD(GetFocusRingValue)

//support state
static E_PsdkStat
CameraCmd_SupportState(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)
{
    T_PsdkCameraSupportStateAck ack;
    ack.ackCode = PSDK_CMD_ACK_CODE_OK;
    ack.isCameraCmdSetSupport = s_isSupportCamera;
    ack.isOpticalZoomSupported = s_cameraHandler.isOpticalZoomSupported;
    ack.isDigitalZoomSupported = s_cameraHandler.isDigitalZoomSupported;
    ack.isAdjustableFocalPointSupported = s_cameraHandler.isAdjustableFocalPointSupported;
    ack.isExposureMeteringSupported = s_cameraHandler.isExposureMeteringSupported;

    PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *) &ack, sizeof(T_PsdkCameraSupportStateAck));

    return PSDK_STAT_OK;
}

//@formatter:off
static const T_PsdkProtCmdItem s_PayloadCameraCmdList[] =
{
//support state
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SUPPORT_STATE, CAMCMD(SupportState)),

PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_MODE, CAMCMD(SetMode)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_MODE, CAMCMD(GetMode)),

PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SHOOT_PHOTO, CAMCMD(ShootPhoto)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_SHOOT_PHOTO_STATE, CAMCMD(GetShootPhotoState)),

PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_SHOOT_PHOTO_MODE, CAMCMD(SetShootPhotoMode)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_SHOOT_PHOTO_MODE, CAMCMD(GetShootPhotoMode)),

PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_RECORD_VIDEO, CAMCMD(RecordVideo)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_RECORD_VIDEO_STATE, CAMCMD(GetRecordVideoState)),

PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_SDCARD_PARAM, CAMCMD(GetSDCardState)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_FORMAT_SDCARD, CAMCMD(FormatSDCard)),

PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_METERING_MODE, CAMCMD(SetMeteringMode)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_METERING_MODE, CAMCMD(GetMeteringMode)),

PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_SPOT_METERING, CAMCMD(SetSpotMetering)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_SPOT_METERING, CAMCMD(GetSpotMetering)),

PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_FOCUS_MODE, CAMCMD(SetFocusMode)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_FOCUS_MODE, CAMCMD(GetFocusMode)),

PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_FOCUS_ZONE, CAMCMD(SetFocusZone)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_FOCUS_ZONE, CAMCMD(GetFocusZone)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_FOCUS_ASSISTANT_SETTING, CAMCMD(SetFocusAssistantSettings)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_FOCUS_ASSISTANT_SETTING, CAMCMD(GetFocusAssistantSettings)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_FOCUS_RING_VALUE_UPPER_BOUND, CAMCMD(GetFocusRingValueUpperBound)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_FOCUS_RING_VALUE, CAMCMD(SetFocusRingValue)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_FOCUS_RING_VALUE, CAMCMD(GetFocusRingValue)),

PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_DIGITALZOOM_SPEC, CAMCMD(GetDigitalZoomSpec)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_DIGTALZOOM_FACTOR, CAMCMD(SetDigitalZoomFactor)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_DIGTALZOOM_FACTOR, CAMCMD(GetDigitalZoomFactor)),

PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_OPTICALZOOM_SPEC, CAMCMD(GetOpticalZoomSpec)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_OPTICALZOOM_FOCAL_LENGTH, CAMCMD(SetOpticalZoomFocalLength)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_OPTICALZOOM_FOCAL_LENGTH, CAMCMD(GetOpticalZoomFocalLength)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_OPTICALZOOM_FACTOR, CAMCMD(GetOpticalZoomFactor)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_START_CONTINUOUS_OPTICAL_ZOOM, CAMCMD(StartContinuousOpticalZoom)),
PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_STOP_CONTINUOUS_OPTICAL_ZOOM, CAMCMD(StopContinuousOpticalZoom)),
};
//@formatter:on


/*********************************************************************
*       Export functions
**********************************************************************
*/
/** @brief Initialize PSDK's camera commands handling.
 *
 * @param psdkUpper:  pointer to the toplevel psdk struct
 * 
 * @param cameraHandler: pointer to the camera handler structure.
 *
 * @return an enum that represents a status of PSDK
 */
E_PsdkStat PsdkCamera_Init(T_PsdkUpper *psdkUpper, const T_PsdkCameraHandler *cameraHandler)
{
    T_PsdkProtCmdSetHandle cmdSetHandle;

    s_cameraHandler = *cameraHandler;
    cmdSetHandle.cmdSet = PSDK_CMDSET_CAMERA;
    cmdSetHandle.cmdList = s_PayloadCameraCmdList;
    cmdSetHandle.cmdCount = sizeof(s_PayloadCameraCmdList) / sizeof(T_PsdkProtCmdItem);

    //support camera
    s_isSupportCamera = 1;

    return PsdkProto_RegCmdSetHandler(&(psdkUpper->protHandle), &cmdSetHandle);
}


/****************** (C) COPYRIGHT DJI Innovations *****END OF FILE****/
