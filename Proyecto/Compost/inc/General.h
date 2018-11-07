/*
 * General.h
 *
 *  Created on: 6 de set. de 2018
 *      Author: sebas
 */

#ifndef TPS_TD2_2018R4051_GRUPO1_PROYECTO_PWM_FREERTOS_INC_GENERAL_H_
#define TPS_TD2_2018R4051_GRUPO1_PROYECTO_PWM_FREERTOS_INC_GENERAL_H_

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                              MACROS GRALES
 *
 *-------------------------------------------------------------------------------------------------------------------------------------------------------*/
#include "../inc/SPI.h"

#define 	HIGH			1
#define 	LOW 			0
#define		INPUT			0
#define		OUTPUT			1
#define		FUNC_0			0x0
#define		FUNC_1			0x1
#define		FUNC_2			0x2
#define		FUNC_3			0x3
#define		FUNC_GPIO		FUNC_0


#define		IOCON_FUNC_SPI	FUNC_3
#define		FUNC_ADC_4		FUNC_3
#define		FUNC_ADC_3		FUNC_1

/*--------------------------------------------------------------------------------------------------------------------------------------------------------
 * 												PINES
 --------------------------------------------------------------------------------------------------------------------------------------------------------*/
#define		D7			2,5
#define		SW_5		1,26
#define		SW_4		0,18




#define		PIN_05		0,9
#define		PIN_06		0,8
#define		PIN_07		0,7
#define		PIN_08		0,6
#define		PIN_09		0,0
#define		PIN_10		0,1
#define		PIN_11		0,18
#define		PIN_12      0,17
#define		PIN_13		0,15
#define		PIN_14		0,16
#define		PIN_15		0,23
#define		PIN_16		0,24
#define		PIN_17 		0,25
#define 	PIN_18		0,26
#define		PIN_19		1,30
#define		PIN_20		1,31
#define		PIN_21		0,2
#define		PIN_22		0,3
#define		PIN_23		0,21


#endif /* TPS_TD2_2018R4051_GRUPO1_PROYECTO_PWM_FREERTOS_INC_GENERAL_H_ */
