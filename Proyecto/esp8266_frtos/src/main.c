#include "../../../tps/td2-2018r4051-grupo1/Proyecto/esp8266_frtos/inc/main.h"

#include <string.h>

#include "../../../tps/td2-2018r4051-grupo1/Proyecto/esp8266_frtos/inc/FreeRTOSConfig.h"
#include "../../../tps/td2-2018r4051-grupo1/Proyecto/esp8266_frtos/inc/uart_driver.h"
#include "queue.h"

xQueueHandle colarx;
xQueueHandle colatx;
espNetworks nets[15];

#define BUFFERSIZE		1024 //Tamaños de las colas
#define HTML_CODE_SIZE	465

unsigned char inicializado = 0;
unsigned int comandoCargado = 0;
unsigned char revisaInic = 0;

char codigoHTML[HTML_CODE_SIZE] = "<!DOCTYPE html><html lang=\"es\"><head><meta charset=\"utf-8\" /><title>Compost TDII</title>"
		"<style>.sangria{text-indent: 30px;}</style><style>.textoAzul{color: blue; font-style: italic; font-weight: bold}"
		"</style></head><body><center><h1>Proyecto Técnicas Digitales II - Sistema de Compost</h1></center><br />"
		"<h2 class=\"textoAzul\">Temperatura:</h2><h1 class=\"sangria\">24ºC</h1><br /><h2 class=\"textoAzul\">Humedad:</h2>"
		"<h1 class=\"sangria\">56%</h1><br /></body></html>\r\n";

espStatus_e status = ESP8266_TIMEOUT;

void initHardware(void)
{
    SystemCoreClockUpdate();
    Board_Init();
    Board_LED_Set(0, false);
    inicializarPulsadores();
    inicializarUART3();
}

void inicializarPulsadores(void){

	Chip_IOCON_PinMuxSet(LPC_IOCON,2,13,FUNC0);	//SW1
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,2,13);

	Chip_IOCON_PinMuxSet(LPC_IOCON,0,28,FUNC0); //SW2
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,0,28);

	Chip_IOCON_PinMuxSet(LPC_IOCON,0,27,FUNC0); //SW3
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,0,27);

}

void inicializarVector(int len, char* vector){

	int i;

	for(i=0;i<len;i++){
		vector[i] = 0;
	}

	return;
}

