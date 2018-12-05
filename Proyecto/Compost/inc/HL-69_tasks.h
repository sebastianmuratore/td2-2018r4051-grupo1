#include "main.h"


#define LPC_EXTINT				        (LPC_SYSCTL_BASE + 0x00140)
#define LPC_EXTMODE				        (LPC_SYSCTL_BASE + 0x00148)
#define LPC_EXTPOLAR			        (LPC_SYSCTL_BASE + 0x0014C)

#define PIN_ADC1						PIN_16
#define FUNC_ADC						1
#define PIN_EINT0						PAD_7
#define FUNC_EINT						1
#define EINT0							0

#define	ADC_CH_HUM						ADC_CH1


void initADC(void);
void ADC_PIN_init(void);
uint16_t calcularPromedio(uint16_t *vector, int cantidad);
//void EINT0_PIN_init(void);

void vReadDataADC(void *a);
uint16_t ReadDataADC(void);
