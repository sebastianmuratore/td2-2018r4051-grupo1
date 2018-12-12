/*
 * HL-69_tasks.c
 *
 *  Created on: 7 de nov. de 2018
 *      Author: Hugo
 *
 */

#include "../inc/main.h"


//Defines
#define FsADC			10000
#define FsADC1			1
#define CANT_MUESTRAS 	10

//Cola de mensajes
extern xQueueHandle xQueueADC;
extern xQueueHandle qHumedad;

/* Número de items que la cola puede almacenar */
//#define mainQUEUE_LENGTH	10

void initADC(void)
{
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_ADC1,FUNC_ADC);
	ADC_CLOCK_SETUP_T adc;
	Chip_ADC_Init(LPC_ADC, &adc);
	Chip_ADC_SetSampleRate(LPC_ADC, &adc, fs);
	Chip_ADC_EnableChannel(LPC_ADC, ADC_CH_HUM, ENABLE);
	Chip_ADC_Int_SetChannelCmd(LPC_ADC, ADC_CH_HUM, ENABLE);
	Chip_ADC_SetBurstCmd(LPC_ADC, ENABLE);
	NVIC_EnableIRQ(ADC_IRQn);
	NVIC_SetPriority(ADC_IRQn,configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY+1);

}
/*
void ADC_PIN_init(void)
{
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_ADC1,FUNC_ADC);
}

*/
uint16_t calcularPromedio(uint16_t *vector, int cantidad){

	int i;
	uint16_t acumulador;

	for(i=0; i<cantidad; i++ ){
		acumulador += vector[i];
	}

	return acumulador/cantidad;

}

void ADC_IRQHandler(void)
{
	portBASE_TYPE HigherPriorityTaskWoken = 0;
	uint16_t data;
	uint16_t porcentaje;
	Chip_ADC_ReadValue(LPC_ADC, ADC_CH_HUM, &data);

	xQueueSendFromISR(xQueueADC, &data, &HigherPriorityTaskWoken);

	portEND_SWITCHING_ISR(HigherPriorityTaskWoken);
	//Chip_ADC_Int_SetChannelCmd(LPC_ADC, ADC_CH_HUM, DISABLE);

}

void vReadDataADC(void* a )
{
	uint16_t dataHumedad;

	while(1)
	{
		xQueueReceive(xQueueADC, &dataHumedad, portMAX_DELAY);
		dataHumedad=100-((dataHumedad*100)/4095);
		xQueueSend(qHumedad, &dataHumedad, portMAX_DELAY);
		vTaskDelay(CINCO_SEG);
	}
}
/*
void vReadDataADC(void *a)
{
	int i = 0, flag = 0;
	uint16_t dato;
	uint16_t dato_procesado;
	uint16_t dato_procesado_ant;
	uint16_t dato_descartado;
	uint16_t muestras[CANT_MUESTRAS];


	while (1)
	{
		dato = ReadDataADC();

		if(!flag){
			muestras[i++] = dato;

			if(i == CANT_MUESTRAS){
				flag = 1;
				dato_procesado = calcularPromedio(muestras, CANT_MUESTRAS);
				dato_procesado_ant = dato_procesado;
				xQueueSend(qHumedad, &dato_procesado, portMAX_DELAY);
			}
		}
		else{

			i = i % CANT_MUESTRAS;

			dato_descartado = muestras[i];
			muestras[i++] = dato;
			dato_procesado = dato_procesado_ant + (dato - dato_descartado)/CANT_MUESTRAS;
			dato_procesado_ant = dato_procesado;
			xQueueSend(qHumedad, &dato_procesado, portMAX_DELAY);

		}


		//vTaskDelay(50000/ portTICK_RATE_MS);
	}
}

*/

