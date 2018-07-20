#include <app_config.h>
#include <psdk.h>
#include "led_button_switch.h"
#include "ms5607.h"
#include <string.h>
#include "sys.h"
#include "uart.h"
#include "log_printf.h"
#include <stdio.h>
#include "flash.h"

#include "app_infor.h"
#include "test_app_func.h"
#include "test_msg_push.h"
#include "test_payload_cam_emu.h"
#include "test_payload_gimbal_emu.h"

//Payload SDK User Info Set
T_PsdkUserInfo userInfo = {
        .APP_Name = USER_APP_NAME,
        .APP_Id = USER_APP_ID,
        .APP_Key = USER_APP_KEY,
        .DeveloperAccount = USER_DEVELOPER_ACCOUNT
};

static T_PsdkUpper s_psdkUpperHandle;

static uint8_t s_uartRecBuf[PSDK_UART_REC_BUF_LEN];
static char printBuffer[512];

uint32_t can_uart_sw_settings = 0;

E_PsdkStat Psdk_Write(const uint8_t *pSendData, uint16_t dataLen)
{
    UART_Write(PSDK_UART_NUM, pSendData, dataLen);
    return PSDK_STAT_OK;
}

int Psdk_Read(uint8_t *pReadData, uint16_t dataLen)
{
    int res;

    res = UART_Read(PSDK_UART_NUM, pReadData, dataLen);

    return res;
}


void RunIndicateTask(void const *parameter)
{
    uint16_t cnt = 0;
    uint32_t setting = 0;

    while (1) {
        setting = flash_read_settings();
        if (can_uart_sw_settings != setting) {
            flash_wirte_settings(can_uart_sw_settings);
            Button_StartUpdate();
        }

        OS_DELAY(1);
        if (cnt++ > 1000) {
            LED_Control(LED1_GREEN, LED_OPT_TOGGLE);
            cnt = 0;
            PSDK_LOG_DEBUG("led indicate\n");
        }
    }
}

void PsdkTestTask(void const *parameter)
{
    double temp=10000000, press=0;
    uint16_t realSendLen;

    // Ms5607_Init();

    while (1) {
        // Ms5607_GetSenorData(&temp, &press);
		press++;
		temp--;
        sprintf(printBuffer, "Demo Sensor Info:\r\n\r\nBaro Pre = %f mbar\r\n\r\nBoard Temp = %f `C\r\n", press, temp);

        //push this info to DJI Pilot Floating Window
        PsdkAppFunc_PushMsgToFloatingWindow(&s_psdkUpperHandle, printBuffer);

        //transfer this info to MSDK
        PsdkAppFunc_TransferToApp(&s_psdkUpperHandle, (const uint8_t *) printBuffer, strlen(printBuffer) + 1,
                                  &realSendLen);
        OS_DELAY(1000);
    }
}

//Receive Psdk Data Process, all callback function process here.
void PrcocessPsdkRecTask(void const *parameter)
{
    int res = 0;

    while (1) {
        //res = UART_Read(PSDK_UART_NUM, s_uartRecBuf, sizeof(s_uartRecBuf));
        res = Psdk_Read(s_uartRecBuf, sizeof(s_uartRecBuf));

        if (res > 0) {
            //===================== psdk Recievie Function ==============================//
            //all callbacks process in this thread.
            PsdkUpper_ProcessReceiveData(&s_psdkUpperHandle, s_uartRecBuf, res);

        }

        osDelay(1);
    }
}

//init for the application
void application_init(void)
{
    //device init
    LED_Init();
    LED_Control(LED1_GREEN, LED_OPT_OFF);
    LED_Control(LED2_RED, LED_OPT_OFF);
    LED_Control(LED3_BLUE, LED_OPT_OFF);

    LOG_Init();

    UART_Init(PSDK_UART_NUM, 115200);

    Button_Init();

    // UART_SW_Init();
    // CAN_SW_Init();

    can_uart_sw_settings = flash_read_settings();
    // Button_StartUpdate();

    // Ms5607Spi_Init();

    //===================== psdk init ==============================//
    //base init
    PsdkUpper_Init(&s_psdkUpperHandle, &userInfo);
    PsdkUpper_RegSendFunction(&s_psdkUpperHandle, Psdk_Write);

    //app function init
    PsdkAppFunc_Init(&s_psdkUpperHandle);
    PsdkAppFunc_SetReceiveFromAppCallback(&s_psdkUpperHandle, Test_ReceiveFromMobileSDKFunc);

    PsdkAppFunc_SetWidgetList(&s_psdkUpperHandle, g_TestWidgetList, g_TestWidgetCount);
    PsdkAppFunc_RegGetWidgetValueCallback(&s_psdkUpperHandle, Test_GetWidgetValueFunc);
    PsdkAppFunc_RegSetWidgetValueCallback(&s_psdkUpperHandle, Test_SetWidgetValueFunc);

    //Msg subscribe Function init, callback functions in Application/psdk_test/test_msg_push.c
    PsdkMsgSub_Init(&s_psdkUpperHandle);
    PsdkMsgSub_RegMsgCallbackList(&s_psdkUpperHandle, &g_PushDataMsgCallbackList);

    // //Camera function Emulate Test, callback functions in Application/psdk_test/test_payload_cam_emu.c
    // //If want transfer video to Mobile SDK or DJI Pilot, this function must call to init Payload camera.
    // PsdkCamera_Init(&s_psdkUpperHandle, &g_testCameraHandler);

    // //Gimbal function Emulate Test, callback functions in Application/psdk_test/test_payload_gimbal_emu.c
    // PsdkGimbal_Init(&s_psdkUpperHandle, &g_testGimbalHandler);
    //===================== psdk init End ============================//

}


