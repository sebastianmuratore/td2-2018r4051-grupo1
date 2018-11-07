#include "../../../tps/td2-2018r4051-grupo1/Proyecto/esp8266_frtos/inc/uart_driver.h"

#include "../../../modules/lpc1769/ciaa/inc/ciaaIO.h"
#include "../../../modules/lpc1769/ciaa/inc/ciaaUART.h"
#include "../../../modules/lpc1769/ciaa/inc/ciaaTick.h"
#include "queue.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../../tps/td2-2018r4051-grupo1/Proyecto/esp8266_frtos/inc/main.h"
#include "../../PWMyTFT/inc/FreeRTOS.h"



extern xQueueHandle colarx;
extern xQueueHandle colatx;
extern espNetworks nets[15];

extern unsigned char inicializado;
extern unsigned char revisaInic;

/*uint8_t rxbuf[UART_BUF_SIZE];
uint8_t txbuf[UART_BUF_SIZE];

RINGBUFF_T rrb;
RINGBUFF_T trb;

uartData_t uart = {LPC_UART3, &(rrb), &(trb)};*/

#define _GNU_SOURCE

#define BUF_LEN 1024
#define TIMEOUT 100


 void inicializarUART3 (void)
{

 	Chip_IOCON_PinMuxSet(LPC_IOCON,0,0,FUNC2); //TXD3
 	Chip_IOCON_PinMuxSet(LPC_IOCON,0,1,FUNC2); //RXD3

	Chip_UART_Init(LPC_UART3);
 	Chip_UART_SetBaud(LPC_UART3, 9600);

 	Chip_UART_ConfigData(LPC_UART3, UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS);
 	//Configuracion de UART con: 8 bits de dato, 1 bit de stop, sin bit de paridad

 	// Cargo los parámetros en la estructura para la FIFO.
 	// Por default: FIFO_DMAMode = DISABLE, FIFO_Level=UART_FIFO_TRGLEV0
 	// FIFO_ResetRxBuf=ENABLE, FIFO_ResetTxBuf=ENABLE, FIFO_State=ENABLE
 	Chip_UART_SetupFIFOS(LPC_UART3, UART_FCR_FIFO_EN | UART_FCR_RX_RS |
 			UART_FCR_TX_RS | UART_FCR_TRG_LEV3);

 	/* dummy read */
 	Chip_UART_ReadByte(LPC_UART3);

 	// Habilito transmisión en pin TXD
 	Chip_UART_TXEnable(LPC_UART3);
 	//Chip_UART_TXDisable(LPC_UART3);

 	//LPC_UART3->IER = IER_RBR;		/* Enable UART3 interrupt */
 	Chip_UART_IntEnable(LPC_UART3,(UART_IER_RBRINT | UART_IER_THREINT));

 	NVIC_EnableIRQ(UART3_IRQn);
 	//NVIC_SetPriority(UART3_IRQn,8);

 	inicializado = 1;

 }

