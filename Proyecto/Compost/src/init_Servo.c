/*
 * init_pwm.c
 *
 *  Created on: 23 de ago. de 2018
 *      Author: sebas
 */
#include "..//inc/main.h"

void init_Servo()
{
	init_PWM();
	init_timers();
	init_pulsador();
}
void init_PWM ()
{
	 init_pinesPWM();
	 init_timers();
}

void init_timers(void)
{
	uint32_t pclock=0;
	uint32_t pclock2=0;
	/* Timer */
	Chip_TIMER_Init(LPC_TIMER1);
	pclock=Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_TIMER1);
	Chip_TIMER_PrescaleSet(LPC_TIMER1,
	#ifdef lpc1769
			Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_TIMER1) / 1000000 - 1
	#else
			 Chip_Clock_GetRate(CLK_MX_TIMER1) / 1000000 - 1
	#endif
	   );

	/* Match 0 (period) */
	   Chip_TIMER_MatchEnableInt(LPC_TIMER1, 0);
	   Chip_TIMER_ResetOnMatchEnable(LPC_TIMER1, 0);//Cuando matchea se resetea el TC
	   Chip_TIMER_StopOnMatchDisable(LPC_TIMER1, 0);//Sigue contando cuando matchea
	   Chip_TIMER_SetMatch(LPC_TIMER1, 0, PERIODO_PWM);

	   /* Match 1 (duty) */
	   Chip_TIMER_MatchEnableInt(LPC_TIMER1, 1);
	   Chip_TIMER_ResetOnMatchDisable(LPC_TIMER1, 1);//Cuando matchea no se resetea
	   Chip_TIMER_StopOnMatchDisable(LPC_TIMER1, 1);
	   Chip_TIMER_SetMatch(LPC_TIMER1, 1, DUTY);

	   Chip_TIMER_Reset(LPC_TIMER1);
	   Chip_TIMER_Enable(LPC_TIMER1);

	   NVIC_EnableIRQ(TIMER1_IRQn);
}

void init_pinesPWM (	void	)
{

	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_PWM,FUNC_GPIO);
	Chip_IOCON_PinMuxSet(LPC_IOCON,SW_ARRIBA,FUNC_GPIO);
	Chip_IOCON_PinMuxSet(LPC_IOCON,SW_ABAJO,FUNC_GPIO);

	Chip_GPIO_SetDir(LPC_GPIO,PIN_PWM,OUTPUT);
	Chip_GPIO_SetDir(LPC_GPIO,SW_ARRIBA,INPUT);
	Chip_GPIO_SetDir(LPC_GPIO,SW_ABAJO,INPUT);
}

void init_pulsador(		void	)
{
	Chip_IOCON_PinMux(LPC_IOCON,PIN_PULSADOR_SERVO,IOCON_MODE_PULLUP,FUNC_GPIO);
	Chip_GPIO_SetDir(LPC_GPIO,PIN_PULSADOR_SERVO,INPUT);
}
