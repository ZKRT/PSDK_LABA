/**
 ******************************************************************************
 * @file    psdk_cmdset_payload_state.h
 * @version V0.0.0
 * @date    10-August-2017
 * @brief   
 * This file defines the payload state cmd-set.
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
#ifndef PSDK_CMDSET_PAYLOAD_STATE_H
#define PSDK_CMDSET_PAYLOAD_STATE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <psdk_typedef.h>

/* Defines, configurable -----------------------------------------------------*/

#define PAYLOADSTATE_MAX_PINGDATA_SIZE          32

#define PAYLOADSTATE_MAX_PRODUCT_NAME_SIZE      32
#define PAYLOADSTATE_MAX_PRODUCT_ID_SIZE        16
#define PAYLOADSTATE_MAX_DEV_ACCOUNT_SIZE       64

/* Defines, fixed ------------------------------------------------------------*/
#pragma pack(1)

//Payload State Cmd ID
typedef enum {
    PSDK_PAYLOADSTATE_CMDID_IDENTITY_VERIFY = 0x01,
    PSDK_PAYLOADSTATE_CMDID_SDK_VERSION = 0x02,
    PSDK_PAYLOADSTATE_CMDID_LINK_HANDSHAKE = 0x03,
    PSDK_PAYLOADSTATE_CMDID_PRODUCT_INFO = 0x04,
} E_PsdkPayLoadStateCmd;

// PSDK_PAYLOADSTATE_CMDID_IDENTITY_VERIFY
typedef struct _LoadStateIdentityVerifyReq {
    uint8_t random[16];
} T_LoadStateIdentityVerifyReq;

typedef struct _LoadStateIdentityVerifyAck {
    uint8_t ackCode;
    uint8_t md5[16];
} T_LoadStateIdentityVerifyAck;

// PSDK_PAYLOADSTATE_CMDID_SDK_VERSION
typedef struct _LoadStatePsdkVersionAck {
    uint8_t ackCode;
    union {
        struct {
            uint32_t verDebug   : 8;
            uint32_t verModify  : 8;
            uint32_t verMinor   : 8;
            uint32_t verMajor   : 8;
        } ver;
        uint32_t data;
    } version;
} T_LoadStatePsdkVersionAck;


// PSDK_PAYLOADSTATE_CMDID_LINK_HANDSHAKE
typedef struct _LoadStateLinkHandShakeReq {
    uint8_t pingData[PAYLOADSTATE_MAX_PINGDATA_SIZE];    //len : 1 ~ PAYLOADSTATE_MAX_PINGDATA_SIZE
} T_LoadStateLinkHandShakeReq;

typedef struct _LoadStateLinkHandShakeAck {
    uint8_t ackCode;
    uint8_t pingData[PAYLOADSTATE_MAX_PINGDATA_SIZE];    //len : 1 ~ PAYLOADSTATE_MAX_PINGDATA_SIZE
} T_LoadStateLinkHandShakeAck;

// PSDK_PAYLOADSTATE_CMDID_PRODUCT_INFO
typedef struct _LoadStateGetProductInfoAck {
    uint8_t ackCode;
    char productName[PAYLOADSTATE_MAX_PRODUCT_NAME_SIZE];
    char productID[PAYLOADSTATE_MAX_PRODUCT_ID_SIZE];
    char developerAccount[PAYLOADSTATE_MAX_DEV_ACCOUNT_SIZE];
} T_LoadStateGetProductInfoAck;

#pragma pack()

#ifdef __cplusplus
}
#endif

#endif //PSDK_CMDSET_PAYLOAD_STATE_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
