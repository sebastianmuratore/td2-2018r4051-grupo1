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
#define		PIN_24		0,22
#define		PIN_25		0,27
#define		PIN_26		0,28
#define		PIN_27		2,13
#define		PIN_28		VCC
#define		PIN_29
#define		PIN_30
#define		PIN_31
#define		PIN_32
#define		PIN_33
#define		PIN_34
#define		PIN_35
#define		PIN_36
#define		PIN_37
#define		PIN_38		0,4
#define		PIN_39		0,5
#define		PIN_40		0,10
#define		PIN_41		0,11
#define		PIN_42		2,0
#define		PIN_43		2,1
#define		PIN_44		2,2
#define		PIN_45		2,3
#define		PIN_46		2,4
#define		PIN_47		2,5
#define		PIN_48		2,6
#define		PIN_49		2,7
#define		PIN_50		2,8
#define		PIN_51		2,10
#define		PIN_52		2,11
#define		PIN_53		2,12
#define		PIN_54		GND

#define		PAD_1		1,18
#define		PAD_2		1,19
#define		PAD_3		1,20
#define		PAD_4		1,21
#define		PAD_5		1,22
#define		PAD_6		1,23
#define		PAD_7		1,24
#define		PAD_8		1,25
#define		PAD_9		1,26
#define		PAD_10		1,27
#define		PAD_11		1,28
#define		PAD_12		1,29
#define		PAD_13		3,25
#define		PAD_14		3,26
#define		PAD_15		4,28
#define		PAD_16		4,29
#define		PAD_17		0,19
#define		PAD_18		0,20
#define		PAD_19		2,9




#define		UN_MINUTO 		60000/portTICK_RATE_MS
#define		DIEZ_SEG		10000/portTICK_RATE_MS
#define		CINCO_SEG		5000/portTICK_RATE_MS


#endif /* TPS_TD2_2018R4051_GRUPO1_PROYECTO_PWM_FREERTOS_INC_GENERAL_H_ */
