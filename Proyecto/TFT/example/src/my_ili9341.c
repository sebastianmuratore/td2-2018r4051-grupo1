
#include "tft.h"

uint32_t color;

char orientacion = LANDSCAPE;

void ili9341_Init(void)
{
	color = 0;

	LCD_Reset();
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
		TIMER_delay_ms(120);

	ili9341_WriteReg(LCD_DISPLAY_ON,1);    //Display on
	ili9341_WriteReg(LCD_GRAM,1);

	setColor(255, 255, 255);
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
  ili9341_WriteReg(LCD_DISPLAY_ON,READ);
}

/**
  * @brief  Disables the Display.
  * @param  None
  * @retval None
  */
void ili9341_DisplayOff(void)
{
  /* Display Off */
  ili9341_WriteReg(LCD_DISPLAY_OFF,READ);
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



/**
  * @brief  Get LCD PIXEL WIDTH.
  * @param  None
  * @retval LCD PIXEL WIDTH.
  */
uint16_t ili9341_GetLcdPixelWidth(void)
{
  /* Return LCD PIXEL WIDTH */
  return ILI9341_LCD_PIXEL_WIDTH;
}

/**
  * @brief  Get LCD PIXEL HEIGHT.
  * @param  None
  * @retval LCD PIXEL HEIGHT.
  */
uint16_t ili9341_GetLcdPixelHeight(void)
{
  /* Return LCD PIXEL HEIGHT */
  return ILI9341_LCD_PIXEL_HEIGHT;
}

/**
  * @}
  */

void setColor(uint8_t r, uint8_t g, uint8_t b)
{

	 //color =((g&28)<<3|b>>3)| ((r&248)|g>>5)<<8; // <-- RGB
	uint16_t rr,gg,bb;
	rr = (r&248)<<8;
	gg = ((g&252)<<3);
	bb = (b>>3);

	color = rr | gg | bb ; // <-- En datos serie se manda 5b R + 5b G + 6b B
}

/**
  * @}
  */

void fillRect(int x1, int y1, int x2, int y2)
{
	//Llena todo el rectangulo del mismo color

	if (x1>x2)
	{
		swap(int, x1, x2); // int t = x1; x1 = x2; x2 = t; Intercambia los limites (para que queden ordenados, x1 < x2
	}
	if (y1>y2)
	{
		swap(int, y1, y2); // Intercambia los limites para que queden ordenados y1<y2
	}

	setXY(x1, y1, x2, y2); //Se setean los limites entre los cuales se va a dibujar
	_fast_fill_16(color, (((x2-x1)+1)*((y2-y1)+1))); //llena todo el rectangulo de el mismo color
}

/**
  * @}
  */
void clrScr()
{
	clrXY();

	_fast_fill_16(0,((ILI9341_LCD_PIXEL_WIDTH+1)*(ILI9341_LCD_PIXEL_HEIGHT+1)));
}

/**
  * @}
  */

void clrXY()
{
	if (orientacion==PORTRAIT)
		setXY(0,0,ILI9341_LCD_PIXEL_HEIGHT,ILI9341_LCD_PIXEL_WIDTH);
	else
		setXY(0,0,ILI9341_LCD_PIXEL_WIDTH,ILI9341_LCD_PIXEL_HEIGHT);

}

/**
  * @}
  */

void setXY(int x1, int y1, int x2, int y2)
{
	if (orientacion==LANDSCAPE )
	{
		swap(int, x1, y1);
		swap(int, x2, y2);
		y1=ILI9341_LCD_PIXEL_HEIGHT-y1;
		y2=ILI9341_LCD_PIXEL_HEIGHT-y2;
		swap(int, y1, y2);
	}

	ili9341_WriteReg(LCD_COLUMN_ADDR,TRUE); //Registro que define las columnas entre las cuales dibuja
	ili9341_WriteData(x1>>8); // Se envia la parte mas significativa de la columna inicial
	ili9341_WriteData(x1); // Se envia la parte mas significativa de la columna inicial
	ili9341_WriteData(x2>>8); // Parte menos significativa de la columna  final
	ili9341_WriteData(x2); // Parte mas significativa de la columna final
	ili9341_WriteReg(LCD_PAGE_ADDR,TRUE); // Lo mismo pero con las filas
	ili9341_WriteData(y1>>8);
	ili9341_WriteData(y1);
	ili9341_WriteData(y2>>8);
	ili9341_WriteData(y2);
}
/**
  * @}
  */

void _fast_fill_16(uint16_t dato, int pix)
{
	//pix es la cantidad de pixeles que tengo que refrescar

	int i,c;


	ili9341_WriteCommand(LCD_GRAM);

	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_CSX);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_DCX);
	//Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_RDX);
	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_WRX);

	for (i=0; i<pix; i++)
	{



		for(c=0;c<2;c++)
		{

			Chip_GPIO_SetPinState(LPC_GPIO,PIN_D0,( color >> ( 0 + c*8 )) & 0x01);
			Chip_GPIO_SetPinState(LPC_GPIO,PIN_D1,( color >> ( 1 + c*8 )) & 0x01);
			Chip_GPIO_SetPinState(LPC_GPIO,PIN_D2,( color >> ( 2 + c*8 )) & 0x01);
			Chip_GPIO_SetPinState(LPC_GPIO,PIN_D3,( color >> ( 3 + c*8 )) & 0x01);
			Chip_GPIO_SetPinState(LPC_GPIO,PIN_D4,( color >> ( 4 + c*8 )) & 0x01);
			Chip_GPIO_SetPinState(LPC_GPIO,PIN_D5,( color >> ( 5 + c*8 )) & 0x01);
			Chip_GPIO_SetPinState(LPC_GPIO,PIN_D6,( color >> ( 6 + c*8 )) & 0x01);
			Chip_GPIO_SetPinState(LPC_GPIO,PIN_D7,( color >> ( 7 + c*8 )) & 0x01);

			Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_WRX);
			Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_WRX);
		}
	}

	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_CSX);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_WRX);

}


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
	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_CSX);
	//Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_RDX);
	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_WRX);

	if(command) Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_DCX);
	else 		Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_DCX);


	Chip_GPIO_SetPinState(LPC_GPIO,PIN_D0,( LCD_Reg >> 0 ) & 0x01);
	Chip_GPIO_SetPinState(LPC_GPIO,PIN_D1,( LCD_Reg >> 1 ) & 0x01);
	Chip_GPIO_SetPinState(LPC_GPIO,PIN_D2,( LCD_Reg >> 2 ) & 0x01);
	Chip_GPIO_SetPinState(LPC_GPIO,PIN_D3,( LCD_Reg >> 3 ) & 0x01);
	Chip_GPIO_SetPinState(LPC_GPIO,PIN_D4,( LCD_Reg >> 4 ) & 0x01);
	Chip_GPIO_SetPinState(LPC_GPIO,PIN_D5,( LCD_Reg >> 5 ) & 0x01);
	Chip_GPIO_SetPinState(LPC_GPIO,PIN_D6,( LCD_Reg >> 6 ) & 0x01);
	Chip_GPIO_SetPinState(LPC_GPIO,PIN_D7,( LCD_Reg >> 7 ) & 0x01);


	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_WRX);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_CSX);


}

#endif

void    ili9341_WriteCommand(uint8_t RegValue)
{
	ili9341_WriteReg(RegValue,TRUE);
}

void LCD_Reset(void) {
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_RST);
	TIMER_delay_ms(5);
	Chip_GPIO_SetPinOutLow(LPC_GPIO,PIN_RST);
	TIMER_delay_ms(15);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_RST);
	TIMER_delay_ms(15);

	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_CSX);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,PIN_WRX);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
