/*
 * Control_tasks.h
 *
 *  Created on: 16 de nov. de 2018
 *      Author: sebas
 */

#ifndef TPS_TD2_2018R4051_GRUPO1_PROYECTO_COMPOST_INC_CONTROL_TASKS_H_
#define TPS_TD2_2018R4051_GRUPO1_PROYECTO_COMPOST_INC_CONTROL_TASKS_H_


typedef struct
{
	float temperatura;
	float humedad;
}Datos;

void vGetReport(void *parametros);

#endif /* TPS_TD2_2018R4051_GRUPO1_PROYECTO_COMPOST_INC_CONTROL_TASKS_H_ */
