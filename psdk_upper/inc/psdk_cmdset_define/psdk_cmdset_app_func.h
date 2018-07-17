/**
 ******************************************************************************
 * @file    psdk_cmdset_app_func.h
 * @version V0.0.0
 * @date    2017/11/9
 * @brief   
 * This file defines the payload SDK App func cmd set.
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
#ifndef PSDK_CMDSET_APP_FUNC_H
#define PSDK_CMDSET_APP_FUNC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <psdk_typedef.h>
#include <psdk_core.h>

/* Defines, configurable -----------------------------------------------------*/

/* Defines, fixed ------------------------------------------------------------*/
#define APPFUNC_APP_TO_LOAD_MAX_LEN                     32
#define APPFUNC_LOAD_TO_APP_MAX_LEN                     128

#define APPFUNC_FLOAT_WINDOW_MSG_MAX_SIZE               128
#define APPFUNC_MAX_WIDGET_NAME_SIZE                    32

#define APPFUNC_LIST_MAX_ITEM_NUM                       10
#define APPFUNC_LIST_MAX_ITEM_NAME_SIZE                 16

#define APPFUNC_INT_INPUT_BOX_PROMPT_CHAR_MAX_SIZE      32

#define APPFUNC_WIDGET_VALUE_GROUP_MAX_ITEM_COUNT       15

// -------------------- Enum Type -------------------- //
//App Func Cmd ID Enum
typedef enum {
    PSDK_APPFUNC_CMDID_TT_APP_TO_LOAD = 0x01,
    PSDK_APPFUNC_CMDID_TT_LOAD_TO_APP = 0x02,

    PSDK_APPFUNC_CMDID_PUSH_FLOATING_WINDOW_MSG = 0x03,

    PSDK_APPFUNC_CMDID_GET_WIDGET_LIST_LENGTH = 0x04,
    PSDK_APPFUNC_CMDID_GET_WIDGET_LIST_VALUE = 0x05,
    PSDK_APPFUNC_CMDID_GET_WIDGET_GROUP_COUNT = 0x06,
    PSDK_APPFUNC_CMDID_GET_WIDGET_GROUP_VALUE = 0x07,
    PSDK_APPFUNC_CMDID_SET_WIDGET_VALUE = 0x08,
} E_PsdkAppFuncCmd;

typedef enum {
    PSDK_APPFUNC_WIDGET_TYPE_BUTTON = 1,
    PSDK_APPFUNC_WIDGET_TYPE_SWITCH = 2,
    PSDK_APPFUNC_WIDGET_TYPE_SCALE = 3,
    PSDK_APPFUNC_WIDGET_TYPE_LIST = 4,
    PSDK_APPFUNC_WIDGET_TYPE_INT_INPUT_BOX = 5,
} E_PsdkAppFuncWidgetType;

typedef enum {
    PSDK_APPFUNC_BUTTON_VAL_PRESS_DOWN = 1,
    PSDK_APPFUNC_BUTTON_VAL_RELEASE_UP = 0,
} E_PsdkAppFuncButtonVal;

typedef enum {
    PSDK_APPFUNC_SWITCH_VAL_OFF = 0,
    PSDK_APPFUNC_SWITCH_VAL_ON = 1,
} E_PsdkAppFuncSwitchVal;

// --------------------- Struct --------------------- //
#pragma pack(1)

typedef union {
    int32_t buttonVal;  //button value; enum-type : E_PsdkAppFuncButtonVal;
                        //attention : this value have meaning when set value.

    int32_t switchVal;  //switch value; enum-type : E_PsdkAppFuncSwitchVal

    int32_t scaleVal;   //scale vale; this value is 0 ~ 100.

    int32_t listVal;    //Indicate the choose list Item number, Numbering start with 0.
    int32_t intInputBoxVal; //Indicate the int input box value.

    int32_t data;
} U_AppFuncWidgetValue;

typedef struct {
    uint8_t widgetType; // enum-type : E_PsdkAppFuncWidgetType
    uint8_t widgetIndex;

    U_AppFuncWidgetValue widgetValue;
} T_PsdkAppFuncWidgetValueItem;

