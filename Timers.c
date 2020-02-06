// Timers.c
// Runs on TM4C123 or LM4F120
// Init Timers Interrupt with a given period in milli seconds
// and interrupt priority 
// 
// 8-6-2018

#include "Timers.h"

/*---------Systick_Init----------------*/
/*
  inputs: period in milliseconds , interrupt priority (0 -> 7) ,
	
	system frequency in KHz(kilohertz) ,state (polling - interrupt)
  
	outputs: none
*/
void Systick_Init(unsigned int period ,unsigned int priority ,unsigned int Fosc ,enum statusOFtimer state)
{
	period = Fosc * period;                 //convert period from ms to reload value
	NVIC_ST_CTRL_R = 0;                     // disable SysTick during setup
	NVIC_ST_RELOAD_R = period-1;            // reload value
	NVIC_ST_CURRENT_R = 0;                  // any write to current clears it
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|(priority << 29); //priority 
	NVIC_ST_CTRL_R = 0x00000005|(state << 1);            // enable with core clock and interrupts
}



/*-----------TimerA2_Init-------------*/
/*
  inputs: period in milliseconds , interrupt priority (0 -> 7) ,
	
	system frequency in KHz(kilohertz) ,state (polling - interrupt)
  
	outputs: none
*/
void TimerA2_Init(unsigned int period ,unsigned int priority ,unsigned int Fosc ,enum statusOFtimer state);
