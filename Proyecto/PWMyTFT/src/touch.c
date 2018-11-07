/*
 * adc.c
 *
 *  Created on: 28 de set. de 2018
 *      Author: sebas
 */
#include "../../PWMyTFT/inc/main.h"


void initTouch (	void	)
{
	initADC();
//	initPinesTouch();
}


void initADC	(	void	)
{
	ADC_CLOCK_SETUP_T ADCSetup;


	Chip_ADC_Init(LPC_ADC, &ADCSetup);
	Chip_ADC_SetSampleRate(LPC_ADC, &ADCSetup, fs);
	Chip_ADC_EnableChannel(LPC_ADC, ADC_CHANNEL_X, TRUE);
	//Chip_ADC_EnableChannel(LPC_ADC, ADC_CHANNEL_Y, TRUE);
	Chip_ADC_SetBurstCmd(LPC_ADC, DISABLE);

}

void initPinesTouch	(	void	)
{
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_Xp,FUNC_GPIO);
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_Yp,FUNC_GPIO);

	Chip_GPIO_SetPinDIROutput(LPC_GPIO,PIN_Xp);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,PIN_Yp);
}

uint16_t readTouchX (	void	)
{

	 uint16_t dataADC=0;

	 enablePinesReadX();

	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_Yp);
	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_Ym);
//	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_Xp);

	Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);//en teoria el trigger no tiene sentido si se selecciona start now
	while (Chip_ADC_ReadStatus(LPC_ADC, ADC_CHANNEL_X, ADC_DR_DONE_STAT) != SET) {} //<---BLOQUEANTE!!!
	Chip_ADC_ReadValue(LPC_ADC, ADC_CHANNEL_X, &dataADC);


	disablePinesReadX();

	return (dataADC);

}

uint16_t readTouchY (	void	)
{
	uint16_t dataADC=0;
	float vy = 0;
	enablePinesReadY();

//	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_Yp);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_Xp);
	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_Xm);

	Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);//en teoria el trigger no tiene sentido si se selecciona start now
	while (Chip_ADC_ReadStatus(LPC_ADC, ADC_CHANNEL_Y, ADC_DR_DONE_STAT) != SET) {} //<---BLOQUEANTE!!!
	Chip_ADC_ReadValue(LPC_ADC, ADC_CHANNEL_Y, &dataADC);

	vy = dataADC*3.3/4095;
	disablePinesReadY();
	return (dataADC);
}

void enablePinesReadX(	void	)
{
	Chip_ADC_EnableChannel(LPC_ADC,ADC_CHANNEL_X,ENABLE);

	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_Xm,FUNC_ADC_3); //ADC
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_Yp,FUNC_GPIO);	//Digital
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_Xp,FUNC_GPIO);  //Digital
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_Ym,FUNC_GPIO);  //Digital

	Chip_GPIO_SetPinDIRInput(LPC_GPIO,PIN_Xp);
	Chip_IOCON_EnableOD(LPC_IOCON,PIN_Xp);

	Chip_GPIO_SetPinDIROutput(LPC_GPIO,PIN_Ym);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,PIN_Yp);


}


void enablePinesReadY(	void	)
{

	Chip_ADC_EnableChannel(LPC_ADC,ADC_CHANNEL_Y,ENABLE);
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_Ym,FUNC_ADC_4); //ADC

	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_Yp,FUNC_GPIO);	//Digital
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_Xp,FUNC_GPIO);  //Digital
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_Xm,FUNC_GPIO);  //Digital

	Chip_GPIO_SetPinDIROutput(LPC_GPIO,PIN_Xp);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,PIN_Xm);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,PIN_Yp);
	Chip_IOCON_EnableOD(LPC_IOCON,PIN_Yp);



}


void disablePinesReadX()
{
	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_Ym);
	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_Yp);
	Chip_IOCON_DisableOD(LPC_IOCON,PIN_Xp);
	Chip_ADC_EnableChannel(LPC_ADC,ADC_CHANNEL_X,DISABLE);

}

void disablePinesReadY()
{
	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_Xm);
	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_Xp);
	Chip_IOCON_DisableOD(LPC_IOCON,PIN_Yp);
	Chip_ADC_EnableChannel(LPC_ADC,ADC_CHANNEL_Y,DISABLE);


}
