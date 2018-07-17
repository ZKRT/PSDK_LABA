/**
 ******************************************************************************
 * @file    psdk_cmdset_gimbal.h
 * @version V0.0.0
 * @date    2017/11/9
 * @brief   
 * This file defines payload sdk gimbal cmd set.
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
 * ******************************************************************************
 */

#ifndef PSDK_CMD_SET_GIMBAL_H
#define PSDK_CMD_SET_GIMBAL_H

#include "psdk_typedef.h"

typedef enum {
    PSDK_GIMBAL_CMD_ID_GET_GIMBAL_PARAM = 0x01,
    PSDK_GIMBAL_CMD_ID_SET_GIMBAL_MODE = 0x02,
    PSDK_GIMBAL_CMD_ID_RETURN_HEAD = 0x03,

    PSDK_GIMBAL_CMD_ID_CONTROL_SPEED = 0x04,
    PSDK_GIMBAL_CMD_ID_ROTATE = 0x05,
    PSDK_GIMBAL_CMD_ID_GET_CTRL_STATE = 0x06,

    PSDK_GIMBAL_CMD_ID_START_CALIBRATION = 0x07,

    //support
            PSDK_GIMBAL_CMD_ID_SUPPORT_STATE = 0xFF,
} E_PsdkGimbalCmd;

typedef enum {
    PSDK_GIMBAL_GIMBAL_MODE_FREE = 0,
    PSDK_GIMBAL_GIMBAL_MODE_YAW_FOLLOW = 1,
    PSDK_GIMBAL_GIMBAL_MODE_FPV = 2,
} E_PsdkGimbalGimbalMode;

#pragma pack(1)

//PSDK_GIMBAL_CMD_ID_GET_GIMBAL_PARAM
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkGimbalGetGimbalStateReq;

typedef struct {
    uint8_t ackCode;

    uint8_t gimbalMode; // enum-type : E_PsdkGimbalGimbalMode

    uint8_t isMountedUpwards    : 1;
    uint8_t isYawLimit      : 1;
    uint8_t isRollLimit     : 1;
    uint8_t isPitchLimit    : 1;
    uint8_t reserved        : 4;

    int16_t pitch;  //unit 0.1 degree
    int16_t roll;   //unit 0.1 degree
    int16_t yaw;    //unit 0.1 degree
} T_PsdkGimbalGetGimbalStateAck;

//PSDK_GIMBAL_CMD_ID_SET_GIMBAL_MODE
typedef struct {
    uint8_t gimbalMode;
} T_PsdkGimbalSetGimbalModeReq;

typedef struct {
    uint8_t ackCode;
} T_PsdkGimbalSetGimbalModeAck;

//PSDK_GIMBAL_CMD_ID_GO_CENTRE
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkGimbalReturnHeadReq;

typedef struct {
    uint8_t ackCode;
} T_PsdkGimbalReturnHeadAck;

//PSDK_GIMBAL_CMD_ID_CONTROL_ANGLE
typedef struct {
    uint16_t pitch;
    uint16_t roll;
    uint16_t yaw;
} T_PsdkGimbalControlAngleReq;

typedef struct {
    uint8_t ackCode;
} T_PsdkGimbalControlAngleAck;

//PSDK_GIMBAL_CMD_ID_CONTROL_SPEED
typedef struct {
    int16_t pitchSpeed;     //0.1 degree/s
    int16_t rollSpeed;      //0.1 degree/s
    int16_t yawSpeed;       //0.1 degree/s
    uint8_t ctrlFlag;      //1: Control Gimbal,  0:Stop Control Gimbal
} T_PsdkGimbalControlSpeedReq;

typedef struct {
    uint8_t ackCode;
} T_PsdkGimbalControlSpeedAck;

//PSDK_GIMBAL_CMD_ID_ROTATE
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkGimbalRotateReq;

typedef struct {
    uint8_t ackCode;
} T_PsdkGimbalRotateAck;

//PSDK_GIMBAL_CMD_ID_START_CALIBRATION
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkGimbalStartCalibrationReq;

typedef struct {
    uint8_t ackCode;
} T_PsdkGimbalStartCalibrationAck;

//PSDK_GIMBAL_CMD_ID_SUPPORT_STATE
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkGimbalSupportStateReq;

typedef struct {
    uint8_t ackCode;

    uint8_t isGimbalCmdSetSupport : 1;
    uint8_t reserved : 7;
} T_PsdkGimbalSupportStateAck;


#pragma pack()


#endif //PSDK_CMD_SET_GIMBAL_H
