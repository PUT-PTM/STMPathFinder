#include "PtmPathFinder_usart.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_usart.h"
#include "ctype.h"
#include "misc.h"

/**
 * @brief  Configures the USART 3
 * @note	Configures the USART 3 on pin PC10 for Tx, and PC11 for Rx
 * @param 	None
 * @retval None
 */
void UsartConfig(void)
{
	//PC 10 USART_ TX
	//i PC11 USART _RX

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	//Konfiguracja lini Tx
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_InitTypeDef GPIO_Tx_InitStucture;
	GPIO_Tx_InitStucture.GPIO_OType = GPIO_OType_PP;
	GPIO_Tx_InitStucture.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Tx_InitStucture.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Tx_InitStucture.GPIO_Pin = GPIO_Pin_10;
	GPIO_Tx_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_Tx_InitStucture);

	//Konfiguracja lini Rx
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);
	GPIO_InitTypeDef GPIO_Rx_InitStucture;
	GPIO_Rx_InitStucture.GPIO_OType = GPIO_OType_PP;
	GPIO_Rx_InitStucture.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Rx_InitStucture.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Rx_InitStucture.GPIO_Pin = GPIO_Pin_11;
	GPIO_Rx_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_Rx_InitStucture);

	USART_InitTypeDef USART_InitStucture;
	USART_InitStucture.USART_BaudRate = 115200;
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
void SendChar(uint16_t character)
{
	USART_SendData(USART3, character);
	while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET);

}

/**
 * @brief  Receives single character
 * @note
 * @param 	None
 * @retval None
 */
uint16_t ReceiveChar(void)
{

	while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE)==RESET);
		return USART_ReceiveData(USART3);
}
