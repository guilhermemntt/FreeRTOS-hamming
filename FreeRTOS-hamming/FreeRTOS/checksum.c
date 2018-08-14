#include "FreeRTOS.h"
#include "checksum.h"

#if( configSUPPORT_TASK_CHECKSUM==1 )

ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack)
{
	volatile StackType_t* i;
	uint16_t usChecksum = 0;
	for(i = pxEndOfStack ;i != pxStartOfStack ;i+=portSTACK_GROWTH)
	{
		usChecksum^=*i;
	}
	return usChecksum;
}

#elif( configSUPPORT_TASK_CHECKSUM==2 )

ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack)
{
	uint16_t	usPolinomio=0x8408;
	uint8_t	i;
	uint16_t	usData;
	uint16_t	usCrc;
	usCrc=0xffff;
	
	if(pxStartOfStack==pxEndOfStack){
		return	(~usCrc);
	}
	do{
		for (i = 0, usData = (uint16_t)0xff && *(pxStartOfStack-=portSTACK_GROWTH); i < 8; i++, usData >>= 1) {
			if((usCrc & 0x0001)^(usData & 0x0001)){
				usCrc = (usCrc >> 1)^usPolinomio;
			}
			else{
				usCrc >>= 1;
			}
		}
	} while (pxEndOfStack != pxStartOfStack);
	usCrc = ~usCrc;
	usData = usCrc;
	usCrc = (usCrc << 8)|(usData >> 8 & 0xff);
	return (usCrc);
}

#elif ( configSUPPORT_TASK_CHECKSUM==3 )

#define checksumPARITY(n) ((0x6996 >> ((n ^ (n >> 4)) & 0x0f)) & 0x01)

static inline uint16_t prvAbs(int16_t sX) {
	int16_t sT = (sX >> 15);
	return sT ^ (sX + sT);
}

static inline uint8_t prvFls(uint16_t usX) {
  uint8_t ucR = 16;

  if (!usX) {
    return 0;
  }
  if (!(usX & 0xff00u)) {
    usX <<= 8;
    ucR -= 8;
  }
  if (!(usX & 0xf000u)) {
    usX <<= 4;
    ucR -= 4;
  }
  if (!(usX & 0xc000u)) {
    usX <<= 2;
    ucR -= 2;
  }
  if (!(usX & 0x8000u)) {
    usX <<= 1;
    ucR -= 1;
  }
  return ucR;
}

ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t *pxEndOfStack) {  // pxStack
  uint8_t *pucDataP = pxStartOfStack - portSTACK_GROWTH;
  uint16_t usLength = pxEndOfStack - pxStartOfStack;
  uint8_t ucPoolH;
  uint16_t usHammingBits = 0;
  uint16_t usPBit;
  int16_t i;
  uint16_t usPosBit;
  uint8_t ucPBitMax;

  ucPoolH = 0;
  usPBit = 0;
  for (i = 0; i != usLength; i -= portSTACK_GROWTH) {
    ucPoolH ^= (*(pucDataP + i) & 0xAA);
  }
  usHammingBits += (checksumPARITY(ucPoolH)) << usPBit;

  ucPoolH = 0;
  usPBit = 1;
  for (i = 0; i != usLength; i -= portSTACK_GROWTH) {
    ucPoolH ^= (*(pucDataP + i) & 0xCC);
  }
  usHammingBits += (checksumPARITY(ucPoolH)) << usPBit;

  ucPoolH = 0;
  usPBit = 2;
  for (i = 0; i != usLength; i -= portSTACK_GROWTH) {
    ucPoolH ^= (*(pucDataP + i) & 0xF0);
  }
  usHammingBits += (checksumPARITY(ucPoolH)) << usPBit;

  usPBit = 3;
  ucPoolH = 0;
  usPosBit = (1 << (usPBit - 3));
  for (i = 0; i != usLength; i -= portSTACK_GROWTH) {
    if (prvAbs(i - portSTACK_GROWTH) & (usPosBit)) {
      ucPoolH ^= (*(pucDataP + i));
    }
  }
  usHammingBits += (checksumPARITY(ucPoolH)) << usPBit;

  ucPBitMax = prvFls(usLength * 8  * -portSTACK_GROWTH);

  for (usPBit = 4; usPBit < ucPBitMax; usPBit++) {
    ucPoolH = 0;
    usPosBit = (1 << (usPBit - 3));
    for (i = 0; i != usLength; i -= portSTACK_GROWTH) {
      if (prvAbs(i - portSTACK_GROWTH) & (usPosBit)) {
        ucPoolH ^= (*(pucDataP + i));
      }
    }
    usHammingBits += (checksumPARITY(ucPoolH)) << usPBit;
  }

  return usHammingBits;
}

#elif ( configSUPPORT_TASK_CHECKSUM==4 )
	
    	ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack){}
	
#endif

#if ( configUSE_TASK_CHECKSUM_HOOK == 1 )

	void vApplicationTaskChecksumHook( void ){}

#endif


