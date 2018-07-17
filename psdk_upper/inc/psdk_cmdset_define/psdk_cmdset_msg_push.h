/**
 ******************************************************************************
 * @file    psdk_cmdset_msg_push.h
 * @version V0.0.0
 * @date    10-August-2017
 * @brief   
 * This file defines the data push cmd-set.
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
#ifndef PSDK_CMDSET_MSG_PUSH_H
#define PSDK_CMDSET_MSG_PUSH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <psdk_typedef.h>

/* Defines, configurable -----------------------------------------------------*/

/* Defines, fixed ------------------------------------------------------------*/
/**
 * @defgroup Psdk_UAV_Type
 * @{
 */
#define PSDK_UAV_TYPE_UNKNOWN     0
#define PSDK_UAV_TYPE_M200        1
#define PSDK_UAV_TYPE_M210        2
#define PSDK_UAV_TYPE_M210RTK     3
#define PSDK_UAV_TYPE_M600        4
#define PSDK_UAV_TYPE_M600PRO     5

#define IS_PSDK_UAV_TYPE(UAV_TYPE) (((UAV_TYPE) == PSDK_UAV_TYPE_UNKNOWN)   || \
                                    ((UAV_TYPE) == PSDK_UAV_TYPE_M200)      || \
                                    ((UAV_TYPE) == PSDK_UAV_TYPE_M210)      || \
                                    ((UAV_TYPE) == PSDK_UAV_TYPE_M210RTK)   || \
                                    ((UAV_TYPE) == PSDK_UAV_TYPE_M600)      || \
                                    ((UAV_TYPE) == PSDK_UAV_TYPE_M600PRO))
/**
 * @}
 */

/**
 * @defgroup Psdk_BaseBandState
 * @{
 */
#define PSDK_BASE_BAND_STATE_LINK         1
#define PSDK_BASE_BAND_STATE_UNLINK       0

#define IS_PSDK_BASE_BAND_STATE(STATE) (((STATE) == PSDK_BASE_BAND_STATE_LINK)  || \
                                        ((STATE) == PSDK_BASE_BAND_STATE_UNLINK))
/**
 * @}
 */

/**
 * @defgroup Psdk_MsgPushLinkState
 * @{
 */
#define PSDK_MSG_PUSH_LINK_STATE_LINK         1
#define PSDK_MSG_PUSH_LINK_STATE_UNLINK       0

#define IS_PSDK_MSGPUSH_STATE(STATE) (((STATE) == PSDK_MSG_PUSH_LINK_STATE_LINK)  || \
                                        ((STATE) == PSDK_MSG_PUSH_LINK_STATE_UNLINK))
/**
 * @}
 */

/**
 * @defgroup Psdk_GPS_State
 * @{
 */
#define PSDK_GPS_STATE_NO_SIGNAL          0
#define PSDK_GPS_STATE_WEAK_SIGNAL        1
#define PSDK_GPS_STATE_MEDIUM_SIGNAL      2
#define PSDK_GPS_STATE_GOOD_SIGNAL        3

#define IS_PSDK_GPS_STATE(STATE) (((STATE) == PSDK_GPS_STATE_NO_SIGNAL)     || \
                                  ((STATE) == PSDK_GPS_STATE_WEAK_SIGNAL)   || \
                                  ((STATE) == PSDK_GPS_STATE_MEDIUM_SIGNAL) || \
                                  ((STATE) == PSDK_GPS_STATE_GOOD_SIGNAL)
/**
 * @}
 */

/**
 * @defgroup Psdk_Compass_State
 * @{
 */
#define PSDK_COMPASS_STATE_NORMAL         0
#define PSDK_COMPASS_STATE_ABNORMAL       1

#define IS_PSDK_COMPASS_STATE(STATE) (((STATE) == PSDK_COMPASS_STATE_NORMAL)    || \
                                      ((STATE) == PSDK_COMPASS_STATE_ABNORMAL))
/**
 * @}
 */

/**
 * @defgroup Psdk_Motor_State
 *
 */
#define PSDK_MOTOR_STATE_ROTATING         1
#define PSDK_MOTOR_STATE_UNROTATING       0

#define IS_PSDK_MOTOR_STATE(STATE) (((STATE) == PSDK_MOTOR_STATE_ROTATING)  || \
                                    ((STATE) == PSDK_MOTOR_STATE_UNROTATING))
