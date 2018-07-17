/*********************************************************************
*       Includes
**********************************************************************
*/

#include <os_util.h>
#include "test_payload_cam_emu.h"

#define EMU_SINGLE_TIME_COST        500

//============================= Base function ===========================================================//
//camera mode
static uint8_t s_cameraMode = PSDK_CAMERA_CAMERA_MODE_SHOOT_PHOTO;

//photography mode
static uint8_t photographyMode = PSDK_CAMERA_SHOOT_PHOTO_MODE_SINGLE;
static uint8_t burstCount = PSDK_CAMERA_BURST_PARAM_3;
static uint8_t intervalCount = 255;
static uint16_t intervalTime = PSDK_CAMERA_INTERVAL_PARAM_5S;   //unit:s

static uint8_t photographyIsOnInterval = 0;
static uint8_t isShootingSinglePhoto = 0; // boolean type
static uint8_t isShootingBurstPhoto = 0;
static uint8_t isStoringPhoto = 0;
static uint32_t ShotStTimeMs = 0;

static uint8_t recordingState = 0;
static uint32_t recordingStTimeMs = 0;

//sd card state
static uint8_t insertState = 1;
static uint32_t capacity = 4096;              //uint: MB
static uint32_t remainCapacity = 2048;        //unit: MB
static uint32_t remainShots = 100;
static uint32_t remainRecordTime = 6000;      //unit: s

