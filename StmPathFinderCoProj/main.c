#include "PtmPathFinder_gpio.h"
#include "PtmPathFinder_adc.h"
#include "PtmPathFinder_usart.h"
#include "stm32f4xx_gpio.h"


int response;

int main(void)
{
	SystemInit();

	/*Config for engines */
	LeftEngineInit();
	RightEngineInit();

	SetupEngines();

	/*Config for the user button*/
	ButtonInit();
	ButtonInterruptInit();

	/*Config for Adc */
	AdcInit();

	/*Configures USART for Bluetooth */

	UsartConfig();

	while (1)
	{
		response = ReceiveChar();
	}

}

