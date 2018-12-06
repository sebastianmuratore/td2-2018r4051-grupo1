#include "../inc/main.h"
#include "Fonts.h"


extern uint32_t color;
extern int mode;
extern char ip[20];
extern xQueueHandle qDatos;
extern xSemaphoreHandle sMenu;
extern xSemaphoreHandle sInicio;
extern char codigoHTML[HTML_CODE_SIZE];
extern xTaskHandle vTemperaturaHandle;


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
	  portBASE_TYPE sem;
	  Datos datos;
	  int flag = 1;

	  xSemaphoreTake(sTFT,portMAX_DELAY);
	  initScreen(&screen);
	  menu = LOADING;
	  uint32_t background = Rectangle_getColor(screen);

	  char msg[100];

	 while(1)
	 {

		 switch(menu)
		 		{
		 			 case PRESENTACION:
		 				 color = background;
		 				 TFT_DrawRectangle(screen.x,screen.y,screen.w,screen.h,TRUE	);
		 				 TFT_DrawText(30,30,"PROYECTO\nTECNICAS DIGITALES II",arial_italic,TFT_getColor(BLANCO));
		 				 vTaskDelay(10000/portTICK_RATE_MS);
		 				 TFT_DrawText(30,100,"Grupo 3\nBruno, Galazan, Gomez, Muratore",arial_italic,TFT_getColor(BLANCO));
		 				 vTaskDelay(10000/portTICK_RATE_MS);
		 				 TFT_DrawRectangle(screen.x,screen.y,screen.w,screen.h,TRUE);
		 				 menu = CONEXION;
		 				 break;

		 			 case CONEXION:

		 				 switch(mode)
		 				 {
		 				 	 case ACCESS_POINT_MODE:
		 				 		 xSemaphoreTake(sMenu,portMAX_DELAY);
		 				 		 TFT_DrawRectangle(screen.x,screen.y,screen.w,screen.h,TRUE);
		 				 		 sprintf(msg,"Conectese a la red FaryLink\n\n"
		 				 				 "Abra el navegador e ingrese la direccion:\n\n%s:80",ip);
		 				 		 TFT_DrawText(30,30,msg,arial_bold,TFT_getColor(BLANCO));
		 				 		 xSemaphoreTake(sMenu,portMAX_DELAY);
		 				 		 break;

		 				 	 case STATION_MODE:
		 				 		xSemaphoreTake(sMenu,portMAX_DELAY);
		 				 		TFT_DrawRectangle(screen.x,screen.y,screen.w,screen.h,TRUE);
		 				 		sprintf(msg,"Ingrese la direccion:\n\n%s:80",ip);
		 				 		TFT_DrawText(30,30,msg,arial_bold,TFT_getColor(BLANCO));
		 				 		xSemaphoreTake(sMenu,portMAX_DELAY);
		 				 		vTaskResume(vTemperaturaHandle);
		 				 		menu = PANTALLA_PPAL;

								break;

		 				 	 case CONNECTION_OK:
		 				 		 TFT_DrawRectangle(screen.x,screen.y,screen.w,screen.h,TRUE);
		 				 		 sprintf(msg,"Conexion exitosa\n\nDirijase a la direccion:\n\n%s:80", ip);
		 				 		 TFT_DrawText(30,30,msg,arial_bold,TFT_getColor(BLANCO));
		 				 		 xSemaphoreTake(sMenu,portMAX_DELAY);
		 				 		 menu = PANTALLA_PPAL;
		 				 		 vTaskResume(vTemperaturaHandle);
		 				 		 break;

		 				 	 default:
		 				 		 break;
		 				 }

		 				 break;

		 			 case LOADING:
		 				 TFT_setColor(NEGRO);
		 				 TFT_DrawRectangle(PANTALLA_COMPLETA,TRUE);
		 				 TFT_DrawText(145,200,"Loading...",arial_bold,TFT_getColor(BLANCO));
		 				 sem = xSemaphoreTake(sInicio,CINCO_SEG);
		 				 if(sem == pdTRUE )
		 				 {
		 					menu = CONEXION;
		 					vTaskPrioritySet(NULL,tskIDLE_PRIORITY+2);
		 				 }
		 				 else
		 					menu =	MJE_ERROR;
		 				 break;



		 			 case PANTALLA_PPAL:

		 				 if(flag)
		 				 {
		 					 TFT_setColor(COLOR_MARGEN_SUPERIOR);
		 					 TFT_DrawRectangle(MARGEN_SUPERIOR,TRUE);
		 					 TFT_DrawText(10,RENGLON(0,32),"Datos Compost :\n 05/12/18",arial_italic,TFT_getColor(NEGRO));
		 					 TFT_setColor(COLOR_MARGEN_INFERIOR);
		 					 TFT_DrawRectangle(MARGEN_INFERIOR,TRUE);
		 					 flag = 0;
		 				 }
		 				 if(xQueueReceive(qDatos,&datos,portMAX_DELAY))
		 				 {
		 					 codigoHTML[364] = 48 + (int)((datos.temperatura >> 4)/10);
		 					 codigoHTML[365] = 48 + (int)((datos.temperatura >> 4) - ((int)codigoHTML[364]-48)*10);
		 					 codigoHTML[435] = 48 + (int)(datos.humedad/10);
		 					 codigoHTML[436] = 48 + (int)(datos.humedad - ((int)codigoHTML[435]-48)*10);

		 					 TFT_clearText(10,RENGLON(4,32),sizeof("Humedad: xx    "),arial_italic,color);
		 					 TFT_clearText(10,RENGLON(5,32),sizeof("Humedad: xx    "),arial_italic,color);
		 					 sprintf(msg,"Temperatura: %d C",datos.temperatura>>4);
		 					 TFT_DrawText(10,RENGLON(4,32),msg,arial_italic,TFT_getColor(BLANCO));
		 					 sprintf(msg,"Humedad: %d ",datos.humedad);
		 					 TFT_DrawText(10,RENGLON(5,32),msg,arial_italic,TFT_getColor(BLANCO));
		 					 vTaskDelay(DIEZ_SEG);
		 				 }
		 				 break;


		 			 case MJE_ERROR:
		 				 TFT_setColor(ROJO);
		 				 TFT_DrawRectangle(PANTALLA_COMPLETA,TRUE);
		 				 TFT_DrawText(0,0,"Error!\nReinicie el\n dispositivo",arial_bold,TFT_getColor(BLANCO));
		 				 menu = 10;

		 				 break;

		 		}





	 }



 }

