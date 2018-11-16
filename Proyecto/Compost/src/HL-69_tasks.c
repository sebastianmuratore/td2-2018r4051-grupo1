/*
 * HL-69_tasks.c
 *
 *  Created on: 7 de nov. de 2018
 *      Author: Hugo
 *
 */

#include "../inc/main.h"


//Defines
#define FsADC		10000
#define FsADC1		1

//Cola de mensajes
extern xQueueHandle xQueueADC;

/* Número de items que la cola puede almacenar */
//#define mainQUEUE_LENGTH	10

void InitADC(void)
{
	ADC_CLOCK_SETUP_T adc;
	Chip_ADC_Init(LPC_ADC, &adc);
	Chip_ADC_SetSampleRate(LPC_ADC, &adc, fs);
	Chip_ADC_EnableChannel(LPC_ADC, ADC_CH1, ENABLE);
	Chip_ADC_Int_SetChannelCmd(LPC_ADC, ADC_CH1, ENABLE);
	Chip_ADC_SetBurstCmd(LPC_ADC, ENABLE);
	NVIC_EnableIRQ(ADC_IRQn);
	NVIC_SetPriority(ADC_IRQn,configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY+1);

}

void ADC_PIN_init(void)
{
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_ADC1,FUNC_ADC);
}

void ADC_IRQHandler(void)
{
	portBASE_TYPE HigherPriorityTaskWoken = 0;
	uint16_t data;
	uint16_t porcentaje;
	Chip_ADC_ReadValue(LPC_ADC, ADC_CH1, &data);

	porcentaje=100-((data*100)/4095);
	//xQueueSendFromISR(xQueueADC,&data, &HigherPriorityTaskWoken); 	//Pruebo mandando el dato crudo o el porcentaje
	xQueueSendFromISR(xQueueADC,porcentaje, &HigherPriorityTaskWoken);

	portEND_SWITCHING_ISR(HigherPriorityTaskWoken);
	//Chip_ADC_Int_SetChannelCmd(LPC_ADC, ADC_CH1, DISABLE);

}

void vReadDataADC(void *a)
{
	while (1)
	{
		ReadDataADC();
		vTaskDelay(50000/ portTICK_RATE_MS);
	}
}

void ReadDataADC()
{
	static uint16_t porcHumedad;
	xQueueReceive(xQueueADC, porcHumedad, portMAX_DELAY);
}


