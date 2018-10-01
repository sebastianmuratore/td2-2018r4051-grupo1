/*
 * initHW.c
 *
 *  Created on: 4 de set. de 2018
 *      Author: jonat
 */

#include "../../OneWire1/inc/OneWireFunctions.h"

void initPins (void)
{
    Chip_IOCON_PinMux(LPC_IOCON, owPin,
    		IOCON_MODE_PULLUP ,
			IOCON_FUNC0);
}

extern volatile uint32_t * DWT_CTRL;

void initHardware (void)
{
	SystemCoreClockUpdate();
	Board_Init();
	SysTick_Config(SystemCoreClock/1000);
	*DWT_CTRL |= 1;
	initPins();
	owSetInput();
}
