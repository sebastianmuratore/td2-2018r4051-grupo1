#include "FreeRTOS.h"
#include "task.h"
#include "../inc/main.h"
#include "../inc/uart.h"
#include "board.h"
#include "queue.h"
#include "../inc/funciones.h"

/*UART3*/
extern xQueueHandle colarxA;
extern xQueueHandle colatxA;
/*UART2*/
extern xQueueHandle colarxB;
extern xQueueHandle colatxB;

void initHardware(void)
{
	 SystemCoreClockUpdate();
	 Board_Init();
	 Board_LED_Set(0, false);
	 inicializarPulsadores();
	 inicializarUART3();
}

void cambioVelocidad(char velocidad){
	char start = START;
	char etx = ETX;
	char stx = STX;
	xQueueSend(colatxA, &(start), portMAX_DELAY);
	xQueueSend(colatxA, &(velocidad), portMAX_DELAY);
	xQueueSend(colatxA, &(etx), portMAX_DELAY);
	Chip_UART_Send(LPC_UART3, &(stx), 1);
}

void enviarComando(char terminal, char comando){
	char etx = ETX;
	char stx = STX;
	if(terminal == TERMINAL_B){
		xQueueSend(colatxB, &(comando), portMAX_DELAY);
		xQueueSend(colatxB, &(etx), portMAX_DELAY);
		Chip_UART_Send(LPC_UART2, &(stx), 1);
	}
	else if(terminal == TERMINAL_A){
		xQueueSend(colatxA, &(comando), portMAX_DELAY);
		xQueueSend(colatxA, &(etx), portMAX_DELAY);
		Chip_UART_Send(LPC_UART3, &(stx), 1);
	}

}

void inicializarPulsadores(void){

	Chip_IOCON_PinMuxSet(LPC_IOCON,SW_OFF,FUNC0);	//SW OFF
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,SW_OFF);

	Chip_IOCON_PinMuxSet(LPC_IOCON,SW_VELOCIDAD1,FUNC0); //SW VELOCIDAD 1
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,SW_VELOCIDAD1);

	Chip_IOCON_PinMuxSet(LPC_IOCON,SW_VELOCIDAD5,FUNC0); //SW VELOCIDAD 5
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,SW_VELOCIDAD5);

	Chip_IOCON_PinMuxSet(LPC_IOCON,SW_VELOCIDAD10,FUNC0); //SW VELOCIDAD 10
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,SW_VELOCIDAD10);

	Chip_IOCON_PinMuxSet(LPC_IOCON,SW_VELOCIDAD20,FUNC0); //SW VELOCIDAD 20
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,SW_VELOCIDAD20);

}

void validarAccion(char accion, int velocidad){

	switch(accion){

		case INICIO:
			enviarComando(TERMINAL_B, OK);
			break;

		case START:
			enviarComando(TERMINAL_B, OK);
			//Se deberia llamar a una función que arranque el motor pero no es requerido
			break;

		case STOP:
			enviarComando(TERMINAL_B, OK);
			//Se deberia llamar a una función que frene el motor pero no es requerido
			break;

		case OK:
			printf("Mensaje válido");
			break;

		case NOK:
			printf("Mensaje inválido");
			break;

		case MOTOR_ACTIVO:
			enviarComando(TERMINAL_A, STOP);
			break;

		case VELOCIDAD_INCORRECTA:
			cambioVelocidad(VELOCIDAD_1);
			break;

	}

}

int procesarTramaInicio(char dato){

	static int estado = ESTADO_IDLE;

	switch(estado){

		case ESTADO_IDLE:
			if(dato == STX)
				estado = ESTADO_INICIO_TRAMA;
			break;

		case ESTADO_INICIO_TRAMA:
			if(dato == OK)
				estado = ESTADO_FIN_TRAMA;
			break;

		case ESTADO_FIN_TRAMA:
			if(dato == ETX)
				return 1;
			break;

		default:
			estado = ESTADO_IDLE;
		break;

	}

	return 0;

}

int procesarTrama(char dato){

	static int estado = ESTADO_IDLE;
	static char accion;
	static int velocidad = 0;

	switch(estado){

		case ESTADO_IDLE:
			accion = 0;
			velocidad = 0;
			if(dato == STX)
				estado = ESTADO_INICIO_TRAMA;
			break;

		case ESTADO_INICIO_TRAMA:
			if(dato == START)
				estado = ESTADO_DATO;
			else{
				accion = dato;
				estado = ESTADO_FIN_TRAMA;
			}
			break;

		case ESTADO_DATO:
			velocidad = dato;
			estado = ESTADO_FIN_TRAMA;
			break;

		case ESTADO_FIN_TRAMA:
			if(dato == STX){
				estado = ESTADO_IDLE;
				if(accion == MANTENIMIENTO || accion == SIN_ENERGIA)
					return accion;
				else{
					validarAccion(accion, velocidad);
					return 0;
				}

			}
			break;

		default:
			estado = ESTADO_IDLE;
			break;

	}

	return 0;

}
