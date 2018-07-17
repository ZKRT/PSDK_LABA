/**
 ******************************************************************************
 * @file    psdk_cmdset.h
 * @version V0.0.0
 * @date    10-August-2017
 * @brief   
 * This file defines the PSDK cmd set.
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
#ifndef PSDK_CMDSET_H
#define PSDK_CMDSET_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "psdk_core.h"
#include "psdk_cmdset_define/psdk_cmdset_payload_state.h"
#include "psdk_cmdset_define/psdk_cmdset_app_func.h"
#include "psdk_cmdset_define/psdk_cmdset_msg_push.h"

#include "psdk_cmdset_define/psdk_cmdset_camera.h"
#include "psdk_cmdset_define/psdk_cmdset_gimbal.h"

/* Defines, configurable -----------------------------------------------------*/

/* Defines, fixed ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/*! @brief PSDK command sets "enum" definition. 
 *
 * @details This enum type is used to specify all the PSDK command set with "enum". 
 * The command sets include:
 * 1. Payload State Command Set 
 * 2. APP Function Command Set 
 * 3. Data Push Command Set 
 * 4. Camera Command Set 
 * 5. Gimbal Command Set 
 */
//define cmd-set
typedef enum {
    PSDK_CMDSET_PAYLOAD_STATE = 0x01,
    PSDK_CMDSET_APP_FUNC = 0x02,
    PSDK_CMDSET_DATA_PUSH = 0x03,

    PSDK_CMDSET_CAMERA = 0x04,
    PSDK_CMDSET_GIMBAL = 0x05,
} E_PsdkCmdSet;

#ifdef __cplusplus
}
#endif

#endif //PSDK_CMDSET_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
