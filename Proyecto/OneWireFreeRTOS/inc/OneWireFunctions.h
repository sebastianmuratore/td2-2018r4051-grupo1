/*
 * OneWireFunctions.h
 *
 *  Created on: 4 de set. de 2018
 *      Author: jonat
 */

#include "board.h"

void pausems(uint32_t);
void pauseus(uint32_t);


#ifndef PROJECTS_ONEWIRE_INC_ONEWIREFUNCTIONS_H_
#define PROJECTS_ONEWIRE_INC_ONEWIREFUNCTIONS_H_

#define owPin	0,20

#define 	owSetOutput()		Chip_GPIO_SetPinDIROutput(LPC_GPIO, owPin)
#define 	owSetInput()		Chip_GPIO_SetPinDIRInput(LPC_GPIO, owPin)
#define 	owReadPin()			Chip_GPIO_GetPinState(LPC_GPIO, owPin)
#define 	owSetLow()			Chip_GPIO_SetPinOutLow(LPC_GPIO, owPin)
#define 	owSetHigh()			Chip_GPIO_SetPinOutHigh(LPC_GPIO, owPin)

#define		SkipROM		0xCC
#define		ConvertT	0x44
#define		ReadScratch	0xBE

int owInitTransaction (void);
void owSendCommand (uint8_t , void *, uint8_t );
int owReadTemperature(void);
void initHardware(void);
static uint8_t owCRC(uint8_t *, uint8_t);

#endif /* PROJECTS_ONEWIRE_INC_ONEWIREFUNCTIONS_H_ */
