/* Copyright 2016
 * All rights reserved.
 *
 * This file is part of lpc1769_template.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.*/


/*==================[inclusions]=============================================*/

#include "../../tp2_ejercicio3/fsm/TP2_Ej3.h"
#include "../../tp2_ejercicio3/fsm/TP2_Ej3Required.h"
#include "../../tp2_ejercicio3/inc/main.h"

#include "../../../Ejercicio/inc/FreeRTOS.h"
#include "../../tp2_ejercicio3/inc/TimerTicks.h"

#include "../../tp2_ejercicio3/inc/FreeRTOSConfig.h"
#include "board.h"
#include "task.h"
#include "queue.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*! This is a state machine */
static TP2_Ej3 statechart;

xQueueHandle xQueue = NULL;

//Estructura de información el evento tecla
typedef struct _TECLA
{
	int 			port;
	int 			pin;
	int 			id;
}TECLA;

/*==================[internal functions declaration]=========================*/
static void initHardware(void);

/*==================[internal data definition]===============================*/
#define mainQUEUE_LENGTH					( 5 )

#define TIEMPO_DE_DIAGNOSTICO_ms 2000
#define SCAN_RATE_ms 150
#define TIEMPO_DE_DEBOUNCE_ms 20

#define MASK_REDLIGHT	1
#define MASK_GREENLIGHT	2
#define MASK_BLUELIGHT	4

#define RED_LED_PORT 2,0
#define BLUE_LED_PORT 0,26
#define GREEN_LED_PORT 2,1

#define LED_RED 1
#define LED_GREEN 2
#define LED_BLUE 3

#define SW_INVERTIR 2,10
#define SW_REANUDAR 0,18
#define SW_PAUSAR 0,11

#define TECLA_INVERTIR  1
#define TECLA_REANUDAR  2
#define TECLA_PAUSAR  3

#define BOTON_NO_PRESIONADO 0
#define BOTON_PRESIONADO	1

unsigned int tiempo_de_diagnostico = TIEMPO_DE_DIAGNOSTICO_ms;

#define NTIMERS	1

#define NO_OPRIMIDO	0
#define DEBOUNCE	1
#define VALIDAR		2
#define OPRIMIDO	3

TimerTicks timers[NTIMERS];
volatile bool SysTickFlag;

/*==================[external data definition]===============================*/
void tP2_Ej3Iface_opLed(const TP2_Ej3* handle, const sc_integer Led, const sc_boolean State){

	switch(Led){

		case LED_RED:
			if(State)
				Chip_GPIO_SetPinOutHigh(LPC_GPIO,RED_LED_PORT);
			else
				Chip_GPIO_SetPinOutLow(LPC_GPIO,RED_LED_PORT);
			break;

		case LED_GREEN:
			if(State)
				Chip_GPIO_SetPinOutHigh(LPC_GPIO,GREEN_LED_PORT);
			else
				Chip_GPIO_SetPinOutLow(LPC_GPIO,GREEN_LED_PORT);
			break;

		case LED_BLUE:
			if(State)
				Chip_GPIO_SetPinOutHigh(LPC_GPIO,BLUE_LED_PORT);
			else
				Chip_GPIO_SetPinOutLow(LPC_GPIO,BLUE_LED_PORT);
			break;

	}
}

void tP2_Ej3_setTimer(TP2_Ej3* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic)
{
	SetNewTimerTick(timers,NTIMERS,evid,time_ms,periodic);
}

void tP2_Ej3_unsetTimer(TP2_Ej3* handle, const sc_eventid evid)
{
	UnsetTimerTick(timers,NTIMERS,evid);
}

/*==================[internal functions definition]==========================*/

void init_pulsadores(){

	Chip_IOCON_PinMuxSet(LPC_IOCON,SW_INVERTIR,FUNC0);
	Chip_IOCON_PinMuxSet(LPC_IOCON,SW_REANUDAR,FUNC0);
	Chip_IOCON_PinMuxSet(LPC_IOCON,SW_PAUSAR,FUNC0);

	Chip_GPIO_SetPinDIRInput(LPC_GPIO,SW_INVERTIR);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,SW_REANUDAR);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,SW_PAUSAR);

}

void init_leds(){

	Chip_IOCON_PinMuxSet(LPC_IOCON,BLUE_LED_PORT,FUNC0);
	Chip_IOCON_PinMuxSet(LPC_IOCON,RED_LED_PORT,FUNC0);
	Chip_IOCON_PinMuxSet(LPC_IOCON,GREEN_LED_PORT,FUNC0);

	Chip_GPIO_SetPinDIROutput(LPC_GPIO,BLUE_LED_PORT);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,RED_LED_PORT);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,GREEN_LED_PORT);

}

static void initHardware(void)
{
	Board_Init();
	init_pulsadores();
	init_leds();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);

}

void vTask_FSM(void * a)
{
	int i;
	SysTickFlag = false;
	InitTimerTicks(timers,NTIMERS);
	tP2_Ej3_init(&statechart);
	tP2_Ej3_enter(&statechart);

	while (1)
	{
		if(SysTickFlag)
		{
			SysTickFlag = false;
			UpdateTimers(timers,NTIMERS);
			for(i=0; i<NTIMERS; i++)
			{
				if(IsPendEvent(timers,NTIMERS,timers[i].evid))
				{
					tP2_Ej3_raiseTimeEvent(&statechart,timers[i].evid);
					MarkAsAttEvent(timers,NTIMERS,timers[i].evid);
				}
			}
			tP2_Ej3_runCycle(&statechart);
			vTaskDelay(1 / portTICK_RATE_MS);
		}

	}

}

