/**
 ******************************************************************************
 * @file    psdk_proto_parse.h
 * @version V0.0.0
 * @date    2017/11/9
 * @brief   
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

#ifndef PSDK_PROTO_PARSE_H
#define PSDK_PROTO_PARSE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "psdk_proto_common.h"

/* Defines, configurable -----------------------------------------------------*/

/* Defines, fixed ------------------------------------------------------------*/
/**
 * @defgroup PsdkProtParse_ErrorCode
 * @{
 */
#define ERRCODE_PSDK_PROT_PARSE_NO_FRAME         1

#define ERRC0DE_PSDK_PROT_PARSE_FRAME_LENGTH     2
#define ERRCODE_PSDK_PROT_PARSE_CRC16            3
#define ERRCODE_PSDK_PROT_PARSE_CRC32            4
/**
 * @}
 */

/* Exported types ------------------------------------------------------------*/
typedef struct {
    uint8_t parseBuffer[PSDK_PROT_MAX_FRAME_LEN];

    uint16_t parseIndex;
} T_PsdkProtParse;

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

void PsdkProtParse_Init(T_PsdkProtParse *protParse);

/**
 * @brief parse one byte
 * @param protParse : protoParse Handler
 * @param byteData : one byte data
 * @param pParseFrame : if parse success, *pParseFrame point to the parse frame buffer
 * @return if return value > 0, parse success, return the frameLen of frame;
 *         if return value < 0, parse error ,return -ErrorCode , ErrorCode @ref PsdkProtParse_ErrorCode
 */
int PsdkProtParse_AddByte(T_PsdkProtParse *protParse, uint8_t byteData, uint8_t **pParseFrame);

#ifdef __cplusplus
}
#endif

#endif //PSDK_PROTO_PARSE_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
