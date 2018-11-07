#include "board.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

#include "../../PWMyTFT/inc/FW_Timer.h"
#include "../../PWMyTFT/inc/FW-Graficos.h"
#include "../../PWMyTFT/inc/FW-ili9341.h"
#include "../../PWMyTFT/inc/General.h"
#include "../../PWMyTFT/inc/SPI.h"

/*------------------------------------------------------------------------------------------------------------------------
 * 							ENUMS
 ----------------------------------------------------------------------------------------------------------------------*/

typedef enum
{
	PRESENTACION 	= 0 ,
	PANTALLA_PPAL	= 1 ,
	LOADING			= 2 ,
	MJE_ERROR		= 3
}MENUES;


typedef struct Rectangles
{
	uint16_t x;
	uint16_t y;
	uint16_t h;
	uint16_t w;
	uint32_t backgroundColor;
}Rectangle;

typedef struct Texts
{
	char* text;
	char* font;
	uint16_t x;
	uint16_t y;

}Text;

/*------------------------------------------------------------------------------------------------------------------------
 * 							FUNCIONES
 ----------------------------------------------------------------------------------------------------------------------*/


uint16_t 	TFT_GetLcdPixelWidth	(	void	);
uint16_t	TFT_GetLcdPixelHeight	(	void	);
void		init_TFT				(	void	);
void 		puntosSuspensivos(uint16_t x, uint16_t y,uint8_t r,uint8_t g, uint8_t b);
void		DrawScreen(MENUES menu, Rectangle screen);
void 		Rectangle_setColor (Rectangle* rect, uint16_t color);
void 		Rectangle_setSize(Rectangle* rect, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
uint16_t 	Rectangle_getColor(Rectangle rect);
uint16_t	Rectangle_getX (Rectangle rect);
void 		initScreen(Rectangle* rect);


/*------------------------------------------------------------------------------------------------------------------------
 * 							DEFINICIONES
 ----------------------------------------------------------------------------------------------------------------------*/

//PINES
#define		PIN_DCX		PIN_06
#define		PIN_CSX		PIN_05
#define		PIN_WRX		PIN_07
#define		PIN_RDX		PIN_08
#define		PIN_D0		PIN_10
#define		PIN_D1		PIN_11
#define		PIN_D2		PIN_12
#define		PIN_D3		PIN_13
#define		PIN_D4		PIN_14
#define		PIN_D5		PIN_15
#define		PIN_D6		PIN_16
#define		PIN_D7		PIN_17
#define		PIN_RST		PIN_09
//MACROS

#define  	TFT_PIXEL_WIDTH    239
#define  	TFT_PIXEL_HEIGHT   319

#define		PANTALLA_COMPLETA  0,0,320,240
#define		COLOR_PANTALLA_PPAL AZUL_FRANCIA


// B , R , G
#define		BLANCO				255,255,255
#define		NEGRO				0,0,0
#define		AZUL_FRANCIA		25,50,100
#define		AZUL				255,0,0 //azul
#define		VERDE				0,0,255
#define		ROJO				0,255,0