void vConfigEsp8266(void *parametros){

	espStatus_e rv = ESP8266_NO_ANSWER;
	char respuesta[BUFFERSIZE] = {0};
	char ip[40] = {0};
	int i = 0;
	int j = 0;

	esp8266Command("AT+RST\r\n");
	while(1){
		if(xQueueReceive(colarx,&(respuesta[i]), portMAX_DELAY) == pdTRUE){
			rv = esp8266ValidateResponse(respuesta);
			if(rv == ESP8266_OK)
				break;
			if(i>BUFFERSIZE-1)
				i = 0;

			i++;
		}
	}
	i=0;
	rv = ESP8266_NO_ANSWER;
	inicializarVector(BUFFERSIZE, respuesta);
	esp8266Command("");
	while(1){
		if(xQueueReceive(colarx,&(respuesta[i]), portMAX_DELAY) == pdTRUE){
			rv = esp8266ValidateResponse(respuesta);
			if(rv == ESP8266_READY)
				break;
			if(i>BUFFERSIZE-1)
				break;

			i++;

		}
	}
	i=0;
	rv = ESP8266_NO_ANSWER;
	inicializarVector(BUFFERSIZE, respuesta);
	esp8266Command("ATE0\r\n");
	while(1){
		if(xQueueReceive(colarx,&(respuesta[i]), portMAX_DELAY) == pdTRUE){
			rv = esp8266ValidateResponse(respuesta);
			if(rv == ESP8266_OK)
				break;

			if(i>BUFFERSIZE-1)
				i = 0;

			i++;
		}
	}
	i=0;
	rv = ESP8266_NO_ANSWER;
	inicializarVector(BUFFERSIZE, respuesta);
	esp8266Command("AT+CWMODE=3\r\n");
	while(1){
		if(xQueueReceive(colarx,&(respuesta[i]), portMAX_DELAY) == pdTRUE){
			rv = esp8266ValidateResponse(respuesta);
			if(rv == ESP8266_OK)
				break;

			if(i>BUFFERSIZE-1)
				i = 0;

			i++;
		}
	}
	i=0;
	rv = ESP8266_NO_ANSWER;
	inicializarVector(BUFFERSIZE, respuesta);
	esp8266Command("AT+CWJAP=\"Bruno 2.4GHz\",\"platensewifi\"\r\n");
	while(1){
		if(xQueueReceive(colarx,&(respuesta[i]), portMAX_DELAY) == pdTRUE){
			rv = esp8266ValidateResponse(respuesta);
			if(rv == ESP8266_OK)
				break;

			if(i>BUFFERSIZE-1)
				i = 0;

			i++;
		}
	}
	i=0;
	rv = ESP8266_NO_ANSWER;
	inicializarVector(BUFFERSIZE, respuesta);
	esp8266Command("AT+CIPMUX=1\r\n");
	while(1){
		if(xQueueReceive(colarx,&(respuesta[i]), portMAX_DELAY) == pdTRUE){
			rv = esp8266ValidateResponse(respuesta);
			if(rv == ESP8266_OK)
				break;

			if(i>BUFFERSIZE-1)
				i = 0;

			i++;
		}
	}
	i=0;
	rv = ESP8266_NO_ANSWER;
	inicializarVector(BUFFERSIZE, respuesta);
	esp8266Command("AT+CIPSERVER=1,80\r\n");
	while(1){
		if(xQueueReceive(colarx,&(respuesta[i]), portMAX_DELAY) == pdTRUE){
			rv = esp8266ValidateResponse(respuesta);
			if(rv == ESP8266_OK)
				break;
			i++;
		}
	}
	i=0;
	rv = ESP8266_NO_ANSWER;
	inicializarVector(BUFFERSIZE, respuesta);
	esp8266Command("AT+CIFSR\r\n");
	while(1){
		if(xQueueReceive(colarx,&(respuesta[i]), portMAX_DELAY) == pdTRUE){
			rv = esp8266ValidateResponse(respuesta);
			if(!j)
				j = esp8266GetIP(ip, respuesta[i]);
			if(rv == ESP8266_OK)
				break;
			i++;
		}
	}

	vTaskDelete(NULL);


}

