/**
 ******************************************************************************
 * @file    psdk_upper.h
 * @version V0.0.0
 * @date    2017/11/10
 * @brief   
 * This is the header file for "psdk_upper.c", defining the 
 * structures and (exported) function prototypes.
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
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PSDK_UPPER_H
#define PSDK_UPPER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <psdk_core.h>

/* Defines, configurable -----------------------------------------------------*/

/* Defines, fixed ------------------------------------------------------------*/

//if use can to communicate, can id set :
#define PSDK_CAN_ID_SEND        0x0021
#define PSDK_CAN_ID_RECEIVE     0x0012

/* Exported types ------------------------------------------------------------*/
/*! @brief This is the set of ID information of your application with PSDK.
 *
 */
typedef struct _PsdkUserInfo {
    char APP_Name[33];          //Payload SDK APP Name
    char APP_Id[17];            //Payload SDK APP ID
    char APP_Key[33];           //Payload SDK APP Key
    char DeveloperAccount[65];  //Developer Account Email
} T_PsdkUserInfo;

/*! @brief This is a structure type for defining a top-level structure for the 
 * integration of your application with PSDK.
 *
 * @details This structure type is used to instantiates an object for all the 
 * features that PSDK is capable of supporting.
 * Use this structure type to define a PSDK object in your code and you will
 * have access to the entire DJI PSDK API.
 *
 */
typedef struct _PsdkUpper {
    T_PsdkProt protHandle;
} T_PsdkUpper;

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
E_PsdkStat PsdkUpper_Init(T_PsdkUpper *psdkUpper, const T_PsdkUserInfo *userInfo);

E_PsdkStat PsdkUpper_ProcessReceiveData(T_PsdkUpper *psdkUpper, const uint8_t *pData, uint16_t len);
E_PsdkStat PsdkUpper_RegSendFunction(T_PsdkUpper *psdkUpper, PsdkSendCallbackFunc sendCallbackFunc);

#ifdef __cplusplus
}
#endif

#endif //PSDK_UPPER_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
