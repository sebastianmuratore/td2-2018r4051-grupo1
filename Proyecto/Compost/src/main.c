/*==================[inclusions]=============================================*/

#include "../inc/main.h"

xSemaphoreHandle sServo;
xSemaphoreHandle sTFT;

xQueueHandle colarx;
xQueueHandle colatx;
xQueueHandle colaConexion;
xQueueHandle colaADC;

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
//static void vServoWrite(void * a)
//{
//	static int giro = 1;
//	float duty;
//
//	while (1)
//	{
//		xSemaphoreTake(sServo,portMAX_DELAY);
//
//		if(giro)
//		{
//			duty = MS(0.6);
//			giro = 0;
//		}
//
//		else
//		{
//			duty = MS(2.4);
//			giro = 1;
//		}
//
//		Chip_TIMER_SetMatch(LPC_TIMER1, 1, duty);
//		Chip_TIMER_Reset(LPC_TIMER1);
//		Chip_TIMER_ClearMatch(LPC_TIMER1, 1);
//		Chip_TIMER_ClearMatch(LPC_TIMER1, 0);
//
//
//
//	}
//
//}





int main(void)
{
	initHardware();

//	vSemaphoreCreateBinary(sServo);
	vSemaphoreCreateBinary(sTFT);
	xSemaphoreTake(sTFT,portMAX_DELAY);

	colarx = xQueueCreate(BUFFERSIZE, sizeof(char));
	colatx = xQueueCreate(BUFFERSIZE, sizeof(char));
	colaConexion = xQueueCreate(10, sizeof(espAnswer));
	colaADC = xQueueCreate(10, sizeof(uint16_t));

	//Tarea que se fija si hay datos para leer.
	xTaskCreate(vUartRead, (const unsigned char * ) "Leer UART", 5*configMINIMAL_STACK_SIZE,
				0, tskIDLE_PRIORITY+2, &vUartReadHandle );

	//Tarea que se fija si hay datos para leer.
	xTaskCreate(vAnswerProcess, (const unsigned char * ) "Procesar respuesta", 5*configMINIMAL_STACK_SIZE,
					0, tskIDLE_PRIORITY+1, &vProcessConectionHandle );


	xTaskCreate(vConfigEsp8266, (const unsigned char * ) "Config esp8266", 5*configMINIMAL_STACK_SIZE,
					0, tskIDLE_PRIORITY+3, 0 );

	//xSemaphoreTake(sServo,portMAX_DELAY);

	//xTaskCreate(vServoWrite, (const char *)"vServoWrite", configMINIMAL_STACK_SIZE*2, 0, tskIDLE_PRIORITY+1, 0);

	//xTaskCreate(vAccion, (const char *)"vAccion", configMINIMAL_STACK_SIZE*2, 0, tskIDLE_PRIORITY+1, 0);

	//xTaskCreate(vTouch, (const char *)"vTouch", configMINIMAL_STACK_SIZE*2, 0, tskIDLE_PRIORITY+1, 0);

	xTaskCreate(vDrawMenues, (const signed char *)"vDrawMenues", configMINIMAL_STACK_SIZE, 0, tskIDLE_PRIORITY+1, 0);

	xTaskCreate(vInitLCD, (const signed char *)"InitLCD", configMINIMAL_STACK_SIZE, 0, tskIDLE_PRIORITY+2, 0);

	xTaskCreate(vReadDataADC, (const char *)"vReadDataADC", configMINIMAL_STACK_SIZE*2, 0, tskIDLE_PRIORITY+1, 0);

	vTaskSuspend(vProcessConectionHandle);
	vTaskSuspend(vUartReadHandle);

	vTaskStartScheduler();


	while (1)
	{
	}
}

