/*==================[inclusions]=============================================*/

#include "../inc/main.h"

xSemaphoreHandle sServo;
xSemaphoreHandle sTFT;
xSemaphoreHandle sMenu;

xQueueHandle colarx;
xQueueHandle colatx;
xQueueHandle colaConexion;
xQueueHandle qDatos;

xTaskHandle vUartReadHandle;
xTaskHandle vProcessConectionHandle;


//void vAccion (void *pvParameters)
//{
//	unsigned int EstadoDebounce = NO_OPRIMIDO;
//	portTickType xMeDesperte;
//
//	//Inicio de variables y recuperación de parámetros
//
//	xMeDesperte = xTaskGetTickCount();
//
//	while(1){
//	//debo verificar rebote
//	switch(EstadoDebounce){
//		case NO_OPRIMIDO:
//			vTaskDelayUntil(&xMeDesperte,SCAN_RATE_ms/portTICK_RATE_MS);
//			if(!Chip_GPIO_GetPinState(LPC_GPIO,SW_ARRIBA))	//Si retorna una opresión
//				EstadoDebounce = DEBOUNCE;		//Indico que esta corriendo el tiempo Debounce
//			break;
//
//		case DEBOUNCE:
//			vTaskDelay(TIEMPO_DE_DEBOUNCE_ms/portTICK_RATE_MS);
//			EstadoDebounce = VALIDAR;
//			break;
//
//		case VALIDAR:
//			if(!Chip_GPIO_GetPinState(LPC_GPIO,SW_ARRIBA))			//Si retorna algo sigue presionado
//			{
//				EstadoDebounce=OPRIMIDO;
//			}
//			else							// fue error
//				EstadoDebounce=NO_OPRIMIDO;
//			break;
//
//		case OPRIMIDO:
//			if(Chip_GPIO_GetPinState(LPC_GPIO,SW_ARRIBA)) //No envio mensaje hasta no soltar
//			{
//				xSemaphoreGive(sServo);
//				EstadoDebounce = NO_OPRIMIDO;
//			}
//			break;
//		default:  break;
//		}
//	}
//}





int main(void)
{

		initHardware();

//	vSemaphoreCreateBinary(sServo);
	vSemaphoreCreateBinary(sTFT);
	vSemaphoreCreateBinary(sMenu);

	xSemaphoreTake(sTFT,portMAX_DELAY);
	xSemaphoreTake(sMenu,portMAX_DELAY);

	colarx = xQueueCreate(BUFFERSIZE, sizeof(char));
	colatx = xQueueCreate(BUFFERSIZE, sizeof(char));
	colaConexion = xQueueCreate(10, sizeof(espAnswer));
	qDatos = xQueueCreate(10,sizeof(Datos));

	//Tarea que se fija si hay datos para leer.
	xTaskCreate(vUartRead, (const unsigned char * ) "Leer UART", 2*configMINIMAL_STACK_SIZE,
				0, tskIDLE_PRIORITY+2, &vUartReadHandle );

	//Tarea que se fija si hay datos para leer.
	xTaskCreate(vAnswerProcess, (const unsigned char * ) "Procesar respuesta", 3*configMINIMAL_STACK_SIZE,
					0, tskIDLE_PRIORITY+1, &vProcessConectionHandle );


	xTaskCreate(vConfigEsp8266, (const unsigned char * ) "Config esp8266", 5*configMINIMAL_STACK_SIZE,
					0, tskIDLE_PRIORITY+3, 0 );

	xTaskCreate(vGetReport, (const unsigned char * ) "Get Report", 1*configMINIMAL_STACK_SIZE,
						0, tskIDLE_PRIORITY+2, 0 );


	//xSemaphoreTake(sServo,portMAX_DELAY);

	//xTaskCreate(vServoWrite, (const char *)"vServoWrite", configMINIMAL_STACK_SIZE, 0, tskIDLE_PRIORITY+2, 0);

	//xTaskCreate(vAccion, (const char *)"vAccion", configMINIMAL_STACK_SIZE*2, 0, tskIDLE_PRIORITY+1, 0);

	//xTaskCreate(vTouch, (const char *)"vTouch", configMINIMAL_STACK_SIZE*2, 0, tskIDLE_PRIORITY+1, 0);

	xTaskCreate(vDrawMenues, (const signed char *)"vDrawMenues", 3*configMINIMAL_STACK_SIZE, 0, tskIDLE_PRIORITY+3, 0);

	xTaskCreate(vInitLCD, (const signed char *)"InitLCD", configMINIMAL_STACK_SIZE, 0, tskIDLE_PRIORITY+4, 0);

	vTaskSuspend(vProcessConectionHandle);
	vTaskSuspend(vUartReadHandle);

	vTaskStartScheduler();


	while (1)
	{
	}
}

