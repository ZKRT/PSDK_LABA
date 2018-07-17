
#include "dji_ringbuffer.h"
#include <string.h>

#define RINGBUF_MIN(a, b) (((a)<(b))?(a):(b))

static uint16_t RingBuf_CutBufSizeToPowOfTwo(uint16_t bufSize)
{
    uint16_t i = 0;

    while (bufSize >> (i++) != 1);

    return (uint16_t) (1 << (i - 1));
}

void RingBuf_Init(T_RingBuffer *pthis, uint8_t *pBuf, uint16_t bufSize)
{
    pthis->readIndex = 0;
    pthis->writeIndex = 0;
    pthis->bufferPtr = pBuf;

    if (bufSize & (bufSize - 1)) {
        //buffer size is not pow of two , cut buf
        pthis->bufferSize = RingBuf_CutBufSizeToPowOfTwo(bufSize);
    } else {
        pthis->bufferSize = bufSize;
    }
}

/**
 * put a block of data into ring buffer
 */
uint16_t RingBuf_Put(T_RingBuffer *pthis, const uint8_t *pData, uint16_t dataLen)
{
    uint16_t writeUpLen;

    dataLen = RINGBUF_MIN(dataLen, (uint16_t) (pthis->bufferSize - pthis->writeIndex + pthis->readIndex));

    //fill up data
    writeUpLen = RINGBUF_MIN(dataLen, (uint16_t) (pthis->bufferSize - (pthis->writeIndex & (pthis->bufferSize - 1))));
    memcpy(pthis->bufferPtr + (pthis->writeIndex & (pthis->bufferSize - 1)), pData, writeUpLen);

    //fill begin data
    memcpy(pthis->bufferPtr, pData + writeUpLen, dataLen - writeUpLen);

    pthis->writeIndex += dataLen;

    return dataLen;
}

/**
 *  get a block of data from ring buffer
 */
uint16_t RingBuf_Get(T_RingBuffer *pthis, uint8_t *pData, uint16_t dataLen)
{
    uint16_t readUpLen;

    dataLen = RINGBUF_MIN(dataLen, (uint16_t) (pthis->writeIndex - pthis->readIndex));

    //get up data
    readUpLen = RINGBUF_MIN(dataLen, (uint16_t) (pthis->bufferSize - (pthis->readIndex & (pthis->bufferSize - 1))));
    memcpy(pData, pthis->bufferPtr + (pthis->readIndex & (pthis->bufferSize - 1)), readUpLen);

    //get begin data
    memcpy(pData + readUpLen, pthis->bufferPtr, dataLen - readUpLen);

    pthis->readIndex += dataLen;

    return dataLen;
}

/**
 * get unused size of ring buffer
 */
uint16_t RingBuf_GetUnusedSize(T_RingBuffer *pthis)
{
    return (uint16_t) (pthis->bufferSize - pthis->writeIndex + pthis->readIndex);
}
