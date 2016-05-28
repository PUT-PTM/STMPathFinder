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
			resultFromFirstAdc = GetConversionValueFromAdc(ADC1);
			resultFromSecondAdc = GetConversionValueFromAdc(ADC2);
			voltageFromFirstAdc = resultFromFirstAdc * 3 / 4095;
			voltageFromSecondAdc = resultFromSecondAdc * 3 / 4095;

			//Test - jesli jest przeszkoda - mrugaj pomaranczowa dioda
			if (voltageFromFirstAdc > 2 || voltageFromSecondAdc > 2)
				GPIO_ToggleBits(GPIOD, GPIO_Pin_13);

			if (voltageFromFirstAdc < 2 && voltageFromSecondAdc < 2)
			{
				DriveStraight();
			}

			//Przeszkoda z lewej strony
			else if (voltageFromFirstAdc > 2 && voltageFromSecondAdc < 2)
			{
				GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
				while (voltageFromFirstAdc > 1.7)
					TurnRight();
			}
			//Przeszkoda z prawej strony
			else if (voltageFromFirstAdc < 2 && voltageFromSecondAdc > 2)
			{
				GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
				while (voltageFromSecondAdc > 1.7)
					TurnLeft();
			}
			else
			{
				StopVehicle();
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
	//Timer2Configuration();
	//Timer2InterruptInit();
	Timer3Configuration();
	Timer3InterruptInit();
	UsartConfig();
	UsartInterruptionInit();
}
