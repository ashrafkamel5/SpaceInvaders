// Timers.h
// Runs on TM4C123 or LM4F120
// Init Timers 
// 
// 8-6-2018
#include "..//tm4c123gh6pm.h"
enum statusOFtimer
{
	polling = 0,
	interrupt = 1
};



void Systick_Init(unsigned int period ,unsigned int priority ,unsigned int Fosc ,enum statusOFtimer state);


void TimerA2_Init(unsigned int period ,unsigned int priority ,unsigned int Fosc ,enum statusOFtimer state);
