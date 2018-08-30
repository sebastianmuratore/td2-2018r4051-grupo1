/*
 * Aplicacion.h
 *
 *  Created on: 22 de ago. de 2018
 *      Author: sebas
 */

#ifndef TPS_TD2_2018R4051_GRUPO1_PROYECTO_PWM_INC_PWM_H_
#define TPS_TD2_2018R4051_GRUPO1_PROYECTO_PWM_INC_PWM_H_

#define 	HIGH		1
#define 	LOW 		0
#define		INPUT		0
#define		OUTPUT		1
#define		FUNC_0		0x0
#define		FUNC_1		0x1
#define		FUNC_2		0x2
#define		FUNC_3		0x3
#define		FUNC_GPIO	FUNC_0

#define 	PIN_PWM		D7
#define		D7			2,5
#define		SW_5		1,26
#define		SW_4		0,18
#define		SW_ARRIBA	SW_5
#define		SW_ABAJO	2,10

#define		PERIODO_PWM MS(20)
#define		DUTY		MS(1)

#define		_1SEGUNDO	MS(1000) //El pclock esta a 2mhz...?

#define		_1MS		1000
#define		MS(x)		(x)*_1MS

/*-----------FUNCIONES-----------------------*/
void initHardware		(	void	);
void init_timers		(	void	);
void init_pines 		(	void	);

#endif /* TPS_TD2_2018R4051_GRUPO1_PROYECTO_PWM_INC_PWM_H_ */
