#ifndef PtmPathFinder_Usart
#define PtmPathFinder_Usart
#include "misc.h"
#include "stm32f4xx_syscfg.h"

void UsartConfig(void);

void SendChar(char character);

uint16_t ReceiveChar(void);

#endif
