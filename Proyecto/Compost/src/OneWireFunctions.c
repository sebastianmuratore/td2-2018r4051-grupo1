/*
 * OneWireFunctions.c
 *
 *  Created on: 1 de set. de 2018
 *      Author: jonat
 */

#include "../inc/main.h"

#define INIT_SUCCESS 0
#define INIT_FAILED 1
#define HIGH 1
#define LOW 0

volatile uint32_t * DWT_CTRL = (uint32_t *)0xE0001000;
static volatile uint32_t * DWT_CYCCNT = (uint32_t *)0xE0001004;

void pauseus(uint32_t t)
{
   *DWT_CTRL |= 1;
	*DWT_CYCCNT = 0;
	t *= (SystemCoreClock/1000000);
	while(*DWT_CYCCNT < t);
}

//La secuencia para utilizar el dispositivo OneWire es la siguiente:
//1- Inicialización de la transacción
//2- Envío de comando ROM
//3- Envío de comando Function

//owInitTransaction: El maestro envía un pulso de reset, y el esclavo responde con otro pulso de "presencia"
//						indicando que está listo para operar.

int owInitTransaction (void)
{
	pauseus(1000);
	owSetOutput();	//Setea pin en Output para enviar al esclavo
	owSetLow();	//Baja la línea mínimo 480us
	pauseus(480);
	owSetInput();	//Setea pin en Input para escuchar al esclavo
	pauseus(40);	//Delay de 50us		//Tiempo que demora en bajar la línea el esclavo

	//Se pone a leer la línea
	if (owReadPin() == HIGH)			//Si está alta, el esclavo no está respondiendo -> Error
		return INIT_FAILED;
	else
	{
		while ( owReadPin() == LOW );	//Mientras que el esclavo mantenga la línea baja, esperar (de 60 a 240us)
		return INIT_SUCCESS;			//Una vez que suelta la línea -> Exito
	}
}

void owSendCommand (uint8_t cmd, void * buffer, uint8_t nBytes )
{
	uint8_t j, i = 1;
	uint8_t * p = (uint8_t *)buffer;

	owSetOutput();	//Lo preparo para enviar

	do
	{
		if(cmd & i)			// Si tiene que generar un time slot para Write 1
		{
			owSetLow();		// Baja la linea
			pauseus(3);		//Delay 3uS		// Espera menos de 15 uS
			owSetHigh();		// La sube
			pauseus(60);	//Delay 60uS;	// Espera el mínimo de duración del time slot
		}
		else				// Si tiene que generar un time slot para Write 0
		{
			owSetLow();		// Baja la línea
			pauseus(60);	//Delay 60uS	// Espera el minimo de duración del time slot (60us)
			owSetHigh();		// Libera la línea
			pauseus(10);	//delay 10 us;	// Espera de recuperación entre time slots de escritura
		}

		if(i==0x80)		//128 -> 8 bits
		{
			break;
		}
		else
		{
			i <<= 1;	//Desplaza el 1 de i para ir barriendo todo el byte dado que es una operación bit a bit.
		}

	}while(i != 0);	// Nunca sale por esta condición, sino que sale por el break.



	//Lectura de datos recibidos

	for(i=0; i<nBytes; i++)	// Los n bytes
	{
		p[i] = 0;	//Inicio en 0 el vector
		for(j=0; j<8; j++)	//Para cada bit del byte
		{
			owSetOutput();	//Out
			owSetLow();	//Low
			pauseus(3);	//delay 3uS	//Wait
			owSetInput();		//In
			pauseus(12);	//Delay 12uS	//Wait
			p[i] >>= 1;	//Desplazo a la derecha
			if( owReadPin() )
				p[i] |= 0x80;		//Si lee un 1 pone un 1 en el bit más alto.
			pauseus(55);	//Delay 55uS	//Wait
		}
	}


}

int owReadTemperature(void)
{
	int rv = -1;
	uint8_t crc = 0;
	uint8_t p[9];

	if(owInitTransaction()==0)
	{
		pauseus(400);	//Delay 400uS

		__set_PRIMASK(1);

		owSendCommand(0x33, p, 8); /* READ ROM CMD */

		owSendCommand(0x44, p, 0); /* START CONVERSION */

		__set_PRIMASK(0);

		owSetInput();
		while(owReadPin() == false); /* wait for end of conv */

		owInitTransaction();

		pauseus(400);	//Delay 400us

		__set_PRIMASK(1);

		owSendCommand(0x33, p, 8); /* READ ROM CMD */

		owSendCommand(ReadScratch, p, 9); /* READ SCRATCH */

		__set_PRIMASK(0);

		crc = owCRC(p, 8);

		if(crc == p[8])
		{
			rv = p[1];
			rv <<= 8;
			rv |= p[0];
		}

	}
	return rv;
}

uint8_t owCRC(uint8_t code[], uint8_t n)
{
	uint8_t i, j, a, b, cy=0, crc=0;

	for(i=0; i<n; i++)
	{
		a = code[i];
		b = code[i];
		for(j=0; j<8; j++)
		{
			a ^= crc;
			cy = a&1;
			a = crc;
			if(cy)
				a ^= 0x18;

			if(cy)
			{
				cy = a&1;
				a >>= 1;
				a |= 0x80;	//128
			}
			else
			{
				cy = a&1;
				a >>= 1;
			}
			crc = a;

			if(b&1)
			{
				b >>= 1;
				b |= 0x80;
			}
			else
			{
				b >>= 1;
			}
			a = b;
		}
	}
	return crc;
}



