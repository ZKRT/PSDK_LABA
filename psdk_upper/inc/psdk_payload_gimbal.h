/**
 **********************************************************************
 * @file    psdk_payload_gimbal.h
 * @brief
 * This is the header file for "psdk_payload_gimbal.c", defining the 
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

#ifndef PSDK_GIMBAL_H
#define PSDK_GIMBAL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
*       Includes
**********************************************************************
*/

#include "psdk_core.h"
#include "psdk_ack_code.h"

/*********************************************************************
*       Defines, configurable
**********************************************************************
*/


/*********************************************************************
*       Defines, fixed
**********************************************************************
*/

/*********************************************************************
*       Types
**********************************************************************
*/

typedef struct {
    void (*GetGimbalState)(const T_PsdkGimbalGetGimbalStateReq *req, T_PsdkGimbalGetGimbalStateAck *ack);
    void (*SetGimbalMode)(const T_PsdkGimbalSetGimbalModeReq *req, T_PsdkGimbalSetGimbalModeAck *ack);
    void (*ReturnHead)(const T_PsdkGimbalReturnHeadReq *req, T_PsdkGimbalReturnHeadAck *ack);

    void (*ControlSpeed)(const T_PsdkGimbalControlSpeedReq *req, T_PsdkGimbalControlSpeedAck *ack);

    void (*StartCalibration)(const T_PsdkGimbalStartCalibrationReq *req, T_PsdkGimbalStartCalibrationAck *ack);
} T_PsdkGimbalHandler;

/*********************************************************************
*       Export functions
**********************************************************************
*/

E_PsdkStat PsdkGimbal_Init(T_PsdkUpper *psdkUpper, const T_PsdkGimbalHandler *gimbalHandler);

#ifdef __cplusplus
}
#endif

#endif //PSDK_PAYLOAD_GIMBAL_H

/****************** (C) COPYRIGHT DJI Innovations *****END OF FILE****/
