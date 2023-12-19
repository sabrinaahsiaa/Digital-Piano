#include <stdint.h>

// Constants
#define PIANO     0  // piano mode: press a key to play a tone
#define AUTO_PLAY 1  // auto play mode: automatic playing a song

extern volatile uint8_t curr_mode;

//---------------------Switch_Init---------------------
// initialize switch interface
// Input: none
// Output: none 
void ButtonLed_Init(void);

//---------------------PianoKeys_Init---------------------
// initialize onboard Piano keys interface: PORT D 0 - 3 are used to generate 
// tones: CDEF:doe ray mi fa
// No need to unlock. Only PD7 needs to be unlocked.
// Input: none
// Output: none 
void PianoKeys_Init(void);

unsigned long Switch_In(void);

uint8_t get_current_mode(void);
