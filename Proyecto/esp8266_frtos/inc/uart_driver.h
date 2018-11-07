/*
 * serie.h
 *
 *  Created on: 28/06/2012
 *      Author: juan
 */

#ifndef SERIE_H_
#define SERIE_H_

#include "../inc/main.h"
#include "../inc/functions.h"

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

void esp8266ProcessConnection(char dato, int*id);
int esp8266GetStationIP(char *ip, char dato);
int esp8266JoinAccessPoint(char dato, espAnswer* response);
int esp8266DataSent(char dato);
espStatus_e procesarRedesDisponibles(char dato);
espStatus_e esp8266ValidateResponse(char* rsp);
espStatus_e esp8266Command(char* cmd);
void connectionToAccessPoint(espAnswer data);
int esp8266SuccessfulConnection(char dato);
void inicializarUART3 (void);


#endif /* SERIE_H_ */
