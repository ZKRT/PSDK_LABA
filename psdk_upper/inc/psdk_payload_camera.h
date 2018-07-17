/**
 *********************************************************************
 * @file    psdk_payload_camera.h
 * @brief
 * This is the header file for "psdk_payload_camera.c", defining the 
 * structures and (exported) function prototypes.
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

#ifndef PSDK_PAYLOAD_CAMERA_H
#define PSDK_PAYLOAD_CAMERA_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
*       Includes
**********************************************************************
*/

#include "psdk_upper.h"
#include "psdk_cmdset.h"

//@formatter:off
typedef struct {
    //======== Camera Base function ==========//
    void (*SetMode)(const T_PsdkCameraSetModeReq *req, T_PsdkCameraSetModeAck *ack);
    void (*GetMode)(const T_PsdkCameraGetModeReq *req, T_PsdkCameraGetModeAck *ack);

    void (*ShootPhoto)(const T_PsdkCameraShootPhotoReq *req, T_PsdkCameraShootPhotoAck *ack);
    void (*GetShootPhotoState)(const T_PsdkCameraGetShootPhotoStateReq *req, T_PsdkCameraGetShootPhotoStateAck *ack);

    void (*SetShootPhotoMode)(const T_PsdkCameraSetShootPhotoModeReq *req, T_PsdkCameraSetShootPhotoModeAck *ack);
    void (*GetShootPhotoMode)(const T_PsdkCameraGetShootPhotoModeReq *req, T_PsdkCameraGetShootPhotoModeAck *ack);

    void (*RecordVideo)(const T_PsdkCameraRecordVideoReq *req, T_PsdkCameraRecordVideoAck *ack);
    void (*GetRecordVideoState)(const T_PsdkCameraGetRecordVideoStateReq *req, T_PsdkCameraGetRecordVideoStateAck *ack);

    void (*GetSDCardState)(const T_PsdkCameraGetSDCardStateReq *req, T_PsdkCameraGetSDCardStateAck *ack);
    void (*FormatSDCard)(const T_PsdkCameraFormatSDCardReq *req, T_PsdkCameraFormatSDCardAck *ack);
    //===== End of Camera Base function =======//

    //========== Exposure Metering ============//
    uint8_t isExposureMeteringSupported;
    void (*SetMeteringMode)(const T_PsdkCameraSetMeteringModeReq *req, T_PsdkCameraSetMeteringModeAck *ack);
    void (*GetMeteringMode)(const T_PsdkCameraGetMeteringModeReq *req, T_PsdkCameraGetMeteringModeAck *ack);
    void (*SetSpotMetering)(const T_PsdkCameraSetSpotMeteringReq *req, T_PsdkCameraSetSpotMeteringAck *ack);
    void (*GetSpotMetering)(const T_PsdkCameraGetSpotMeteringReq *req, T_PsdkCameraGetSpotMeteringAck *ack);
    //========= End of Exposure Metering ======//

    //=============== Focus ===================//
    uint8_t isAdjustableFocalPointSupported;
    void (*SetFocusMode)(const T_PsdkCameraSetFocusModeReq *req, T_PsdkCameraSetFocusModeAck *ack);
    void (*GetFocusMode)(const T_PsdkCameraGetFocusModeReq *req, T_PsdkCameraGetFocusModeAck *ack);
    void (*SetFocusZone)(const T_PsdkCameraSetFocusZoneReq *req, T_PsdkCameraSetFocusZoneAck *ack);
    void (*GetFocusZone)(const T_PsdkCameraGetFocusZoneReq *req, T_PsdkCameraGetFocusZoneAck *ack);
    void (*SetFocusAssistantSettings)(const T_PsdkCameraSetFocusAssistantSettingsReq *req, T_PsdkCameraSetFocusAssistantSettingsAck *ack);
    void (*GetFocusAssistantSettings)(const T_PsdkCameraGetFocusAssistantSettingsReq *req, T_PsdkCameraGetFocusAssistantSettingsAck *ack);
    void (*GetFocusRingValueUpperBound)(const T_PsdkCameraGetFocusRingValueUpperBoundReq *req, T_PsdkCameraGetFocusRingValueUpperBoundAck *ack);
    void (*SetFocusRingValue)(const T_PsdkCameraSetFocusRingValueReq *req, T_PsdkCameraSetFocusRingValueAck *ack);
    void (*GetFocusRingValue)(const T_PsdkCameraGetFocusRingValueReq *req, T_PsdkCameraGetFocusRingValueAck *ack);
    //============ End of Focus ===============//

    //=============== zoom ====================//
    uint8_t isDigitalZoomSupported;
    void (*GetDigitalZoomSpec)(const T_PsdkCameraGetDigitalZoomSpecReq *req, T_PsdkCameraGetDigitalZoomSpecAck *ack);
    void (*SetDigitalZoomFactor)(const T_PsdkCameraSetDigitalZoomFactorReq *req, T_PsdkCameraSetDigitalZoomFactorAck *ack);
    void (*GetDigitalZoomFactor)(const T_PsdkCameraGetDigitalZoomFactorReq *req, T_PsdkCameraGetDigitalZoomFactorAck *ack);

    uint8_t isOpticalZoomSupported;
    void (*GetOpticalZoomSpec)(const T_PsdkCameraGetOpticalZoomSpecReq *req, T_PsdkCameraGetOpticalZoomSpecAck *ack);
    void (*SetOpticalZoomFocalLength)(const T_PsdkCameraSetOpticalZoomFocalLengthReq *req, T_PsdkCameraSetOpticalZoomFocalLengthAck *ack);
    void (*GetOpticalZoomFocalLength)(const T_PsdkCameraGetOpticalZoomFocalLengthReq *req, T_PsdkCameraGetOpticalZoomFocalLengthAck *ack);
    void (*GetOpticalZoomFactor)(const T_PsdkCameraGetOpticalZoomFactorReq *req, T_PsdkCameraGetOpticalZoomFactorAck *ack);
    void (*StartContinuousOpticalZoom)(const T_PsdkCameraStartContinuousOpticalZoomReq *req, T_PsdkCameraStartContinuousOpticalZoomAck *ack);
    void (*StopContinuousOpticalZoom)(const T_PsdkCameraStopContinuousOpticalZoomReq *req, T_PsdkCameraStopContinuousOpticalZoomAck *ack);
    //=========== End of zoom =================//
} T_PsdkCameraHandler;
//@formatter:on

/*********************************************************************
*       Export functions
**********************************************************************
*/

E_PsdkStat PsdkCamera_Init(T_PsdkUpper *psdkUpper, const T_PsdkCameraHandler *cameraHandler);

#ifdef __cplusplus
}
#endif

#endif //PSDK_PAYLOAD_CAMERA_H

/****************** (C) COPYRIGHT DJI Innovations *****END OF FILE****/
