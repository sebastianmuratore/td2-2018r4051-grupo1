/*
 * functions.h
 *
 *  Created on: 14 de oct. de 2018
 *      Author: Juan Bruno
 */

#ifndef TPS_TD2_2018R4051_GRUPO1_PROYECTO_ESP8266_FRTOS_INC_FUNCTIONS_H_
#define TPS_TD2_2018R4051_GRUPO1_PROYECTO_ESP8266_FRTOS_INC_FUNCTIONS_H_

#include "../inc/main.h"

/*==================[macros]=================================================*/
#define BUFFERSIZE			1220 //Tamaños de las colas
#define HTML_CODE_SIZE		465
#define HTML_FORM_SIZE		472
#define STATION_MODE		100
#define ACCESS_POINT_MODE	200
#define CONNECTION_OK		300

#define ESP8266_IDLE	 0

/*==================[typedef]================================================*/
typedef enum
{
	ESP8266_NO_ANSWER			= -4,
    ESP8266_BUF_FULL    		= -3,
    ESP8266_TIMEOUT     		= -2,
    ESP8266_ERROR       		= -1,
    ESP8266_OK          		=  0,
    ESP8266_NO_CHANGE   		=  1,
    ESP8266_READY       	  	=  2,
	ESP8266_DEVICE_CONNECTED  	=  3,
	ESP8266_NO_AP				=  4,
	ESP8266_AP	 				=  5
}espStatus_e;

typedef enum
{
	ESP8266_NOK				= 0,
	ESP8266_ACCESS_POINT	= 1,
    ESP8266_CONNECTED		= 2,
	ESP8266_RESPONSE		= 3,
	ESP8266_AP_CONNECTION	= 4,
	ESP8266_CLOSE			= 5
}espType_e;


typedef struct{
	char pass[40];
	int passLen;
	char net[50];
	int netLen;
	espType_e tipo;
	int id;
	char ip[40];
}espAnswer;



int main(void);
void initHardware(void);
void inicializarPulsadores(void);
void inicializarVector(int len, char* vector);
int esp8266SendCommand(char* comando);

#endif /* TPS_TD2_2018R4051_GRUPO1_PROYECTO_ESP8266_FRTOS_INC_FUNCTIONS_H_ */
