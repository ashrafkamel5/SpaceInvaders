// ADC.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0 SS3 to be triggered by
// software and trigger a conversion, wait for it to finish,
// and return the result. 
// Daniel Valvano
// January 15, 2016

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2015

 Copyright 2016 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
 //Edited by ashraf kamel 
 //2018-6-12

#include "ADC.h"
#include "..//tm4c123gh6pm.h"
#include <stdint.h>

// This initialization function sets up the ADC 
// Max sample rate: <=125,000 samples/second
// SS3 triggering event: software trigger
// SS3 1st sample source:  channel 1
// SS3 interrupts: enabled but not promoted to controller
void ADC0_Init_polling(void)
{ 
	volatile uint32_t delay;
  SYSCTL_RCGC2_R |= 0x00000010;   // 1) activate clock for Port E
  delay = SYSCTL_RCGC2_R;         //    allow time for clock to stabilize
  GPIO_PORTE_DIR_R &= ~0x04;      // 2) make PE2 input
  GPIO_PORTE_AFSEL_R |= 0x04;     // 3) enable alternate function on PE2
  GPIO_PORTE_DEN_R &= ~0x04;      // 4) disable digital I/O on PE2
  GPIO_PORTE_AMSEL_R |= 0x04;     // 5) enable analog function on PE2
	
  SYSCTL_RCGC0_R |= 0x00010000;   // 6) activate ADC0
  delay = SYSCTL_RCGC2_R;        
  SYSCTL_RCGC0_R &= ~0x00000300;  // 7) configure for 125K
  ADC0_SSPRI_R = 0x0123;          // 8) Sequencer 3 is highest priority
  ADC0_ACTSS_R &= ~0x0008;        // 9) disable sample sequencer 3
  ADC0_EMUX_R = 0x0000;         // 10) seq3 is softwear trigger
  ADC0_SSMUX3_R &= ~0x000F;       // 11) clear SS3 field
  ADC0_SSMUX3_R += 1;             //    set channel Ain1 (PE2)
  ADC0_SSCTL3_R = 0x0006;         // 12) no TS0 D0, yes IE0 END0
  ADC0_ACTSS_R |= 0x0008;         // 13) enable sample sequencer 3
}


//------------ADC0_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
unsigned long ADC0_In(void)
{  
	unsigned int result;
	ADC0_PSSI_R = 0x0008;            // 1) initiate SS3
  while((ADC0_RIS_R&0x08)==0){};   // 2) wait for conversion done
  result = ADC0_SSFIFO3_R&0xFFF;   // 3) read result
  ADC0_ISC_R = 0x0008;             // 4) acknowledge completion
  return result;
  //return 0; // replace this line with proper code
}

