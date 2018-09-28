/*
 * uart.c
 *
 *  Created on: 3 de sept. de 2018
 *      Author: Juan Bruno
 */

#include "FreeRTOS.h"
#include "board.h"
#include "uart.h"
#include "queue.h"

xQueueHandle colarx;
xQueueHandle colatx;

void inicializarUART3 (void)
{

 	Chip_IOCON_PinMuxSet(LPC_IOCON,LPC_TX3); //TXD
 	Chip_IOCON_PinMuxSet(LPC_IOCON,LPC_RX3); //RXD

	Chip_UART_Init(LPC_UART3);
 	Chip_UART_SetBaud(LPC_UART3, 9600);

 	Chip_UART_ConfigData(LPC_UART3, UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS);
 	//Configuracion de UART con: 8 bits de dato, 1 bit de stop, sin bit de paridad

 	// Cargo los parámetros en la estructura para la FIFO.
 	// Por default: FIFO_DMAMode = DISABLE, FIFO_Level=UART_FIFO_TRGLEV0
 	// FIFO_ResetRxBuf=ENABLE, FIFO_ResetTxBuf=ENABLE, FIFO_State=ENABLE
 	Chip_UART_SetupFIFOS(LPC_UART3, UART_FCR_FIFO_EN | UART_FCR_RX_RS |
 			UART_FCR_TX_RS | UART_FCR_TRG_LEV0);

 	/* dummy read */
 	Chip_UART_ReadByte(LPC_UART3);

 	// Habilito transmisión en pin TXD
 	Chip_UART_TXEnable(LPC_UART3);

 	/* Enable UART interrupt */
 	Chip_UART_IntEnable(LPC_UART3, (UART_IER_RBRINT | UART_IER_THREINT));

 	NVIC_EnableIRQ(UART3_IRQn);

}

void  UART3_IRQHandler(void)
 {
	 portBASE_TYPE  HigherPriorityTaskWoken = 0;
	 int rIIR;
	 int i;
	 int ret;
	 unsigned char dato;
	 LPC_USART_T *p = LPC_UART3;

	 //leo para saber que tipo de interrupción se generó.
	 rIIR=(p->IIR)>>1;
	 rIIR&=0x07;

	 switch(rIIR&0x07)
	{
	 	case IIR_RLS:
	 		//Por error, en teoría no entro jamás (no la activo en la inicialización)
	 		i=p->LSR;
			break;

	 	case IIR_CTI:
	 	case IIR_RDA:

	 		//Tengo que leer la FIFO
	 		//(saltó por disparo de RX)
	 		for(i=0;i<14;i++)
	 		{
	 			//Verifico que la FIFO no este vacía
	 			if(!((p->LSR)&LSR_RDR)) break;

	 			dato = p->RBR;

	 			//Cargo el dato leido en la cola de recepción
	 			xQueueSendFromISR(colarx,&dato,&HigherPriorityTaskWoken);
	 		}
	 		break;

	 	case IIR_THRE:
	 		//Interrupción por Transmisión,FIFO de TX vacía, la intento llenar.

	 		for(i=0;i<8;i++)
	 		{
	 			//Leo los datos pendientes en la cola de transmisión
	 			ret = xQueueReceiveFromISR(colatx,&dato,&HigherPriorityTaskWoken);

	 			//En caso de que haya datos en la cola de transmisión
	 			if(ret!=errQUEUE_EMPTY)
				{
	 				//Envió el dato por la uart a través del registro correspondiente
	 				p->THR = dato;
	 			}
	 			else
	 			{
					break;
				}
	 		}

			break;


	}

	 portEND_SWITCHING_ISR(HigherPriorityTaskWoken);

 }