// PSDK_APPFUNC_CMDID_TT_APP_TO_LOAD
typedef struct {
    uint8_t data[APPFUNC_APP_TO_LOAD_MAX_LEN];
} T_PsdkAppFuncTransAppToLoadReq;

typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkAppFuncTransAppToLoadAck;

// PSDK_APPFUNC_CMDID_TT_LOAD_TO_APP
typedef struct {
    uint8_t data[APPFUNC_LOAD_TO_APP_MAX_LEN];
} T_PsdkAppFuncTransLoadToAppReq;

typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkAppFuncTransLoadToAppAck;

//PSDK_APPFUNC_CMDID_PUSH_FLOATING_WINDOW_MSG
typedef struct {
    uint8_t msg[APPFUNC_FLOAT_WINDOW_MSG_MAX_SIZE];
} T_PsdkAppFuncPushFloatingWindowMsgReq;

typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkAppFuncPushFloatWindowMsgAck;

//PSDK_APPFUNC_CMDID_GET_WIDGET_LIST_LENGTH
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkAppFuncGetWidgetListLengthReq;

typedef struct {
    uint8_t ackCode; // enum-type : E_PsdkCmdAckCode
    uint8_t widgetListLength;
} T_PsdkAppFuncGetWidgetListLengthAck;

//PSDK_APPFUNC_CMDID_GET_WIDGET_LIST_VALUE
typedef struct {
    uint8_t widgetListSubscript;
} T_PsdkAppFuncGetWidgetListValueReq;

typedef struct {
    uint8_t widgetType; // enum-type : E_PsdkAppFuncWidgetType
    uint8_t widgetIndex;
    uint8_t widgetName[APPFUNC_MAX_WIDGET_NAME_SIZE];

    union {
        struct {
            PSDK_EMPTY_STRUCT
        } buttonAttribute;

        struct {
            PSDK_EMPTY_STRUCT
        } switchAttribute;

        struct {
            PSDK_EMPTY_STRUCT
        } scaleAttribute;

        struct {
            uint8_t listItemNum;
            uint8_t listItemName[APPFUNC_LIST_MAX_ITEM_NUM][APPFUNC_LIST_MAX_ITEM_NAME_SIZE];
        } listAttribute;

        struct {
            uint8_t promptChar[APPFUNC_INT_INPUT_BOX_PROMPT_CHAR_MAX_SIZE];
        } intInputBoxAttribute;
    };
} T_PsdkAppFuncWidgetProperty;

typedef struct {
    uint8_t ackCode;
    T_PsdkAppFuncWidgetProperty prop;
} T_PsdkAppFuncGetWidgetListValueAck;

//PSDK_APPFUNC_CMDID_GET_WIDGET_GROUP_COUNT
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkAppFuncGetWidgetGroupCountReq;

typedef struct {
    uint8_t ackCode;
    uint8_t groupCount;
} T_PsdkAppFuncGetWidgetGroupCountAck;

//PSDK_APPFUNC_CMDID_GET_WIDGET_GROUP_VALUE
typedef struct {
    uint8_t groupNum;
} T_PsdkAppFuncGetWidgetGroupValueReq;

typedef struct {
    uint8_t ackCode; // enum-type : E_PsdkCmdAckCode

    uint8_t widgetValueCount;
    T_PsdkAppFuncWidgetValueItem widgetValue[APPFUNC_WIDGET_VALUE_GROUP_MAX_ITEM_COUNT];
} T_PsdkAppFuncGetWidgetGroupValueAck;

// PSDK_APPFUNC_CMDID_SET_WIDGET_VALUE
typedef struct {
    T_PsdkAppFuncWidgetValueItem widgetValue;
} T_PsdkAppFuncSetWidgetValueReq;

typedef struct {
    uint8_t ackCode;
} T_PsdkAppFuncSetWidgetValueAck;

#pragma pack()

#ifdef __cplusplus
}
#endif

#endif //PSDK_CMDSET_APP_FUNC_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/

