#include "FreeRTOS.h"
#include "checksum.h"

#define MSG_SIZE 10
#define HMM_SIZE 7
#define TWO( c ) (0x1u << ( c ) )
#define MASK( c ) ( ( ( unsigned int ) (-1) ) / (TWO(TWO( c ) ) + 1u) )
#define COUNT(x , c ) ( ( x ) & MASK( c ) ) + ( ( ( x ) >> (TWO( c ) ) ) & MASK( c ) )

#if( configCHECKSUM_METHOD==0 )

int bitcount (unsigned int n ) {
	n = COUNT (n , 0) ;
	n = COUNT (n , 1) ;
	n = COUNT (n , 2) ;
	n = COUNT (n , 3) ;
	return n ;
}
ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack);{

	uint8_t *data_p = 	pxEndOfStack;
	uint16_t length =	pxEndOfStack-pxStartOfStack;
	
	uint8_t poolH=0;
	uint8_t hammingBits = 0 ;
	uint8_t pBit=0;
	uint8_t msg ;

	for ( msg=0; msg < length ; msg++)
	{
		poolH += bitcount (  ( data_p+msg ) & 0xAA ) ;
	}
	hammingBits += ( poolH & 0x01 ) << pBit ;
	poolH = 0 ;
	pBit = 1 ;
	for ( msg=0; msg < MSG_SIZE ; msg++)
	{
		poolH += bitcount (  ( data_p + msg ) & 0xCC ) ;
	}
	hammingBits += ( poolH & 0x01 ) << pBit ;
	poolH = 0 ;
	pBit = 2 ;
	for ( msg=0; msg < MSG_SIZE ; msg++)
	{
		poolH += bitcount (  ( data_p + msg ) & 0xF0 ) ;
	}
	hammingBits += ( poolH&0x01 )<<pBit ;
	for ( pBit=3; pBit < HMM_SIZE ; pBit++)
	{
		poolH = 0 ;
		for ( msg=0; msg < MSG_SIZE ; msg++)
		{
			poolH = 0 ;
			if ( ( msg8+136) & (1 << pBit ) ) 
			{
				poolH += bitcount (  ( data_p+msg ) ) ;
			}
		}
	hammingBits += ( poolH&0x01 )<<pBit ;
	}
	return (uint16_t) hammingBits ;
}

#elif( configCHECKSUM_METHOD==1 )

ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack)
{
	volatile StackType_t* i;
	uint16_t xChecksum = 0;
	for(i = pxEndOfStack ;i > pxStartOfStack ;i--)
	{
		xChecksum^=*i;
	}
	return (uint16_t)xChecksum;
}

#elif ( configCHECKSUM_METHOD==2 )

ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack);
{
	uint16_t	polinomio=0x8408;
	uint8_t	i;
	uint16_t	uiData;
	uint16_t	uiCrc;
	
	uint16_t uiLength =	 ;
	
	uiCrc=0xffff;
	if(uiLength==0){
		return	(~uiCrc);
	}
	do{
		for(i = 0, uiData = (uint16_t) 0xff && *(pxEndOfStack++); i < 8; i++,uiData >>= 1){
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

#endif

#if ( configUSE_TASK_CHECKSUM_HOOK == 1 )

	void vApplicationTaskChecksumHook( void ){}
	void vApplicationTaskChecksumHook1( void ){}

#endif

