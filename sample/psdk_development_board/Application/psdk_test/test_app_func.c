/*********************************************************************
*       Includes
**********************************************************************
*/

#include "test_app_func.h"
#include "led_button_switch.h"
#include <string.h>

/*********************************************************************
*       Defines, configurable
**********************************************************************
*/
//unique index define
#define SWITCH1_INDEX   0
#define SWITCH2_INDEX   1
#define BUTTON1_INDEX   2
#define SCALE1_INDEX    3
#define INPUT1_INDEX    4
#define LIST1_INDEX     5
#define BUTTON2_INDEX   6
#define BUTTON3_INDEX   7
#define LIST3_INDEX     8
#define LIST4_INDEX     9
#define LIST2_INDEX     10
#define INPUT2_INDEX    11

#define BUTTON4_INDEX   12

/*********************************************************************
*       Static data
**********************************************************************
*/

////@formatter:off
//static const T_PsdkAppFuncWidgetListItem s_TestWidgetList[] = {
//APPFUNC_DEF_SWITCH_WIDGET(SWITCH1_INDEX, "Red LED"),
//APPFUNC_DEF_SWITCH_WIDGET(SWITCH2_INDEX, "Blue LED"),
//    
//APPFUNC_DEF_BUTTON_WIDGET(BUTTON1_INDEX, "Button_1"),
//APPFUNC_DEF_SCALE_WIDGET(SCALE1_INDEX, "Scale_1"),
//APPFUNC_DEF_INT_INPUT_BOX_WIDGET(INPUT1_INDEX, "InputBox_1", "Unit : m"),
//APPFUNC_DEF_LIST_WIDGET(LIST1_INDEX, "List_1", 3, "CH1", "CH2", "CH3"),

//APPFUNC_DEF_BUTTON_WIDGET(BUTTON2_INDEX, "Button_2"),

//APPFUNC_DEF_BUTTON_WIDGET(BUTTON3_INDEX, "Button_3"),
//APPFUNC_DEF_LIST_WIDGET(LIST3_INDEX, "List_3", 10, "CH1", "CH2", "CH3", "CH4", "CH5", "CH6", "CH7", "CH8", "CH9", "CH10"),
//APPFUNC_DEF_LIST_WIDGET(LIST4_INDEX, "List_4", 2, "TEST1", "TEST2"),
//APPFUNC_DEF_LIST_WIDGET(LIST2_INDEX, "List_5", 1, "TEST_CHOOSE1"),
//APPFUNC_DEF_INT_INPUT_BOX_WIDGET(INPUT2_INDEX, "InputBox_2", "Unit : ms"),
//};
////@formatter:on

//@formatter:off  //add by yanly180713
static const T_PsdkAppFuncWidgetListItem s_TestWidgetList[] = {
APPFUNC_DEF_SWITCH_WIDGET(SWITCH1_INDEX, "hong deng"),
APPFUNC_DEF_SWITCH_WIDGET(SWITCH2_INDEX, "lan deng"),
    
APPFUNC_DEF_BUTTON_WIDGET(BUTTON1_INDEX, "an niu 1"),
APPFUNC_DEF_SCALE_WIDGET(SCALE1_INDEX, "Scale_1"),
APPFUNC_DEF_INT_INPUT_BOX_WIDGET(INPUT1_INDEX, "InputBox_1", "Unit : m"),
APPFUNC_DEF_LIST_WIDGET(LIST1_INDEX, "List_1", 3, "CH1", "CH2", "CH3"),

APPFUNC_DEF_BUTTON_WIDGET(BUTTON2_INDEX, "Button_2"),

APPFUNC_DEF_BUTTON_WIDGET(BUTTON3_INDEX, "Button_3"),
APPFUNC_DEF_LIST_WIDGET(LIST3_INDEX, "List_3", 10, "CH1", "CH2", "CH3", "CH4", "CH5", "CH6", "CH7", "CH8", "CH9", "CH10"),
APPFUNC_DEF_LIST_WIDGET(LIST4_INDEX, "List_4", 2, "TEST1", "TEST2"),
APPFUNC_DEF_LIST_WIDGET(LIST2_INDEX, "List_5", 1, "TEST_CHOOSE1"),
APPFUNC_DEF_INT_INPUT_BOX_WIDGET(INPUT2_INDEX, "InputBox_2", "Unit : ms"),

	
APPFUNC_DEF_BUTTON_WIDGET(BUTTON4_INDEX, "Button_4_test_yanly"),	
};
//@formatter:on

const T_PsdkAppFuncWidgetListItem *g_TestWidgetList = s_TestWidgetList;
const uint8_t g_TestWidgetCount = sizeof(s_TestWidgetList) / sizeof(T_PsdkAppFuncWidgetListItem);

/*********************************************************************
*       Static functions
**********************************************************************
*/
//static U_AppFuncWidgetValue button1Val; //buttonVal get not have meaning

static U_AppFuncWidgetValue switch1Val = {.switchVal = PSDK_APPFUNC_SWITCH_VAL_OFF};
static U_AppFuncWidgetValue scale1Val = {.scaleVal = 50};
static U_AppFuncWidgetValue input1Val = {.intInputBoxVal = 200};
static U_AppFuncWidgetValue list1Val = {.listVal = 1};

static U_AppFuncWidgetValue switch2Val = {.switchVal = PSDK_APPFUNC_SWITCH_VAL_OFF};

static U_AppFuncWidgetValue list3Val = {.listVal = 9};
static U_AppFuncWidgetValue list4Val = {.listVal = 0};
static U_AppFuncWidgetValue list2Val = {.listVal = 0};
static U_AppFuncWidgetValue input2Val = {.intInputBoxVal = 2000};
static char receivePrint[1024];

