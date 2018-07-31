#include "FreeRTOS.h"
#include "checksum.h"

#if( configSUPPORT_TASK_CHECKSUM==1 )

ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack)
{
	volatile StackType_t* i;
	uint16_t xChecksum = 0;
	for(i = pxEndOfStack ;i != pxStartOfStack ;i+=portSTACK_GROWTH)
	{
		xChecksum^=*i;
	}
	return (uint16_t)xChecksum;
}

#elif( configSUPPORT_TASK_CHECKSUM==2 )

ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack)
{
	uint16_t	uiPolinomio=0x8408;
	uint8_t	i;
	uint16_t	uiData;
	uint16_t	uiCrc;
	
	uiCrc=0xffff;
	if(pxStartOfStack==pxEndOfStack){
		return	(~uiCrc);
	}
	do{
		for(i = 0, uiData = (uint16_t) 0xff && *pxStartOfStack++; i < 8; i++,uiData >>= 1){
			if((uiCrc & 0x0001)^(uiData & 0x0001)){
				uiCrc = (uiCrc >> 1)^uiPolinomio;
			}
			else{
				uiCrc >>= 1;
			}
		}
	} while (pxEndOfStack != pxStartOfStack);
	uiCrc = ~uiCrc;
	uiData = uiCrc;
	uiCrc = (uiCrc << 8)|(uiData >> 8 & 0xff);
	return (uiCrc);
}

#elif ( configSUPPORT_TASK_CHECKSUM==3 )

#define PARITY(n) ((0x6996 >> ((n^(n>>4))&0x0f))&0x01)

static inline uint8_t ucFls(uint16_t uiX)
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
	uint8_t * ucDataP=pxStartOfStack+1;
	uint16_t uiLength = pxEndOfStack-pxStartOfStack;
	uint8_t ucPoolH;
	uint16_t uiHammingBits = 0;
	uint16_t uiPBit;
	uint16_t i;
	uint16_t uiPosBit;
	
	ucPoolH = 0;
	uiPBit = 0;
	for(i=0;i<uiLength;i++){
		ucPoolH ^= (*(ucDataP+i) & 0xAA);
	}
	uiHammingBits += (PARITY(ucPoolH))<<uiPBit;
	
	ucPoolH = 0;
	uiPBit = 1;
	for(i=0;i<uiLength;i++){
		ucPoolH ^= (*(ucDataP+i) & 0xCC);
	}
	uiHammingBits += (PARITY(ucPoolH))<<uiPBit;
	
	ucPoolH = 0;
	uiPBit = 2;
	for(i=0;i<uiLength;i++){
		ucPoolH ^= (*(ucDataP+i) & 0xF0);
	}
	uiHammingBits += (PARITY(ucPoolH))<<uiPBit;
	
	uiPBit=3;
	ucPoolH = 0;
	uiPosBit = (1<<(uiPBit-3));
	for(i=0;i<uiLength;i++){
		if((i+1) & (uiPosBit)){
			ucPoolH ^= (*(ucDataP+i));
		}
	}
	uiHammingBits += (PARITY(ucPoolH))<<uiPBit;
	
	uint8_t pBitmax = ucFls(uiLength*8);
	
	for(uiPBit=4;uiPBit<pBitmax;uiPBit++){
		ucPoolH = 0;
		uiPosBit = (1<<(uiPBit-3));
		for(i=0;i<uiLength;i++){
			if((i+1) & (uiPosBit)){
				ucPoolH ^= (*(ucDataP+i));
			}
		}
		uiHammingBits += (PARITY(ucPoolH))<<uiPBit;
	}
	return (ChecksumType_t)uiHammingBits;
}


#elif ( configSUPPORT_TASK_CHECKSUM==4 )
	
    	ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack){}
	
#endif

#if ( configUSE_TASK_CHECKSUM_HOOK == 1 )

	void vApplicationTaskChecksumHook( void ){}

#endif


