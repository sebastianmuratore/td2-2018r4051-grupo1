#include "../../PWMyTFT/inc/tft.h"

uint32_t count = 0;

void TIMER0_IRQHandler(void)
{
	if (Chip_TIMER_MatchPending(LPC_TIMER0, 1)) {
		Chip_TIMER_ClearMatch(LPC_TIMER0, 1);
		count--;
	}
}

void TIMER_delay(uint32_t time, uint32_t freq) {
	count = time;

	Chip_TIMER_Init(LPC_TIMER0);
	Chip_Clock_SetPCLKDiv(SYSCTL_CLOCK_TIMER0, 1);
	Chip_TIMER_Reset(LPC_TIMER0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER0, 1);
	Chip_TIMER_SetMatch(LPC_TIMER0, 1, (Chip_Clock_GetSystemClockRate() / freq));
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER0, 1);
	Chip_TIMER_Enable(LPC_TIMER0);

	NVIC_ClearPendingIRQ(TIMER0_IRQn);
	NVIC_EnableIRQ(TIMER0_IRQn);

	while(count > 0) { }

	Chip_TIMER_Disable(LPC_TIMER0);
	NVIC_DisableIRQ(TIMER0_IRQn);
	Chip_TIMER_DeInit(LPC_TIMER0);
}

void TIMER_delay_seg(uint32_t time) {
	TIMER_delay(time, 1);
}

void TIMER_delay_ms(uint32_t time) {
	TIMER_delay(time, 1000);
}

void TIMER_delay_us(uint32_t time) {
	TIMER_delay(time, 1000 * 1000);
}
