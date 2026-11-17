// Declares the functions for the silence button. The button uses an interrupt to mute the buzzer for two minutes.

#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

// Initialize the button and its interrupt
void Button_Init(void);

// Update the two-minute silence timer
void Button_Update(void);

// Check whether the buzzer is silenced
int Button_IsSilenced(void);

#endif
