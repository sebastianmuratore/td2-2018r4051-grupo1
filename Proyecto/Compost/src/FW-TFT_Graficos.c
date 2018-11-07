#include "../inc/Fonts.h"
#include "../inc/tft.h"


extern uint32_t color;
uint16_t _borderWidth = 2;
extern char orientacion;

uint32_t TFT_getColor (uint8_t r, uint8_t g, uint8_t b)
{
	uint16_t rr,gg,bb;
	rr = (r&248)<<8;
	gg = ((g&252)<<3);
	bb = (b>>3);

//	return (((g & 28) << 3 | b >> 3) | ((r & 248) | g >> 5) << 8); // <-- En datos serie se manda 5b R + 5b G + 6b B
	return ( rr | gg | bb );
}
void TFT_setColor(uint8_t r, uint8_t g, uint8_t b)
{

	 //color =((g&28)<<3|b>>3)| ((r&248)|g>>5)<<8; // <-- RGB
	uint16_t rr,gg,bb;
	rr = (r&248)<<8;
	gg = ((g&252)<<3);
	bb = (b>>3);
	//color = ((g & 28) << 3 | b >> 3) | ((r & 248) | g >> 5) << 8;
	color = rr | gg | bb ; // <-- En datos serie se manda 5b R + 5b G + 6b B
}

void TFT_fillRect(int x1, int y1, int x2, int y2)
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

	TFT_setArea(x1, y1, x2, y2); //Se setean los limites entre los cuales se va a dibujar
	TFT_fillArea(color, (((x2-x1)+1)*((y2-y1)+1))); //llena todo el rectangulo de el mismo color
}

/**
  * @}
  */
void TFT_clrScr()
{
	/*Limpia la pantalla
	 *
	 */
	TFT_clrXY();

	TFT_fillArea(0,((TFT_PIXEL_WIDTH+1)*(TFT_PIXEL_HEIGHT+1)));
}


void TFT_clearText(uint16_t x, uint16_t y,uint8_t size , char* font, uint32_t background)
{
	uint8_t font_width = font[0];
	uint8_t font_heigth = font[1];
	uint16_t w = size*font_width;
	uint16_t h = font_heigth;
	color = background;

	TFT_DrawRectangle(x,y,w,h,TRUE);

}


void TFT_clrXY()
{
	/*
	 * Selecciona toda la pantalla
	 */

	if (orientacion==PORTRAIT)
		TFT_setArea(0,0,TFT_PIXEL_HEIGHT,TFT_PIXEL_WIDTH);
	else
		TFT_setArea(0,0,TFT_PIXEL_WIDTH,TFT_PIXEL_HEIGHT);

}

/**
  * @}
  */

void TFT_setArea(int x1, int y1, int x2, int y2)
{
	if (orientacion==LANDSCAPE )
	{
		swap(int, x1, y1);
		swap(int, x2, y2);
		y1=TFT_PIXEL_HEIGHT-y1;
		y2=TFT_PIXEL_HEIGHT-y2;
		swap(int, y1, y2);
	}

	ili9341_WriteCommand(LCD_COLUMN_ADDR); //Registro que define las columnas entre las cuales dibuja
	ili9341_WriteData(x1>>8); // Se envia la parte mas significativa de la columna inicial
	ili9341_WriteData(x1); // Se envia la parte mas significativa de la columna inicial
	ili9341_WriteData(x2>>8); // Parte menos significativa de la columna  final
	ili9341_WriteData(x2); // Parte mas significativa de la columna final
	ili9341_WriteCommand(LCD_PAGE_ADDR); // Lo mismo pero con las filas
	ili9341_WriteData(y1>>8);
	ili9341_WriteData(y1);
	ili9341_WriteData(y2>>8);
	ili9341_WriteData(y2);
}
/**
  * @}
  */

void TFT_fillArea(uint16_t dato, int pix)
{
	//pix es la cantidad de pixeles que tengo que refrescar

	int i;


	ili9341_WriteCommand(LCD_GRAM);
	ili9341_enableDataWrite();

	for (i=0; i<pix; i++)
	{


		ili9341_cargarDato(color);
		ili9341_write();
		ili9341_cargarDato(color>>8 & 0xFF);
		ili9341_write();

	}

	ili9341_disableWrite();

}


void TFT_DrawPoint(uint16_t x, uint16_t y)
{
	/*
	 * Dibuja un punto en la pantalla con el ancho especificado en _borderWidth
	 */

	uint16_t tmp_x1 = x;
	uint16_t tmp_y1 = y;
	uint16_t tmp_x2 = x + _borderWidth;
	uint16_t tmp_y2 = y + _borderWidth;

	TFT_setArea(tmp_x1, tmp_y1, tmp_x2, tmp_y2);
	TFT_fillArea(color, (((tmp_x2-tmp_x1)+1)*((tmp_y2-tmp_y1)+1)));
}

