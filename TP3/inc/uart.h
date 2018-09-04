/*
 * uart.h
 *
 *  Created on: 3 de sept. de 2018
 *      Author: Juan Bruno
 */

#ifndef TPS_TD2_2018R4051_GRUPO1_TP3_INC_UART_H_
#define TPS_TD2_2018R4051_GRUPO1_TP3_INC_UART_H_

/** \addtogroup rtos_blink FreeRTOS blink example
 ** @{ */

/*==================[inclusions]=============================================*/
#include "board.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

	/*======================General======================*/
#define IER_RBR		0x01
#define IER_THRE	0x02
#define IER_RLS		0x04

#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80

#define BitsTX_5		((unsigned int)0)
#define BitsTX_6		((unsigned int)1)
#define BitsTX_7		((unsigned int)2)
#define BitsTX_8		((unsigned int)3)

#define BitsStop1		((unsigned int)0)
#define BitsStop2		((unsigned int)1<<2)

#define ParidadEn		((unsigned int)1<<3)
#define ParidadImpar	((unsigned int)0<<4)
#define ParidadPar		((unsigned int)1<<5)
#define ParidadForz1	((unsigned int)2<<5)
#define ParidadForz0	((unsigned int)3<<5)

#define BreakControl	((unsigned int)(1<<6))
#define DLAB			((unsigned int)(1<<7))

#define	FIFO_EN			1
#define RX_FIFO_RST		2
#define TX_FIFO_RST		4
#define UART_DMA		8
#define RX_TRIG_1		(0<<6)
#define RX_TRIG_4		(1<<6)
#define RX_TRIG_8		(2<<6)
#define RX_TRIG_14		(3<<6)

#define LPC_TX3		0,0,FUNC2
#define LPC_RX3		0,1,FUNC2
#define LPC_TX2		0,10,FUNC1
#define LPC_RX2		0,11,FUNC1

	/*======================TP3======================*/
#define TERMINAL_A	1 		//Terminal A
#define TERMINAL_B	2		//Terminal B

#define STX 			0xAA
#define ETX 			0x55
#define INICIO			0x01
#define ARRANQUE_MOTOR	0x05
#define FRENAR_MOTOR	0x80

#define VELOCIDAD_1		0x01
#define VELOCIDAD_5		0x05
#define VELOCIDAD_10	0x10
#define VELOCIDAD_20	0x20

#define OK				0xFF
#define NOK				0x00

#define SIN_ENERGIA				0x30
#define MOTOR_ACTIVO			0x40
#define VELOCIDAD_INCORRECTA	0x50
#define MANTENIMIENTO			0x60

/*==================[external functions declaration]=========================*/

/** @brief main function
 * @return main function should never return
 */
void inicializarUART2 (void);
void inicializarUART3 (void);

#endif /* TPS_TD2_2018R4051_GRUPO1_TP3_INC_UART_H_ */
