/*
 * @brief SPI example
 * This example show how to use the SPI in 2 modes : Polling and Interrupt.
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "tft.h"
#include "Fonts.h"
/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

uint8_t spi_tx_buf[BUFFER_SIZE];
uint8_t spi_rx_buf[BUFFER_SIZE];
SPI_CONFIG_FORMAT_T spi_format;
SPI_DATA_SETUP_T spi_xf;
uint8_t  spi_xfer_completed = 0;

int main(void)
{
	SystemCoreClockUpdate();
	Board_Init();
	uint32_t data;

	Chip_SystemInit();

	//init_SPI();
	init_pinesLCD();
	ili9341_Init();
<<<<<<< HEAD:Proyecto/TFT/example/src/tft.c
	TFT_setColor(255,255,0);
	TFT_fillRect(0,0,220,300);

	TFT_DrawRectangle(0,0,250,200,FALSE);
	TFT_setColor(255,255,255);
	TFT_DrawTextAllFontsV2(50,50,"Estocasticos",arial_italic);
	TFT_setColor(255,0,0);
=======


	//ili9341_WriteCommand(LCD_SWRESET);
	data = ili9341_ReadData( LCD_RDDCOLMOD   ,2);
	ili9341_WriteCommand(LCD_DINVON );

	setColor(0,0,255);
	fillRect(0,0,40,40);

>>>>>>> b7cb94a6f629c8ab2dac3b471bedce9836c0ee3f:Proyecto/TFT/example/src/spi.c
	while (1)
	{

	}
	return 0;
}
