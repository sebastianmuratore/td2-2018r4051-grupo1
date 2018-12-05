/*
 * Aplicacion.h
 *
 *  Created on: 22 de ago. de 2018
 *      Author: sebas
 */

#ifndef TPS_TD2_2018R4051_GRUPO1_PROYECTO_PWMYTFT_INC_PWM_H_
#define TPS_TD2_2018R4051_GRUPO1_PROYECTO_PWMYTFT_INC_PWM_H_



#define 	PIN_PWM					PAD_4
#define		SW_ARRIBA				SW_5
#define		SW_ABAJO				2,10
#define		PIN_PULSADOR_SERVO		2,2

#define		PERIODO_PWM MS(20)
#define		DUTY		MS(1)

#define		_1SEGUNDO	MS(1000)

#define		_1MS		1000
#define		MS(x)		(x)*_1MS


#define REFRESH_RATE_ms 500
#define TIEMPO_DE_DIAGNOSTICO_ms 2000
#define TIEMPO_DE_DEBOUNCE_ms 20
#define SCAN_RATE_ms 150

#define NO_OPRIMIDO	0
#define DEBOUNCE	1
#define VALIDAR		2
#define OPRIMIDO	3

/*-----------FUNCIONES-----------------------*/
void initHardware		(	void	);
void init_PWM 			(	void	);
void init_timers		(	void	);
void init_pinesPWM 		(	void	);
void init_Servo			(	void	);
void init_pulsador		(		void	);
#endif /* TPS_TD2_2018R4051_GRUPO1_PROYECTO_PWMYTFT_INC_PWM_H_ */
