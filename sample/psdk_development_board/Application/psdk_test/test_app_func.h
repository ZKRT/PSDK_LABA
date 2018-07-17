#ifndef TEST_APP_FUNC_H
#define TEST_APP_FUNC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <psdk.h>

//receive from mobile sdk function
void Test_ReceiveFromMobileSDKFunc(const uint8_t *pData, uint16_t dataLen);

//DJI Pilot Custom Widget function
extern const T_PsdkAppFuncWidgetListItem *g_TestWidgetList;
extern const uint8_t g_TestWidgetCount;
E_PsdkStat Test_GetWidgetValueFunc(E_PsdkAppFuncWidgetType widgetType, uint8_t widgetIndex, U_AppFuncWidgetValue *pWidgetValue);
E_PsdkStat Test_SetWidgetValueFunc(E_PsdkAppFuncWidgetType widgetType, uint8_t widgetIndex, const U_AppFuncWidgetValue *pWidgetValue);

#ifdef __cplusplus
}
#endif

#endif //M4_TANSFERRING_TEST_APP_FUNC_H

/****************** (C) COPYRIGHT DJI Innovations *****END OF FILE****/
