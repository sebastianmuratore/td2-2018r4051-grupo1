/*
 * Servo_tasks.c
 *
 *  Created on: 16 de nov. de 2018
 *      Author: sebas
 */


#include "main.h"

void vServoWrite(void * a)
{
	float duty=0,dutyAnt=0;
	portBASE_TYPE pdSem;

	while (1)
	{
		/*
		if(!Chip_GPIO_GetPinState(LPC_GPIO,PIN_PULSADOR_SERVO))
		{
			duty = invertirGiro();
		}

		pdSem =  xSemaphoreTake(sServo,1000/portTICK_RATE_MS);

		if( pdSem == pdTRUE)
			duty = invertirGiro();

		if(duty != dutyAnt)
		{
			servoWrite(duty);
			dutyAnt = duty;
		}

		xSemaphoreTake(sServo,portMAX_DELAY);*/


		duty = invertirGiro();
		servoWrite(duty);
		vTaskDelay(5000/portTICK_RATE_MS);
	}
}


void servoWrite(float duty)
{

	Chip_TIMER_SetMatch(LPC_TIMER1, 1, duty);
	Chip_TIMER_Reset(LPC_TIMER1);
	Chip_TIMER_ClearMatch(LPC_TIMER1, 1);
	Chip_TIMER_ClearMatch(LPC_TIMER1, 0);

}

float invertirGiro(void)
{
	static int giro = 1;
	float duty;
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

	return duty;
}
