//Includes
#include "../../freertos_adc/inc/main.h"
#include "../../freertos_adc/inc/FreeRTOSConfig.h"
#include "../../PWMyTFT/inc/FreeRTOS.h"
#include "board.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
//#include "basic_io.h"

//Defines
#define FsADC		10000
#define FsADC1		1

//Cola de mensajes
xQueueHandle xQueueADC = NULL;

/* Número de items que la cola puede almacenar */
#define mainQUEUE_LENGTH	10

void InitADC(int fs)
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


static void initHardware(void)
{
    SystemCoreClockUpdate();
    Board_Init();
    Chip_DAC_Init(LPC_DAC);
    ADC_PIN_init();
    Board_LED_Set(0, false);
}

void ReadDataADC()
{
	static uint16_t porcHumedad;
	xQueueReceive(xQueueADC, porcHumedad, portMAX_DELAY);
}

void vReadDataADC(void * a)
{
	//static uint16_t dato;

	while (1)
	{
		Board_LED_Toggle(0);
		ReadDataADC();									//Leo el dato, levantandolo de la cola

		//Donde lo mando ahora?

		//xQueueReceive(xQueueADC, &dato, portMAX_DELAY);
		//Chip_ADC_Int_SetChannelCmd(LPC_ADC, ADC_CH1, ENABLE);
		vTaskDelay(250/ portTICK_RATE_MS);
	}
}

int main(void)
{
	initHardware();
	xTaskCreate(vReadDataADC, (const char *)"task", configMINIMAL_STACK_SIZE*2, 0, tskIDLE_PRIORITY+1, 0);

	xQueueADC = xQueueCreate( mainQUEUE_LENGTH, sizeof( uint16_t ) );

	//Creo tarea y cola antes de inicializar Interrupciones
	InitADC(FsADC1);
	vTaskStartScheduler();
	for(;;);
}
