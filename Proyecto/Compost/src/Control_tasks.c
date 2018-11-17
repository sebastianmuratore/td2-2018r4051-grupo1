/*
 * Control_tasks.c
 *
 *  Created on: 16 de nov. de 2018
 *      Author: sebas
 */
#include "main.h"

extern xQueueHandle qDatos;
void vGetReport(void *parametros)
{
	Datos datos;
	datos.humedad = 70;
	datos.temperatura = 30;

	while(1)
	{
		//LLama a get temperatura y get humedad
		if(datos.humedad == 100 )
		{
			datos.humedad = 70;
			datos.temperatura = 30;
		}
		datos.humedad++;
		datos.temperatura++;

		xQueueSend(qDatos,&datos,portMAX_DELAY);
		vTaskDelay(10000/portTICK_RATE_MS);
	}

}
