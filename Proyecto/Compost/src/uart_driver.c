#include "main.h"

extern unsigned char inicializado;
extern unsigned char revisaInic;

extern xQueueHandle colarx;
extern xQueueHandle colatx;
extern xQueueHandle colaConexion;

#define _GNU_SOURCE
#define BUF_LEN 1024

void inicializarUART3 (void)
{

 	Chip_IOCON_PinMuxSet(LPC_IOCON,0,0,FUNC2); //TXD3
 	Chip_IOCON_PinMuxSet(LPC_IOCON,0,1,FUNC2); //RXD3

	Chip_UART_Init(LPC_UART3);
 	Chip_UART_SetBaud(LPC_UART3, 115200);

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
 	//Chip_UART_TXDisable(LPC_UART3);

 	//LPC_UART3->IER = IER_RBR;		/* Enable UART3 interrupt */
 	Chip_UART_IntEnable(LPC_UART3,(UART_IER_RBRINT | UART_IER_THREINT));

 	NVIC_EnableIRQ(UART3_IRQn);
 	NVIC_SetPriority(UART3_IRQn,8);

 	inicializado = 1;

 }

 espStatus_e procesarRedesDisponibles(char dato){

	 static int estado = ESP8266_IDLE;
	 static int i = 0;
	 static int j = 0;
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
	 		//nets[j].pass = dato;
	 		estado = 9;
	 		break;
	 	case 9:
	 		if(dato == ',')
	 			estado = 10;
	 		else{
	 			estado = ESP8266_IDLE;
	 			//nets[j].pass = -1;
	 		}
	 		break;
	 	case 10:
	 		if(dato == '\"'){
	 			estado = 11;
	 			i = 0;
	 		}
	 		else{
	 			estado = ESP8266_IDLE;
	 			//nets[j].pass = -1;
	 		}
	 		break;
	 	case 11: //Nombre de la red
	 		if(dato == '\"'){
	 			estado = ESP8266_IDLE;
	 			j++;
	 			i = 0;
	 		}
	 		else{
	 			//nets[j].net[i] = dato;
	 			i++;
	 		}
	 		break;

	 }

	 return rv;

 }

 void connectionToAccessPoint(espAnswer data){

	 char sendCommand[100] = {0};

	 sprintf(sendCommand, "AT+CWJAP=\"%s\",\"%s\"\r\n", data.net, data.pass);
	 esp8266Command(sendCommand);

 }

 int esp8266GetStationIP(char *ip, char dato){

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
	 else if(strstr(rsp, "No AP\r\n")){
		 rv = ESP8266_NO_AP;
	 }
	 else if(strstr(rsp, "+CWJAP:")){
		 rv = ESP8266_AP;
	 }


	 return rv;

 }

 espStatus_e esp8266Command(char* cmd){

	 int i;
	 int len = strlen(cmd);

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

 int esp8266JoinAccessPoint(char dato, espAnswer *response){

	 static int estado = ESP8266_IDLE;
	 static int i = 0;
	 static int j = 0;

	 switch(estado){

		 case ESP8266_IDLE:
			 i = 0;
			 j = 0;
			 if(dato == 'G')
				 estado = 1;
			 break;
		 case 1:
			 if(dato == 'E')
				 estado = 2;
			 else
				 estado = ESP8266_IDLE;
			 break;
		case 2:
			 if(dato == 'T')
				estado = 3;
			 else
				estado = ESP8266_IDLE;
			 break;
		case 3:
			 if(dato == ' ')
				estado = 4;
			 else
				estado = ESP8266_IDLE;
			 break;
		 case 4:
			 if(dato == '/')
				 estado = 5;
			 else
				 estado = ESP8266_IDLE;
			 break;
		 case 5:
			 if(dato == '?' || dato == ' ')
				estado = 6;
			 else if(dato == 'f'){
				 //favicon
				estado = ESP8266_IDLE;
				return 0;
			 }
			 break;
		case 6:
			 if(dato == 'n')
				estado = 7;
			 else if(dato == 'H'){
				 estado = ESP8266_IDLE;
				 return 1;
			 }
			 else
				estado = ESP8266_IDLE;
			 break;
		 case 7:
			 if(dato == 'e')
				 estado = 8;
			 else
				 estado = ESP8266_IDLE;
			 break;
		case 8:
			 if(dato == 't')
				estado = 9;
			 else
				estado = ESP8266_IDLE;
			 break;
		case 9:
			 if(dato == '=')
				estado = 10;
			 else
				estado = ESP8266_IDLE;
			 break;
		case 10:
			 if(dato == '&'){
				response->netLen = i;
				estado = 11;
			 }
			 else{
				response->net[i] = dato;
				i++;
			 }
			 break;
		case 11:
			if(dato == 'p')
				estado = 12;
			else
				estado = ESP8266_IDLE;
			break;
		 case 12:
			 if(dato == 'a')
				 estado = 13;
			 else
				 estado = ESP8266_IDLE;
			 break;
		case 13:
			 if(dato == 's')
				estado = 14;
			 else
				estado = ESP8266_IDLE;
			 break;
		case 14:
			 if(dato == 's')
				estado = 15;
			 else
				estado = ESP8266_IDLE;
			 break;
		case 15:
			 if(dato == '=')
				estado = 16;
			 else
				estado = ESP8266_IDLE;
			 break;
		case 16:
			 if(dato == ' '){
				 response->passLen = j;
				 estado = ESP8266_IDLE;
				 return 2;
			 }
			 else{
				response->pass[j] = dato;
				j++;
			 }
			 break;

	 }

	 return -1;

 }

 int esp8266SuccessfulConnection(char dato){

	 static int estado = ESP8266_IDLE;

	 switch(estado){

		 case ESP8266_IDLE:
			 if(dato == 'W')
				 estado = 1;
			 break;
		 case 1:
			 if(dato == 'I')
				 estado = 2;
			 else
				 estado = ESP8266_IDLE;
			 break;
		 case 2:
			 if(dato == 'F')
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
			 if(dato == ' ')
				 estado = 5;
			else
				 estado = ESP8266_IDLE;
			break;
		 case 5:
			 if(dato == 'G')
				 estado = 6;
			 else
				 estado = ESP8266_IDLE;
			 break;
		 case 6:
			 if(dato == 'O')
				 estado = 7;
			 else
				 estado = ESP8266_IDLE;
			 break;
		 case 7:
			 if(dato == 'T')
				 estado = 8;
			else
				 estado = ESP8266_IDLE;
			break;
		 case 8:
			 if(dato == ' ')
				 estado = 9;
			else
				 estado = ESP8266_IDLE;
			break;
		 case 9:
			 if(dato == 'I')
				 estado = 10;
			else
				 estado = ESP8266_IDLE;
			break;
		 case 10:
			 if(dato == 'P')
				 estado = 11;
			 else
				 estado = ESP8266_IDLE;
			 break;
		 case 11:
			 if(dato == '\r')
				 estado = 12;
			 else
				 estado = ESP8266_IDLE;
			 break;
		 case 12:
			 if(dato == '\n')
				 estado = 13;
			 else
				 estado = ESP8266_IDLE;
			 break;
		 case 13:
			 if(dato == '\r')
				 estado = 14;
			 else
				 estado = ESP8266_IDLE;
			 break;
		 case 14:
			 if(dato == '\n')
				 estado = 15;
			 else
				 estado = ESP8266_IDLE;
			 break;
  		 case 15:
			 if(dato == 'O')
				 estado = 16;
			 else
				 estado = ESP8266_IDLE;
			 break;
		 case 16:
			 if(dato == 'K')
				 estado = 17;
			 else
				 estado = ESP8266_IDLE;
			 break;
		 case 17:
			 if(dato == '\r')
				 estado = 18;
			 else
				 estado = ESP8266_IDLE;
			 break;
		 case 18:
			 if(dato == '\n'){
				 estado = ESP8266_IDLE;
				 return 1;
			 }
			 break;

	 }

	 return -1;
 }

 int esp8266DataSent(char dato){

	 static int estado = ESP8266_IDLE;

	 switch(estado){

	 	 case ESP8266_IDLE:
	 		 if(dato == 'S')
	 			 estado = 1;
	 		 break;
	 	 case 1:
	 		 if(dato == 'E')
	 			 estado = 2;
	 		 else
	 			 estado = ESP8266_IDLE;
	 		 break;
	 	 case 2:
	 		 if(dato == 'N')
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
	 		 if(dato == ' ')
	 			 estado = 5;
	 		else
				 estado = ESP8266_IDLE;
			break;
	 	 case 5:
	 		 if(dato == 'O')
	 			 estado = 6;
	 		 else
	 			 estado = ESP8266_IDLE;
	 		 break;
	 	 case 6:
	 		 if(dato == 'K'){
	 			 estado = ESP8266_IDLE;
	 			 return 1;
	 		 }
	 		 break;

	 }

	 return -1;

 }

 void esp8266ProcessConnection(char dato, int*id){

	 static int estado = ESP8266_IDLE;

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
	 		estado = ESP8266_IDLE;
	 		break;
	 }

	 return;
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
	 		for(i=0;i<8;i++)
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
	 				//Chip_UART_IntDisable(LPC_UART3, UART_IER_THREINT);
	 				//Chip_UART_IntEnable(LPC_UART3, UART_IER_RBRINT);
					break;
				}
	 		}

			break;


	}

	 portEND_SWITCHING_ISR(HigherPriorityTaskWoken);

 }
