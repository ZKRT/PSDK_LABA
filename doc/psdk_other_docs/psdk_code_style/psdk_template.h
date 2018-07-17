/**
  ******************************************************************************
  * @file    psdk_template.h
  * @version V0.0.0
  * @date    10-August-2017
  * @brief   This file to indicate psdk coding style and comment style.
  *
  * @copyright 2017 DJI. All right reserved.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PSDK_TEMPLATE_H
#define PSDK_TEMPLATE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Defines, configurable -----------------------------------------------------*/
#define PSDK_TEMPLATE_MAX_BUFFER_SIZE   256

/* Defines, fixed ------------------------------------------------------------*/
#define PSDK_TEMPLATE_SUCCESS   0
#define PSDK_TEMPLATE_FAILURE   -1
/**
 * @defgroup psdk_some_flag
 * @{
 */
#define PSDK_SOME_FLAG_AAA  1    /*!< define line comment */
#define PSDK_SOME_FLAG_BB   2    /*!< define line comment.
                                 if comment is too long , split line */
#define PSDK_SOME_FLAG_C    3

#define IS_PSDK_SOME_FLAG(FLAG)   (((FLAG) == PSDK_SOME_FLAG_AAA) || \
                                   ((FLAG) == PSDK_SOME_FLAG_BBB) || \
                                   ((FLAG) == PSDK_SOME_FLAG_CCC))
/**
 * @}
 */

/* Exported types ------------------------------------------------------------*/
/**
 * @brief enum brief comment
 */
typedef enum {
    TEMPLATE_COLOR_RED = 0,
    TEMPLATE_COLOR_GREED = 1,
    TEMPLATE_COLOR_BLUE = 2,
} E_TemplateColor;

/**
  * @brief  struct brief comment
  */
typedef struct {
    uint8_t structMember1;        /*!< struct member comment. */
    uint8_t longStructMember2;    /*!< struct member comment. */

    uint8_t someFlag;             /*!< if this value use marco define ,must use defgroup to indicate, and comment here
                                  use ref. for example:
                                  someFlag of psdk template. This parameter can be a value of @ref psdk_some_flag */
} T_StructDefine;

typedef void (*PsdkTemplateFunc)(void);

typedef int Inttype;

/* use pack(1) to transfer struct */
#pragma pack(1)
typedef struct {
    uint8_t structMember1;
    uint32_t structMember2;
} T_StructProtocolCommunication;
#pragma pack()

/* Exported macro ------------------------------------------------------------*/
/**
 * @brief exported macro comment in headfile
 */
#define PSDK_TEMPLATE_MIN(a, b) (((a)<(b))?(a):(b))

/* Exported functions --------------------------------------------------------*/
/**
 * @brief exported function comment in headfile
 */
void PsdkTemplate_Init(void);

/**
 * @brief send data
 * @param buffer : the buffer point send data
 * @param len : send data length
 * @return if >= 0, indicate the real send data length; if < 0, indicate the -ErrorCode for send failure reason.
 */
int PsdkTemplate_Send(const uint8_t *buffer, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif //PSDK_TEMPLATE_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/

/* other rules */

/* rule : file encoding use UTF8 */

/* rule : max line length 120 characters----------------------------------------------------------------------------- */

/* rule: line separator \r\n */

/* rule: use clion auto code format tool.
 * if not want to format some code , use @formatter:off & @formatter:on to disable code format, for example :
 */
//@formatter:off
extern int              g_testCodeFormatOFF;
//@formatter:on