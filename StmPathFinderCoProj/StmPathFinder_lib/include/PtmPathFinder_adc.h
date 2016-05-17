#ifndef PtmPathFinder_adc
#define PtmPathFinder_adc
#include "stdafx.h"

void Adc1Init(void);

void Adc2Init(void);

uint16_t GetConversionValueFromAdc(ADC_TypeDef* ADCx);


#endif
