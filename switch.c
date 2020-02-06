#include "switch.h"
#include "..//tm4c123gh6pm.h"

bool MISSILE = false;
bool SPECIAL_MISSILE = false;
void init_switch()
{
	  volatile unsigned long delay;
    SYSCTL_RCGC2_R |= 0x10;           // 1) activate clock for PortE
    delay = SYSCTL_RCGC2_R;           // allow time for clock to start
    GPIO_PORTE_AMSEL_R &= ~0x03;      // 3) disable analog on PE0&1
    GPIO_PORTE_PCTL_R = 0x00;         // 4) PCTL GPIO on PE
    GPIO_PORTE_DIR_R = 0x00;          // 5) INPUT
	  GPIO_PORTE_DEN_R |= 0x03;         //
    GPIO_PORTE_AFSEL_R = 0x00;        // 6) disable alt funct on PE7-0
	  GPIO_PORTE_IS_R = 0x00;           // 7) interrupt sense is edge triggered
	  GPIO_PORTE_IBE_R = 0x00;          // 8) interrupt on both edges is disabled
	  GPIO_PORTE_IEV_R = 0x00;          // 9)	interrupt event on falling edge
	  GPIO_PORTE_IM_R = 0x03;           // 10) interrupt is enabled on pins 0&1
	  NVIC_EN0_R |= 0x04;               // 11) enable portE interrupt
    NVIC_PRI1_R |= 0x20;              // 12) set portE priorty to 1
}