/*
  inputs: period in milliseconds ,
	
	system frequency in KHz(kilohertz)

  prescaler of the timer
  
	outputs: none
*/
void ADC0_InitTimer0ATriggerSeq3PE2(uint32_t period ,uint32_t Fosc ,uint32_t prescale)
{
  volatile uint32_t delay;
	
	period = Fosc * period;         //convert period from ms to reload value
SYSCTL_RCGCADC_R |= 0x001;      // 1) activate ADC0's clock
	SYSCTL_RCGC2_R |= 0x00000010;   // 1) activate clock for Port E
  delay = SYSCTL_RCGC2_R;         //    allow time for clock to stabilize
  GPIO_PORTE_DIR_R &= ~0x04;      // 2) make PE2 input
  GPIO_PORTE_AFSEL_R |= 0x04;     // 3) enable alternate function on PE2
  GPIO_PORTE_DEN_R &= ~0x04;      // 4) disable digital I/O on PE2
  GPIO_PORTE_AMSEL_R |= 0x04;     // 5) enable analog function on PE2
	
	SYSCTL_RCGCTIMER_R |= 0x01;     // 1) activate clock for Timer0
	delay = SYSCTL_RCGCTIMER_R;
	TIMER0_CTL_R &= ~0x01;          // 2) disable Timer0A
	TIMER0_CFG_R = 0x00;            // 3) 32-bit mode
	TIMER0_TAMR_R |= 0x02;          // 4) config as a periodic timer
	TIMER0_CTL_R |= (0x01<<5);      // 5) The output Timer A ADC trigger is enabled
	TIMER0_TAILR_R = period-1;      // 6) reload value
  TIMER0_TAPR_R = prescale;       // 7) prescale value for trigger
	TIMER0_IMR_R = 0x00;            // 8) disable all interrupts
  TIMER0_CTL_R |= 0x01;           // 9) enable timer0A
	
	
	delay = SYSCTL_RCGCADC_R;       
  
  ADC0_SSPRI_R = 0x0123;          // 2) Sequencer 3 is highest priority
  ADC0_ACTSS_R &= ~0x08;          // 3) disable sample sequencer 3
	ADC0_IM_R |= 0x08;              // 4) enable SS3 interrupts
  ADC0_EMUX_R &= ~(0x0F << 12);    
	ADC0_EMUX_R |= (0x05 << 12);    // 5) seq3 is timer triggered  
  ADC0_SSMUX3_R = 1;              // 6) set channel Ain1 (PE2)
  ADC0_SSCTL3_R = 0x0006;         // 7) no TS0 D0, yes IE0 END0
  ADC0_ACTSS_R |= 0x0008;         // 8) enable sample sequencer 3
	NVIC_PRI4_R = (NVIC_PRI4_R&0xFFFF00FF)|0x00004000; // 11)priority 2
	NVIC_EN0_R = 1<<17;             // 12) enable interrupt 17 in NVIC
	
}

void ADC0_InitTimer0ATriggerSeq3PD3(uint32_t period){
volatile uint32_t delay;
SYSCTL_RCGCADC_R |= 0x01; // 1) activate ADC0
SYSCTL_RCGCGPIO_R |= 0x08; // Port D clock
delay = SYSCTL_RCGCGPIO_R; // allow time for clock to stabilize
GPIO_PORTD_DIR_R &= ~0x08; // make PD3 input
GPIO_PORTD_AFSEL_R |= 0x08; // enable alternate function on PD3
GPIO_PORTD_DEN_R &= ~0x08; // disable digital I/O on PD3
GPIO_PORTD_AMSEL_R |= 0x08; // enable analog functionality on PD3
ADC0_PC_R = 0x01; // 2) configure for 125K samples/sec
ADC0_SSPRI_R = 0x3210; // 3) seq 0 is highest, seq 3 is lowest
SYSCTL_RCGCTIMER_R |= 0x01; // 4) activate timer0
delay = SYSCTL_RCGCGPIO_R;
TIMER0_CTL_R = 0x00000000; // disable timer0A during setup
TIMER0_CTL_R |= 0x00000020; // enable timer0A trigger to ADC
TIMER0_CFG_R = 0; // configure for 32-bit timer mode
TIMER0_TAMR_R = 0x00000002; // configure for periodic mode
TIMER0_TAPR_R = 0; // prescale value for trigger
TIMER0_TAILR_R = period-1; // start value for trigger
TIMER0_IMR_R = 0x00000000; // disable all interrupts
TIMER0_CTL_R |= 0x00000001; // enable timer0A 32-b, periodic
ADC0_ACTSS_R &= ~0x08; // 5) disable sample sequencer 3
ADC0_EMUX_R = (ADC0_EMUX_R&0xFFFF0FFF)+0x5000; // 6) timer trigger
ADC0_SSMUX3_R = 4; // 7) PD3 is analog channel 4
ADC0_SSCTL3_R = 0x06; // 8) set flag and end after first sample
ADC0_IM_R |= 0x08; // 9) enable SS3 interrupts
ADC0_ACTSS_R |= 0x08; // 10) enable sample sequencer 3
NVIC_PRI4_R = (NVIC_PRI4_R&0xFFFF00FF)|0x00004000; // 11)priority 2
NVIC_EN0_R = 1<<17; // 12) enable interrupt 17 in NVIC
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
