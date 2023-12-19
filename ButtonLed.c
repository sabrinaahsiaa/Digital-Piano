#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "ButtonLed.h"

// Constants
#define SW1 0x10  // bit position for onboard switch 1(left switch)
#define SW2 0x01  // bit position for onboard switch 2(right switch)
#define NVIC_EN0_PORTF 0x40000000  // enable PORTF edge interrupt
#define NVIC_EN0_PORTD 0x00000008  // enable PORTD edge interrupt

// Globals
volatile uint8_t curr_mode = 0;  // 0: piano mode, 1: auto-play mode

//---------------------Switch_Init---------------------
// initialize onboard switch and LED interface
// Input: none
// Output: none 
void ButtonLed_Init(void){ //volatile unsigned long delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF; // (a) activate clock for port F
  GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY; // unlock GPIO Port F
  GPIO_PORTF_CR_R |= 0x11;         // allow changes to PF4,0
  GPIO_PORTF_DIR_R &= ~0x11;    // (c) make PF4,0 in (built-in button)
  GPIO_PORTF_AFSEL_R &= ~0x11;  //     disable alt funct on PF4,0
  GPIO_PORTF_DEN_R |= 0x11;     //     enable digital I/O on PF4,0
  GPIO_PORTF_PCTL_R &= ~0x000F000F; //  configure PF4,0 as GPIO
  GPIO_PORTF_AMSEL_R &= ~0x11;  //     disable analog functionality on PF4,0
  GPIO_PORTF_PUR_R |= 0x11;     //     enable weak pull-up on PF4,0
  GPIO_PORTF_IS_R &= ~0x11;     // (d) PF4,PF0 is edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x11;    //     PF4,PF0 is not both edges
  GPIO_PORTF_IEV_R &= ~0x11;    //     PF4,PF0 falling edge event
  GPIO_PORTF_ICR_R = 0x11;      // (e) clear flags 4,0
  GPIO_PORTF_IM_R |= 0x11;      // (f) arm interrupt on PF4,PF0
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00800000; // (g) priority 4
  NVIC_EN0_R |= 0x40000000;      // (h) enable interrupt 30 in NVIC
}

//---------------------PianoKeys_Init---------------------
// initialize onboard Piano keys interface: PORT D 0 - 3 are used to generate 
// tones: CDEF:doe ray mi fa
// No need to unlock. Only PD7 needs to be unlocked.
// Input: none
// Output: none 
void PianoKeys_Init(void){ 
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD; // (a) activate clock for port D
  GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY; // unlock GPIO Port D
  GPIO_PORTD_CR_R |= 0x0F;         // allow changes to PD3-0
  GPIO_PORTD_DIR_R &= ~0x0F;    // (c) make PD3-0 in
  GPIO_PORTD_AFSEL_R &= ~0x0F;  //     disable alt funct on PD3-0
  GPIO_PORTD_DEN_R |= 0x0F;     //     enable digital I/O on PD3-0
  GPIO_PORTD_PCTL_R &= ~0x0000FFFF; //  configure PD3-0 as GPIO
  GPIO_PORTD_AMSEL_R &= ~0x0F;  //     disable analog functionality on PD3-0
  GPIO_PORTD_PUR_R |= 0x0F;     //     enable weak pull-up on PD3-0
  GPIO_PORTD_IS_R &= ~0x0F;     // (d) PD3-0 is edge-sensitive
  GPIO_PORTD_IBE_R |= 0x0F;    //     PD3-0 is both edges
  //GPIO_PORTD_IEV_R &= ~0x0F;    //     PD3-0 falling edge event
  GPIO_PORTD_ICR_R = 0x0F;      // (e) clear flags 3-0
  GPIO_PORTD_IM_R |= 0x0F;      // (f) arm interrupt on PD3-0
  NVIC_PRI0_R = (NVIC_PRI0_R&0x0FFFFFFF)|0xA0000000; // (g) priority 5 //fix this
  NVIC_EN0_R |= 0x00000008;      // (h) enable interrupt 30 in NVIC
}

unsigned long Switch_In(void){ 
  return (GPIO_PORTD_DATA_R&0x0F)^0x0F;
}

uint8_t get_current_mode(void)
{
	return curr_mode;
}
