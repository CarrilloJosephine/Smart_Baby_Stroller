// Controls the silence button using an interrupt. Pressing the button silences the buzzer for two minutes before allowing it to sound again.

#include "stm32l476xx.h"
#include "button.h"
#include "systick.h"

// Silence button is connected to PB5
#define BUTTON_PIN 5U

// Silence duration in milliseconds
#define SILENCE_TIME 120000U

static volatile uint8_t button_pressed = 0;
static uint32_t silence_start = 0;
static uint32_t last_press = 0;
static int silenced = 0;

// Initialize the button and interrupt
void Button_Init(void)
{
    // Enable GPIOB and SYSCFG clocks
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // Set PB5 as an input
    GPIOB->MODER &= ~(3U << 10);

    // Enable internal pull-up resistor
    GPIOB->PUPDR &= ~(3U << 10);
    GPIOB->PUPDR |= (1U << 10);

    // Connect EXTI5 to PB5
    SYSCFG->EXTICR[1] &= ~(0xFU << 4);
    SYSCFG->EXTICR[1] |= (1U << 4);

    // Trigger interrupt when button is pressed
    EXTI->FTSR1 |= (1U << BUTTON_PIN);
    EXTI->RTSR1 &= ~(1U << BUTTON_PIN);

    // Clear any pending interrupt
    EXTI->PR1 = (1U << BUTTON_PIN);

    // Enable EXTI5 interrupt
    EXTI->IMR1 |= (1U << BUTTON_PIN);

    // Enable interrupt in NVIC
    NVIC_EnableIRQ(EXTI9_5_IRQn);
}

// Update the silence timer
void Button_Update(void)
{
    uint32_t now = SysTick_Millis();

    // Check if the button was pressed
    if (button_pressed)
    {
        button_pressed = 0;

        // Ignore repeated presses caused by bouncing
        if ((uint32_t)(now - last_press) >= 200U)
        {
            last_press = now;
            silence_start = now;
            silenced = 1;
        }
    }

    // End silence after two minutes
    if (silenced)
    {
        if ((uint32_t)(now - silence_start) >= SILENCE_TIME)
        {
            silenced = 0;
        }
    }
}

// Check if the buzzer is silenced
int Button_IsSilenced(void)
{
    return silenced;
}

// Interrupt runs when PB5 is pressed
void EXTI9_5_IRQHandler(void)
{
    if (EXTI->PR1 & (1U << BUTTON_PIN))
    {
        // Clear the interrupt flag
        EXTI->PR1 = (1U << BUTTON_PIN);

        // Tell the main program the button was pressed
        button_pressed = 1;
    }
}
