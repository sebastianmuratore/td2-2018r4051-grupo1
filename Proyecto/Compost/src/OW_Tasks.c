
#include "../inc/main.h"

//#include "../../PWMyTFT/inc/FreeRTOS.h"
//#include "OneWireFunctions.h"
//#include "board.h"
//#include "FreeRTOSConfig.h"
//#include "task.h"

extern xQueueHandle qTemp;

void vTemperatureTask (void *pvParameters)
{
	float Temperatura=0;
	while(1)
	{
		taskENTER_CRITICAL();
			Temperatura=owReadTemperature();
			xQueueSend(qTemp,&Temperatura,portMAX_DELAY);
			pauseus(1000000);
		taskEXIT_CRITICAL();
		vTaskDelay(2000/portTICK_RATE_MS);	//Tiempo entre mediciones
	}
}
