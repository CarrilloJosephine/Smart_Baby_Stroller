// Uses the STM32 SysTick timer to keep track of time in milliseconds.

#include "stm32l476xx.h"
#include "systick.h"

// Counts the milliseconds since startup
static volatile uint32_t milliseconds = 0;

// Initialize the SysTick timer
void SysTick_Init(void)
{
    // Set timer for 1 millisecond at 4 MHz
    SysTick->LOAD = 4000U - 1U;

    // Clear the current timer value
    SysTick->VAL = 0;

    // Enable SysTick, its interrupt, and CPU clock
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk |
                    SysTick_CTRL_ENABLE_Msk;
}

// Runs automatically every millisecond
void SysTick_Handler(void)
{
    milliseconds++;
}

// Return the elapsed time in milliseconds
uint32_t SysTick_Millis(void)
{
    return milliseconds;
}
