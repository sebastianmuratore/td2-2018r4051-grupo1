
#include "../inc/main.h"

extern xQueueHandle colarx;

void initHardware(void)
{
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/1000);
	Board_Init();
//	init_Servo();
//	initTouch();
	init_TFT();
    inicializarUART3();
    //initADC();
//    init_OW();
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

