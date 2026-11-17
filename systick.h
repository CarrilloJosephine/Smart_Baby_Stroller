// Declares the functions used to keep track of time in milliseconds using SysTick.

#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

// Initialize the SysTick timer
void SysTick_Init(void);

// Get the time in milliseconds
uint32_t SysTick_Millis(void);

#endif
