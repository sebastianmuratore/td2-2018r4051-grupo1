/*==================[inclusions]=============================================*/

#include "../../PWMyTFT/inc/main.h"

xSemaphoreHandle sServo;
xSemaphoreHandle sTFT;

//void vAccion (void *pvParameters)
//{
//	unsigned int EstadoDebounce = NO_OPRIMIDO;
//	portTickType xMeDesperte;
//
//	//Inicio de variables y recuperación de parámetros
//
//	xMeDesperte = xTaskGetTickCount();
//
//	while(1){
//	//debo verificar rebote
//	switch(EstadoDebounce){
//		case NO_OPRIMIDO:
//			vTaskDelayUntil(&xMeDesperte,SCAN_RATE_ms/portTICK_RATE_MS);
//			if(!Chip_GPIO_GetPinState(LPC_GPIO,SW_ARRIBA))	//Si retorna una opresión
//				EstadoDebounce = DEBOUNCE;		//Indico que esta corriendo el tiempo Debounce
//			break;
//
//		case DEBOUNCE:
//			vTaskDelay(TIEMPO_DE_DEBOUNCE_ms/portTICK_RATE_MS);
//			EstadoDebounce = VALIDAR;
//			break;
//
//		case VALIDAR:
//			if(!Chip_GPIO_GetPinState(LPC_GPIO,SW_ARRIBA))			//Si retorna algo sigue presionado
//			{
//				EstadoDebounce=OPRIMIDO;
//			}
//			else							// fue error
//				EstadoDebounce=NO_OPRIMIDO;
//			break;
//
//		case OPRIMIDO:
//			if(Chip_GPIO_GetPinState(LPC_GPIO,SW_ARRIBA)) //No envio mensaje hasta no soltar
//			{
//				xSemaphoreGive(sServo);
//				EstadoDebounce = NO_OPRIMIDO;
//			}
//			break;
//		default:  break;
//		}
//	}
//}
//static void vServoWrite(void * a)
//{
//	static int giro = 1;
//	float duty;
//
//	while (1)
//	{
//		xSemaphoreTake(sServo,portMAX_DELAY);
//
//		if(giro)
//		{
//			duty = MS(0.6);
//			giro = 0;
//		}
//
//		else
//		{
//			duty = MS(2.4);
//			giro = 1;
//		}
//
//		Chip_TIMER_SetMatch(LPC_TIMER1, 1, duty);
//		Chip_TIMER_Reset(LPC_TIMER1);
//		Chip_TIMER_ClearMatch(LPC_TIMER1, 1);
//		Chip_TIMER_ClearMatch(LPC_TIMER1, 0);
//
//
//
//	}
//
//}




static void vDrawMenues( void *a)
{
	  MENUES menu;
	  Rectangle screen;


	  xSemaphoreTake(sTFT,portMAX_DELAY);
	  initScreen(&screen);


	 while(1)
	 {

		 menu = PRESENTACION;
		 DrawScreen(menu,screen);

		 vTaskDelay(1000/portTICK_RATE_MS);

		 menu = PANTALLA_PPAL;
		 DrawScreen(menu,screen);

		 vTaskDelay(3000/portTICK_RATE_MS);



	 }



 }

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

int main(void)
{
	initHardware();

//	vSemaphoreCreateBinary(sServo);
	vSemaphoreCreateBinary(sTFT);
	xSemaphoreTake(sTFT,portMAX_DELAY);

	//xSemaphoreTake(sServo,portMAX_DELAY);

	//xTaskCreate(vServoWrite, (const char *)"vServoWrite", configMINIMAL_STACK_SIZE*2, 0, tskIDLE_PRIORITY+1, 0);

	//xTaskCreate(vAccion, (const char *)"vAccion", configMINIMAL_STACK_SIZE*2, 0, tskIDLE_PRIORITY+1, 0);

	//xTaskCreate(vTouch, (const char *)"vTouch", configMINIMAL_STACK_SIZE*2, 0, tskIDLE_PRIORITY+1, 0);

	xTaskCreate(vDrawMenues, (const signed char *)"vDrawMenues", configMINIMAL_STACK_SIZE*5, 0, tskIDLE_PRIORITY+1, 0);

	xTaskCreate(vInitLCD, (const signed char *)"InitLCD", configMINIMAL_STACK_SIZE*5, 0, tskIDLE_PRIORITY+3, 0);

	vTaskStartScheduler();

	while (1)
	{
	}
}

