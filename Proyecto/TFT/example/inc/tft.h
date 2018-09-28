#include "General.h"
#include "SPI.h"
#include "board.h"
#include "stdio.h"
#include "my_ili9341.h"
#include "FW_Timer.h"

extern uint8_t spi_tx_buf[BUFFER_SIZE];
extern uint8_t spi_rx_buf[BUFFER_SIZE];
extern SPI_CONFIG_FORMAT_T spi_format;
extern SPI_DATA_SETUP_T spi_xf;
extern uint8_t  spi_xfer_completed;



void    ili9341_WriteCommand(uint8_t RegValue);
void 	ili9341_WriteReg(uint8_t Reg, uint8_t size);
uint32_t LCD_IO_ReadData(uint8_t RegValue, uint8_t ReadSize);
