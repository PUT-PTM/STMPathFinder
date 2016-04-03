#include "PtmPathFinder_gpio.h"

#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_exti.h"
#include "misc.h"




/**
 * @brief  Configures the GPIO ports
 * @note	Configures the GPIO D port and sets Pin12..Pin15
 * @param 	None
 * @retval None
 */
void LedInit(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GpioLedInit;
	GpioLedInit.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GpioLedInit.GPIO_Mode = GPIO_Mode_OUT;
	GpioLedInit.GPIO_OType = GPIO_OType_PP;
	GpioLedInit.GPIO_Speed = GPIO_Speed_100MHz;
	GpioLedInit.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GpioLedInit);
}


/**
 * @brief  Configures the GPIO ports to run engies on the left side
 * @note	Configures the GPIO D port and sets Pin9..Pin12
 * @param 	None
 * @retval None
 */
void LeftEngineInit(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GpioLedInit;
	GpioLedInit.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	GpioLedInit.GPIO_Mode = GPIO_Mode_OUT;
	GpioLedInit.GPIO_OType = GPIO_OType_PP;
	GpioLedInit.GPIO_Speed = GPIO_Speed_100MHz;
	GpioLedInit.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GpioLedInit);
}

/**
 * @brief  Configures the GPIO ports to run engies on the right side
 * @note	Configures the GPIO A port and sets Pin10, Pin 13..Pin15
 * @param 	None
 * @retval None
 */
void RightEngineInit(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GpioLedInit;
	GpioLedInit.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GpioLedInit.GPIO_Mode = GPIO_Mode_OUT;
	GpioLedInit.GPIO_OType = GPIO_OType_PP;
	GpioLedInit.GPIO_Speed = GPIO_Speed_100MHz;
	GpioLedInit.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GpioLedInit);
}


/**
 * @brief  Configures the user button
 * @note	Configures the GPIO A port and sets Pin0
 * @param 	None
 * @retval None
 */
void ButtonInit(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef str;

	str.GPIO_Pin = GPIO_Pin_0;
	str.GPIO_Mode = GPIO_Mode_IN;
	str.GPIO_OType = GPIO_OType_PP;
	str.GPIO_PuPd = GPIO_PuPd_DOWN;
	str.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &str);
}

/**
 * @brief  Configures the NVIC and EXTI for user button
 * @note	Configures the GPIO A port and sets Pin0
 * @param 	None
 * @retval None
 */
void ButtonInterruptInit(void)
{

	NVIC_InitTypeDef str;
	str.NVIC_IRQChannel = EXTI0_IRQn;
	str.NVIC_IRQChannelPreemptionPriority = 0;
	str.NVIC_IRQChannelSubPriority = 0;
	str.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&str);

	EXTI_InitTypeDef structure;
	structure.EXTI_Line = EXTI_Line0;
	structure.EXTI_Mode = EXTI_Mode_Interrupt;
	structure.EXTI_Trigger = EXTI_Trigger_Rising;
	structure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&structure);
	SYSCFG_EXTILineConfig(GPIOA, EXTI_PinSource0);

}

/**
 * @brief  The EXTI0 Handler
 * @note	Configures the GPIO A port and sets Pin0
 * @param 	None
 * @retval None
 */
void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET)
	{

		GPIO_ToggleBits(GPIOD, GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12);
		GPIO_ToggleBits(GPIOA, GPIO_Pin_10 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     );

		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
