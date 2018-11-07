#include "General.h"
#include "SPI.h"
#include "board.h"
#include "stdio.h"
#include "FW_Timer.h"
#include "FW-Graficos.h"
#include "string.h"
#include "math.h"
#include "FW-ili9341.h"

/*------------------------------------------------------------------------------------------------------------------------
 * 							FUNCIONES
 ----------------------------------------------------------------------------------------------------------------------*/

extern uint8_t spi_tx_buf[BUFFER_SIZE];
extern uint8_t spi_rx_buf[BUFFER_SIZE];
extern SPI_CONFIG_FORMAT_T spi_format;
extern SPI_DATA_SETUP_T spi_xf;
extern uint8_t  spi_xfer_completed;



uint16_t 	TFT_GetLcdPixelWidth	(	void	);
uint16_t	TFT_GetLcdPixelHeight	(	void	);

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
