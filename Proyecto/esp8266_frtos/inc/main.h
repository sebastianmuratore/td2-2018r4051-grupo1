/* Copyright 2015, Pablo Ridolfi
 * All rights reserved.
 *
 * This file is part of lpc1769_template.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _MAIN_H_
#define _MAIN_H_

/** \addtogroup rtos_blink FreeRTOS blink example
 ** @{ */

/*==================[inclusions]=============================================*/

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

typedef enum
{
	ESP8266_NO_ANSWER			= -4,
    ESP8266_BUF_FULL    		= -3,
    ESP8266_TIMEOUT     		= -2,
    ESP8266_ERROR       		= -1,
    ESP8266_OK          		=  0,
    ESP8266_NO_CHANGE   		=  1,
    ESP8266_READY       	  	=  2,
	ESP8266_DEVICE_CONNECTED  	=  3
}espStatus_e;

typedef enum
{
	ESP8266_IDLE			= 0,
    ESP8266_INICIO_COMANDO  = 1,
    ESP8266_FIN_COMANDO     = 2,
    ESP8266_WAIT_ANSWER  	= 3,
    ESP8266_ANSWER   		= 4
}espMdeE;

typedef enum
{
    ESP8266_STATION     = 1,
    ESP8266_AP          = 2,
    ESP8266_AP_STATION  = 3
}espMode_e;

typedef enum
{
	ESP8266_DEFAULT		= 0,
	ESP8266_RESET		= 1,
    ESP8266_MODE		= 2,
	ESP8266_NETWORKS	= 3,
	ESP8266_IP			= 4
}espCommand_e;

typedef struct
{
	char pass;
	char net[100];
}espNetworks;

/*==================[external functions declaration]=========================*/

/** @brief main function
 * @return main function should never return
 */
int main(void);
void initHardware(void);
void inicializarPulsadores(void);

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _MAIN_H_ */