void TFT_DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool fill)
{
	/*
	 * Dibuja un rectangulo:
	 * x = X inicial
	 * y = Y inicial
	 * W = ancho
	 * h = altura
	 * fill: Si es TRUE, indica que el rectangulo esta lleno
	 * 		 Si es FALSE, indica que el rectangulo está vacio
	 */

	//DECLARACION DE VARIABLES

	uint16_t x1 = x;
	uint16_t y1 = y;
	uint16_t x2 = x + w - 1;
	uint16_t y2 = y + h - 1;
	uint16_t tmp_x1 = 0;
	uint16_t tmp_y1 = 0;
	uint16_t tmp_x2 = 0;
	uint16_t tmp_y2 = 0;
	uint16_t i =0 ;

	//Rectangulo lleno
	if(fill) {
		TFT_setArea(x1, y1, x2, y2);
		TFT_fillArea(color, (((x2-x1)+1)*((y2-y1)+1)));
	} else {//Rectangulo vacio


		for(i = y1; i <= y2 - _borderWidth; i++) {
			if(i == y1 || i == y2 - _borderWidth) {
				tmp_x1 = x1;
				tmp_y1 = i;
				tmp_x2 = x2;
				tmp_y2 = i + _borderWidth;

				TFT_setArea(tmp_x1, tmp_y1, tmp_x2, tmp_y2); // Dibuja los bordes superior e inferior con ancho _borderWidth
				TFT_fillArea(color, (((tmp_x2-tmp_x1)+1)*((tmp_y2-tmp_y1)+1)));
			} else {
				TFT_DrawPoint(x1, i); //Borde izquierdo
				TFT_DrawPoint(x2 - _borderWidth, i); //Borde derecho
			}
		}
	}
}


void TFT_DrawCircle(uint16_t cx, uint16_t cy, uint16_t r)
{
	/* Dibuja un Circulo en la pantalla
	 * cx = centro en X
	 * cy = centro en y
	 * r = radio
	 */


	uint16_t x,y;

	for(x = cx - r; x < cx + r; x++) { //desde el extremo izqueirdo al derecho
		for(y = cy - r; y < cy + r; y++) { //desde el extremo inferior al superior
			if(pow(x - cx, 2) + pow(y - cy, 2) <= pow(r, 2)) TFT_DrawPoint(x, y); //ecuacion del circulo, todo lo que sea menor al radio lo llena
		}
	}
}



void TFT_DrawChar(uint16_t x, uint16_t y, char c, char* font)
{

	/* Dibuja un caracter en la posicion indicada
	 * x = posicion en X
	 * y = posicion en Y
	 * c = Caracter a dibujar
	 * font_size = Tamaño de la fuente
	 */


	uint8_t i,j;
	uint32_t letra_nueva;

	uint8_t  font_width 		= font[0];
	uint8_t  font_heigth 		= font[1];
	uint16_t inicio_ascii 		= font[2];
	uint16_t cant_caracteres	= font[3];

	//validacion de caracteres
	if(c < CARACTER(0,font_heigth ) || c > CARACTER(cant_caracteres,font_heigth )) return;
// [byte1.1][byte1.2][byte2.1][byte2.2]
// Si C = 33 ; --> c - inicio = 1 , pero el primer renglon de la letra que corresponde al codigo ascii "33" está en la posicion
// 3 + 32*1


//Recorre todos los pixeles
	for(i = 0; i < font_width; i++)
	{
		for( j = 0; j < font_heigth; j++)
		{
			letra_nueva = 0;
			switch(font_width)
			{//nos quedamos con un renglon
				case LCD_FONT_SIZE_SMALL:
					letra_nueva = font[CARACTER((c-inicio_ascii),font_heigth ) + j];//letra[j];
					break;
				case LCD_FONT_SIZE_LARGE:
					letra_nueva = (font[CARACTER((c-inicio_ascii),font_heigth*2 ) + j*2] << 8 ) | font[CARACTER((c-inicio_ascii),font_heigth*2 ) + j*2 + 1]; //(letra[j*2] << 8) | letra[j*2+1]; //el tamaño es 16
					break;
				default:
					letra_nueva = font[CARACTER((c-inicio_ascii),font_heigth ) + j];
					break;
			}

			//Un renglon es, por ejemplo: 0x20 = 0 0 1 0 0 0 0 0 en el caso de small font (width = 8 )
			//Se recorre bit por bit ese renglon, y si hay un 1 se chequea que este dentro de la pantalla y se lo
			//dibuja, desplazado a partir del punto x especificado como parametro
			if((letra_nueva >> ((font_width - 1) - i)) & 0x01)
			{
				if(//verifica que este dentro de la pantalla
						x + i >= 0 &&
						x + i < TFT_GetLcdPixelWidth() &&
						y + j >= 0 &&
						y + j < TFT_GetLcdPixelHeight()
				) TFT_DrawPoint(x + i, y + j);
			}
		}
	}
}

void TFT_SetBorderWidth(uint8_t width)
{
	if(width == 0) width = 1;
	_borderWidth = width - 1;
}


void TFT_DrawText(uint16_t x, uint16_t y, char* str , char* font, uint32_t textColor)
{
	uint8_t font_width = 0;
	uint8_t font_heigth = 0;
	uint16_t len = strlen(str);
	uint16_t j =0;
	//if(orientacion == LANDSCAPE)
		//swap(int,x,y);
	uint32_t colorAnt = color; //guardo  el color anterior
	color = textColor;

	font_width  = font[0];
	font_heigth = font[1];

	for(uint16_t i = 0; i < len; i++) {
		if(str[i] == 0x0) break;
		if(x + (i-j) * font_width > ( TFT_GetLcdPixelWidth()-1 ) || str[i] == '\n')//Chequea si la letra entra en la pantalla
		{
			j = (str[i] == '\n') ? (i+1): i ;
			y = y + RENGLON(1,font_heigth);
		}//Si no entra la escribe en el renglon de abajo, en la posicion enviada en X

		if(str[i] != '\n')
			TFT_DrawChar(x + ((i-j) * (font_width - 1)), y, str[i], font);

	}

	color = colorAnt;
}


uint16_t TFT_GetLcdPixelWidth(void)
{
	if(orientacion == PORTRAIT)
		return TFT_PIXEL_WIDTH;
	else
		return TFT_PIXEL_HEIGHT;
}
uint16_t TFT_GetLcdPixelHeight(void)
{
	if(orientacion == LANDSCAPE)
		return TFT_PIXEL_WIDTH;
	else
		return TFT_PIXEL_HEIGHT;
}
