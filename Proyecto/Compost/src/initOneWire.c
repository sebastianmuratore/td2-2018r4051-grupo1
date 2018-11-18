/*
 * initHW.c
 *
 *  Created on: 4 de set. de 2018
 *      Author: jonat
 */

//#include "../inc/OneWireFunctions.h"
#include "../inc/main.h"

void initPins (void)
{
    Chip_IOCON_PinMux(LPC_IOCON, owPin,
    		IOCON_MODE_PULLUP ,
			IOCON_FUNC0);
}

//extern volatile uint32_t * DWT_CTRL;

void init_OW (void)
{
	extern volatile uint32_t * DWT_CTRL;
//	SystemCoreClockUpdate();
//	Board_Init();
	SysTick_Config(SystemCoreClock/1000);
	*DWT_CTRL |= 1;
	initPins();
	owSetInput();
}
