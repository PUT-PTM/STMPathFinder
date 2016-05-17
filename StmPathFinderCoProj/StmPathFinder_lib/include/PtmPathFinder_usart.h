#ifndef PtmPathFinder_Usart
#define PtmPathFinder_Usart
#include "PtmPathFinderLib.h"

void UsartConfig(void);

void SendChar(char character);

void SendString(char* s);

uint16_t ReceiveChar(void);

void UsartInterruptionInit();

void USART3_IRQHandler(void);

void HandleBluetoothRequest(char bluetoothData);

#endif
