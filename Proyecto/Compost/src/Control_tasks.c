/*
 * Control_tasks.c
 *
 *  Created on: 16 de nov. de 2018
 *      Author: sebas
 */
#include "main.h"

extern xQueueHandle qDatos;
extern xQueueHandle qHumedad;
extern xQueueHandle qTemp;

void vGetReport(void *parametros)
{
	Datos datos;

	while(1)
	{
		//Lee los datos de humedad
		if(xQueueReceive(qHumedad, &(datos.humedad), portMAX_DELAY)){
			xQueueReset(qHumedad);
		}

		//Lee los datos de temp
		if(xQueueReceive(qTemp, &(datos.temperatura), portMAX_DELAY)){
			xQueueReset(qTemp);
		}

		xQueueSend(qDatos,&datos,portMAX_DELAY);

	}

}
