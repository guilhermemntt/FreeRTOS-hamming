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

int main(void)
{
	xTaskCreate(task_tx, (const char*)"t1", 100, 0, 1, 0);
	xTaskCreate(task_rx, (const char*)"t2", 100, 0, 1, 0);
	vTaskStartScheduler();
	
	return 0;
}
extern "C"{
	void vApplicationTaskChecksumHook( void ){
		globa=1;
	}
	void vApplicationTaskChecksumHook1( void ){
		globa=2;
	}
}