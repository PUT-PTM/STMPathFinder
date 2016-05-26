#include "PtmPathFinderLib.h"



int main(void)
{
	SystemInit();
	StartupConfiguration();

	float ResultAdc = 0;
	float Result2 = 0;
	float voltage1 = 0;
	float voltage2 = 0;

	while (1)
	{
		Sleep(200);
		GPIO_ToggleBits(GPIOD,
				GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

		ResultAdc = GetConversionValueFromAdc(ADC1);
		Result2 = GetConversionValueFromAdc(ADC2);

		voltage1 = ResultAdc * 3 / 4095;
		voltage2 = Result2 * 3 / 4095;

		if (voltage1 > 2 || voltage2 > 2)
			GPIO_ToggleBits(GPIOD, GPIO_Pin_14);

		if (voltage1 < 2 && voltage2 < 2)
			DriveStraight();
		else if (voltage1 > 2 && voltage2 < 2)
		{
			TurnRight();
			Sleep(500);
		}

		else if (voltage1 < 2 && voltage2 > 2)
		{
			TurnLeft();
			Sleep(500);
		}

		else
		{
			DriveBack();
			Sleep(500);
		}
	}
}

void StartupConfiguration(void)
{
	SysTick_Config(SystemCoreClock / 1000);
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

