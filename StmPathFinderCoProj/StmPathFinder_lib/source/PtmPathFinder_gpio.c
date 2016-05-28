#include "PtmPathFinderLib.h"

extern volatile int timerCount;

/**
 * @brief  Configures the GPIO ports
 * @note	Configures the GPIO D port and sets Pin12..Pin15
 * @param 	None
 * @retval None
 */
void LedInit(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14
			| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/**
 * @brief  Configures the GPIO ports to run engies
 * @note	Configures the GPIO D port and sets Pin1..4 and Pin9..Pin12
 * @param 	None
 * @retval None
 */
void EnginesInit(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
			| GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11
			| GPIO_Pin_12;

	GPIO_Init(GPIOE, &GPIO_InitStructure);
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
 * @brief  Setups the engines to drive back
 * @note	Configures the GPIO ports
 * @param 	None
 * @retval None
 */
void DriveBack(void)
{
	GPIO_SetBits(GPIOD, GPIO_Pin_1 | GPIO_Pin_3);
	GPIO_ResetBits(GPIOD, GPIO_Pin_2 | GPIO_Pin_4);

	GPIO_SetBits(GPIOE, GPIO_Pin_9 | GPIO_Pin_11);
	GPIO_ResetBits(GPIOE, GPIO_Pin_10 | GPIO_Pin_12);
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

void TurnLeftUsingTimer()
{
	TIM_Cmd(TIM2, ENABLE);
	TurnLeft();
	while (timerCount < 30)
	{

	}
	StopVehicle();
	TIM_Cmd(TIM2, DISABLE);
	timerCount = 0;
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

void TurnRightUsingTimer()
{
	TIM_Cmd(TIM2, ENABLE);
	TurnRight();
	while (timerCount < 30)
	{

	}
	StopVehicle();
	TIM_Cmd(TIM2, DISABLE);
	timerCount = 0;
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

void StopVehicleTest(void)
{
	TIM_Cmd(TIM2, ENABLE);
	StopVehicle();
	while (timerCount < 30)
	{

	}
	StopVehicle();
	TIM_Cmd(TIM2, DISABLE);
	timerCount = 0;
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

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief  Configures the NVIC and EXTI for user button
 * @note	Configures the GPIO A port and sets Pin0
 * @param 	None
 * @retval None
 */
void UserButtonInterruptInit(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
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

	if (EXTI_GetITStatus(EXTI_Line0) == RESET)
		return;

	DebounceDelay();
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
		return;

	HandleUserButton();

	EXTI_ClearITPendingBit(EXTI_Line0);
}
/**
 * @brief  Handles User button when it is pressed
 * @param 	None
 * @retval None
 */
int mode = 0;
void HandleUserButton(void)
{
	mode++;
	if (mode % 2 == 1)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		TIM_Cmd(TIM3, ENABLE);
	}
	else
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		TIM_Cmd(TIM3, DISABLE);
		StopVehicle();
	}

}

/**
 * @brief  The simple function to delay
 * @note	Function used to debounce the user button
 * @param 	None
 * @retval None
 */
void DebounceDelay(void)
{
	int i = 0;
	for (i = 0; i < 400000; i++)
		;
}

