# Digital-Piano

This repository contains resources related to the Digital Piano. The Digital Piano project imitates piano keys (C, D, E, F) in 3 different octaves and cycles through 3 songs in a round-robin order on the tm4c123gh6pm microcontroller.

# Development Tools

* Keil uVision5 for tm4c123gh6pm microcontroller

# Contents

* `Main.c` : Main Function
* `ButtonLed` : Initialization of GPIO ports and retrieves external button inputs
* `Sound` : Score table for songs, reload values for major keys, initialization of DAC and SysTick, and handlers

# Demo Video
https://youtu.be/LOWW6T8jv0M
