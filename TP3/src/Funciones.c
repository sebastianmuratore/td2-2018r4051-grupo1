/*
 * Init.c
 *
 *  Created on: 23 de may. de 2018
 *      Author: sebas
 */
#include "Aplicacion.h"

void molineteIface_opBloquear(const Molinete* handle, const sc_boolean Estado)
{
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PUERTO_LED,PIN_LED); //Bloquear
}

void molineteIface_opDesbloquear(const Molinete* handle, const sc_boolean Estado)
{
	Chip_GPIO_SetPinOutLow(LPC_GPIO,PUERTO_LED,PIN_LED);
}

void init_hardware(void)
{
    SystemCoreClockUpdate();
    Board_Init();
    Chip_GPIO_Init(LPC_GPIO);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO,PUERTO_LED,PIN_LED);
}