/* void inicializarUART3BIS (void)
 {

  	Chip_IOCON_PinMuxSet(LPC_IOCON,0,0,FUNC2); //TXD3
  	Chip_IOCON_PinMuxSet(LPC_IOCON,0,1,FUNC2); //RXD3

 	Chip_UART_Init(LPC_UART3);
  	Chip_UART_SetBaud(LPC_UART3, 9600);

  	Chip_UART_ConfigData(LPC_UART3, UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS);
  	//Configuracion de UART con: 8 bits de dato, 1 bit de stop, sin bit de paridad

  	// Cargo los parámetros en la estructura para la FIFO.
  	// Por default: FIFO_DMAMode = DISABLE, FIFO_Level=UART_FIFO_TRGLEV0
  	// FIFO_ResetRxBuf=ENABLE, FIFO_ResetTxBuf=ENABLE, FIFO_State=ENABLE
  	Chip_UART_SetupFIFOS(LPC_UART3, UART_FCR_FIFO_EN | UART_FCR_RX_RS |
  			UART_FCR_TX_RS | UART_FCR_TRG_LEV0);

  	// Habilito transmisión en pin TXD
  	Chip_UART_TXEnable(LPC_UART3);

  	Chip_UART_IntEnable(LPC_UART3, UART_IER_RBRINT);
  	NVIC_EnableIRQ(UART3_IRQn);

  	RingBuffer_Init(uart.rrb, rxbuf, 1, UART_BUF_SIZE);
  	RingBuffer_Init(uart.trb, txbuf, 1, UART_BUF_SIZE);

  	inicializado = 1;

  }*/

 espCommand_e esp8266EvaluateCommand(char *cmd){

	 espCommand_e command = ESP8266_DEFAULT;

	 if(strcmp("RST", cmd) == 0)
		 command = ESP8266_RESET;
	 else if(strcmp("CWMODE_CUR", cmd) == 0)
		 command = ESP8266_MODE;
	 else if(strcmp("CWLAP", cmd) == 0)
		 command = ESP8266_NETWORKS;
	 else if(strcmp("CIFSR", cmd) == 0)
		 command = ESP8266_IP;

	 return command;

 }

 int esp8266GetIP(char *ip, char dato){

	 static int estado = ESP8266_IDLE;
	 static int j = 0;

	 switch(estado){

	 	 case ESP8266_IDLE:
	 		 if(dato == 'S')
	 			 estado = 1;
	 		 break;
	 	 case 1:
	 		 if(dato == 'T')
	 			 estado = 2;
	 		 else
	 			 estado = ESP8266_IDLE;
	 		 break;
	 	case 2:
	 		 if(dato == 'A')
	 			 estado = 3;
	 		 else
	 		 	 estado = ESP8266_IDLE;
	 		 break;
	 	case 3:
	 		 if(dato == 'I')
	 			 estado = 4;
	 		 else
	 			 estado = ESP8266_IDLE;
	 		 break;
	 	case 4:
	 		 if(dato == 'P')
	 			 estado = 5;
	 		 else
	 		 	 estado = ESP8266_IDLE;
	 		 break;
	 	case 5:
	 		 if(dato == ',')
	 			 estado = 6;
	 		 else
	 			 estado = ESP8266_IDLE;
	 		 break;
	 	case 6:
	 		if(dato == '"')
	 			estado = 7;
	 		else
	 			estado = ESP8266_IDLE;
	 		break;
	 	case 7:
	 		if(dato == '"'){
	 			estado = ESP8266_IDLE;
	 			j = 0;
	 			return 1;
	 		}
	 		else{
	 			ip[j++] = dato;
	 		}
	 		break;

	 }

	 return 0;

 }

 espCommand_e esp8266DetectCommand(char dato){

	 static int estado = ESP8266_IDLE;
	 espCommand_e cmd = ESP8266_DEFAULT;
	 static char command[15];
	 static int i = 0;

	 switch(estado){

	  	 case ESP8266_IDLE:
	  		 if(dato == '+'){
	  			 estado = ESP8266_INICIO_COMANDO;
	  			 for(i=0;i<15;i++){
	  				 command[i] = 0;
	  			 }
	  			 i = 0;
	  		 }
	  		 break;

	  	 case ESP8266_INICIO_COMANDO:
	 	 	 if(dato == '\r' || dato == '=' || dato == '?'){
	 	 		i = 0;
	 	 		estado = ESP8266_IDLE;
	 	 		cmd = esp8266EvaluateCommand(command);
	 	 		break;
	 	 	 }
	 	 	 command[i] = dato;
	 	 	 i++;
	 	 	 break;

	  	 default:
	  		 estado = ESP8266_IDLE;
	  		 break;

	 }

	 return cmd;

 }

  void esp8266SeparateResponse(char dato, char *rsp, char *command, espCommand_e *cmd, int len){

	 static int i = 0;
	 static int j = 0;
	 static int estado = ESP8266_IDLE;

	 j++;

	 switch(estado){

	 	 case ESP8266_IDLE:
	 		 i = 0;
	 		 if(dato == '+')
	 			 estado = ESP8266_INICIO_COMANDO;
	 		 break;

	 	 case ESP8266_INICIO_COMANDO:
	 		 if(dato == '\r'){
	 			*cmd = esp8266EvaluateCommand(command);
	 			i = 0;
	 			estado = ESP8266_WAIT_ANSWER;
	 			break;
	 		 }
	 		 (command[i]) = dato;
	 		 i++;
	 		 break;

	 	 case ESP8266_WAIT_ANSWER:
	 		 if(dato != '\n' && dato != '\r'){
	 			rsp[i] = dato;
	 			i++;
	 			estado = ESP8266_ANSWER;
	 		 }
	 		 break;

	 	 case ESP8266_ANSWER:
	 		 if(j >= len){
	 			estado = ESP8266_IDLE;
	 			j = 0;
	 		 }
	 		 else{
	 			rsp[i] = dato;
	 			i++;
	 		 }
	 		 break;

	 	 default:
	 		 estado = ESP8266_IDLE;
	 		 break;

	 }

 }

 espStatus_e esp8266ProcessResponse(char dato, espCommand_e cmd){

	 espStatus_e rv = ESP8266_NO_ANSWER;
	 static int i = 0;
	 static char rsp[BUF_LEN] = {0};

	 switch(cmd){

	 	 case ESP8266_RESET:
	 	 case ESP8266_MODE:
	 		 if(i < BUF_LEN)
	 			 rsp[i++] = dato;
	 		 else
	 			 i=0;

	 		rv = esp8266ValidateResponse(rsp);

	 		if(rv == ESP8266_OK)
	 			i = 0;

	 	 case ESP8266_IP:
	 		 break;

	 	 case ESP8266_NETWORKS:
	 		 rv = procesarRedesDisponibles(dato);
	 		 break;

	 }

	 return rv;

 }

 espStatus_e procesarRedesDisponibles(char dato){

	 static int estado = ESP8266_IDLE;
	 static int i = 0;
	 static int j = 0;
	 static int password = -1;
	 espStatus_e rv = ESP8266_TIMEOUT;

	 switch(estado){
	 	 case ESP8266_IDLE:
	 		 i = 0;
	 		 if(dato == '+')
	 			estado = 1;
	 		 break;
	 	 case 1:
	 		 if(dato == 'C')
	 			 estado = 2;
	 		 else
	 			 estado = ESP8266_IDLE;
	 		 break;
	 	case 2:
	 		 if(dato == 'W')
	 			 estado = 3;
	 		 else
	 			 estado = ESP8266_IDLE;
	 		 break;
	 	case 3:
	 		 if(dato == 'L')
	  			 estado = 4;
	  		 else
	  			 estado = ESP8266_IDLE;
	 		 break;
	 	case 4:
	 		 if(dato == 'A')
	 			 estado = 5;
	 		 else
	 			 estado = ESP8266_IDLE;
	  		 break;

	 	case 5:
	 		 if(dato == 'P')
	 		 	 estado = 6;
	 		 else
	 		 	 estado = ESP8266_IDLE;
	 		 break;
	 	case 6:
	 		 if(dato == ':')
	 		 	 estado = 7;
	 		 else
				 estado = ESP8266_IDLE;
	  		 break;
	 	case 7:
	 		 if(dato == '(')
	 		 	 estado = 8;
	 		 else
	 			 estado = ESP8266_IDLE;
	 		 break;
	 	case 8: //Con/Sin Contraseña
	 		nets[j].pass = dato;
	 		estado = 9;
	 		break;
	 	case 9:
	 		if(dato == ',')
	 			estado = 10;
	 		else{
	 			estado = ESP8266_IDLE;
	 			nets[j].pass = -1;
	 		}
	 		break;
	 	case 10:
	 		if(dato == '\"'){
	 			estado = 11;
	 			i = 0;
	 		}
	 		else{
	 			estado = ESP8266_IDLE;
	 			nets[j].pass = -1;
	 		}
	 		break;
	 	case 11: //Nombre de la red
	 		if(dato == '\"'){
	 			estado = ESP8266_IDLE;
	 			j++;
	 			i = 0;
	 		}
	 		else{
	 			nets[j].net[i] = dato;
	 			i++;
	 		}
	 		break;

	 }

	 return rv;

 }

 espStatus_e esp8266ValidateResponse(char* rsp){

	 espStatus_e rv = ESP8266_NO_ANSWER;

		 //The memmem() function finds the start of the first occurrence of the substring
	 //(2nd parameter) of length 'nlen' (3rd parameter) in the memory area (1st parameter)
	 if (strstr(rsp, "\r\nno change\r\n")) {
	 	 rv = ESP8266_NO_CHANGE;
	 }
	 else if (strstr(rsp, "\r\nready\r\n")) {
	   	 rv = ESP8266_READY;
	 }
	 else if (strstr(rsp, "\r\nOK\r\n")) {
	     rv = ESP8266_OK;
	 }
	 else if (strstr(rsp, "\r\nERROR\r\n")) {
	     rv = ESP8266_ERROR;
	 }
	 else if(strstr(rsp, "CONNECT")){
		 rv = ESP8266_DEVICE_CONNECTED;
	 }


	 return rv;

 }

 espStatus_e esp8266Command(char* cmd){

	 int i;
	 int len = strlen(cmd);

	 //Chip_UART_SendRB(uart.uart, uart.trb, cmd, len);

	 //Chip_UART_IntEnable(LPC_UART3, UART_IER_THREINT);
	 //Chip_UART_IntDisable(LPC_UART3, UART_IER_RBRINT);

	 //Chip_UART_IntEnable(LPC_UART3, UART_IER_RBRINT);
	 //NVIC_EnableIRQ(UART3_IRQn);

	 for(i=1;i<len;i++){
		xQueueSend(colatx, &(cmd[i]), portMAX_DELAY);

		//while(!(LPC_UART3->LSR & (1<<6))){}

		//LPC_UART3->THR = cmd[i];
	 }


	 LPC_UART3->THR = cmd[0];
	 //Chip_UART_Send(LPC_UART3, &(comando[0]), len);

 }

 espStatus_e esp8266Init(espMode_e m)
 {
     int rv;

     rv = esp8266Command("AT+RST\r\n");
     if (rv == ESP8266_OK) {
         rv = esp8266Command("");
         if (rv == ESP8266_READY) {
             char str[100];
             sprintf(str, "AT+CWMODE=%u\r\n", m);
             rv = esp8266Command(str);
         }
     }
     return rv;
 }

 espStatus_e esp8266ConnectToAP(char * ssid, char * pw)
 {
     char str[120];

     sprintf(str, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, pw);

     return esp8266Command(str);
 }

 espStatus_e esp8266StartUDP(char * url, uint16_t port, uint16_t localport)
 {
     char str[100];

     sprintf(str, "AT+CIPSTART=\"UDP\",\"%s\",%u,%u,2\r\n", url, port, localport);

     return esp8266Command(str);
 }

 int esp8266ProcessConnection(char dato, int*id){

	 static int estado = ESP8266_IDLE;
	 static char bytes[10] = {0};
	 static int i = 0;

	 switch(estado){

	 	 case ESP8266_IDLE:
	 		 if(dato == '+')
	 			 estado = 1;
	 		 break;
	 	 case 1:
	 		 if(dato == 'I')
	 			 estado = 2;
	 		 else
	 			 estado = ESP8266_IDLE;
	 		 break;
	 	case 2:
	 		 if(dato == 'P')
	 		 	estado = 3;
	 		 else
	 		 	estado = ESP8266_IDLE;
	 		 break;
	 	case 3:
	 		 if(dato == 'D')
	 		 	estado = 4;
	 		 else
	 		 	estado = ESP8266_IDLE;
	 		 break;
	 	case 4:
	 		 if(dato == ',')
	 			estado = 5;
	 		 else
	 			estado = ESP8266_IDLE;
	 		 break;
	 	case 5:
	 		*id = atoi(dato);
	 		estado = 6;
	 		break;
	 	case 6:
	 		if(dato == ',')
	 			estado = 7;
	 		else
	 			estado = ESP8266_IDLE;
	 		break;
	 	case 7:
	 		if(dato == ':'){
	 			estado = ESP8266_IDLE;
	 			i = 0;
	 			return atoi(bytes);
	 		}

	 		else
	 			bytes[i++] = dato;
	 		break;

	 }

	 return -1;
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

	 		for(i=0;i<14;i++)
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
	 				//Chip_UART_IntDisable(LPC_UART3, UART_IER_THREINT);
	 				//Chip_UART_IntEnable(LPC_UART3, UART_IER_RBRINT);
					break;
				}
	 		}

			break;


	}

	 portEND_SWITCHING_ISR(HigherPriorityTaskWoken);

 }
