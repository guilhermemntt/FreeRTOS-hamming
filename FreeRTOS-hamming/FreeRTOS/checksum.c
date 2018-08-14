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

#define checksumPARITY(n) ((0x6996 >> ((n^(n>>4))&0x0f))&0x01)

static inline uint8_t prvFls(uint16_t uiX)
{
          uint8_t uiR = 16;
  
          if (!uiX){
                  return 0;
		  }
          if (!(uiX & 0xff00u)) {
                  uiX <<= 8;
                  uiR -= 8;
          }
          if (!(uiX & 0xf000u)) {
                  uiX <<= 4;
                  uiR -= 4;
          }
          if (!(uiX & 0xc000u)) {
                  uiX <<= 2;
                  uiR -= 2;
          }
          if (!(uiX & 0x8000u)) {
                  uiX <<= 1;
                  uiR -= 1;
          }
         return uiR;
  }


ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack)
{
	uint8_t * pucDataP=pxStartOfStack+1;
	uint16_t usLength = pxEndOfStack-pxStartOfStack;
	uint8_t ucPoolH;
	uint16_t usHammingBits = 0;
	uint16_t usPBit;
	uint16_t i;
	uint16_t usPosBit;
	
	ucPoolH = 0;
	usPBit = 0;
	for(i=0;i<usLength;i++){
		ucPoolH ^= (*(pucDataP+i) & 0xAA);
	}
	usHammingBits += (checksumPARITY(ucPoolH))<<usPBit;
	
	ucPoolH = 0;
	usPBit = 1;
	for(i=0;i<usLength;i++){
		ucPoolH ^= (*(pucDataP+i) & 0xCC);
	}
	usHammingBits += (checksumPARITY(ucPoolH))<<usPBit;
	
	ucPoolH = 0;
	usPBit = 2;
	for(i=0;i<usLength;i++){
		ucPoolH ^= (*(pucDataP+i) & 0xF0);
	}
	usHammingBits += (checksumPARITY(ucPoolH))<<usPBit;
	
	usPBit=3;
	ucPoolH = 0;
	usPosBit = (1<<(usPBit-3));
	for(i=0;i<usLength;i++){
		if((i+1) & (usPosBit)){
			ucPoolH ^= (*(pucDataP+i));
		}
	}
	usHammingBits += (checksumPARITY(ucPoolH))<<usPBit;
	
	uint8_t pBitmax = prvFls(usLength*8);
	
	for(usPBit=4;usPBit<pBitmax;usPBit++){
		ucPoolH = 0;
		usPosBit = (1<<(usPBit-3));
		for(i=0;i<usLength;i++){
			if((i+1) & (usPosBit)){
				ucPoolH ^= (*(pucDataP+i));
			}
		}
		usHammingBits += (checksumPARITY(ucPoolH))<<usPBit;
	}
	return (ChecksumType_t)usHammingBits;
}


#elif ( configSUPPORT_TASK_CHECKSUM==4 )
	
    	ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack){}
	
#endif

#if ( configUSE_TASK_CHECKSUM_HOOK == 1 )

	void vApplicationTaskChecksumHook( void ){}

#endif


