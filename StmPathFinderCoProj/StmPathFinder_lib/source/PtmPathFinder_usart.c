#include "PtmPathFinderLib.h"

/**
 * @brief  Configures the USART 3
 * @note	Configures the USART 3 on pin PC10 for Tx, and PC11 for Rx
 * @param 	None
 * @retval None
 */
void UsartConfig(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	/*Tx line config*/
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_InitTypeDef GPIO_TxInitStucture;
	GPIO_TxInitStucture.GPIO_OType = GPIO_OType_PP;
	GPIO_TxInitStucture.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_TxInitStucture.GPIO_Mode = GPIO_Mode_AF;
	GPIO_TxInitStucture.GPIO_Pin = GPIO_Pin_10;
	GPIO_TxInitStucture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_TxInitStucture);

	/*Rx line config*/
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);
	GPIO_InitTypeDef GPIO_RxInitStucture;
	GPIO_RxInitStucture.GPIO_OType = GPIO_OType_PP;
	GPIO_RxInitStucture.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_RxInitStucture.GPIO_Mode = GPIO_Mode_AF;
	GPIO_RxInitStucture.GPIO_Pin = GPIO_Pin_11;
	GPIO_RxInitStucture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_RxInitStucture);

	USART_InitTypeDef USART_InitStucture;

	USART_InitStucture.USART_BaudRate = 9600;
	USART_InitStucture.USART_WordLength = USART_WordLength_8b;
	USART_InitStucture.USART_StopBits = USART_StopBits_1;
	USART_InitStucture.USART_Parity = USART_Parity_No;
	USART_InitStucture.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART3, &USART_InitStucture);
	USART_Cmd(USART3, ENABLE);

}

/**
 * @brief  Sends single character
 * @note
 * @param 	None
 * @retval None
 */
void SendChar(char character)
{
	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
		;
	USART_SendData(USART3, character);
}

/**
 * @brief  Receives single character
 * @note
 * @param 	None
 * @retval None
 */
uint16_t ReceiveChar(void)
{
	while (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET)
		;
	return USART_ReceiveData(USART3);
}

/**
 * @brief  Configures the NVIC for Usart
 * @note	Configures the USART3 Interrupt channel
 * @param 	None
 * @retval None
 */
void UsartInterruptionInit()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
	NVIC_EnableIRQ(USART3_IRQn);

}

/**
 * @brief  Handler for USART3 interrupt
 * @param 	None
 * @retval None
 */

void USART3_IRQHandler(void)
{
	if (USART_GetITStatus(USART3, USART_IT_RXNE) == RESET)
		return;

	GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
	HandleBluetoothRequest(USART3->DR);

	NVIC_ClearPendingIRQ(USART3_IRQn);

}

/**
 * @brief  Handles bluetooth request
 * @param 	data received from bluetooth adapter
 * @retval None
 */
void HandleBluetoothRequest(char bluetoothData)
{
	if (bluetoothData == 'w')
	{
		DriveStraight();
	}
	else if (bluetoothData == 'a')
	{
		TurnLeft();
	}
	else if (bluetoothData == 'd')
	{
		TurnRight();
	}

	else if (bluetoothData == 's')
	{
		StopVehicle();
	}
	else if (bluetoothData == 'r')
	{
		DriveBack();
	}
}
