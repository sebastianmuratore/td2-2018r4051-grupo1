#include "../../PWMyTFT/inc/main.h"
#include "Fonts.h"
extern uint32_t color;

void init_TFT	(	void 	)
{
	init_pinesLCD();
}


void puntosSuspensivos(uint16_t x, uint16_t y,uint8_t r,uint8_t g, uint8_t b)
{

	TFT_DrawText(x,y,".",arial_bold, TFT_getColor(BLANCO));
	vTaskDelay(100/portTICK_RATE_MS);
	TFT_DrawText(x,y,"..",arial_bold,TFT_getColor(BLANCO));
	vTaskDelay(100/portTICK_RATE_MS);
	TFT_DrawText(x,y,"..",arial_bold,TFT_getColor(BLANCO));
	vTaskDelay(100/portTICK_RATE_MS);
	TFT_DrawText(x,y,"...",arial_bold,TFT_getColor(BLANCO));
	vTaskDelay(100/portTICK_RATE_MS);
	TFT_clearText(x,y,sizeof("..."),arial_bold,color);

}

void DrawScreen(MENUES menu, Rectangle screen)
{

		uint32_t background = Rectangle_getColor(screen);
		uint8_t i=0;


		switch(menu)
		{
			 case PRESENTACION:
				 color = background;
				 TFT_DrawRectangle(screen.x,screen.y,screen.w,screen.h,TRUE	);
				 TFT_DrawText(30,30,"PROYECTO\nTECNICAS DIGITALES II",arial_italic,TFT_getColor(BLANCO));
				 vTaskDelay(1000/portTICK_RATE_MS);
				 TFT_DrawText(30,100,"Grupo 3\nBruno, Galazan, Gomez, Muratore",arial_italic,TFT_getColor(BLANCO));
				 TFT_clearText(30,30,sizeof("PROYECTO"),arial_italic,background);
				 TFT_DrawRectangle(screen.x,screen.y,screen.w,screen.h,TRUE	);


				 break;

			 case LOADING:
				 TFT_setColor(0,0,0);
				 TFT_DrawRectangle(PANTALLA_COMPLETA,TRUE);
				 TFT_setColor(255,255,255);
				 TFT_DrawText(145,200,"Loading",arial_bold,TFT_getColor(BLANCO));
				 for(i=0;i<3;i++)
					 puntosSuspensivos(357, 200 , 0,0,0);


				 break;

			 case PANTALLA_PPAL:
				 TFT_setColor(COLOR_PANTALLA_PPAL);
				 TFT_DrawRectangle(PANTALLA_COMPLETA,TRUE);
				 TFT_DrawText(RENGLON(1,32),150,"PROCESAMIENTO",arial_bold,TFT_getColor(BLANCO));
				 break;



			 default:
				 menu = LOADING;
				 break;
		}



}


void Rectangle_setColor (Rectangle* rect, uint16_t color)
{
	rect->backgroundColor = color;
}

void Rectangle_setSize(Rectangle* rect, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}

uint16_t Rectangle_getColor(Rectangle rect)
{
	return rect.backgroundColor;
}

uint16_t Rectangle_getX (Rectangle rect)
{
	return rect.x;
}

void initScreen(Rectangle* rect)
{
	Rectangle_setColor(rect,TFT_getColor(COLOR_PANTALLA_PPAL));
	Rectangle_setSize(rect,PANTALLA_COMPLETA);
}
