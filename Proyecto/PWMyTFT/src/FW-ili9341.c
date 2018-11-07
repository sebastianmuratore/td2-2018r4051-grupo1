
#include "../../PWMyTFT/inc/main.h"

uint32_t color;

char orientacion = LANDSCAPE;

void ili9341_Init(void)
{
	color = 0;

	ili9341_Reset();
	ili9341_WriteReg(LCD_POWERA,1);
	ili9341_WriteData(0x39);
	ili9341_WriteData(0x2C);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x34);
	ili9341_WriteData(0x02);

	ili9341_WriteReg(LCD_POWERB,1);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0X81);
	ili9341_WriteData(0X30);

	ili9341_WriteReg(LCD_DTCA,1);
	ili9341_WriteData(0x85);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x78);

	ili9341_WriteReg(LCD_DTCB,1);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x00);

	ili9341_WriteReg(LCD_POWER_SEQ,1);
	ili9341_WriteData(0x64);
	ili9341_WriteData(0x03);
	ili9341_WriteData(0X12);
	ili9341_WriteData(0X81);

	ili9341_WriteReg(LCD_PRC,1);
	ili9341_WriteData(0x20);

	ili9341_WriteReg(LCD_POWER1,1);    //Power control
	ili9341_WriteData(0x23);   //VRH[5:0]

	ili9341_WriteReg(LCD_POWER2,1);    //Power control
	ili9341_WriteData(0x10);   //SAP[2:0];BT[3:0]

	ili9341_WriteReg(LCD_VCOM1,1);    //VCM control
	ili9341_WriteData(0x3e);   //Contrast
	ili9341_WriteData(0x28);

	ili9341_WriteReg(LCD_VCOM2,1);    //VCM control2
	ili9341_WriteData(0x86);   //--

	ili9341_WriteReg(LCD_MAC,1);    // Memory Access Control
	ili9341_WriteData(0x48);

	ili9341_WriteReg(LCD_PIXEL_FORMAT,1);
	ili9341_WriteData(0x55);

	ili9341_WriteReg(LCD_FRMCTR1,1);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x18);

	ili9341_WriteReg(LCD_DFC,1);    // Display Function Control
	ili9341_WriteData(0x08);
	ili9341_WriteData(0x82);
	ili9341_WriteData(0x27);

	ili9341_WriteReg(LCD_SLEEP_OUT,1);//Exit Sleep
	vTaskDelay(120/portTICK_RATE_MS);

	ili9341_WriteReg(LCD_DISPLAY_ON,1);    //Display on
	ili9341_WriteReg(LCD_GRAM,1);

	TFT_setColor(255, 255, 255);
}

/**
  * @brief  Disables the Display.
  * @param  None
  * @retval LCD Register Value.
  */
uint16_t ili9341_ReadID(void)
{
 // LCD_IO_Init();
  return ((uint16_t)ili9341_ReadData(LCD_READ_ID4, LCD_READ_ID4_SIZE));
}

/**
  * @brief  Enables the Display.
  * @param  None
  * @retval None
  */
void ili9341_DisplayOn(void)
{
  /* Display On */
  ili9341_WriteCommand(LCD_DISPLAY_ON);
}

/**
  * @brief  Disables the Display.
  * @param  None
  * @retval None
  */
void ili9341_DisplayOff(void)
{
  /* Display Off */
  ili9341_WriteCommand(LCD_DISPLAY_OFF);
}


/**
  * @brief  Reads the selected LCD Register.
  * @param  RegValue: Address of the register to read
  * @param  ReadSize: Number of bytes to read
  * @retval LCD Register Value.
  */

#ifdef SPI_MODE

uint32_t ili9341_ReadData(uint8_t RegValue, uint8_t ReadSize)
{
	uint32_t readed;
	int i=0;

	spi_tx_buf[0] = RegValue;

	for(i=0;i<ReadSize;i++)
	{
		spi_rx_buf[i] = 0;
	}

	spi_xf.cnt = 0;
	spi_xf.length = ReadSize+1;
	spi_xf.pTxData = spi_tx_buf;
	spi_xf.pRxData = spi_rx_buf;

	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_DCX);
	Chip_SPI_RWFrames_Blocking(LPC_SPI, &spi_xf);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_DCX);
	readed = ( spi_rx_buf[0] >> 24  ) | (spi_rx_buf[1] >> 16 ) | (spi_rx_buf[2] >> 8 ) | (spi_rx_buf[3]);
	return readed;
}

