#ifndef INC_FREERTOS_H
#error FreeRTOS.h must be included before checksum.h
#endif

#ifndef CHECKSUM_H
#define CHECKSUM_H

#ifdef __cplusplus
	extern "C" {
#endif

	#if( configSUPPORT_TASK_CHECKSUM > 0 )
	
		#if( portSTACK_GROWTH == (-1))
			#define checksumGET_TASK_CHECKSUM uxChecksumGetTaskChecksum(pxCurrentTCB->pxTopOfStack, pxCurrentTCB->pxEndOfStack)
			#define checksumGET_TASK_CHECKSUM_ON_CREATION uxChecksumGetTaskChecksum(pxNewTCB->pxTopOfStack, pxNewTCB->pxEndOfStack)
		#else
			#define checksumGET_TASK_CHECKSUM uxChecksumGetTaskChecksum(pxCurrentTCB->pxTopOfStack, pxCurrentTCB->pxStack)
			#define checksumGET_TASK_CHECKSUM_ON_CREATION uxChecksumGetTaskChecksum(pxNewTCB->pxTopOfStack, pxNewTCB->pxStack)
		#endif
	
		typedef	uint16_t	ChecksumType_t;
		ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack);
	
		#undef  configRECORD_STACK_HIGH_ADDRESS
		#define	configRECORD_STACK_HIGH_ADDRESS		1

		#undef	traceTASK_SWITCHED_OUT
		#undef	traceTASK_SWITCHED_IN
		#undef	traceTASK_CREATE
		
		#define INCLUDE_vTaskDelete 1

		#define traceTASK_CREATE( pxNewTCB ) do{ \
			pxCurrentTCB->ucChecksum = checksumGET_TASK_CHECKSUM_ON_CREATION; \
		}while(0);
		
		#define traceTASK_SWITCHED_OUT() 	do{ \
			pxCurrentTCB->ucChecksum = checksumGET_TASK_CHECKSUM; \
		}while(0);
		
		#if( configUSE_TASK_CHECKSUM_HOOK > 0 )
			void vApplicationTaskChecksumHook( void ) __attribute__((weak));
		#else
			void vApplicationTaskChecksumHook( void ){}
		#endif
	
	#endif
		
	#if( configSUPPORT_TASK_CHECKSUM == 1 || configSUPPORT_TASK_CHECKSUM == 2 || configSUPPORT_TASK_CHECKSUM == 4 )
				
		#define traceTASK_SWITCHED_IN() 	do{ \
			if(pxCurrentTCB->ucChecksum == checksumGET_TASK_CHECKSUM){ \
				vApplicationTaskChecksumHook(); \
			}else{ \
				vTaskDelete(NULL); \
			} \
		}while(0);
			
	#elif( configSUPPORT_TASK_CHECKSUM == 3 )

			#define traceTASK_SWITCHED_IN() 	do{ \
				pxCurrentTCB->ucChecksum ^= checksumGET_TASK_CHECKSUM; \
				if(pxCurrentTCB->ucChecksum == 0){ \
					vApplicationTaskChecksumHook(); \
				} else { \
					pxCurrentTCB->pxTopOfStack[-portSTACK_GROWTH*(pxCurrentTCB->ucChecksum /8)] ^=  (1<<(pxCurrentTCB->ucChecksum%8)); \
				} \
			}while(0);
				
		static inline uint16_t prvAbs(int16_t sX);
				
		static inline uint8_t prvFls(uint16_t usX);
	
	#endif
	
	#if ( configSUPPORT_TASK_CHECKSUM ==4 )
	
		ChecksumType_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack) __attribute__((weak));
		
	#endif
		
#ifdef __cplusplus    
	}
#endif

#endif

