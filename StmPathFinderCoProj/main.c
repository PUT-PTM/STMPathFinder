#include "PtmPathFinder_gpio.h"
#include "PtmPathFinder_adc.h"
#include "PtmPathFinder_usart.h"
#include "stm32f4xx_gpio.h"

uint8_t response = 0;
uint16_t odleglosc = 0;

int main(void)
{
	SystemInit();

	/*Config for engines */
	LedInit();

	//EnginesInit();

	//Uruchamia silniki do jazdy auta do przodu
	//SetupEngines();

	/*Config for the user button*/
	ButtonInit();
	ButtonInterruptInit();

	/*Config for Adc */
	ADC2_init();
	/*Configures USART for Bluetooth */

	//UsartConfig();
	while (1)
	{
		odleglosc = pomiar_ADC2();
	}

}

void LedBluetoothTest()
{
	response = ReceiveChar();

	if (response == 227)
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
	if (response == 228)
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
	if (response == 231)
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
	if (response == 232)
		GPIO_SetBits(GPIOD, GPIO_Pin_15);

	if (response == 235)
	{
		GPIO_ToggleBits(GPIOD,
				GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

	}

}

