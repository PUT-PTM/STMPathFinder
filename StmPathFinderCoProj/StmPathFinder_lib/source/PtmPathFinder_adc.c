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

	ADC_CommonInitTypeDef common_str;
	common_str.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	common_str.ADC_Mode = ADC_Mode_Independent;
	common_str.ADC_Prescaler = ADC_Prescaler_Div2;
	common_str.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&common_str);

	ADC_InitTypeDef str;
	str.ADC_Resolution = ADC_Resolution_12b;
	str.ADC_ContinuousConvMode = ENABLE;
	str.ADC_DataAlign = ADC_DataAlign_Right;
	str.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	str.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	str.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &str);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_84Cycles);
	ADC_Cmd(ADC1, ENABLE);

	GPIO_InitTypeDef stru;
	stru.GPIO_Mode = GPIO_Mode_AN;
	stru.GPIO_PuPd = GPIO_PuPd_NOPULL;
	stru.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA, &stru);
}

/**
  * @brief  Returns the last ADC1 conversion result data for regular channel.
  * @param  none
  * @retval The Data conversion value.
  */
int GetConversionValue(void)
{
	ADC_SoftwareStartConv(ADC1);
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
		;
	return (int) ADC_GetConversionValue(ADC1);
}
