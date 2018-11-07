/*
 * touch.h
 *
 *  Created on: 28 de set. de 2018
 *      Author: sebas
 */

#ifndef TPS_TD2_2018R4051_GRUPO1_PROYECTO_PWMYTFT_INC_TOUCH_H_
#define TPS_TD2_2018R4051_GRUPO1_PROYECTO_PWMYTFT_INC_TOUCH_H_

#include "../inc/General.h"

/*------------------------------------------------------------------------------------------------------------------------
 * 							MACROS
 *----------------------------------------------------------------------------------------------------------------------
 */

//Pines

#define		PIN_Ym			PIN_19//ADC
#define		PIN_Yp			PIN_20
#define		PIN_Xp			PIN_21
#define		PIN_Xm			PIN_18//ADC

//Defines
#define		RANGO_ADC		4095
#define		ADC_CHANNEL_X 	ADC_CH3
#define		ADC_CHANNEL_Y	ADC_CH4
#define		fs				1
/*------------------------------------------------------------------------------------------------------------------------
 * 							FUNCIONES
 *----------------------------------------------------------------------------------------------------------------------
 */
void 		initTouch 		(	void	);
void 		initADC			(	void	);
void 		initPinesTouch	(	void	);
uint16_t 	readTouchY 		(	void	);
uint16_t 	readTouchX 		(	void	);
void 		enablePinesReadY(	void	);
void 		enablePinesReadX(	void	);
void 		disablePinesReadX(	void	);
void 		disablePinesReadY(	void	);






/*GND----------------D7 *
 *
 * Y=1300			Y=270
 *
 *
 * GND---------------CD
 *
 */
#endif /* TPS_TD2_2018R4051_GRUPO1_PROYECTO_PWMYTFT_INC_TOUCH_H_ */