#else

uint32_t ili9341_ReadData(uint8_t RegValue, uint8_t ReadSize)
{
	uint8_t i=0;
	uint32_t data=0;



	ili9341_WriteCommand(RegValue);
	enableReadPines();

	for(i=0;i<ReadSize;i++)
	{
		Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_CSX);
		Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_DCX);
		Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_WRX);

		Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_RDX);
		Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_RDX);

		data = data | Chip_GPIO_GetPinState(LPC_GPIO,PIN_D0) << ( 0 + 8*i );
		data = data | Chip_GPIO_GetPinState(LPC_GPIO,PIN_D1) << ( 1 + 8*i ) ;
		data = data | Chip_GPIO_GetPinState(LPC_GPIO,PIN_D2) << ( 2 + 8*i ) ;
		data = data | Chip_GPIO_GetPinState(LPC_GPIO,PIN_D3) << ( 3 + 8*i ) ;
		data = data | Chip_GPIO_GetPinState(LPC_GPIO,PIN_D4) << ( 4 + 8*i ) ;
		data = data | Chip_GPIO_GetPinState(LPC_GPIO,PIN_D5) << ( 5 + 8*i ) ;
		data = data | Chip_GPIO_GetPinState(LPC_GPIO,PIN_D6) << ( 6 + 8*i ) ;
		data = data | Chip_GPIO_GetPinState(LPC_GPIO,PIN_D7) << ( 7 + 8*i ) ;

	}

	enableWritePines();
	return data;

}

#endif



void 	ili9341_WriteData	(	uint8_t RegValue )
{

	ili9341_WriteReg(RegValue,FALSE);
}


#ifdef SPI_MODE

void 	ili9341_WriteReg		(	uint8_t LCD_Reg	, uint8_t command)
{
	spi_tx_buf[0] = LCD_Reg;
	spi_xf.cnt = 0;
	spi_xf.length = 1;
	spi_xf.pTxData = spi_tx_buf;
	spi_xf.pRxData = spi_rx_buf;


	if(command)	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_DCX);
	else		Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_DCX);

 	Chip_SPI_RWFrames_Blocking(LPC_SPI, &spi_xf);

 	Chip_GPIO_SetPinToggle(LPC_GPIO,PIN_DCX);
}

#else
#define PARALELL_MODE

void 	ili9341_WriteReg		(	uint8_t LCD_Reg	, uint8_t command)
{



	if(command==1)	ili9341_enableCommandWrite();
	else 			ili9341_enableDataWrite();


	ili9341_cargarDato(LCD_Reg);
	ili9341_disableWrite();


}

#endif

void    ili9341_WriteCommand(uint8_t RegValue)
{
	ili9341_WriteReg(RegValue,TRUE);
}

void ili9341_Reset(void) {
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_RST);
	vTaskDelay(5/portTICK_RATE_MS);

	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_RST);
	vTaskDelay(15/portTICK_RATE_MS);

	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_RST);
	vTaskDelay(15/portTICK_RATE_MS);

	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_CSX);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_WRX);
}


void ili9341_cargarDato		(uint8_t dato)
{
	Chip_GPIO_SetPinState(LPC_GPIO,PIN_D0,( dato >> 0 ) & 0x01);
	Chip_GPIO_SetPinState(LPC_GPIO,PIN_D1,( dato >> 1 ) & 0x01);
	Chip_GPIO_SetPinState(LPC_GPIO,PIN_D2,( dato >> 2 ) & 0x01);
	Chip_GPIO_SetPinState(LPC_GPIO,PIN_D3,( dato >> 3 ) & 0x01);
	Chip_GPIO_SetPinState(LPC_GPIO,PIN_D4,( dato >> 4 ) & 0x01);
	Chip_GPIO_SetPinState(LPC_GPIO,PIN_D5,( dato >> 5 ) & 0x01);
	Chip_GPIO_SetPinState(LPC_GPIO,PIN_D6,( dato >> 6 ) & 0x01);
	Chip_GPIO_SetPinState(LPC_GPIO,PIN_D7,( dato >> 7 ) & 0x01);

}
void ili9341_disableWrite(	void	)
{
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_WRX);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_CSX);

}

void ili9341_enableCommandWrite(	void	)
{
	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_CSX);
	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_WRX);
	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_DCX);
}
void ili9341_enableDataWrite(	void	)
{
	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_CSX);
	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_WRX);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_DCX);
}

void ili9341_write(void)
{
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_WRX);
	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_WRX);

}
