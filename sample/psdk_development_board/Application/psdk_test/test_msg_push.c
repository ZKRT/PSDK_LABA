
#include <psdk.h>

//static void bandWidthMsgCallback(const T_BandWidthMsg *bandWidthMsg)
//{
////    PSDK_LOG_DEBUG("Receive bandwidth message", OS_GET_TIME_MS);
//}

static void uavAttitudeMsgCallback(const T_UavAttitudeMsg *uavAttitudeMsg)
{
//    PSDK_LOG_DEBUG("Receive Uav AttitudeMsg");
}

static void batteryInfoMsgCallback(const T_BatteryInfoMsg *batteryInfoMsg)
{
//    PSDK_LOG_DEBUG("Receive Battery Info Msg");
}

static void gpsInfoMsgCallback(const T_GPSInfoMsg *gpsInfoMsg)
{
//    PSDK_LOG_DEBUG("Receive gps info msg");
}

static void uavStateMsgCallback(const T_UavStateMsg *uavStateMsg)
{
//    PSDK_LOG_DEBUG("Receive Uav state Msg");
}

static void appDateTimeMsgCallback(const T_AppDateTimeMsg *appDateTimeMsg)
{
//    PSDK_LOG_DEBUG("Receive AppdateTime Msg");
}

//message subscribe function list
const T_PsdkPushDataMsgCallbackList g_PushDataMsgCallbackList = {
        .bandWidthMsgCallback = NULL, // //if not support, callback function can be null
        .uavAttitudeMsgCallback = uavAttitudeMsgCallback,
        .batteryInfoMsgCallback = batteryInfoMsgCallback,
        .gpsInfoMsgCallback = gpsInfoMsgCallback,
        .uavStateMsgCallback = uavStateMsgCallback,
        .appDateTimeMsgCallback = appDateTimeMsgCallback,
};

/****************** (C) COPYRIGHT DJI Innovations *****END OF FILE****/
