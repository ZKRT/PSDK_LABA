/**
 ******************************************************************************
 * @file    psdk_cmdset_camera.h
 * @version V0.0.0
 * @date    2017/11/9
 * @brief   
 * This file defines the payload SDK camera cmd set.
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

#ifndef PSDK_CMD_CAMERA_H
#define PSDK_CMD_CAMERA_H

#include "psdk_typedef.h"

// -------------------- Enum Type -------------------- //
//@formatter:off
//Psdk Camera Cmd ID
typedef enum {
    //base function
    PSDK_CAMERA_CMD_ID_SET_MODE = 0x01,
    PSDK_CAMERA_CMD_ID_GET_MODE = 0x02,

    PSDK_CAMERA_CMD_ID_SHOOT_PHOTO = 0x03,
    PSDK_CAMERA_CMD_ID_GET_SHOOT_PHOTO_STATE = 0x04,

    PSDK_CAMERA_CMD_ID_SET_SHOOT_PHOTO_MODE = 0x05,
    PSDK_CAMERA_CMD_ID_GET_SHOOT_PHOTO_MODE = 0x06,

    PSDK_CAMERA_CMD_ID_RECORD_VIDEO = 0x07,
    PSDK_CAMERA_CMD_ID_GET_RECORD_VIDEO_STATE = 0x08,

    PSDK_CAMERA_CMD_ID_GET_SDCARD_PARAM = 0x09,
    PSDK_CAMERA_CMD_ID_FORMAT_SDCARD = 0x0A,

    PSDK_CAMERA_CMD_ID_SET_METERING_MODE = 0x20,
    PSDK_CAMERA_CMD_ID_GET_METERING_MODE = 0x21,

    PSDK_CAMERA_CMD_ID_SET_SPOT_METERING = 0x22,
    PSDK_CAMERA_CMD_ID_GET_SPOT_METERING = 0x23,

    //focus
    PSDK_CAMERA_CMD_ID_SET_FOCUS_MODE = 0x30,
    PSDK_CAMERA_CMD_ID_GET_FOCUS_MODE = 0x31,

    PSDK_CAMERA_CMD_ID_SET_FOCUS_ZONE = 0x32,
    PSDK_CAMERA_CMD_ID_GET_FOCUS_ZONE = 0x33,


    //zoom
    PSDK_CAMERA_CMD_ID_SET_DIGTALZOOM_FACTOR = 0x34,
    PSDK_CAMERA_CMD_ID_GET_DIGTALZOOM_FACTOR = 0x35,

    PSDK_CAMERA_CMD_ID_GET_OPTICALZOOM_SPEC = 0x36,

    PSDK_CAMERA_CMD_ID_SET_OPTICALZOOM_FOCAL_LENGTH = 0x37,
    PSDK_CAMERA_CMD_ID_GET_OPTICALZOOM_FOCAL_LENGTH = 0x38,

    PSDK_CAMERA_CMD_ID_GET_OPTICALZOOM_FACTOR = 0x39,

    PSDK_CAMERA_CMD_ID_START_CONTINUOUS_OPTICAL_ZOOM = 0x40,
    PSDK_CAMERA_CMD_ID_STOP_CONTINUOUS_OPTICAL_ZOOM = 0x41,

    //Append Focus
    PSDK_CAMERA_CMD_ID_SET_FOCUS_ASSISTANT_SETTING = 0x42,
    PSDK_CAMERA_CMD_ID_GET_FOCUS_ASSISTANT_SETTING = 0x43,
    PSDK_CAMERA_CMD_ID_GET_FOCUS_RING_VALUE_UPPER_BOUND = 0x44,
    PSDK_CAMERA_CMD_ID_SET_FOCUS_RING_VALUE = 0x45,
    PSDK_CAMERA_CMD_ID_GET_FOCUS_RING_VALUE = 0x46,

    //Append zoom
    PSDK_CAMERA_CMD_ID_GET_DIGITALZOOM_SPEC = 0x47,

    //other
    PSDK_CAMERA_CMD_ID_SUPPORT_STATE = 0xFF,
} E_PsdkCameraCmd;
//@formatter:on

typedef enum {
    PSDK_CAMERA_CAMERA_MODE_SHOOT_PHOTO = 0,
    PSDK_CAMERA_CAMERA_MODE_RECORD_VIDEO = 1,
} E_PsdkCameraCameraMode;

typedef enum {
    PSDK_CAMERA_SHOOT_PHOTO_ACTION_STOP = 0,
    PSDK_CAMERA_SHOOT_PHOTO_ACTION_START = 1,
} E_PsdkCameraShootPhotoAction;

typedef enum {
    PSDK_CAMERA_SHOOT_PHOTO_MODE_SINGLE = 1,
    PSDK_CAMERA_SHOOT_PHOTO_MODE_BURST = 4,
    PSDK_CAMERA_SHOOT_PHOTO_MODE_INTERVAL = 6,
} E_PsdkCameraShootPhotoMode;

typedef enum {
    PSDK_CAMERA_RECORD_VIDEO_ACTION_STOP = 0,
    PSDK_CAMERA_RECORD_VIDEO_ACTION_START = 1,
} E_PsdkCameraRecordVideoAction;

typedef enum {
    PSDK_CAMERA_BURST_PARAM_2 = 2,
    PSDK_CAMERA_BURST_PARAM_3 = 3,
    PSDK_CAMERA_BURST_PARAM_5 = 5,
    PSDK_CAMERA_BURST_PARAM_7 = 7,
    PSDK_CAMERA_BURST_PARAM_10 = 10,
} E_PsdkCameraBurstParam;

typedef enum {
    PSDK_CAMERA_INTERVAL_PARAM_1S = 1,
    PSDK_CAMERA_INTERVAL_PARAM_3S = 3,
    PSDK_CAMERA_INTERVAL_PARAM_5S = 5,
    PSDK_CAMERA_INTERVAL_PARAM_7S = 7,
    PSDK_CAMERA_INTERVAL_PARAM_10S = 10,
    PSDK_CAMERA_INTERVAL_PARAM_15S = 15,
    PSDK_CAMERA_INTERVAL_PARAM_20S = 20,
    PSDK_CAMERA_INTERVAL_PARAM_30S = 30,
} E_PsdkCameraIntervalParam;

typedef enum {
    PSDK_CAMERA_FOCUS_MODE_MANUAL = 0,
    PSDK_CAMERA_FOCUS_MODE_AUTO = 1,
} E_PsdkCameraFocusMode;

typedef enum {
    PSDK_CAMERA_METERING_MODE_CENTER = 0,
    PSDK_CAMERA_METERING_MODE_AVERAGE = 1,
    PSDK_CAMERA_METERING_MODE_SPOT = 2,
} E_PsdkCameraMeteringMode;

typedef enum {
    PSDK_CAMERA_ZOOM_OUT = 0,
    PSDK_CAMERA_ZOOM_IN = 1,
} E_PsdkCameraZoomDirection;

typedef enum {
    PSDK_CAMERA_ZOOM_SPEED_SLOWEST = 72,
    PSDK_CAMERA_ZOOM_SPEED_SLOW = 73,
    PSDK_CAMERA_ZOOM_SPEED_MODERATELY_SLOW = 74,
    PSDK_CAMERA_ZOOM_SPEED_NORMAL = 75,
    PSDK_CAMERA_ZOOM_SPEED_MODERATELY_FAST = 76,
    PSDK_CAMERA_ZOOM_SPEED_FASE = 77,
    PSDK_CAMERA_ZOOM_SPEED_FASTEST = 78,
} E_PsdkCameraZoomSpeed;

// --------------------- Struct --------------------- //

#pragma pack(1)

//PSDK_CAMERA_CMD_ID_SET_MODE
typedef struct {
    uint8_t cameraMode; // enum-type : E_PsdkCameraCameraMode
} T_PsdkCameraSetModeReq;

typedef struct {
    uint8_t ackCode;    // enum-type : E_PsdkCmdAckCode
} T_PsdkCameraSetModeAck;

//PSDK_CAMERA_CMD_ID_GET_MODE
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetModeReq;

typedef struct {
    uint8_t ackCode; // enum-type : E_PsdkCmdAckCode
    uint8_t cameraMode; // enum-type : E_PsdkCameraCameraMode
} T_PsdkCameraGetModeAck;

//PSDK_CAMERA_CMD_ID_SHOOT_PHOTO
typedef struct {
    uint8_t shootPhotoAction; // enum-type : E_PsdkCameraShootPhotoAction
} T_PsdkCameraShootPhotoReq;

typedef struct {
    uint8_t ackCode; // enum-type : E_PsdkCmdAckCode
} T_PsdkCameraShootPhotoAck;

//PSDK_CAMERA_CMD_ID_GET_SHOOT_PHOTO_STATE
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetShootPhotoStateReq;

typedef struct {
    uint8_t ackCode; // enum-type : E_PsdkCmdAckCode
    uint8_t isShootingSinglePhoto  : 1; // boolean type
    uint8_t isShootingIntervalPhoto : 1; // boolean type
    uint8_t isShootingBurstPhoto : 1; // boolean type
    uint8_t isStoringPhoto : 1; // boolean type
    uint8_t reserved : 4;
} T_PsdkCameraGetShootPhotoStateAck;

//PSDK_CAMERA_CMD_ID_SET_SHOOT_PHOTO_MODE
typedef struct {
    uint8_t shootPhotoMode;  // enum-type : E_PsdkCameraShootPhotoMode
    uint8_t burstCount; // enum-type : E_PsdkCameraBurstParam
    uint8_t intervalCount; //interval capture count, value 255 means continue capture
    uint16_t intervalTime;   //unit:s
} T_PsdkCameraSetShootPhotoModeReq;

typedef struct {
    uint8_t ackCode; // enum-type : E_PsdkCmdAckCode
} T_PsdkCameraSetShootPhotoModeAck;

//PSDK_CAMERA_CMD_ID_GET_SHOOT_PHOTO_MODE
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetShootPhotoModeReq;

typedef struct {
    uint8_t ackCode;
    uint8_t shootPhotoMode; // enum-type : E_PsdkCameraShootPhotoMode
    uint8_t burstCount; // enum-type : E_PsdkCameraBurstParam
    uint8_t intervalCount; //interval capture count, value 255 means continue capture
    uint16_t intervalTime;   //unit:s
} T_PsdkCameraGetShootPhotoModeAck;

//PSDK_CAMERA_CMD_ID_RECORD_VIDEO
typedef struct {
    uint8_t recordVideoAction; // enum-type : E_PsdkCameraRecordVideoAction
} T_PsdkCameraRecordVideoReq;

typedef struct {
    uint8_t ackCode;
} T_PsdkCameraRecordVideoAck;

//PSDK_CAMERA_CMD_ID_GET_RECORD_VIDEO_STATE
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetRecordVideoStateReq;

typedef struct {
    uint8_t ackCode;
    uint8_t isRecording; // boolean type
    uint16_t currentRecordingTimeInSeconds; // unit:s
} T_PsdkCameraGetRecordVideoStateAck;

typedef struct {
    uint8_t ackCode;

    // if the SD card is inserted in the camera.
    uint8_t isInserted : 1;
    // if the SD card is verified as genuine.
    uint8_t isVerified : 1;

    uint8_t isInitializing : 1;
    uint8_t isReadOnly : 1;
    uint8_t isFormatting : 1;
    uint8_t isFull : 1;
    uint8_t isInvalidFormat : 1;
    uint8_t hasError : 1;

    uint8_t reserved;

    uint32_t totalSpaceInMB;  //uint: MB
    uint32_t remainSpaceInMB; //unit: MB
    uint32_t availableCaptureCount;
    uint32_t availableRecordingTimeInSeconds; //unit: s
} T_PsdkCameraGetSDCardStateAck;

//PSDK_CAMERA_CMD_ID_FORMAT_SDCARD
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraFormatSDCardReq;

typedef struct {
    uint8_t ackCode;
    uint8_t formatPercent; //unit:% 0 ~ 100
} T_PsdkCameraFormatSDCardAck;

//PSDK_CAMERA_CMD_ID_SET_SPOT_METERING
typedef struct {
    uint8_t col : 4;    // 0 ~ 11
    uint8_t row : 4;    // 0 ~ 7
} T_PsdkCameraSetSpotMeteringReq;

typedef struct {
    uint8_t ackCode;
} T_PsdkCameraSetSpotMeteringAck;

//PSDK_CAMERA_CMD_ID_GET_SPOT_METERING
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetSpotMeteringReq;

typedef struct {
    uint8_t ackCode;
    uint8_t col : 4;    // 0 ~ 11
    uint8_t row : 4;    // 0 ~ 7
} T_PsdkCameraGetSpotMeteringAck;

//PSDK_CAMERA_CMD_ID_GET_SDCARD_PARAM
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetSDCardStateReq;

//PSDK_CAMERA_CMD_ID_SET_METERING_MODE
typedef struct {
    uint8_t meteringMode; // enum-type : E_PsdkCameraMeteringMode
} T_PsdkCameraSetMeteringModeReq;

typedef struct {
    uint8_t ackCode;
} T_PsdkCameraSetMeteringModeAck;

//PSDK_CAMERA_CMD_ID_GET_METERING_MODE
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetMeteringModeReq;

typedef struct {
    uint8_t ackCode;
    uint8_t meteringMode; // enum-type : E_PsdkCameraMeteringMode
} T_PsdkCameraGetMeteringModeAck;

//PSDK_CAMERA_CMD_ID_SET_FOCUS_MODE
typedef struct {
    uint8_t focusMode;  // enum-type: E_PsdkCameraFocusMode
} T_PsdkCameraSetFocusModeReq;

typedef struct {
    uint8_t ackCode;
} T_PsdkCameraSetFocusModeAck;

//PSDK_CAMERA_CMD_ID_GET_FOCUS_MODE
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetFocusModeReq;

typedef struct {
    uint8_t ackCode;
    uint8_t focusMode; // enum-type: E_PsdkCameraFocusMode
} T_PsdkCameraGetFocusModeAck;

//PSDK_CAMERA_CMD_ID_SET_FOCUS_ZONE
typedef struct {
    psdk_f32_t focusX;  // 0 ~ 1
    psdk_f32_t focusY;  // 0 ~ 1
} T_PsdkCameraSetFocusZoneReq;

typedef struct {
    uint8_t ackCode;
} T_PsdkCameraSetFocusZoneAck;

//PSDK_CAMERA_CMD_ID_GET_FOCUS_ZONE
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetFocusZoneReq;

typedef struct {
    uint8_t ackCode;
    psdk_f32_t focusX;  // 0 ~ 1
    psdk_f32_t focusY;  // 0 ~ 1
} T_PsdkCameraGetFocusZoneAck;

//PSDK_CAMERA_CMD_ID_SET_DIGTALZOOM_FACTOR
typedef struct {
    psdk_f32_t factor;  //1.0 to maxDigitalZoomFactor
} T_PsdkCameraSetDigitalZoomFactorReq;

typedef struct {
    uint8_t ackCode;
} T_PsdkCameraSetDigitalZoomFactorAck;

//PSDK_CAMERA_CMD_ID_GET_DIGTALZOOM_FACTOR
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetDigitalZoomFactorReq;

typedef struct {
    uint8_t ackCode;
    psdk_f32_t factor;
} T_PsdkCameraGetDigitalZoomFactorAck;

//PSDK_CAMERA_CMD_ID_GET_OPTICALZOOM_SPEC
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetOpticalZoomSpecReq;

typedef struct {
    uint8_t ackCode;
    uint16_t maxFocalLength;    //unit: 0.1mm
    uint16_t minFocalLength;    //unit: 0.1mm
    uint16_t focalLengthStep;   //unit: 0.1mm
} T_PsdkCameraGetOpticalZoomSpecAck;

//PSDK_CAMERA_CMD_ID_SET_OPTICALZOOM_FOCAL_LENGTH
typedef struct {
    uint16_t focalLength;   //unit: 0.1mm
} T_PsdkCameraSetOpticalZoomFocalLengthReq;

typedef struct {
    uint8_t ackCode;
} T_PsdkCameraSetOpticalZoomFocalLengthAck;

//PSDK_CAMERA_CMD_ID_GET_OPTICALZOOM_FOCAL_LENGTH
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetOpticalZoomFocalLengthReq;

typedef struct {
    uint8_t ackCode;
    uint16_t focalLength;   //unit: 0.1mm
} T_PsdkCameraGetOpticalZoomFocalLengthAck;

//PSDK_CAMERA_CMD_ID_GET_OPTICALZOOM_FACTOR
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetOpticalZoomFactorReq;

typedef struct {
    uint8_t ackCode;
    psdk_f32_t factor;  //1.0 to 30.0
} T_PsdkCameraGetOpticalZoomFactorAck;

//PSDK_CAMERA_CMD_ID_START_CONTINUOUS_OPTICAL_ZOOM
typedef struct {
    uint8_t zoomSpeed; // enum-type : E_PsdkCameraZoomSpeed
    uint8_t zoomDirection; //enum-type : E_PsdkCameraZoomDirection
} T_PsdkCameraStartContinuousOpticalZoomReq;

typedef struct {
    uint8_t ackCode;
} T_PsdkCameraStartContinuousOpticalZoomAck;

//PSDK_CAMERA_CMD_ID_STOP_CONTINUOUS_OPTICAL_ZOOM
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraStopContinuousOpticalZoomReq;

typedef struct {
    uint8_t ackCode;
} T_PsdkCameraStopContinuousOpticalZoomAck;

//PSDK_CAMERA_CMD_ID_SET_FOCUS_ASSISTANT_SETTING
typedef struct {
    uint8_t isEnabledAF:1; // boolean type, if the lens focus assistant is enabled for auto Focusing.
    uint8_t isEnabledMF:1; // boolean type, if the lens focus assistant is enabled for Manual Focusing.
    uint8_t reserved:6;
} T_PsdkCameraSetFocusAssistantSettingsReq;

typedef struct {
    uint8_t ackCode;
} T_PsdkCameraSetFocusAssistantSettingsAck;

//PSDK_CAMERA_CMD_ID_GET_FOCUS_ASSISTANT_SETTING
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetFocusAssistantSettingsReq;

typedef struct {
    uint8_t ackCode;
    uint8_t isEnabledAF:1; // boolean type, if the lens focus assistant is enabled for auto Focusing.
    uint8_t isEnabledMF:1; // boolean type, if the lens focus assistant is enabled for Manual Focusing.
    uint8_t reserved:6;
} T_PsdkCameraGetFocusAssistantSettingsAck;

//PSDK_CAMERA_CMD_ID_GET_FOCUS_RING_VALUE_UPPER_BOUND
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetFocusRingValueUpperBoundReq;

typedef struct {
    uint8_t ackCode;
    uint16_t focusRingValueUpperBound; // the lens focusing ring value's max value.
} T_PsdkCameraGetFocusRingValueUpperBoundAck;

//PSDK_CAMERA_CMD_ID_SET_FOCUS_RING_VALUE
typedef struct {
    uint16_t focusRingValue;
} T_PsdkCameraSetFocusRingValueReq;

typedef struct {
    uint8_t ackCode;
} T_PsdkCameraSetFocusRingValueAck;

//PSDK_CAMERA_CMD_ID_GET_FOCUS_RING_VALUE
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetFocusRingValueReq;

typedef struct {
    uint8_t ackCode;
    uint16_t focusRingValue;
} T_PsdkCameraGetFocusRingValueAck;

//PSDK_CAMERA_CMD_ID_GET_DIGITALZOOM_SPEC
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetDigitalZoomSpecReq;

typedef struct {
    uint8_t ackCode;
    psdk_f32_t maxDigitalZoomFactor; //max digital zoom factor.
} T_PsdkCameraGetDigitalZoomSpecAck;

//PSDK_CAMERA_CMD_ID_SUPPORT_STATE
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraSupportStateReq;

typedef struct {
    uint8_t ackCode;

    uint8_t isCameraCmdSetSupport : 1;
    uint8_t isDigitalZoomSupported : 1;
    uint8_t isOpticalZoomSupported : 1;
    uint8_t isAdjustableFocalPointSupported : 1;
    uint8_t isExposureMeteringSupported : 1;
    uint8_t reserved : 3;
} T_PsdkCameraSupportStateAck;

#pragma pack()


#endif //PSDK_CMD_CAMERA_H
