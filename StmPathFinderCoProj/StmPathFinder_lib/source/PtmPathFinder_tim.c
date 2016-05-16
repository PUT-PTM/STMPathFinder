#include "PtmPathFinder_gpio.h"
#include "PtmPathFinder_usart.h"
#include "PtmPathFinder_adc.h"
#include "PtmPathFinder_tim.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_exti.h"
#include "misc.h"
/**
 * @brief  Global variables
 * @note	Global variables used to read voltage from ADC
 * @param 	None
 * @retval None
 */
float Adc1_Result = 0;
float Adc2_Result = 0;
float napiecie1 = 0;
float napiecie2 = 0;

/**
 * @brief  Configures the Tim2 on 10 Hz
 * @note	Configures Tim2 with Period 42000 and prescaler 200
 * @param 	None
 * @retval None
 */
void Timer2Configuration(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitTypeDef str;
	str.TIM_Period = 42000 - 1;
	str.TIM_Prescaler = 200 - 1;
	str.TIM_ClockDivision = TIM_CKD_DIV1;
	str.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &str);
	TIM_Cmd(TIM2, ENABLE);
}

/**
 * @brief  Configures the Tim2 interrupt vector
 * @param 	None
 * @retval None
 */
void Timer2InterruptInit(void)
{
	NVIC_InitTypeDef str;
	str.NVIC_IRQChannel = TIM2_IRQn;
	str.NVIC_IRQChannelPreemptionPriority = 0x00;
	str.NVIC_IRQChannelSubPriority = 0x00;
	str.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&str);
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

/**
 * @brief  Tim2 interrupt handler
 * @note	Checks the Sharp sensor, and handles the finding path logic
 * @param 	None
 * @retval None
 */
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == RESET)
		return;

	Adc1_Result = GetConversionValueFromAdc(ADC1);
	Adc2_Result = GetConversionValueFromAdc(ADC2);
	napiecie1 = Adc1_Result * 3 / 4095;
	napiecie2 = Adc2_Result * 3 / 4095;

	if (napiecie1 > 2 || napiecie2 > 2)
	{
		StopVehicle();
		GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
	}

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

}

/**
 * @brief  Configures the Tim3 on 10 Hz
 * @note	Configures Tim3 with Period 42000 and prescaler 200
 * @param 	None
 * @retval None
 */
void Timer3Configuration(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_3;
	TIM_3.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_3.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_3.TIM_Period = 42000 - 1;
	TIM_3.TIM_Prescaler = 200 - 1;
	TIM_TimeBaseInit(TIM3, &TIM_3);
	TIM_Cmd(TIM3, ENABLE);

}
/**
 * @brief  Configures the Tim3 interrupt vector
 * @param 	None
 * @retval None
 */
void Timer3InterruptInit(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef str;
	str.NVIC_IRQChannel = TIM3_IRQn;
	str.NVIC_IRQChannelPreemptionPriority = 0x00;
	str.NVIC_IRQChannelSubPriority = 0x00;
	str.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&str);

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

}

/**
 * @brief  Tim3 interrupt handler
 * @param 	None
 * @retval None
 */
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		GPIO_ToggleBits(GPIOD, GPIO_Pin_13);

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

