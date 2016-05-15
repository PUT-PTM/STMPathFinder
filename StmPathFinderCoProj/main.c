#include "PtmPathFinder_gpio.h"
#include "PtmPathFinder_adc.h"
#include "PtmPathFinder_usart.h"
#include "PtmPathFinder_tim.h"

int main(void)
{
	SystemInit();

	LedInit();
	EnginesInit();
	UserButtonInit();
	UserButtonInterruptInit();
	Adc1Init();
	Adc2Init();
	Timer2Configuration();
	Timer2InterruptInit();
	UsartConfig();
	UsartInterruptionInit();

	while (1)
	{

	}

}

