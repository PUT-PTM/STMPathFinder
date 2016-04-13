#include "PtmPathFinder_gpio.h"
#include "PtmPathFinder_adc.h"
#include "PtmPathFinder_usart.h"
#include "stm32f4xx_gpio.h"

uint8_t response = 0;

int main(void)
{
	SystemInit();

	/*Config for engines */

	//LeftEngineInit();
	//RightEngineInit();
	//SetupEngines();
	/*Config for the user button*/
	ButtonInit();
	ButtonInterruptInit();

	/*Config for Adc */
	//AdcInit();
	/*Configures USART for Bluetooth */

	LedInit();
	UsartConfig();

	while (1)
	{

		response = ReceiveChar();

		if (response == 227)
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
		if (response == 228)
			GPIO_SetBits(GPIOD, GPIO_Pin_13);
		if (response == 231)
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
		if (response == 232)
			GPIO_SetBits(GPIOD, GPIO_Pin_15);

		if (response == 235)
		{
			GPIO_ToggleBits(GPIOD,
					GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

		}

	}

}