/*********************************************************************
*       Export functions
**********************************************************************
*/

void Test_ReceiveFromMobileSDKFunc(const uint8_t *pData, uint16_t dataLen)
{
    memcpy(receivePrint, pData, dataLen);
    receivePrint[dataLen] = 0;
    PSDK_LOG_DEBUG("%s",receivePrint);
}

E_PsdkStat
Test_GetWidgetValueFunc(E_PsdkAppFuncWidgetType widgetType, uint8_t widgetIndex, U_AppFuncWidgetValue *pWidgetValue)
{
    switch (widgetIndex) {
        case SWITCH1_INDEX:
            *pWidgetValue = switch1Val;
            break;
        case SWITCH2_INDEX:
            *pWidgetValue = switch2Val;
            break;

        case SCALE1_INDEX:
            *pWidgetValue = scale1Val;
            break;
        case INPUT1_INDEX:
            *pWidgetValue = input1Val;
            break;
        case INPUT2_INDEX:
            *pWidgetValue = input2Val;
            break;

        case LIST1_INDEX:
            *pWidgetValue = list1Val;
            break;
        case LIST2_INDEX:
            *pWidgetValue = list2Val;
            break;
        case LIST3_INDEX:
            *pWidgetValue = list3Val;
            break;
        case LIST4_INDEX:
            *pWidgetValue = list4Val;
            break;
        default:
            break;
    }

    return PSDK_STAT_OK;
}

E_PsdkStat Test_SetWidgetValueFunc(E_PsdkAppFuncWidgetType widgetType, uint8_t widgetIndex,
                                   const U_AppFuncWidgetValue *pWidgetValue)
{
    switch (widgetIndex) {
        case BUTTON1_INDEX:
            if (pWidgetValue->buttonVal == PSDK_APPFUNC_BUTTON_VAL_PRESS_DOWN) {
                PSDK_LOG_DEBUG("Button1 Press Down");
            } else if (pWidgetValue->buttonVal == PSDK_APPFUNC_BUTTON_VAL_RELEASE_UP) {
                PSDK_LOG_DEBUG("Button1 Release Up");
            }
            break;
        case BUTTON2_INDEX:
            if (pWidgetValue->buttonVal == PSDK_APPFUNC_BUTTON_VAL_PRESS_DOWN) {
                PSDK_LOG_DEBUG("Button2 Press Down");
            } else if (pWidgetValue->buttonVal == PSDK_APPFUNC_BUTTON_VAL_RELEASE_UP) {
                PSDK_LOG_DEBUG("Button2 Release Up");
            }
            break;
        case BUTTON3_INDEX:
            if (pWidgetValue->buttonVal == PSDK_APPFUNC_BUTTON_VAL_PRESS_DOWN) {
                PSDK_LOG_DEBUG("Button3 Press Down");
            } else if (pWidgetValue->buttonVal == PSDK_APPFUNC_BUTTON_VAL_RELEASE_UP) {
                PSDK_LOG_DEBUG("Button3 Release Up");
            }
            break;
        case BUTTON4_INDEX:
            if (pWidgetValue->buttonVal == PSDK_APPFUNC_BUTTON_VAL_PRESS_DOWN) {
                PSDK_LOG_DEBUG("Button4 Press Down");
            } else if (pWidgetValue->buttonVal == PSDK_APPFUNC_BUTTON_VAL_RELEASE_UP) {
                PSDK_LOG_DEBUG("Button4 Release Up");
            }
            break;            
        case SWITCH1_INDEX:
            PSDK_LOG_DEBUG("Switch1 Opt");
            switch1Val = *pWidgetValue;
            if (switch1Val.data == PSDK_APPFUNC_SWITCH_VAL_ON) {
                LED_Control(LED2_RED, LED_OPT_ON);
            } else {
                LED_Control(LED2_RED, LED_OPT_OFF);
            }
            break;
        case SWITCH2_INDEX:
            PSDK_LOG_DEBUG("Switch2 Opt");
            switch2Val = *pWidgetValue;
            if (switch2Val.data == PSDK_APPFUNC_SWITCH_VAL_ON) {
                LED_Control(LED3_BLUE, LED_OPT_ON);
            } else {
                LED_Control(LED3_BLUE, LED_OPT_OFF);
            }
            break;

        case SCALE1_INDEX:
            PSDK_LOG_DEBUG("Scale1 Opt");
            scale1Val = *pWidgetValue;
            break;

        case INPUT1_INDEX:
            PSDK_LOG_DEBUG("Input1 Opt");
            input1Val = *pWidgetValue;
            break;
        case INPUT2_INDEX:
            PSDK_LOG_DEBUG("Input2 Opt");
            input2Val = *pWidgetValue;
            break;

        case LIST1_INDEX:
            PSDK_LOG_DEBUG("List1 Opt");
            list1Val = *pWidgetValue;
            break;
        case LIST2_INDEX:
            PSDK_LOG_DEBUG("List2 Opt");
            list2Val = *pWidgetValue;
            break;
        case LIST3_INDEX:
            PSDK_LOG_DEBUG("List3 Opt");
            list3Val = *pWidgetValue;
            break;
        case LIST4_INDEX:
            PSDK_LOG_DEBUG("List4 Opt");
            list4Val = *pWidgetValue;
            break;
        default:
            break;
    }

    return PSDK_STAT_OK;
}

/****************** (C) COPYRIGHT DJI Innovations *****END OF FILE****/
