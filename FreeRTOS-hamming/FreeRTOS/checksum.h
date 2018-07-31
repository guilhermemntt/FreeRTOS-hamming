#ifndef INC_FREERTOS_H
#error FreeRTOS.h must be included before checksum.h
#endif

#ifndef CHECKSUM_H
#define CHECKSUM_H

#ifdef __cplusplus
	extern "C" {
#endif

	#if( configSUPPORT_TASK_CHECKSUM > 0 )
	
		typedef	uint16_t	ChecksumType_t;
		ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack);
	
		#undef  configRECORD_STACK_HIGH_ADDRESS
		#define	configRECORD_STACK_HIGH_ADDRESS		1

		#undef	traceTASK_SWITCHED_OUT
		#undef	traceTASK_SWITCHED_IN
		#undef	traceTASK_CREATE

		#define traceTASK_CREATE( pxNewTCB ) do{ \
			pxCurrentTCB->ucChecksum = uxChecksumGetTaskChecksum(pxNewTCB->pxTopOfStack, pxNewTCB->pxEndOfStack);\
		}while(0);
		
		#define traceTASK_SWITCHED_OUT() 	do{ \
			pxCurrentTCB->ucChecksum = uxChecksumGetTaskChecksum(pxCurrentTCB->pxTopOfStack, pxCurrentTCB->pxEndOfStack);\
		}while(0);
	
	#endif
		
	#if( configSUPPORT_TASK_CHECKSUM== 1 || configSUPPORT_TASK_CHECKSUM== 2 )
				
		#define traceTASK_SWITCHED_IN() 	do{ \
			if(pxCurrentTCB->ucChecksum == uxChecksumGetTaskChecksum(pxCurrentTCB->pxTopOfStack, pxCurrentTCB->pxEndOfStack)){\
				vApplicationTaskChecksumHook();\
			}\
		}while(0);
				
		void vApplicationTaskChecksumHook( void ) __attribute__((weak));
			
	#elif( configSUPPORT_TASK_CHECKSUM== 3 )

		#define traceTASK_SWITCHED_IN() 	do{ \
			pxCurrentTCB->ucChecksum ^= uxChecksumGetTaskChecksum(pxCurrentTCB->pxTopOfStack, pxCurrentTCB->pxEndOfStack); \
			if(pxCurrentTCB->ucChecksum == 0){ \
				vApplicationTaskChecksumHook(); \
			} else { \
				pxCurrentTCB->pxTopOfStack[pxCurrentTCB->ucChecksum /8] ^=  (1<<(pxCurrentTCB->ucChecksum%8)); \
			} \
		}while(0);
				
		static inline uint8_t prvFls(uint16_t uiX);
			
		void vApplicationTaskChecksumHook( void ) __attribute__((weak));
		
	#elif ( configSUPPORT_TASK_CHECKSUM==4 )
	
		#define traceTASK_SWITCHED_IN() 	do{ \
			if(pxCurrentTCB->ucChecksum == uxChecksumGetTaskChecksum(pxCurrentTCB->pxTopOfStack, pxCurrentTCB->pxEndOfStack)){\
				vApplicationTaskChecksumHook();\
			}\
		}while(0);
	
		ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack) __attribute__((weak));
		
	#endif
		
#ifdef __cplusplus    
	}
#endif

#endif

