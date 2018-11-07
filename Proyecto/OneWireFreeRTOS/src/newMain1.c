#include "../../PWMyTFT/inc/FreeRTOS.h"
#include "OneWireFunctions.h"
#include "board.h"
#include "FreeRTOSConfig.h"
#include "task.h"

void xTemperatureTask (void *pvParameters)
{
	int Temperatura=0;
	char str[20];
	while(1)
	{
		taskENTER_CRITICAL();
			Temperatura=owReadTemperature();
			sprintf(str, "Temperatura:%d.%04d\r\n", Temperatura >> 4, (Temperatura & 0xF) * 625);
			DEBUGSTR(str);
			Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 22);
			pauseus(1000000);
		taskEXIT_CRITICAL();
		vTaskDelay(pdMS_TO_TICKS(1000));	//Tiempo entre mediciones
	}
}


int main(void)
{

	initHardware();

	xTaskCreate( xTemperatureTask,( signed portCHAR* )
							"TemperatureTask",
							configMINIMAL_STACK_SIZE,
							NULL,
							tskIDLE_PRIORITY+1,
							NULL );

	//Inicio el Scheduler
	vTaskStartScheduler();
	//----------

	return 0;	//Should never arrive here.
}