void vTask_LaunchEvent(void *pvParameters){

	TECLA tecla;

	while(1){

		//la suspendo hasta que alguien envíe un mensaje por la cola
		if(xQueueReceive( xQueue, &tecla, portMAX_DELAY ) == pdTRUE){

			switch(tecla.id){
				case TECLA_INVERTIR:
					tP2_Ej3_invertirSecuencia(&statechart);
					break;

				case TECLA_REANUDAR:
					tP2_Ej3_raise_evReanudar(&statechart);
					break;

				case TECLA_PAUSAR:
					tP2_Ej3_raise_evPausar(&statechart);
					break;
			}

		}

	}

}

void Diagnostico(void *pvParameters)
{

	//	vPrint("Comienza el diagnostico\n")
	//Loop infinito
	while(1)
	{
		//IMPORTANTE:
		//Este loop pretende simular un conjunto de funciones que
		//insumen un tiempo para realizar el diagnostico del equipo
		//Pero NO es aceptable tener al micro dentro de esta tarea
		//haciendo nada, esto es solo un ejemplo.
		if(!tiempo_de_diagnostico)
		{
			//vPrintString("Termina el diagnostico\n");
			Board_LED_Set(0, 1);
			vTaskDelay(TIEMPO_DE_DIAGNOSTICO_ms/portTICK_RATE_MS);
			tiempo_de_diagnostico = TIEMPO_DE_DIAGNOSTICO_ms;
			Board_LED_Set(0, 0);
			//vPrintString("Comienza el diagnostico\n");
		}

	}

}

void TeclaEvent (void *pvParameters)
{
	unsigned int EstadoDebounce = NO_OPRIMIDO;
	TECLA tecla = *((TECLA*) pvParameters);
	portTickType xMeDesperte;

	//Inicio de variables y recuperación de parámetros

	xMeDesperte = xTaskGetTickCount();

	while(1){
	//debo verificar rebote
	switch(EstadoDebounce){
		case NO_OPRIMIDO:
			vTaskDelayUntil(&xMeDesperte,SCAN_RATE_ms/portTICK_RATE_MS);
			if(Chip_GPIO_GetPinState(LPC_GPIO,tecla.port,tecla.pin))	//Si retorna una opresión
				EstadoDebounce = DEBOUNCE;		//Indico que esta corriendo el tiempo Debounce
			break;

		case DEBOUNCE:
			vTaskDelay(TIEMPO_DE_DEBOUNCE_ms/portTICK_RATE_MS);
			EstadoDebounce = VALIDAR;

		case VALIDAR:
			if(Chip_GPIO_GetPinState(LPC_GPIO,tecla.port,tecla.pin))			//Si retorna algo sigue presionado
				EstadoDebounce=OPRIMIDO;
			else							// fue error
				EstadoDebounce=NO_OPRIMIDO;
			break;

		case OPRIMIDO:
			if(!Chip_GPIO_GetPinState(LPC_GPIO,tecla.port,tecla.pin)) //No envio mensaje hasta no soltar
			{
				//Envío a la cola, optamos por no bloquear si está llena
				xQueueSend( xQueue, &tecla, 0 );
				EstadoDebounce = NO_OPRIMIDO;
			}
			break;
		default:  break;
		}
	}
}

int main(void) {

	//Inicialización del Hardware
	initHardware();

	//Creación de las estructuras tecla
	TECLA sw_invertir;
	TECLA sw_reanudar;
	TECLA sw_pausar;

	sw_invertir.id = TECLA_INVERTIR;
	sw_invertir.port = 2;
	sw_invertir.pin = 10;

	sw_reanudar.id = TECLA_REANUDAR;
	sw_reanudar.port = 0;
	sw_reanudar.pin = 18;

	sw_pausar.id = TECLA_PAUSAR;
	sw_pausar.port = 0;
	sw_pausar.pin = 11;

	//Creación de la cola
	xQueue = xQueueCreate(5,sizeof(TECLA));

	//Creación de las tareas
	xTaskCreate(	vTask_FSM,
					(const char *)"Task_FSM",
					configMINIMAL_STACK_SIZE*4,
					0,
					tskIDLE_PRIORITY+3,
					0);

	xTaskCreate(	vTask_LaunchEvent,
					(const char *)"Task_LaunchEvent",
					configMINIMAL_STACK_SIZE,
					NULL,
					tskIDLE_PRIORITY+2,
					0);

	xTaskCreate(	Diagnostico, ( signed portCHAR* )
					"Diag",
					configMINIMAL_STACK_SIZE,
					NULL,
					tskIDLE_PRIORITY+1,
					NULL );

	xTaskCreate(	TeclaEvent,
					( signed portCHAR* )"TeclaInvertir",
					configMINIMAL_STACK_SIZE,
					(void*)&sw_invertir,
					tskIDLE_PRIORITY+2,
					NULL );

	xTaskCreate(	TeclaEvent,
					( signed portCHAR* )"TeclaReanudar",
					configMINIMAL_STACK_SIZE,
					(void*)&sw_reanudar,
					tskIDLE_PRIORITY+2,
					NULL );

	xTaskCreate(	TeclaEvent,
					( signed portCHAR* )"TeclaPausar",
					configMINIMAL_STACK_SIZE,
					(void*)&sw_pausar,
					tskIDLE_PRIORITY+2,
					NULL );

	//Inicio el Scheduler
	vTaskStartScheduler();

	// Enter an infinite loop, just incrementing a counter
	volatile static int i = 0 ;
	while(1) {
		i++ ;
	}
	return 0 ;
}

void vApplicationTickHook ( void )
{
	if(tiempo_de_diagnostico)
		tiempo_de_diagnostico--;
}


void vApplicationIdleHook ( void )
{
	__ASM volatile ("wfi");
}

