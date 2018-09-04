/*
 * uart.c
 *
 *  Created on: 3 de sept. de 2018
 *      Author: Juan Bruno
 */

#include "board.h"
#include "uart.h"
//#include "../../../../modules/lpc1769/freertos/inc/queue.h"
#include "queue.h"

xQueueHandle colarx;
xQueueHandle colatx;

void inicializarUART2 (void)
{

 	Chip_IOCON_PinMuxSet(LPC_IOCON,LPC_TX2); //TXD
 	Chip_IOCON_PinMuxSet(LPC_IOCON,LPC_RX2); //RXD

	Chip_UART_Init(LPC_UART2);
 	Chip_UART_SetBaud(LPC_UART2, 9600);

 	Chip_UART_ConfigData(LPC_UART2, UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS);
 	//Configuracion de UART con: 8 bits de dato, 1 bit de stop, sin bit de paridad

 	// Cargo los parámetros en la estructura para la FIFO.
 	// Por default: FIFO_DMAMode = DISABLE, FIFO_Level=UART_FIFO_TRGLEV0
 	// FIFO_ResetRxBuf=ENABLE, FIFO_ResetTxBuf=ENABLE, FIFO_State=ENABLE
 	Chip_UART_SetupFIFOS(LPC_UART2, UART_FCR_FIFO_EN | UART_FCR_RX_RS |
 			UART_FCR_TX_RS | UART_FCR_TRG_LEV0);

 	/* dummy read */
 	Chip_UART_ReadByte(LPC_UART2);

 	// Habilito transmisión en pin TXD
 	Chip_UART_TXEnable(LPC_UART2);

 	/* Enable UART interrupt */
 	Chip_UART_IntEnable(LPC_UART2, (UART_IER_RBRINT | UART_IER_THREINT));

 	NVIC_EnableIRQ(UART2_IRQn);

}

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


