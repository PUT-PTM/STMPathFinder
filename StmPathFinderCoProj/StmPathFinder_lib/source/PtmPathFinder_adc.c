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
void Adc1Init(void)
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
 * @brief  Configures the ADC
 * @note	Configures the ADC on pin PA2, 12 bit resolution
 * @param 	None
 * @retval None
 */
void Adc2Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);

	ADC_InitTypeDef str;
	str.ADC_Resolution = ADC_Resolution_12b;
	str.ADC_ContinuousConvMode = ENABLE;
	str.ADC_DataAlign = ADC_DataAlign_Right;
	str.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC2;
	str.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	str.ADC_NbrOfConversion = 1;
	ADC_Init(ADC2, &str);
	ADC_RegularChannelConfig(ADC2, ADC_Channel_2, 1, ADC_SampleTime_84Cycles);
	ADC_Cmd(ADC2, ENABLE);

	GPIO_InitTypeDef stru;
	stru.GPIO_Mode = GPIO_Mode_AN;
	stru.GPIO_PuPd = GPIO_PuPd_NOPULL;
	stru.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOA, &stru);
}

/**
 * @brief  Returns the last ADC conversion result data for regular channel.
 * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
 * @retval The Data conversion value.
 */

uint16_t GetConversionValueFromAdc(ADC_TypeDef* ADCx)
{
	ADC_SoftwareStartConv(ADCx);
	while(ADC_GetFlagStatus(ADCx,ADC_FLAG_EOC)==RESET);
	return ADC_GetConversionValue(ADCx);
}


