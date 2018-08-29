/*==================[inclusions]=============================================*/

#include "main.h"

static void vServoWrite(void * a)
{
	int duty = DUTY;//1ms

	while (1){


		  if(Chip_GPIO_GetPinState(LPC_GPIO,SW_ARRIBA) == LOW && duty <= PERIODO_PWM)//2ms
		  {
			  duty = duty +100000;
			  Chip_TIMER_SetMatch(LPC_TIMER1, 1, duty);
			  Chip_TIMER_Reset(LPC_TIMER1);
			  Chip_TIMER_ClearMatch(LPC_TIMER1, 1);
			  Chip_TIMER_ClearMatch(LPC_TIMER1, 0);
		  }
		  if(Chip_GPIO_GetPinState(LPC_GPIO,SW_ABAJO) == LOW && duty >= 500000 )
		  {
			  duty = duty - 100000;
			  Chip_TIMER_SetMatch(LPC_TIMER1, 1, duty);
			  Chip_TIMER_Reset(LPC_TIMER1);
			  Chip_TIMER_ClearMatch(LPC_TIMER1, 1);
			  Chip_TIMER_ClearMatch(LPC_TIMER1, 0);
		  }

	}
}


int main(void)
{
	initHardware();

	xTaskCreate(vServoWrite, (const char *)"vServoWrite", configMINIMAL_STACK_SIZE*2, 0, tskIDLE_PRIORITY+1, 0);

	vTaskStartScheduler();

	while (1){
	}
}

