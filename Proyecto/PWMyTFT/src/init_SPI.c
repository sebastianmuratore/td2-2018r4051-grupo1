/*
 * init_SPI.c
 *
 *  Created on: 6 de set. de 2018
 *      Author: sebas
 */
#include "../../PWMyTFT/inc/tft.h"

/*

void init_SPI(void)
{

	init_PinesSPI();

	 SPI initialization
	Chip_SPI_Init(LPC_SPI);
	spi_format.bits = SPI_BITS_8;
	spi_format.clockMode = SPI_CLOCK_MODE0;
	spi_format.dataOrder = SPI_DATA_MSB_FIRST;
	Chip_SPI_SetFormat(LPC_SPI, &spi_format);

	spi_xf.fnBefFrame = NULL;
	spi_xf.fnAftFrame = NULL;
	spi_xf.fnBefTransfer = SPI_Conectar;
	spi_xf.fnAftTransfer = SPI_Desconectar;
	Chip_SPI_SetMode(LPC_SPI, SPI_MODE_MASTER);


}

void	init_PinesSPI(	void	)
{

	int i=0;

	Extraido desde board.c void Board_SPI_Init(bool isMaster)

	Chip_IOCON_PinMux(LPC_IOCON, PIN_SCK, IOCON_MODE_PULLDOWN, IOCON_FUNC_SPI);
	Chip_IOCON_PinMux(LPC_IOCON,PIN_SSEL, IOCON_MODE_PULLUP, FUNC_0	);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PIN_SSEL, true);
	Chip_GPIO_WritePortBit(LPC_GPIO, PIN_SSEL, true);
	Chip_IOCON_PinMux(LPC_IOCON,PIN_MISO, IOCON_MODE_INACT, IOCON_FUNC_SPI);
	Chip_IOCON_PinMux(LPC_IOCON, PIN_MOSI, IOCON_MODE_INACT, IOCON_FUNC_SPI);

	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_DCX,FUNC_GPIO);
	Chip_GPIO_SetDir(LPC_GPIO,PIN_DCX,OUTPUT);


}

void SPI_Conectar(void) {
	Chip_GPIO_WritePortBit(LPC_GPIO, PIN_SSEL, LOW);
}

void SPI_Desconectar(void) {
	Chip_GPIO_WritePortBit(LPC_GPIO, PIN_SSEL, HIGH);
}

*/
void init_pinesLCD	(void)
{

	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_D0,FUNC_GPIO);
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_D1,FUNC_GPIO);
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_D2,FUNC_GPIO);
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_D3,FUNC_GPIO);
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_D4,FUNC_GPIO);
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_D5,FUNC_GPIO);
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_D6,FUNC_GPIO);
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_D7,FUNC_GPIO);
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_WRX,FUNC_GPIO);
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_RDX,FUNC_GPIO);
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_CSX,FUNC_GPIO);
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_DCX,FUNC_GPIO);
	Chip_IOCON_PinMuxSet(LPC_IOCON,PIN_RST,FUNC_GPIO);

	Chip_GPIO_SetPinDIROutput(LPC_GPIO,PIN_DCX);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,PIN_RDX);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,PIN_WRX);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,PIN_CSX);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,PIN_RST);

	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_RST);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_CSX);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_WRX);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_RDX);
	enableWritePines();


}

void enableReadPines	(	void	)
{

	Chip_GPIO_SetPinDIRInput(LPC_GPIO,PIN_D0);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,PIN_D1);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,PIN_D2);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,PIN_D3);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,PIN_D4);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,PIN_D5);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,PIN_D6);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,PIN_D7);

}

void enableWritePines	(	void	)
{
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,PIN_D0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,PIN_D1);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,PIN_D2);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,PIN_D3);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,PIN_D4);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,PIN_D5);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,PIN_D6);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,PIN_D7);
}

