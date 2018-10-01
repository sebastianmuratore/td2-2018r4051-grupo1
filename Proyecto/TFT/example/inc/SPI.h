/*
 * init_SPI.h
 *
 *  Created on: 6 de set. de 2018
 *      Author: sebas
 */

#ifndef TPS_TD2_2018R4051_GRUPO1_PROYECTO_TFT_EXAMPLE_INC_SPI_H_
#define TPS_TD2_2018R4051_GRUPO1_PROYECTO_TFT_EXAMPLE_INC_SPI_H_
#endif


#define 	BUFFER_SIZE                         (0x100)
#define 	SPI0

#define		PIN_SCK0	PIN_13
#define		PIN_SSEL0	PIN_14
#define		PIN_MISO0	PIN_12
#define		PIN_MOSI0	PIN_11

#define		PIN_SCK1	0,7
#define		PIN_SSEL1	0,6
#define		PIN_MISO1	0,8
#define		PIN_MOSI1	0,9

#ifdef 		SPI0

#define		PIN_SCK		PIN_SCK0
#define		PIN_SSEL	PIN_SSEL0
#define		PIN_MISO	PIN_MISO0
#define		PIN_MOSI	PIN_MOSI0

#ifdef		SPI1
#define		PIN_SCK		PIN_SCK1
#define		PIN_SSEL	PIN_SSEL1
#define		PIN_MISO	PIN_MISO1
#define		PIN_MOSI	PIN_MOSI1

#endif


/*-------------------------------------------------------------------------------------------------------------------------------------------------
 * 					COMANDOS
 -------------------------------------------------------------------------------------------------------------------------------------------------*/




void 	init_SPI 	 (	void	);
void	init_PinesSPI(	void	);
void 	SPI_Conectar (	void	);
void 	SPI_Desconectar (	void	);
void	enableWritePines	(void);
void 	enableReadPines		(void);
void 	init_pinesLCD		(void);

#endif /* TPS_TD2_2018R4051_GRUPO1_PROYECTO_TFT_EXAMPLE_INC_SPI_H_ */
