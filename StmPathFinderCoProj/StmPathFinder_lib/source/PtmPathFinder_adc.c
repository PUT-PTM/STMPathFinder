#include "PtmPathFinder_adc.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include <stdint.h>

/**
 * @brief  Configures the ADC
 * @note	Configures the ADC on pin PA1, 12 bit resolution
 * @param 	None
 * @retval None
 */
void AdcInit(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_CommonInitTypeDef str;
	str.ADC_Mode = ADC_Mode_Independent;
	str.ADC_Prescaler = ADC_Prescaler_Div2;
	str.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	str.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&str);

	ADC_InitTypeDef stru;
	stru.ADC_Resolution = ADC_Resolution_12b;
	stru.ADC_ScanConvMode = DISABLE;
	stru.ADC_ContinuousConvMode = ENABLE;
	stru.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	stru.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	stru.ADC_DataAlign = ADC_DataAlign_Right;
	stru.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &stru);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_84Cycles);
	ADC_Cmd(ADC1, ENABLE);

	GPIO_InitTypeDef struu;
	struu.GPIO_Pin = GPIO_Pin_1;
	struu.GPIO_Mode = GPIO_Mode_AN;
	struu.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &struu);
}

/**
 * @brief  Returns the last ADC1 conversion result data for regular channel.
 * @param  none
 * @retval The Data conversion value.
 */

uint16_t GetConversionValueFromAdc(void)
{
	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
	return ADC_GetConversionValue(ADC1);
}

