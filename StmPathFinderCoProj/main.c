#include "PtmPathFinder_gpio.h"
#include "PtmPathFinder_adc.h"
#include "PtmPathFinder_usart.h"
#include "stm32f4xx_gpio.h"


int main(void)
{
	SystemInit();
	LedInit();
	//EnginesInit();
	//SetupEngines();
	//ButtonInit();
	//ButtonInterruptInit();
	//ADC2_init();

	UsartConfig();
	UsartInterruptionInit();

	while (1)
	{

	}

}


