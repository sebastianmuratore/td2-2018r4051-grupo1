/*
 * Servo_tasks.c
 *
 *  Created on: 16 de nov. de 2018
 *      Author: sebas
 */


#include "main.h"

void vServoWrite(void * a)
{
	static int giro = 1;
	float duty;

	while (1)
	{
		xSemaphoreTake(sServo,portMAX_DELAY);

		if(giro)
		{
			duty = MS(0.6);
			giro = 0;
		}

		else
		{
			duty = MS(2.4);
			giro = 1;
		}

		servoWrite(duty);

		vTaskDelay(10000/portTICK_RATE_MS);
	}
}


void servoWrite(float duty)
{

	Chip_TIMER_SetMatch(LPC_TIMER1, 1, duty);
	Chip_TIMER_Reset(LPC_TIMER1);
	Chip_TIMER_ClearMatch(LPC_TIMER1, 1);
	Chip_TIMER_ClearMatch(LPC_TIMER1, 0);

}
