#include "PtmPathFinderLib.h"

extern volatile float resultFromFirstAdc;
extern volatile float resultFromSecondAdc;
extern volatile float voltageFromFirstAdc;
extern volatile float voltageFromSecondAdc;
extern volatile int mode;

float voltage1 = 0;
float voltage2 = 0;
float ResultAdc = 0;
float Result2 = 0;

int main(void)
{
	SystemInit();
	StartupConfiguration();

	while (1)
	{
		if (mode % 2 == 0)
		{
			continue;
			StopVehicle();
		}

		Sleep(200);


		ResultAdc = GetConversionValueFromAdc(ADC1);
		Result2 = GetConversionValueFromAdc(ADC2);

		voltage1 = ResultAdc * 3 / 4095;
		voltage2 = Result2 * 3 / 4095;

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
	//Timer2Configuration();
	//Timer2InterruptInit();
	//Timer3Configuration();
	//Timer3InterruptInit();
	UsartConfig();
	UsartInterruptionInit();
}
