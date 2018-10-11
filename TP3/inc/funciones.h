/*
 * function.h
 *
 *  Created on: 6 de sept. de 2018
 *      Author: Juan Bruno
 */

#ifndef TPS_TD2_2018R4051_GRUPO1_TP3_INC_FUNCIONES_H_
#define TPS_TD2_2018R4051_GRUPO1_TP3_INC_FUNCIONES_H_

void initHardware(void);
void cambioVelocidad(char velocidad);
void enviarComando(char terminal, char comando);
void inicializarPulsadores(void);
void validarAccion(char accion, int velocidad);
int procesarTrama(char dato);
int procesarTramaInicio(char dato);

#endif /* TPS_TD2_2018R4051_GRUPO1_TP3_INC_FUNCIONES_H_ */
