// Smart Baby Stroller
// STM32 NUCLEO-L476RG
// LED Control Module

#include "stm32l476xx.h"
#include "led.h"

// Temporary LED pin assignments
#define BLUE_LED    1
#define GREEN_LED   4
#define YELLOW_LED  6
#define RED_LED     8

void LED_Init(void)
{
    // Enable GPIOA clock
    RCC->AHB2ENR |= (1U << 0);

    // Configure PA1 as output
    GPIOA->MODER &= ~(3U << (BLUE_LED * 2));
    GPIOA->MODER |=  (1U << (BLUE_LED * 2));

    // Configure PA4 as output
    GPIOA->MODER &= ~(3U << (GREEN_LED * 2));
    GPIOA->MODER |=  (1U << (GREEN_LED * 2));

    // Configure PA6 as output
    GPIOA->MODER &= ~(3U << (YELLOW_LED * 2));
    GPIOA->MODER |=  (1U << (YELLOW_LED * 2));

    // Configure PA8 as output
    GPIOA->MODER &= ~(3U << (RED_LED * 2));
    GPIOA->MODER |=  (1U << (RED_LED * 2));

    // Start with all LEDs OFF
    LED_AllOff();
}

void LED_AllOff(void)
{
    GPIOA->BSRR = (1U << (BLUE_LED + 16));
    GPIOA->BSRR = (1U << (GREEN_LED + 16));
    GPIOA->BSRR = (1U << (YELLOW_LED + 16));
    GPIOA->BSRR = (1U << (RED_LED + 16));
}

void LED_Blue(void)
{
    LED_AllOff();
    GPIOA->BSRR = (1U << BLUE_LED);
}

void LED_Green(void)
{
    LED_AllOff();
    GPIOA->BSRR = (1U << GREEN_LED);
}

void LED_Yellow(void)
{
    LED_AllOff();
    GPIOA->BSRR = (1U << YELLOW_LED);
}

void LED_Red(void)
{
    LED_AllOff();
    GPIOA->BSRR = (1U << RED_LED);
}