/**
 * @}
 */

/**
 * @defgroup Psdk_Land_State
 * @{
 */
#define PSDK_LAND_STATE_UNKNOWN           0
#define PSDK_LAND_STATE_LANDED            1
#define PSDK_LAND_STATE_UNLANDED          2

#define IS_PSDK_LAND_STATE(STATE) (((STATE) == PSDK_LAND_STATE_UNKNOWN)     || \
                                   ((STATE) == PSDK_LAND_STATE_LANDED)      || \
                                   ((STATE) == PSDK_LAND_STATE_UNLANDED))
/**
 * @}
 */

//Message Push Cmd ID
typedef enum {
    PSDK_DATAPUSH_CMD_ID_PUSH_BANDWIDTH = 0x01,
    PSDK_DATAPUSH_CMD_ID_PUSH_ATTITUDE = 0x02,
    PSDK_DATAPUSH_CMD_ID_PUSH_BATTERY_INFO = 0x03,
    PSDK_DATAPUSH_CMD_ID_PUSH_GPS_INFO = 0x04,
    PSDK_DATAPUSH_CMD_ID_PUSH_UAV_STATE = 0x05,
    PSDK_DATAPUSH_CMD_ID_PUSH_APP_DATETIME = 0x06,
} E_PsdkDataPushCmd;

#pragma pack(1)

// PSDK_DATAPUSH_CMD_ID_PUSH_BANDWIDTH
typedef struct {
    uint8_t baseBandState;           /*!< Specifies the base band state of wireless image transmission.
                                           This parameter can be a value of @ref Psdk_BaseBandState */
    uint8_t maxBandWidth;           /*!< mbps */
    uint8_t reserve;

    uint8_t remoteControlLinkState :1; /*!< Specifies remote control link state.
                                           This parameter can be a value of @ref Psdk_MsgPushLinkState */
    uint8_t downVideoLinkState :1; /*!< Specifies downlink video link state.
                                           This parameter can be a value of @ref Psdk_MsgPushLinkState */
    uint8_t downDataCmdLinkState :1;
    uint8_t AppLinkState :1;
    uint8_t reseveBit :4;
} T_BandWidthMsg;

// PSDK_DATAPUSH_CMD_ID_PUSH_ATTITUDE
typedef struct {
    //q = q0 + q1*i + q2*j + q3*k
    psdk_f32_t q0;
    psdk_f32_t q1;
    psdk_f32_t q2;
    psdk_f32_t q3;
} T_UavAttitudeMsg;

// PSDK_DATAPUSH_CMD_ID_PUSH_BATTERY_INFO
typedef struct {
    uint8_t capacityPercent;           /*!< this value can be 0 ~ 100 */
} T_BatteryInfoMsg;

// PSDK_DATAPUSH_CMD_ID_PUSH_GPS_INFO
typedef struct {
    psdk_f64_t longitude;            /*!< unit: rad */
    psdk_f64_t latitude;             /*!< unit: rad */
    int16_t refHeight;               /*!< unit: 0.1m */
    uint8_t sateNum;
    uint8_t gpsState;                /*!< @ref Psdk_GPS_State */
} T_GPSInfoMsg;

// PSDK_DATAPUSH_CMD_ID_PUSH_UAV_STATE
typedef struct {
    struct {
        uint8_t compassState : 1;    /*!< Specifies uav compass state.
                                           This parameter can be a value of @ref Psdk_Compass_State */

        uint8_t motorState   : 1;    /*!< Specifies uav motor state.
                                           This parameter can be a value of @ref Psdk_Motor_State */

        uint8_t landState    : 2;   /*!< Specifies uav land state.
                                           This parameter can be a value of @ref Psdk_Land_State */

        uint8_t reserved     : 4;
    } uavState;

    uint16_t flightTime;             /*!< unit: 0.1s */

    uint8_t uavType;                /*!< Specifies uav type.
                                           This parameter can be a value of @ref Psdk_UAV_Type */
} T_UavStateMsg;

// PSDK_DATAPUSH_CMD_ID_PUSH_APP_DATETIME
typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} T_AppDateTimeMsg;

#pragma pack()

#ifdef __cplusplus
}
#endif

#endif //PSDK_CMDSET_MSG_PUSH_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
