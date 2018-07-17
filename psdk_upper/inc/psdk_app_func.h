/**
 ******************************************************************************
 * @file    psdk_app_func.h
 * @version V0.0.0
 * @date    10-August-2017
 * @brief   
 * This file defines the app function interface.
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
#ifndef PSDK_APP_FUNC_H
#define PSDK_APP_FUNC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <psdk_upper.h>
#include "psdk_cmdset.h"

/* Defines, configurable -----------------------------------------------------*/

/* Defines, fixed ------------------------------------------------------------*/

#define APPFUNC_DEF_BUTTON_WIDGET(index, nameStr)  \
{ \
    .widgetType = PSDK_APPFUNC_WIDGET_TYPE_BUTTON, \
    .widgetIndex = index, \
    .widgetName = nameStr, \
}

#define APPFUNC_DEF_SWITCH_WIDGET(index, nameStr) \
{ \
    .widgetType = PSDK_APPFUNC_WIDGET_TYPE_SWITCH, \
    .widgetIndex = index, \
    .widgetName = nameStr, \
}

#define APPFUNC_DEF_SCALE_WIDGET(index, nameStr) \
{ \
    .widgetType = PSDK_APPFUNC_WIDGET_TYPE_SCALE, \
    .widgetIndex = index, \
    .widgetName = nameStr, \
}

#define APPFUNC_DEF_LIST_WIDGET(index, nameStr, chooseCount, choose1Str, ...) \
{ \
    .widgetType = PSDK_APPFUNC_WIDGET_TYPE_LIST, \
    .widgetIndex = index, \
    .widgetName = nameStr, \
    .listAttribute.listItemNum = chooseCount, \
    .listAttribute.listItemName = {choose1Str,##__VA_ARGS__}, \
}

#define APPFUNC_DEF_INT_INPUT_BOX_WIDGET(index, nameStr, promtStr) \
{ \
    .widgetType = PSDK_APPFUNC_WIDGET_TYPE_INT_INPUT_BOX, \
    .widgetIndex = index, \
    .widgetName = nameStr, \
    .intInputBoxAttribute.promptStr = promtStr, \
}

/* Exported types ------------------------------------------------------------*/
typedef void (*ReceiveFromAppFunc)(const uint8_t *pData, uint16_t dataLen);

typedef E_PsdkStat (*GetWidgetValueFunc)(E_PsdkAppFuncWidgetType widgetType, uint8_t widgetIndex,
                                         U_AppFuncWidgetValue *pWidgetValue);

typedef E_PsdkStat (*SetWidgetValueFunc)(E_PsdkAppFuncWidgetType widgetType, uint8_t widgetIndex,
                                         const U_AppFuncWidgetValue *pWidgetValue);

typedef struct {
    E_PsdkAppFuncWidgetType widgetType;

    uint8_t widgetIndex;    //unique index for widget, Numbering start with 0; the DJI Pilot widget show sequence
                            //relay on the widgetIndex.

    //widget name max length : APPFUNC_MAX_WIDGET_NAME_SIZE (32)
    const char *widgetName;

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
            //list item Name max length : APPFUNC_LIST_MAX_ITEM_NAME_SIZE (16)
            const char *listItemName[APPFUNC_LIST_MAX_ITEM_NUM];
        } listAttribute;

        struct {
            //promptStr max length : APPFUNC_INT_INPUT_BOX_PROMPT_CHAR_MAX_SIZE (32)
            const char *promptStr;
        } intInputBoxAttribute;
    };
} T_PsdkAppFuncWidgetListItem;

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
//init
E_PsdkStat PsdkAppFunc_Init(T_PsdkUpper *psdkUpper);

//Communication with Mobile SDK
E_PsdkStat PsdkAppFunc_TransferToApp(T_PsdkUpper *psdkUpper, const uint8_t *pSendData, uint16_t needSendLen,
                                     uint16_t *pRealSendLen);
E_PsdkStat PsdkAppFunc_SetReceiveFromAppCallback(T_PsdkUpper *psdkUpper, ReceiveFromAppFunc func);

//DJI Pilot Widget Function
//floating window max msg length : APPFUNC_FLOAT_WINDOW_MSG_MAX_SIZE (128)
E_PsdkStat PsdkAppFunc_PushMsgToFloatingWindow(T_PsdkUpper *psdkUpper, const char *msg);

E_PsdkStat PsdkAppFunc_SetWidgetList(T_PsdkUpper *psdkUpper, const T_PsdkAppFuncWidgetListItem *widgetList,
                                     uint8_t widgetItemCount);

//Note : the Button Widget not need get value.
E_PsdkStat PsdkAppFunc_RegGetWidgetValueCallback(T_PsdkUpper *psdkUpper, GetWidgetValueFunc getWidgetValueFunc);

E_PsdkStat PsdkAppFunc_RegSetWidgetValueCallback(T_PsdkUpper *psdkUpper, SetWidgetValueFunc setWidgetValueFunc);

#ifdef __cplusplus
}
#endif

#endif //PSDK_APP_FUNC_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
