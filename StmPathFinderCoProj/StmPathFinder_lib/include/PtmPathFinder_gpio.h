#ifndef PtmPathFinder_Gpio
#define PtmPathFinder_Gpio

void LedInit(void);

void EnginesInit(void);

void DriveStraight(void);

void DriveBack(void);

void TurnLeft(void);

void TurnRight(void);

void StopVehicle(void);

void UserButtonInit(void);

void UserButtonInterruptInit(void);

void EXTI0_IRQHandler(void);

#endif
