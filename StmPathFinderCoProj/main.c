#include "PtmPathFinderLib.h"

extern volatile float resultFromFirstAdc;
extern volatile float resultFromSecondAdc;
extern volatile float voltageFromFirstAdc;
extern volatile float voltageFromSecondAdc;
extern volatile int mode;

int main(void)
{
	SystemInit();
	StartupConfiguration();

	while (1)
	{
		if (mode % 2 == 1)
		{
			if (voltageFromFirstAdc < 1.6 && voltageFromSecondAdc < 1.6)
			{
				DriveStraight();
			}
			//Przeszkoda z lewej strony
			else if (voltageFromFirstAdc > 1.6 && voltageFromSecondAdc < 1.6)
			{
				GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
				while (voltageFromFirstAdc > 1.6)
				{
					TurnRight();
				}

				GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
			}
			//Przeszkoda z prawej strony
			else if (voltageFromFirstAdc < 1.6 && voltageFromSecondAdc > 1.6)
			{
				GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
				while (voltageFromSecondAdc > 1.6)
				{
					TurnLeft();
				}
				GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
			}
		}
		else
		{
			StopVehicle();
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
	//Timer2Configuration();
	//Timer2InterruptInit();
	Timer3Configuration();
	Timer3InterruptInit();
	UsartConfig();
	UsartInterruptionInit();
}
