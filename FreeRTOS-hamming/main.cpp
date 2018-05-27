#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/queue.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/portable.h"

#include <avr/io.h>
#include "util/delay.h"

void task_tx(void* p)
{
	while(1)
	{
	}
}

void task_rx(void* p)
{	
	while(1)
	{
		
	}
}


volatile uint16_t globa;
uint16_t globa1;


int main(void)
{
	DDRB = 0xFF; //Nakes PORTC as Output
	xTaskCreate(task_tx, (const char*)"t1", 100, 0, 1, 0);
	xTaskCreate(task_rx, (const char*)"t2", 100, 0, 1, 0);
	vTaskStartScheduler();
	
	return 0;
}

extern "C"{
	
	void vApplicationTaskChecksumHook( void ){ 
	//	globa=0x11;
	}
//
//uint16_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack)
	//{
		//volatile StackType_t* i;
		//uint16_t xChecksum = 0;
		//for(i = pxEndOfStack ;i > pxStartOfStack ;i--)
		//{
			//xChecksum^=*i;
		//}
		//globa=0xaa;
		//return (uint16_t)xChecksum;
	//}
}