#include "PtmPathFinder_gpio.h"
#include "PtmPathFinder_adc.h"
#include <math.h>
#include "stm32f4xx_gpio.h"


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

	/*COnfig for Adc */
	AdcInit();

	while (1)
	{

	}

}

void SetupEngines(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_14 | GPIO_Pin_10);
	GPIO_SetBits(GPIOA, GPIO_Pin_13 | GPIO_Pin_15);

	GPIO_ResetBits(GPIOD, GPIO_Pin_9 | GPIO_Pin_11);
	GPIO_SetBits(GPIOD, GPIO_Pin_10 | GPIO_Pin_12);

}
