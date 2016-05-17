#include "stdafx.h"

void StartupConfiguration(void);

int main(void)
{
	SystemInit();
	StartupConfiguration();

	while (1)
	{

	}

}

void StartupConfiguration(void)
{
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
}

