#ifndef PtmPathFinder_Usart
#define PtmPathFinder_Usart
#include "PtmPathFinderLib.h"

void UsartConfig(void);

void SendChar(char character);

uint16_t ReceiveChar(void);

void UsartInterruptionInit();

void USART3_IRQHandler(void);

void HandleBluetoothRequest(char bluetoothData);

#endif
