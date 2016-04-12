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

	/*Config for Adc */
	AdcInit();

	while (1)
	{

	}

}

