/*
* functions.c

 *
 *  Created on: 14 de oct. de 2018
 *      Author: Juan Bruno
 */

#include "../inc/main.h"

extern xQueueHandle colarx;

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
		vector[i] = '\0';
	}

	return;
}

int esp8266SendCommand(char* comando){

	int i = 0;
	esp8266Command(comando);
	espStatus_e rv = ESP8266_NO_ANSWER;
	char respuesta[BUFFERSIZE] = {0};

	while(1){
		if(xQueueReceive(colarx,&(respuesta[i]), portMAX_DELAY) == pdTRUE){
			rv = esp8266ValidateResponse(respuesta);
			if(rv == ESP8266_OK)
				return 1;

			if(i>BUFFERSIZE-1)
				return -1;

			i++;
		}
	}

}

