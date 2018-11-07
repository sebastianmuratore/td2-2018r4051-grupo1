/*
 * Fonts.h
 *
 *  Created on: 21 de oct. de 2018
 *      Author: sebas
 */

#ifndef TPS_TD2_2018R4051_GRUPO1_PROYECTO_TFT_EXAMPLE_INC_FONTS_H_
#define TPS_TD2_2018R4051_GRUPO1_PROYECTO_TFT_EXAMPLE_INC_FONTS_H_


extern char arial_bold[3044];
extern char smallFonts[1144];
extern char largeFonts[95][32];
extern char arial_italic[3044];
extern char arial_normal[3044];
extern char BigFont[3044];


#define		CARACTER(c,w)			(4 + w*c)
#define		RENGLON(x,h)			(x*h + 1)


#endif /* TPS_TD2_2018R4051_GRUPO1_PROYECTO_TFT_EXAMPLE_INC_FONTS_H_ */
