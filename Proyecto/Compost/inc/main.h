#ifndef _MAIN_H_
#define _MAIN_H_


/*==================[inclusions]=============================================*/
#include "../inc/FreeRTOS.h"
#include "../inc/FreeRTOSConfig.h"
#include "../inc/General.h"
#include "../inc/pwm.h"
#include "../inc/tft.h"
#include "../inc/touch.h"
#include "../inc/uart_driver.h"
#include "../inc/functions.h"
#include "../inc/esp8266_tasks.h"
#include "../inc/TFT_tasks.h"
#include "../inc/HL-69_tasks.h"
#include "../inc/OneWireFunctions.h"
#include "task.h"
#include "board.h"
#include "queue.h"
#include "Semphr.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/Control_tasks.h"
#include "../inc/Servo_tasks.h"

/*Variables Globales*/
extern xSemaphoreHandle sServo;
extern xSemaphoreHandle sTFT;
int main(void);

/*==================[end of file]============================================*/
#endif /* #ifndef _MAIN_H_ */
