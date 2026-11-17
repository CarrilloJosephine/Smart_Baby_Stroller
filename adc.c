// Reads temperature from three TMP36 sensors using the STM32 ADC. Converts the analog voltage into temperature in Celsius.

#include "stm32l476xx.h"
#include "adc.h"

// Initialize ADC1 and the temperature sensor pins
void ADC_Init(void)
{
    // Enable GPIOA and ADC clocks
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;

    // PA0, PA1, PA4 as analog inputs
    GPIOA->MODER |= (3U << 0);
    GPIOA->MODER |= (3U << 2);
    GPIOA->MODER |= (3U << 8);

    // Disable pull-up and pull-down resistors
    GPIOA->PUPDR &= ~((3U << 0) |
                      (3U << 2) |
                      (3U << 8));

    // Connect analog pins to ADC
    GPIOA->ASCR |= (1U << 0) |
                   (1U << 1) |
                   (1U << 4);

    // Select ADC clock
    ADC123_COMMON->CCR &= ~ADC_CCR_CKMODE;
    ADC123_COMMON->CCR |= (1U << ADC_CCR_CKMODE_Pos);

    // Exit deep power-down mode
    ADC1->CR &= ~ADC_CR_DEEPPWD;

    // Enable ADC voltage regulator
    ADC1->CR |= ADC_CR_ADVREGEN;

    // Wait for regulator startup
    for (volatile uint32_t i = 0; i < 1000; i++)
    {
    }

    // Calibrate ADC
    ADC1->CR |= ADC_CR_ADCAL;

    while (ADC1->CR & ADC_CR_ADCAL)
    {
    }

    // Clear ADC ready flag
    ADC1->ISR |= ADC_ISR_ADRDY;

    // Enable ADC
    ADC1->CR |= ADC_CR_ADEN;

    while (!(ADC1->ISR & ADC_ISR_ADRDY))
    {
    }

    // Use 12-bit resolution
    ADC1->CFGR &= ~ADC_CFGR_RES;

    // One conversion at a time
    ADC1->SQR1 &= ~ADC_SQR1_L;

    // Longer sampling time for stability
    ADC1->SMPR1 |= (7U << 15) |
                   (7U << 18) |
                   (7U << 27);
}


// Read one temperature sensor
uint16_t ADC_Read(uint8_t sensor)
{
    uint32_t channel;

    if (sensor == 1)
    {
        channel = 5;   // PA0
    }
    else if (sensor == 2)
    {
        channel = 6;   // PA1
    }
    else if (sensor == 3)
    {
        channel = 9;   // PA4
    }
    else
    {
        return 0;
    }

    // Select ADC channel
    ADC1->SQR1 &= ~ADC_SQR1_SQ1;
    ADC1->SQR1 |= (channel << ADC_SQR1_SQ1_Pos);

    // Start conversion
    ADC1->CR |= ADC_CR_ADSTART;

    // Wait for conversion
    while (!(ADC1->ISR & ADC_ISR_EOC))
    {
    }

    // Return the ADC result
    return (uint16_t)ADC1->DR;
}


// Convert ADC reading to Celsius
float ADC_ReadTemperature(uint8_t sensor)
{
    uint16_t value;
    float voltage;
    float temperature;

    value = ADC_Read(sensor);

    // Convert ADC value to voltage
    voltage = ((float)value * 3.3f) / 4095.0f;

    // TMP36 temperature formula
    temperature = (voltage - 0.5f) * 100.0f;

    return temperature;
}
