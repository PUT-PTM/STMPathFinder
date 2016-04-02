#include "PtmPathFinder_gpio.h"
#include "PtmPathFinder_adc.h"


int AdcResult = 0;

int main(void)
{
	SystemInit();

	LedInit();
	ButtonInit();
	ButtonInterruptInit();
	AdcInit();

	unsigned int i;

	while (1)
	{
		AdcResult = GetConversionValue();
	}

}