void CamEmu_SetCameraMode(const T_PsdkCameraSetModeReq *req, T_PsdkCameraSetModeAck *ack)
{
    PSDK_LOG_DEBUG("Set Camera Work Mode");

    s_cameraMode = req->cameraMode;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_GetCameraMode(const T_PsdkCameraGetModeReq *req, T_PsdkCameraGetModeAck *ack)
{
//    PSDK_LOG_DEBUG("Get Camera Work Mode");

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
    ack->cameraMode = s_cameraMode;
}

void CamEmu_Photography(const T_PsdkCameraShootPhotoReq *req, T_PsdkCameraShootPhotoAck *ack)
{
    PSDK_LOG_DEBUG("ShootPhoto");

    //photography process
    if (req->shootPhotoAction == PSDK_CAMERA_SHOOT_PHOTO_ACTION_START) {
        ShotStTimeMs = OS_GET_TIME_MS;

        if (photographyMode == PSDK_CAMERA_SHOOT_PHOTO_MODE_INTERVAL) {
            isShootingSinglePhoto = 1;
            photographyIsOnInterval = 1;
        } else if (photographyMode == PSDK_CAMERA_SHOOT_PHOTO_MODE_SINGLE) {
            isShootingSinglePhoto = 1;
        } else if (photographyMode == PSDK_CAMERA_SHOOT_PHOTO_MODE_BURST) {
            isShootingBurstPhoto = 1;
        }
    } else if (req->shootPhotoAction == PSDK_CAMERA_SHOOT_PHOTO_ACTION_STOP) {
        photographyIsOnInterval = 0;
        isShootingSinglePhoto = 0;
        isShootingBurstPhoto = 0;
        isStoringPhoto = 0;
    }

    //ack
    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_GetPhotographyState(const T_PsdkCameraGetShootPhotoStateReq *req, T_PsdkCameraGetShootPhotoStateAck *ack)
{
//    PSDK_LOG_DEBUG("Get ShootPhoto State");

    //emulate phtography state
    if (photographyIsOnInterval == 1) {
        //interval
        uint32_t tmp = (OS_GET_TIME_MS - ShotStTimeMs) % (intervalTime * 1000);
        if (tmp <= EMU_SINGLE_TIME_COST) {
            isShootingSinglePhoto = 1;
        } else {
            isShootingSinglePhoto = 0;
        }
    } else {
        //other
        if (isShootingSinglePhoto == 1) {
            if (OS_GET_TIME_MS - ShotStTimeMs > EMU_SINGLE_TIME_COST) {
                isShootingSinglePhoto = 0;
            }
        } else if (isShootingBurstPhoto == 1) {
            if (OS_GET_TIME_MS - ShotStTimeMs > EMU_SINGLE_TIME_COST * burstCount) {
                isShootingBurstPhoto = 0;
            }
        }
    }

    //ack
    ack->ackCode = PSDK_CMD_ACK_CODE_OK;

    ack->isShootingIntervalPhoto = photographyIsOnInterval;
    ack->isShootingSinglePhoto = isShootingSinglePhoto;
    ack->isShootingBurstPhoto = isShootingBurstPhoto;
    ack->isStoringPhoto = isStoringPhoto;

}

void CamEmu_SetPhotographyMode(const T_PsdkCameraSetShootPhotoModeReq *req, T_PsdkCameraSetShootPhotoModeAck *ack)
{
    PSDK_LOG_DEBUG("Set ShootPhoto Mode");
    ack->ackCode = PSDK_CMD_ACK_CODE_OK;

    photographyMode = req->shootPhotoMode;
    burstCount = req->burstCount;
    intervalCount = req->intervalCount;
    intervalTime = req->intervalTime;
}

void CamEmu_GetPhotographyMode(const T_PsdkCameraGetShootPhotoModeReq *req, T_PsdkCameraGetShootPhotoModeAck *ack)
{
//    PSDK_LOG_DEBUG("Get ShootPhoto Mode");
    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
    ack->shootPhotoMode = photographyMode;
    ack->burstCount = burstCount;
    ack->intervalCount = intervalCount;
    ack->intervalTime = intervalTime;
}

void CamEmu_SetRecording(const T_PsdkCameraRecordVideoReq *req, T_PsdkCameraRecordVideoAck *ack)
{
    PSDK_LOG_DEBUG("Set Recording");

    //recording process
    if (req->recordVideoAction == PSDK_CAMERA_RECORD_VIDEO_ACTION_START) {
        recordingState = 1;
        recordingStTimeMs = OS_GET_TIME_MS;
    } else {
        recordingState = 0;
    }

    //ack
    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_GetRecordingState(const T_PsdkCameraGetRecordVideoStateReq *req, T_PsdkCameraGetRecordVideoStateAck *ack)
{
//    PSDK_LOG_DEBUG("Get Recording State");

    ack->isRecording = recordingState;
    ack->currentRecordingTimeInSeconds = (uint16_t) ((OS_GET_TIME_MS - recordingStTimeMs) / 1000);

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_GetSdcardParam(const T_PsdkCameraGetSDCardStateReq *req, T_PsdkCameraGetSDCardStateAck *ack)
{
//    PSDK_LOG_DEBUG("Get Sd card Param");

    ack->isInserted = insertState;
    ack->isVerified = 1;

    ack->isInitializing = 0;
    ack->isReadOnly = 0;
    ack->isFormatting = 0;
    ack->isFull = 0;
    ack->isInvalidFormat = 0;
    ack->hasError = 0;

    ack->totalSpaceInMB = capacity;
    ack->remainSpaceInMB = remainCapacity;
    ack->availableRecordingTimeInSeconds = remainRecordTime;
    ack->availableCaptureCount = remainShots;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_FormatSdcard(const T_PsdkCameraFormatSDCardReq *req, T_PsdkCameraFormatSDCardAck *ack)
{
    PSDK_LOG_DEBUG("Format Sd card");

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
    ack->formatPercent = 100;
}

//============================= Metering ===========================================================//
//metering
static uint8_t meteringMode = PSDK_CAMERA_METERING_MODE_SPOT;
static uint8_t meteringCol = 6;    // 0 ~ 11
static uint8_t meteringRow = 4;    // 0 ~ 7

void CamEmu_SetMeteringMode(const T_PsdkCameraSetMeteringModeReq *req, T_PsdkCameraSetMeteringModeAck *ack)
{
    PSDK_LOG_DEBUG("Set Metering Mode");

    //set metering mode
    meteringMode = req->meteringMode;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_GetMeteringMode(const T_PsdkCameraGetMeteringModeReq *req, T_PsdkCameraGetMeteringModeAck *ack)
{
//    PSDK_LOG_DEBUG("Get Metering Mode");

    ack->meteringMode = meteringMode;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_SetSpotMetering(const T_PsdkCameraSetSpotMeteringReq *req, T_PsdkCameraSetSpotMeteringAck *ack)
{
    PSDK_LOG_DEBUG("Set Spot Metering");

    //set SpotMetering
    meteringCol = req->col;
    meteringRow = req->row;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_GetSpotMetering(const T_PsdkCameraGetSpotMeteringReq *req, T_PsdkCameraGetSpotMeteringAck *ack)
{
//    PSDK_LOG_DEBUG("Get Spot Metering");

    //get spot metering
    ack->col = meteringCol;
    ack->row = meteringRow;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

//============================= focus ===========================================================//
//focus test data
static uint8_t focusMode = PSDK_CAMERA_FOCUS_MODE_AUTO;
static psdk_f32_t focusX = 0.5;  // 0 ~ 1
static psdk_f32_t focusY = 0.5;  // 0 ~ 1
static uint8_t isEnableMF = 1;
static uint8_t isEnableAF = 1;
static uint16_t focusRingValueUpperBound = 1000;
static uint16_t focusRingValue = 500;

//focus function
void CamEmu_SetFocusMode(const T_PsdkCameraSetFocusModeReq *req, T_PsdkCameraSetFocusModeAck *ack)
{
    PSDK_LOG_DEBUG("Set Focus Mode");

    //set focus mode
    focusMode = req->focusMode;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_GetFocusMode(const T_PsdkCameraGetFocusModeReq *req, T_PsdkCameraGetFocusModeAck *ack)
{
//    PSDK_LOG_DEBUG("Get Focus Zone");

    //get focus mode
    ack->focusMode = focusMode;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_SetFocusZone(const T_PsdkCameraSetFocusZoneReq *req, T_PsdkCameraSetFocusZoneAck *ack)
{
    PSDK_LOG_DEBUG("Set Focus Zone");

    //set focus zone
    focusX = req->focusX;
    focusY = req->focusY;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_GetFocusZone(const T_PsdkCameraGetFocusZoneReq *req, T_PsdkCameraGetFocusZoneAck *ack)
{
//    PSDK_LOG_DEBUG("Get Focus Zone");

    //get focus zone
    ack->focusX = focusX;
    ack->focusY = focusY;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_SetFocusAssistantSettings(const T_PsdkCameraSetFocusAssistantSettingsReq *req,
                                      T_PsdkCameraSetFocusAssistantSettingsAck *ack)
{
    PSDK_LOG_DEBUG("Set Focus Assistant Setting");
    isEnableMF = req->isEnabledMF;
    isEnableAF = req->isEnabledAF;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_GetFocusAssistantSettings(const T_PsdkCameraGetFocusAssistantSettingsReq *req,
                                      T_PsdkCameraGetFocusAssistantSettingsAck *ack)
{
//    PSDK_LOG_DEBUG("Get Focus Assistant Setting");

    ack->isEnabledMF = isEnableMF;
    ack->isEnabledAF = isEnableAF;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_GetFocusRingValueUpperBound(const T_PsdkCameraGetFocusRingValueUpperBoundReq *req,
                                        T_PsdkCameraGetFocusRingValueUpperBoundAck *ack)
{
//    PSDK_LOG_DEBUG("Get Focus Ring Value Bound");

    ack->focusRingValueUpperBound = focusRingValueUpperBound;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_SetFocusRingValue(const T_PsdkCameraSetFocusRingValueReq *req, T_PsdkCameraSetFocusRingValueAck *ack)
{
    PSDK_LOG_DEBUG("Set Focus Ring Value");

    focusRingValue = req->focusRingValue;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_GetFocusRingValue(const T_PsdkCameraGetFocusRingValueReq *req, T_PsdkCameraGetFocusRingValueAck *ack)
{
//    PSDK_LOG_DEBUG("Get Focus Ring Value");

    ack->focusRingValue = focusRingValue;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

//============================= zoom ===========================================================//
//zoom param
static uint16_t maxFocalLength = 410;    //unit: 0.1mm
static uint16_t minFocalLength = 120;    //unit: 0.1mm
static uint16_t focalLengthStep = 10;   //unit: 0.1mm
static uint16_t currentFocalLength = 120;

static psdk_f32_t digitalFactor = 1.0;  //1.0 to 2.0
static psdk_f32_t opticalFactor = 1.0;  //1.0 to 30.0

static E_PsdkCameraZoomDirection zoomDirection;
static E_PsdkCameraZoomSpeed zoomSpeed;
static uint8_t isZooming = 0;

//zoom function
void CamEmu_GetDigitalZoomSpec(const T_PsdkCameraGetDigitalZoomSpecReq *req, T_PsdkCameraGetDigitalZoomSpecAck *ack)
{
    ack->maxDigitalZoomFactor = 12.0;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void
CamEmu_SetDigitalZoomFactor(const T_PsdkCameraSetDigitalZoomFactorReq *req, T_PsdkCameraSetDigitalZoomFactorAck *ack)
{
    PSDK_LOG_DEBUG("Set Digital Zoom Factor");

    digitalFactor = req->factor;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void
CamEmu_GetDigitalZoomFactor(const T_PsdkCameraGetDigitalZoomFactorReq *req, T_PsdkCameraGetDigitalZoomFactorAck *ack)
{
//    PSDK_LOG_DEBUG("Get Digital Zoom Factor");

    ack->factor = digitalFactor;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_GetOpticalZoomSpec(const T_PsdkCameraGetOpticalZoomSpecReq *req, T_PsdkCameraGetOpticalZoomSpecAck *ack)
{
//    PSDK_LOG_DEBUG("GetOpticalZoomSpec");

    ack->maxFocalLength = maxFocalLength;
    ack->minFocalLength = minFocalLength;
    ack->focalLengthStep = focalLengthStep;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void
CamEmu_SetOpticalZoomFocalLength(const T_PsdkCameraSetOpticalZoomFocalLengthReq *req,
                                 T_PsdkCameraSetOpticalZoomFocalLengthAck *ack)
{
    PSDK_LOG_DEBUG("SetOpticalZoomFocalLength");

    currentFocalLength = req->focalLength;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_GetOpticalZoomFocalLength(const T_PsdkCameraGetOpticalZoomFocalLengthReq *req,
                                      T_PsdkCameraGetOpticalZoomFocalLengthAck *ack)
{
//    PSDK_LOG_DEBUG("GetOpticalZoomFocalLength");

    if (isZooming) {
        int tempFocalLength = currentFocalLength;

        if (zoomDirection == PSDK_CAMERA_ZOOM_IN) {
            tempFocalLength += (zoomSpeed - 71) * 5;
        } else {
            tempFocalLength -= (zoomSpeed - 71) * 5;
        }

        if (tempFocalLength > maxFocalLength) {
            tempFocalLength = maxFocalLength;
        }

        if (tempFocalLength < minFocalLength) {
            tempFocalLength = minFocalLength;
        }

        currentFocalLength = (uint16_t) tempFocalLength;
    }

    ack->focalLength = currentFocalLength;
    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void
CamEmu_GetOpticalZoomFactor(const T_PsdkCameraGetOpticalZoomFactorReq *req, T_PsdkCameraGetOpticalZoomFactorAck *ack)
{
//    PSDK_LOG_DEBUG("GetOpticalZoomFactor");

    opticalFactor = (psdk_f32_t) ((currentFocalLength - minFocalLength) / 10 + 1.0);
    ack->factor = opticalFactor;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_StartContinuousOpticalZoom(const T_PsdkCameraStartContinuousOpticalZoomReq *req,
                                       T_PsdkCameraStartContinuousOpticalZoomAck *ack)
{
    PSDK_LOG_DEBUG("Start Continuous Zoom");
    isZooming = 1;
    zoomDirection = (E_PsdkCameraZoomDirection) req->zoomDirection;
    zoomSpeed = (E_PsdkCameraZoomSpeed) req->zoomSpeed;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

void CamEmu_StopContinuousOpticalZoom(const T_PsdkCameraStopContinuousOpticalZoomReq *req,
                                      T_PsdkCameraStopContinuousOpticalZoomAck *ack)
{
    PSDK_LOG_DEBUG("Stop Continuous Zoom");
    isZooming = 0;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

const T_PsdkCameraHandler g_testCameraHandler = {
        .SetMode = CamEmu_SetCameraMode,
        .GetMode = CamEmu_GetCameraMode,

        .ShootPhoto = CamEmu_Photography,
        .GetShootPhotoState = CamEmu_GetPhotographyState,

        .SetShootPhotoMode = CamEmu_SetPhotographyMode,
        .GetShootPhotoMode = CamEmu_GetPhotographyMode,

        .RecordVideo = CamEmu_SetRecording,
        .GetRecordVideoState = CamEmu_GetRecordingState,

        .GetSDCardState = CamEmu_GetSdcardParam,
        .FormatSDCard = CamEmu_FormatSdcard,

        //Exposure metering
        .isExposureMeteringSupported = 1,
        .SetMeteringMode = CamEmu_SetMeteringMode,
        .GetMeteringMode = CamEmu_GetMeteringMode,
        .SetSpotMetering = CamEmu_SetSpotMetering,
        .GetSpotMetering = CamEmu_GetSpotMetering,

        //focus
        .isAdjustableFocalPointSupported = 1,
        .SetFocusMode = CamEmu_SetFocusMode,
        .GetFocusMode = CamEmu_GetFocusMode,
        .SetFocusZone = CamEmu_SetFocusZone,
        .GetFocusZone = CamEmu_GetFocusZone,
        .SetFocusAssistantSettings = CamEmu_SetFocusAssistantSettings,
        .GetFocusAssistantSettings = CamEmu_GetFocusAssistantSettings,
        .GetFocusRingValueUpperBound = CamEmu_GetFocusRingValueUpperBound,
        .SetFocusRingValue = CamEmu_SetFocusRingValue,
        .GetFocusRingValue = CamEmu_GetFocusRingValue,

        //digital zoom
        .isDigitalZoomSupported = 0, //not support digital zoom
        .GetDigitalZoomSpec = NULL,  //if not support, callback function can be null
        .SetDigitalZoomFactor = NULL,
        .GetDigitalZoomFactor = NULL,

        //optical zoom
        .isOpticalZoomSupported = 1,
        .GetOpticalZoomSpec = CamEmu_GetOpticalZoomSpec,
        .SetOpticalZoomFocalLength = CamEmu_SetOpticalZoomFocalLength,
        .GetOpticalZoomFocalLength = CamEmu_GetOpticalZoomFocalLength,
        .GetOpticalZoomFactor = CamEmu_GetOpticalZoomFactor,
        .StartContinuousOpticalZoom = CamEmu_StartContinuousOpticalZoom,
        .StopContinuousOpticalZoom = CamEmu_StopContinuousOpticalZoom,
};


/****************** (C) COPYRIGHT DJI Innovations *****END OF FILE****/
