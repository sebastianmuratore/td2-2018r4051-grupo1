#include "board.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

#include "../inc/FW_Timer.h"
#include "../inc/FW-Graficos.h"
#include "../inc/FW-ili9341.h"
#include "../inc/General.h"
#include "../inc/SPI.h"

/*------------------------------------------------------------------------------------------------------------------------
 * 							ENUMS
 ----------------------------------------------------------------------------------------------------------------------*/

typedef enum
{
	PRESENTACION 	= 0 ,
	PANTALLA_PPAL	= 1 ,
	LOADING			= 2 ,
	MJE_ERROR		= 3,
	CONEXION		= 4
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

#define		PIN_DCX		PIN_39
#define		PIN_CSX		PIN_38
#define		PIN_WRX		PIN_40
#define		PIN_RDX		PIN_41
#define		PIN_D0		PIN_43
#define		PIN_D1		PIN_44
#define		PIN_D2		PIN_45
#define		PIN_D3		PIN_46
#define		PIN_D4		PIN_47
#define		PIN_D5		PIN_48
#define		PIN_D6		PIN_49
#define		PIN_D7		PIN_50
#define		PIN_RST		PIN_42

//MACROS

#define  	TFT_PIXEL_WIDTH    239
#define  	TFT_PIXEL_HEIGHT   319

//Pantallas
#define		PANTALLA_COMPLETA  	0,0,320,240
#define		MARGEN_SUPERIOR		0,0,320,40
#define		MARGEN_INFERIOR		0,40,320,240

//Colores
#define		COLOR_PANTALLA_PPAL AZUL_FRANCIA
#define		COLOR_MARGEN_SUPERIOR 	VERDE
#define		COLOR_MARGEN_INFERIOR	AZUL_FRANCIA



// B , R , G
#define		BLANCO				255,255,255
#define		NEGRO				0,0,0
#define		AZUL_FRANCIA		25,50,100
#define		AZUL				255,0,0 //azul
#define		VERDE				0,0,255
#define		ROJO				0,255,0

