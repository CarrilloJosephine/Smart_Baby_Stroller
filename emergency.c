// Monitors the emergency-stop switch. Detects when the switch is activated so the main program can turn off the fan.

#include "stm32l476xx.h"
#include "emergency.h"

// Emergency-stop input connected to PC0
#define EMERGENCY_PIN 0U

// Initialize the emergency-stop input
void Emergency_Init(void)
{
    // Enable GPIOC clock
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    // Set PC0 as an input
    GPIOC->MODER &= ~(3U << 0);

    // Enable internal pull-up resistor
    GPIOC->PUPDR &= ~(3U << 0);
    GPIOC->PUPDR |= (1U << 0);
}

// Check if emergency stop is active
int Emergency_IsActive(void)
{
    // HIGH means the switch is open
    if (GPIOC->IDR & (1U << EMERGENCY_PIN))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
