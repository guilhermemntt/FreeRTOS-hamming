#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/queue.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/portable.h"

#include <avr/io.h>
#include "util/delay.h"

void task_tx(void* p)
{
	volatile uint8_t teste=45;
	volatile uint8_t teste2=45;
	while(1)
	{
		teste=50;
	}
}

void task_rx(void* p)
{	
	volatile uint8_t teste=85;
	volatile uint8_t teste2=45;
	while(1)
	{
		
	}
}


volatile uint16_t globa;
volatile uint16_t globa1;


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
		globa=0x01;
	}
	
	
	void vApplicationTaskChecksumHook1( void ){
		globa1=0x02;
	}

uint16_t uxChecksumGetTaskChecksum(volatile StackType_t *pxStartOfStack, volatile StackType_t	*pxEndOfStack)
	{
		volatile StackType_t* i;
		uint16_t xChecksum = 0;
		for(i = pxEndOfStack ;i > pxStartOfStack ;i--)
		{
			xChecksum^=*i;
		}
		globa=0xaa;
		return (uint16_t)xChecksum;
	}
}