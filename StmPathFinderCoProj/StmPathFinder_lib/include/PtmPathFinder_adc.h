#ifndef PtmPathFinder_adc
#define PtmPathFinder_adc
#include "misc.h"
#include "stm32f4xx_syscfg.h"

void Adc1Init(void);

void Adc2Init(void);

uint16_t GetConversionValueFromAdc(ADC_TypeDef* ADCx);

#endif
