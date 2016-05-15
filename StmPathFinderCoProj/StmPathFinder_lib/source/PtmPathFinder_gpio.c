#include "PtmPathFinder_gpio.h"
#include "PtmPathFinder_usart.h"
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
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GpioLedInit;
	GpioLedInit.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GpioLedInit.GPIO_Mode = GPIO_Mode_OUT;
	GpioLedInit.GPIO_OType = GPIO_OType_PP;
	GpioLedInit.GPIO_Speed = GPIO_Speed_100MHz;
	GpioLedInit.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GpioLedInit);
}

/**
 * @brief  Configures the GPIO ports to run engies
 * @note	Configures the GPIO D port and sets Pin1..4 and Pin9..Pin12
 * @param 	None
 * @retval None
 */
void EnginesInit(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GpioLedInit;
	GpioLedInit.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GpioLedInit.GPIO_Mode = GPIO_Mode_OUT;
	GpioLedInit.GPIO_OType = GPIO_OType_PP;
	GpioLedInit.GPIO_Speed = GPIO_Speed_100MHz;
	GpioLedInit.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GpioLedInit);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitTypeDef GpioLedInitStructure;
	GpioLedInitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11
			| GPIO_Pin_12;
	GpioLedInitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GpioLedInitStructure.GPIO_OType = GPIO_OType_PP;
	GpioLedInitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GpioLedInitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GpioLedInitStructure);
}

/**
 * @brief  Setups the engines to drive straight
 * @note	Configures the GPIO ports
 * @param 	None
 * @retval None
 */
void DriveStraight(void)
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_1 | GPIO_Pin_3);
	GPIO_SetBits(GPIOD, GPIO_Pin_2 | GPIO_Pin_4);

	GPIO_ResetBits(GPIOE, GPIO_Pin_9 | GPIO_Pin_11);
	GPIO_SetBits(GPIOE, GPIO_Pin_10 | GPIO_Pin_12);

}

/**
 * @brief  Setups the engines to turn left
 * @note	Configures the GPIO ports
 * @param 	None
 * @retval None
 */
void TurnLeft(void)
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_1 | GPIO_Pin_3);
	GPIO_SetBits(GPIOD, GPIO_Pin_2 | GPIO_Pin_4);

	GPIO_ResetBits(GPIOE, GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12);
}

/**
 * @brief  Setups the engines to turn right
 * @note	Configures the GPIO ports
 * @param 	None
 * @retval None
 */
void TurnRight(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_9 | GPIO_Pin_11);
	GPIO_SetBits(GPIOE, GPIO_Pin_10 | GPIO_Pin_12);

	GPIO_ResetBits(GPIOD, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
}

/**
 * @brief  Setups the engines to stop vehicle
 * @note	Configures the GPIO ports
 * @param 	None
 * @retval None
 */
void StopVehicle(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12);
	GPIO_ResetBits(GPIOD, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
}

/**
 * @brief  Configures the user button
 * @note	Configures the GPIO A port and sets Pin0
 * @param 	None
 * @retval None
 */
void UserButtonInit(void)
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
void UserButtonInterruptInit(void)
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
		GPIO_ToggleBits(GPIOD,
				GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

		DriveStraight();

		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
