/*
 * FW-Graficos.h
 *
 *  Created on: 1 de oct. de 2018
 *      Author: sebas
 */

#ifndef TPS_TD2_2018R4051_GRUPO1_PROYECTO_TFT_EXAMPLE_INC_FW_GRAFICOS_H_
#define TPS_TD2_2018R4051_GRUPO1_PROYECTO_TFT_EXAMPLE_INC_FW_GRAFICOS_H_


/*------------------------------------------------------------------------------------------------------------------------
 * 							MACROS
 ----------------------------------------------------------------------------------------------------------------------*/
#define LCD_FONT_SIZE_SMALL		8
#define LCD_FONT_SIZE_MEDIUM	1
#define LCD_FONT_SIZE_LARGE		16


/*------------------------------------------------------------------------------------------------------------------------
 * 							FUNCIONES
 ----------------------------------------------------------------------------------------------------------------------*/
void TFT_clrScr(void);
void TFT_clrXY(void);
void TFT_setXY(int x1, int y1, int x2, int y2);
void TFT_fillArea(uint16_t dato, int pix);
void TFT_setArea(int x1, int y1, int x2, int y2);
void TFT_setColor(uint8_t r, uint8_t g, uint8_t b);
uint32_t TFT_getColor (uint8_t r, uint8_t g, uint8_t b);
void TFT_fillRect(int x1, int y1, int x2, int y2);
void TFT_DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool fill);
void TFT_DrawCircle(uint16_t cx, uint16_t cy, uint16_t r);
void TFT_SetBorderWidth(uint8_t width);
void TFT_DrawText(uint16_t x, uint16_t y, char* str , char* font, uint32_t textColor);
void TFT_DrawChar(uint16_t x, uint16_t y, char c, char* font);
void TFT_clearText(uint16_t x, uint16_t y,uint8_t size, char* font,uint32_t background);

#endif /* TPS_TD2_2018R4051_GRUPO1_PROYECTO_TFT_EXAMPLE_INC_FW_GRAFICOS_H_ */
