/*==================[inclusions]=============================================*/

#include "main.h"

static void vServoWrite(void * a)
{
	float duty = MS(1);//1ms

	while (1){


		  if(Chip_GPIO_GetPinState(LPC_GPIO,SW_ARRIBA)==LOW)//2ms
		  {
			  duty = duty + MS(0.2);
			  Chip_TIMER_SetMatch(LPC_TIMER1, 1, duty);
			  Chip_TIMER_Reset(LPC_TIMER1);
			  Chip_TIMER_ClearMatch(LPC_TIMER1, 1);
			  Chip_TIMER_ClearMatch(LPC_TIMER1, 0);
		  }
		  if(Chip_GPIO_GetPinState(LPC_GPIO,SW_ABAJO) == LOW)
		  {
			  duty = duty - MS(0.2);
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

