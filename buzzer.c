// Controls the buzzer for temperature warnings and sensor errors. Uses SysTick for beep timing and checks if the silence button is active.

#include "stm32l476xx.h"
#include "buzzer.h"
#include "button.h"
#include "systick.h"

// Buzzer connected to PB4
#define BUZZER_PIN 4U

// Initialize the buzzer pin
void Buzzer_Init(void)
{
    // Enable GPIOB clock
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    // Set PB4 as output
    GPIOB->MODER &= ~(3U << 8);
    GPIOB->MODER |= (1U << 8);

    // Set output as push-pull
    GPIOB->OTYPER &= ~(1U << BUZZER_PIN);

    // Start with buzzer off
    Buzzer_Off();
}

// Turn off the buzzer
void Buzzer_Off(void)
{
    GPIOB->BSRR = (1U << (BUZZER_PIN + 16U));
}

// Slow beep for cold temperatures
void Buzzer_Slow(void)
{
    uint32_t time = SysTick_Millis();

    // Check if the silence button is active
    if (Button_IsSilenced())
    {
        Buzzer_Off();
        return;
    }

    // Beep for 200 ms every 3 seconds
    if ((time % 3000U) < 200U)
    {
        GPIOB->BSRR = (1U << BUZZER_PIN);
    }
    else
    {
        Buzzer_Off();
    }
}

// Fast beep for hot temperatures
void Buzzer_Fast(void)
{
    uint32_t time = SysTick_Millis();

    if (Button_IsSilenced())
    {
        Buzzer_Off();
        return;
    }

    // Two short beeps every second
    if ((time % 1000U) < 150U ||
        ((time % 1000U) >= 300U &&
         (time % 1000U) < 450U))
    {
        GPIOB->BSRR = (1U << BUZZER_PIN);
    }
    else
    {
        Buzzer_Off();
    }
}

// Repeating beep for sensor errors
void Buzzer_Fault(void)
{
    uint32_t time = SysTick_Millis();

    if (Button_IsSilenced())
    {
        Buzzer_Off();
        return;
    }

    // Beep for 500 ms every second
    if ((time % 1000U) < 500U)
    {
        GPIOB->BSRR = (1U << BUZZER_PIN);
    }
    else
    {
        Buzzer_Off();
    }
}
