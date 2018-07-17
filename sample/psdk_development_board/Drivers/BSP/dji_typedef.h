
#ifndef TRANSFER_RING_DJI_TYPEDEF_H
#define TRANSFER_RING_DJI_TYPEDEF_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef void                VOID;
typedef char                CHAR;
typedef unsigned char       Bool;
typedef unsigned char       BOOLEAN;

#define STATIC              static

#define INTERFACE
#define RTN_SUCCESS     0
#define RTN_FAILURE     -1

#define BOOL            uint8_t

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

typedef enum {
    RT_STAT_OK              = 0x00,
    RT_STAT_ERR_TIMEOUT     = 0x01,
    RT_STAT_ERR_ALLOC       = 0x02,
    RT_STAT_ERR_BUSY        = 0x03,
    RT_STAT_ERR_PARAM       = 0x04,
    RT_STAT_ERR_ACK_LEN     = 0x05,

    RT_STAT_ERR             = 0xFF,
}E_RtStat;

#endif //TRANSFER_RING_DJI_TYPEDEF_H