//Creo una tarea que cada 10ms se fija si hay datos para leer.
void vUartRead(void *parametros)
{
	int i = 0, j = 0, largo = 0, cantidad1 = 0, id = -1, bytes = 0;
	Bool inicio = FALSE, flag = FALSE, mensajeRecibido = FALSE;
	int conectado = FALSE, enviar = FALSE;
	char dato;
	char respuesta[BUFFERSIZE] = {0}, respuestaNeta[BUFFERSIZE] = {0};
	char sendCommand[30] = {0};
	espStatus_e rv = ESP8266_NO_ANSWER;
	espCommand_e comando = ESP8266_DEFAULT;

	while(1)
	{
		//vTaskDelay(10/portTICK_RATE_MS);

		if(!inicializado) continue;


		if(xQueueReceive(colarx,&(respuesta[i]), portMAX_DELAY) == pdTRUE){

			if(i<BUFFERSIZE && !conectado && !enviar){

				if(rv == ESP8266_DEVICE_CONNECTED){
					bytes = esp8266ProcessConnection(respuesta[i], &id);
					if(bytes > 0){
						conectado = TRUE;
					}
				}
				else{
					rv = esp8266ValidateResponse(respuesta);
				}

			}
			else if(conectado){
				j++;
				if(j == bytes-1){
					vTaskDelay(10/portTICK_RATE_MS);
					int tam = HTML_CODE_SIZE;
					sprintf(sendCommand, "AT+CIPSEND=%d,%d\r\n", id, tam);
					esp8266Command(sendCommand);
					enviar = TRUE;
					conectado = FALSE;
					bytes = 0;
					j = 0;
				}
			}
			else if(enviar){
				if(respuesta[i] == '>'){
					esp8266Command(codigoHTML);
					enviar = FALSE;
					inicializarVector(BUFFERSIZE, respuesta);
					i = 0;
					sprintf(sendCommand, "AT+CIPCLOSE=%d\r\n", id);
					esp8266Command(sendCommand);
					id = -1;
				}
			}

			i++;

		}




/*

		//Leo los datos en la cola rx
		cantidad = uxQueueMessagesWaiting(colarx);

		if(cantidad){

			for(i=0;i<BUFFERSIZE;i++){
				respuesta[i] = 0;
				respuestaNeta[i] = 0;
			}

			for(i=0;i<20;i++){
				comando[i] = 0;
			}

			i = 0;

			while(xQueueReceive(colarx,&(respuesta[i]),portMAX_DELAY) == pdTRUE){

				esp8266SeparateResponse(respuesta[i], &(respuestaNeta), &(comando), &cmd, cantidad);
				i++;

				if(i==30)
					cantidad = 0;
			}

			//cantidad1 = uxQueueMessagesWaiting(colarx);

			rv = esp8266ProcessResponse(respuestaNeta, cmd);

		}
*/

	}

}

//Carga el comando seleccionado en la cola tx
void vSelectCommand(void *a){

	while(1){

		vTaskDelay(10/portTICK_RATE_MS);

		//SW1 - Reset
		if(!Chip_GPIO_GetPinState(LPC_GPIO,2,13)){
			char cmdMode[20] = "ATE0\r\n";
			//char cmdMode[20] = "AT+CIPMUX=1\r\n";
			esp8266Command(cmdMode);
		}
		//SW2 - Modo 1
		else if(!Chip_GPIO_GetPinState(LPC_GPIO,0,28)){
			//char cmdModo[20] = "AT+CWLAP\r\n";
			//char cmdModo[30] = "AT+UART_DEF=9600,8,1,0,0\r\n";
			//char cmdModo[28] = "AT+CIOBAUD=9600\r\n";
			char cmdConnect[100] = "AT+CIPSERVER=1,80\r\n";
			//char cmdConnect[40] = "ATE0\r\n";
			esp8266Command(cmdConnect);
		}
		//SW3 - Modo?
		else if(!Chip_GPIO_GetPinState(LPC_GPIO,0,27)){
			//char cmdConsultarModo[20] = "AT+CWMODE=?\r\n";
			char cmdConsultarIP[20] = "AT+CIFSR\r\n";
			esp8266Command(cmdConsultarIP);
		}

	}

}

int main(void)
{
	initHardware();

	colarx = xQueueCreate(BUFFERSIZE, sizeof(char));
	colatx = xQueueCreate(BUFFERSIZE, sizeof(char));

	//Tarea que se fija si hay datos por enviar.
	//xTaskCreate(vUartWrite,(const char * ) "Escribir UART", configMINIMAL_STACK_SIZE,
	//				0, tskIDLE_PRIORITY+1, 0 );

	//Tarea que se fija si hay datos para leer.
	xTaskCreate(vUartRead, (const char * ) "Leer UART", 10*configMINIMAL_STACK_SIZE,
					0, tskIDLE_PRIORITY+1, 0 );

	//Tarea que lee los sw
	//xTaskCreate(vSelectCommand, (const char * ) "Leer teclas", configMINIMAL_STACK_SIZE,
	//				0, tskIDLE_PRIORITY+1, 0 );

	xTaskCreate(vConfigEsp8266, (const char * ) "Config esp8266", 4*configMINIMAL_STACK_SIZE,
					0, tskIDLE_PRIORITY+2, 0 );

	vTaskStartScheduler();

	while (1);
}
