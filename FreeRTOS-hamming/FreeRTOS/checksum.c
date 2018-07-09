#include "FreeRTOS.h"
#include "checksum.h"

#define paridade(n) ((0x6996 >> ((n^(n>>4))&0x0f))&0x01)

#if( configSUPPORT_TASK_CHECKSUM==1 )

ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack)
{
	volatile StackType_t* i;
	uint16_t xChecksum = 0;
	for(i = pxEndOfStack ;i > pxStartOfStack ;i+=portSTACK_GROWTH)
	{
		xChecksum^=*i;
	}
	return (uint16_t)xChecksum;
}

#elif( configSUPPORT_TASK_CHECKSUM==2 )

ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack)
{
	uint16_t	polinomio=0x8408;
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
				uiCrc = (uiCrc >> 1)^polinomio;
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


static inline uint8_t fls(uint16_t x)
{
          uint8_t r = 16;
  
          if (!x)
                  return 0;
          if (!(x & 0xff00u)) {
                  x <<= 8;
                  r -= 8;
          }
          if (!(x & 0xf000u)) {
                  x <<= 4;
                  r -= 4;
          }
          if (!(x & 0xc0000u)) {
                  x <<= 2;
                  r -= 2;
          }
          if (!(x & 0x8000u)) {
                  x <<= 1;
                  r -= 1;
          }
         return r;
  }


ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack)
{
	uint8_t * data_p=pxStartOfStack+1;
	uint16_t length = pxEndOfStack-pxStartOfStack;
	uint8_t poolH;
	uint16_t hammingBits = 0;
	uint16_t pBit;
	uint16_t i;
	uint16_t posbit;
	
	poolH = 0;
	pBit = 0;
	for(i=0;i<length;i++){
		poolH ^= (*(data_p+i) & 0xAA);
	}
	hammingBits += (paridade(poolH))<<pBit;
	
	poolH = 0;
	pBit = 1;
	for(i=0;i<length;i++){
		poolH ^= (*(data_p+i) & 0xCC);
	}
	hammingBits += (paridade(poolH))<<pBit;
	
	poolH = 0;
	pBit = 2;
	for(i=0;i<length;i++){
		poolH ^= (*(data_p+i) & 0xF0);
	}
	hammingBits += (paridade(poolH))<<pBit;
	
	pBit=3;
	poolH = 0;
	posbit = (1<<(pBit-3));
	for(i=0;i<length;i++){
		if((i+1) & (posbit)){
			poolH ^= (*(data_p+i));
		}
	}
	hammingBits += (paridade(poolH))<<pBit;
	
	uint8_t pBitmax = fls(length+1)+2;
	//for(pBit=4;((1<<(pBit-2))-1)<=(length);pBit++){
	
	for(pBit=4;pBit<=pBitmax;pBit++){
		poolH = 0;
		posbit = (1<<(pBit-3));
		for(i=0;i<length;i++){
			if((i+1) & (posbit)){
				poolH ^= (*(data_p+i));
			}
		}
		hammingBits += (paridade(poolH))<<pBit;
	}
	return (ChecksumType_t)hammingBits;
}


#elif ( configSUPPORT_TASK_CHECKSUM==4 )
	
    	ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack){}
	
#endif

#if ( configUSE_TASK_CHECKSUM_HOOK == 1 )

	void vApplicationTaskChecksumHook( void ){}

#endif

