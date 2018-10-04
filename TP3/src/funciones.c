#include "FreeRTOS.h"
#include "task.h"
#include "../inc/main.h"
#include "../inc/uart.h"
#include "board.h"
#include "queue.h"
#include "../inc/funciones.h"

extern xQueueHandle colarx;
extern xQueueHandle colatx;

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
	xQueueSend(colatx, &(start), portMAX_DELAY);
	xQueueSend(colatx, &(velocidad), portMAX_DELAY);
	xQueueSend(colatx, &(etx), portMAX_DELAY);
	Chip_UART_Send(LPC_UART3, &(stx), 1);
}

void enviarComando(char comando){
	char etx = ETX;
	char stx = STX;
	xQueueSend(colatx, &(comando), portMAX_DELAY);
	xQueueSend(colatx, &(etx), portMAX_DELAY);
	Chip_UART_Send(LPC_UART3, &(stx), 1);
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
			enviarComando(OK);
			break;

		case START:
			//cambiarVelocidadMotor(velocidad);
			enviarComando(OK);
			break;

		case STOP:
			enviarComando(OK);
			break;

		case OK:
			printf("Mensaje válido");
			break;

		case NOK:
			printf("Mensaje inválido");
			break;

		case SIN_ENERGIA:
			printf("Motor sin energía, vuelva a enviar el mensaje en 1min");
			break;

		case MOTOR_ACTIVO:
			printf("En caso de querer mofidicar la velocidad primero debe frenar el motor");
			break;

		case VELOCIDAD_INCORRECTA:
			printf("Velocidad incorrecta");
			break;

		case MANTENIMIENTO:
			printf("Motor en mantenimiento, vuelva a enviar el mensaje en 1min");
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
			if(dato == INICIO)
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
			accion = dato;
			if(dato == START)
				estado = ESTADO_DATO;
			else if(dato == ETX)
				estado = ESTADO_FIN_TRAMA;
			else
				estado = ESTADO_IDLE;
			break;

		case ESTADO_DATO:
			velocidad = dato;
			if(dato == ETX)
				estado = ESTADO_FIN_TRAMA;
			else
				estado = ESTADO_IDLE;
			break;

		case ESTADO_FIN_TRAMA:
			validarAccion(accion, velocidad);
			estado = ESTADO_IDLE;
			if(accion == MANTENIMIENTO || accion == SIN_ENERGIA)
				return 1;
			else
				return 0;
			break;

		default:
			estado = ESTADO_IDLE;
			break;

	}

	return 0;

}
