// Controls the four temperature indicator LEDs. Only one LED turns on at a time based on the temperature inside the stroller.

#include "stm32l476xx.h"
#include "led.h"

// LED connections
// Blue   = PB0
// Green  = PB1
// Yellow = PB2
// Red    = PB10

// Initialize the LED pins
void LED_Init(void)
{
    // Enable GPIOB clock
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    // Set LED pins as outputs
    GPIOB->MODER &= ~((3U << 0) |
                      (3U << 2) |
                      (3U << 4) |
                      (3U << 20));

    GPIOB->MODER |= (1U << 0) |
                    (1U << 2) |
                    (1U << 4) |
                    (1U << 20);

    // Set outputs to push-pull
    GPIOB->OTYPER &= ~((1U << 0) |
                       (1U << 1) |
                       (1U << 2) |
                       (1U << 10));

    // Turn all LEDs off
    LED_AllOff();
}

// Turn off all four LEDs
void LED_AllOff(void)
{
    GPIOB->BSRR = (1U << 16) |
                  (1U << 17) |
                  (1U << 18) |
                  (1U << 26);
}

// Turn on blue LED
void LED_Blue(void)
{
    LED_AllOff();
    GPIOB->BSRR = (1U << 0);
}

// Turn on green LED
void LED_Green(void)
{
    LED_AllOff();
    GPIOB->BSRR = (1U << 1);
}

// Turn on yellow LED
void LED_Yellow(void)
{
    LED_AllOff();
    GPIOB->BSRR = (1U << 2);
}

// Turn on red LED
void LED_Red(void)
{
    LED_AllOff();
    GPIOB->BSRR = (1U << 10);
}
