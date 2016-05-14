#include "PtmPathFinder_gpio.h"
#include "PtmPathFinder_adc.h"
#include "PtmPathFinder_usart.h"
#include "stm32f4xx_gpio.h"

int main(void)
{
	SystemInit();

	LedInit();
	EnginesInit();
	UserButtonInit();
	UserButtonInterruptInit();
	Adc1Init();
	Adc2Init();
	UsartConfig();
	UsartInterruptionInit();

	while (1)
	{

	}

}

