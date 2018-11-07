#include "../inc/main.h"


void vInitLCD	(void* ptr)
{
	while(1)
	{
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

		xSemaphoreGive(sTFT);

		vTaskSuspend(NULL);
	}
}

void vDrawMenues( void *a)
{
	  MENUES menu;
	  Rectangle screen;


	  xSemaphoreTake(sTFT,portMAX_DELAY);
	  initScreen(&screen);


	 while(1)
	 {

		 menu = PRESENTACION;
		 DrawScreen(menu,screen);

		 vTaskDelay(50000/portTICK_RATE_MS);

		 menu = PANTALLA_PPAL;
		 DrawScreen(menu,screen);

		 vTaskDelay(50000/portTICK_RATE_MS);



	 }



 }

