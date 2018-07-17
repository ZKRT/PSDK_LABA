
#ifndef _DJI_RING_BUFFER_H_
#define _DJI_RING_BUFFER_H_

#include <stdint.h>

//Note: not need lock for just one producer / one consumer
//need mutex to protect for multi-producer / multi-consumer

typedef struct _ringBuffer {
    uint8_t *bufferPtr;
    uint16_t bufferSize;

    uint16_t readIndex;
    uint16_t writeIndex;
} T_RingBuffer;

void RingBuf_Init(T_RingBuffer *pthis, uint8_t *pBuf, uint16_t bufSize);

uint16_t RingBuf_Put(T_RingBuffer *pthis, const uint8_t *pData, uint16_t dataLen);
uint16_t RingBuf_Get(T_RingBuffer *pthis, uint8_t *pData, uint16_t dataLen);
uint16_t RingBuf_GetUnusedSize(T_RingBuffer *pthis);

#endif


