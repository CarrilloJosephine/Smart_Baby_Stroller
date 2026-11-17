
// Controls the cooling fan using PWM. The fan runs at low or high speed depending on the temperature inside the stroller.

#include "stm32l476xx.h"
#include "fan.h"

// Fan PWM output is connected to PA6
#define FAN_PIN 6U

// Initialize the fan PWM
void Fan_Init(void)
{
    // Enable GPIOA and TIM3 clocks
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;

    // Set PA6 to alternate function mode
    GPIOA->MODER &= ~(3U << 12);
    GPIOA->MODER |= (2U << 12);

    // Select AF2 for TIM3 Channel 1
    GPIOA->AFR[0] &= ~(0xFU << 24);
    GPIOA->AFR[0] |= (2U << 24);

    // Set PA6 as push-pull
    GPIOA->OTYPER &= ~(1U << FAN_PIN);

    // Set timer prescaler and period
    // Assumes a 4 MHz timer clock
    // PWM frequency = 1000 Hz
    TIM3->PSC = 3U;
    TIM3->ARR = 999U;

    // Start with 0% duty cycle
    TIM3->CCR1 = 0U;

    // Set Channel 1 to PWM mode 1
    TIM3->CCMR1 &= ~(7U << 4);
    TIM3->CCMR1 |= (6U << 4);

    // Enable preload for Channel 1
    TIM3->CCMR1 |= TIM_CCMR1_OC1PE;

    // Enable Channel 1 output
    TIM3->CCER |= TIM_CCER_CC1E;

    // Enable automatic reload preload
    TIM3->CR1 |= TIM_CR1_ARPE;

    // Load timer settings
    TIM3->EGR = TIM_EGR_UG;

    // Start the timer
    TIM3->CR1 |= TIM_CR1_CEN;
}

// Turn the fan off
void Fan_Off(void)
{
    TIM3->CCR1 = 0U;
}

// Run the fan at approximately 50% duty cycle
void Fan_Low(void)
{
    TIM3->CCR1 = 500U;
}

// Run the fan at 100% duty cycle
void Fan_High(void)
{
    TIM3->CCR1 = 1000U;
}
