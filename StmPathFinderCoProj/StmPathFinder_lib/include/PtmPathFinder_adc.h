#ifndef PtmPathFinder_adc
#define PtmPathFinder_adc
#include "misc.h"
#include "stm32f4xx_syscfg.h"

void AdcInit(void);

uint16_t GetConversionValueFromAdc(void);

#endif
