/* Copyright 2016, Pablo Ridolfi
 * All rights reserved.
 *
 * This file is part of Workspace.
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
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
 
/** @brief This is a simple blink example.
 */

/** \addtogroup blink Bare-metal blink example
 ** @{ */

/*==================[inclusions]=============================================*/

#include "FreeRTOS.h"
#include "task.h"
#include "../inc/main.h"
#include "../inc/funciones.h"
#include "../inc/uart.h"
#include "board.h"
#include "queue.h"


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*UART3*/
extern xQueueHandle colarxA;
extern xQueueHandle colatxA;
/*UART2*/
extern xQueueHandle colarxB;
extern xQueueHandle colatxB;


/*==================[internal functions declaration]=========================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

//Creo una tarea que cada 10ms se fija si hay datos para leer.
void vUartRead(void *parametro)
{
	char dato;
	int cantidad = 0, i = 0;
	xQueueHandle colarx = *((xQueueHandle *)parametro);

	while(1)
	{
		vTaskDelay(10/portTICK_RATE_MS);

		//Leo los datos en la cola rx
		cantidad = uxQueueMessagesWaiting(colarx);

		if(cantidad > 0){

			for(i=0;i<cantidad;i++){

				xQueueReceive(colarx,&dato,portMAX_DELAY);
				i = procesarTrama(dato);
				if(i > 0){
					/*Frena todo por 1min en caso de:
					 *Mantenimiento
					 *Sin energía
					 *Luego vuelve a enviar comando de encendido*/
					vTaskDelay(60000/portTICK_RATE_MS);
					cambioVelocidad(VELOCIDAD_1);
					i = 0;

				}

			}

		}

	}

}

void vSelectedSW(void *a){

	while(1){

		vTaskDelay(10/portTICK_RATE_MS);

		//SW1 - OFF
		if(!Chip_GPIO_GetPinState(LPC_GPIO,SW_OFF)){
			enviarComando(TERMINAL_A, STOP);
		}

		//SW2 - VELOCIDAD 1
		else if(!Chip_GPIO_GetPinState(LPC_GPIO,SW_VELOCIDAD1)){
			cambioVelocidad(VELOCIDAD_1);
		}

		//SW3 - VELOCIDAD 5
		else if(!Chip_GPIO_GetPinState(LPC_GPIO,SW_VELOCIDAD5)){
			cambioVelocidad(VELOCIDAD_5);
		}

		//SW4 - VELOCIDAD 10
		else if(!Chip_GPIO_GetPinState(LPC_GPIO,SW_VELOCIDAD10)){
			cambioVelocidad(VELOCIDAD_10);
		}

		//SW5 - VELOCIDAD 20
		else if(!Chip_GPIO_GetPinState(LPC_GPIO,SW_VELOCIDAD20)){
			cambioVelocidad(VELOCIDAD_20);
		}

	}

}

int main(void)
{
	int i, flag = 0, cantidad = 0;
	char dato;
	initHardware();

	colarxA = xQueueCreate(512,sizeof(char));
	colatxA = xQueueCreate(512,sizeof(char));
	colarxB = xQueueCreate(512,sizeof(char));
	colatxB = xQueueCreate(512,sizeof(char));


	//Si es la terminal A, no comienza el proceso hasta que no reciba un OK, al INICIO enviado.
	#ifdef EQUIPO_A
	enviarComando(TERMINAL_A, INICIO);

	while(flag==0){
		//Leo los datos en la cola rx
		cantidad = uxQueueMessagesWaiting(colarxA);

		if(cantidad > 0){

			for(i=0;i<cantidad;i++){

				xQueueReceive(colarxA,&dato,portMAX_DELAY);
				flag = procesarTramaInicio(dato);

				if(flag==1)
					break;
				else{
					i = 0;
					enviarComando(TERMINAL_A, INICIO);
				}
			}
		}
	}

#endif

/*Si es la terminal A:
 * Crea la tarea para el manejo de los pulsadores
 * Le asigna la comunicación a traves de la UART3
*/
#ifdef EQUIPO_A
	xTaskCreate(vSelectedSW, (signed char* )"Pulsadores", configMINIMAL_STACK_SIZE,
						NULL, tskIDLE_PRIORITY+1, NULL );
	xTaskCreate(vUartRead, (signed char* )"Leer Uart 3", configMINIMAL_STACK_SIZE,
							&colarxA, tskIDLE_PRIORITY+1, NULL );
#endif

/*Si es la terminal B:
 * Le asigna la comunicación a traves de la UART2
*/
#ifdef EQUIPO_B
	xTaskCreate(vUartRead, (signed char* )"Leer Uart 2", configMINIMAL_STACK_SIZE,
							&colarxB, tskIDLE_PRIORITY+1, NULL );
#endif

	//Inicio el Scheduler
	vTaskStartScheduler();

	while (1){}
}

/** @} doxygen end group definition */

/*==================[end of file]============================================*/
