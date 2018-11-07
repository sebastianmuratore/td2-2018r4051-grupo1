/*
 * TIMER_IRQHandler.c
 *
 *  Created on: 23 de ago. de 2018
 *      Author: sebas
 */
#include "../../PWMyTFT/inc/main.h"

void TIMER1_IRQHandler(void)
{
   if (Chip_TIMER_MatchPending(LPC_TIMER1, 0)) {
      Chip_TIMER_ClearMatch(LPC_TIMER1, 0);
      Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_PWM);
   }
   if (Chip_TIMER_MatchPending(LPC_TIMER1, 1)) {
      Chip_TIMER_ClearMatch(LPC_TIMER1, 1);
      Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_PWM);

   }
}
