#ifndef INC_FREERTOS_H
#error FreeRTOS.h must be included before checksum.h
#endif

#ifndef CHECKSUM_H
#define CHECKSUM_H


#ifdef __cplusplus
extern "C" {
#endif

#define configCHECKSUM_METHOD	1

typedef	uint16_t	ChecksumType_t;

#if ( configUSE_TASK_CHECKSUM_HOOK == 1 )

void vApplicationTaskChecksumHook( void ) __attribute__((weak));

void vApplicationTaskChecksumHook1( void ) __attribute__((weak));

#endif

ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack);

	
#if( configSUPPORT_TASK_CHECKSUM == 1 )

	#undef	traceTASK_SWITCHED_OUT
	#undef	traceTASK_SWITCHED_IN
	
	#define traceTASK_SWITCHED_OUT() 	do{ \
		pxCurrentTCB->ucChecksum = uxChecksumGetTaskChecksum(pxCurrentTCB->pxTopOfStack, pxCurrentTCB->pxEndOfStack);\
	}while(0);

	#if( configUSE_TASK_CHECKSUM_HOOK== 1 )

		#define traceTASK_SWITCHED_IN() 	do{ \
			if(pxCurrentTCB->ucChecksum == uxChecksumGetTaskChecksum(pxCurrentTCB->pxTopOfStack, pxCurrentTCB->pxEndOfStack)){\
				vApplicationTaskChecksumHook();\
				}else{ \
				vApplicationTaskChecksumHook1();\
			}\
		}while(0);

	#endif

#endif


#ifdef __cplusplus
}
#endif

#endif

