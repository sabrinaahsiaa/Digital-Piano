#include <stdint.h>

// define music note data structure 
struct Note {
  uint32_t tone_index;
  uint8_t delay;
};
typedef const struct Note NTyp;

// Constants

// **************DAC_Init*********************
// Initialize 3-bit DAC 
// Input: none
// Output: none
void DAC_Init(void);

// **************Sound_Start*********************
// Set reload value and enable systick timer
// Input: time duration to be generated in number of machine cycles
// Output: none
void Sound_Start(uint32_t period);
void Sound_stop(void);
void play_a_song();
void Next_Song();
