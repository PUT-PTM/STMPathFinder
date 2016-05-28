#include "PtmPathFinderLib.h"

extern volatile float resultFromFirstAdc;
extern volatile float resultFromSecondAdc;
extern volatile float voltageFromFirstAdc;
extern volatile float voltageFromSecondAdc;
extern volatile int mode;

/*
 while (1)
 {
 StopVehicleTest();
 TurnRightTest();
 }
 * */

int czyPrzeszkoda = 0;
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

		if (voltageFromFirstAdc < 1.5 && voltageFromSecondAdc < 1.5)
			DriveStraight();
		else
		{
			TurnRightUsingTimer();
		}
	}
}

void test()
{
	while (1)
	{

		if (voltageFromFirstAdc < 1.5 && voltageFromSecondAdc < 1.5)
			DriveStraight();
		else
		{
			if (voltageFromFirstAdc > 1.5 && voltageFromSecondAdc < 1.5)
			{
				GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
				while (voltageFromFirstAdc > 2)
				{
					TurnRight();
				}

				GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
			}
			//Przeszkoda z prawej strony
			else if (voltageFromFirstAdc < 1.5 && voltageFromSecondAdc > 1.5)
			{
				GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
				while (voltageFromSecondAdc > 2)
				{
					TurnLeft();
				}
				GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
			}

			else if (voltageFromFirstAdc > 1.8 && voltageFromSecondAdc > 1.8)
			{
				while (voltageFromFirstAdc > 2 || voltageFromSecondAdc > 2)
				{
					DriveBack();
				}
			}

		}

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
	Timer3Configuration();
	Timer3InterruptInit();
	UsartConfig();
	UsartInterruptionInit();
}
