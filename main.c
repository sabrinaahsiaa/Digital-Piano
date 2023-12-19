// Header files 
#include "tm4c123gh6pm.h"
#include "Sound.h"
#include "ButtonLed.h"

// 2. Declarations Section

// Function Prototypes
extern void DisableInterrupts(void);
extern void EnableInterrupts(void);
extern void WaitForInterrupt(void);

  
// 3. Subroutines Section
// MAIN: Mandatory for a C Program to be executable
int main(void){
  DisableInterrupts();    
  DAC_Init();        // Port B 
	ButtonLed_Init();  // Port F
  PianoKeys_Init();  // Port D
	EnableInterrupts();
	
  while(1){
		switch (get_current_mode()) {
			case PIANO:
				WaitForInterrupt();
				break;
			case AUTO_PLAY:
				play_a_song();
				break;
			default:
				break;
		}
  }
}
