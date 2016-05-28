#include "PtmPathFinderLib.h"
/**
 * @note Global variables used in program
 */
volatile float resultFromFirstAdc = 0;
volatile float resultFromSecondAdc = 0;
volatile float voltageFromFirstAdc = 0;
volatile float voltageFromSecondAdc = 0;

/**
 * @brief  Configures the Tim2 on 10 Hz
 * @note	Configures Tim2 with Period 42000 and prescaler 200
 * @param 	None
 * @retval None
 */
void Timer2Configuration(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_Period = 42000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 200 - 1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	TIM_Cmd(TIM2, DISABLE);
}

/**
 * @brief  Configures the Tim2 interrupt vector
 * @param 	None
 * @retval None
 */
void Timer2InterruptInit(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x05;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x05;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
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
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_Period = 42000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 100 - 1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	TIM_Cmd(TIM3, DISABLE);

}
/**
 * @brief  Configures the Tim3 interrupt vector
 * @param 	None
 * @retval None
 */
void Timer3InterruptInit(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

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
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == RESET)
		return;


	resultFromFirstAdc = GetConversionValueFromAdc(ADC1);
	resultFromSecondAdc = GetConversionValueFromAdc(ADC2);
	voltageFromFirstAdc = resultFromFirstAdc * 3 / 4095;
	voltageFromSecondAdc = resultFromSecondAdc * 3 / 4095;

	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

}

