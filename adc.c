// Reads temperature from three TMP36 sensors using the STM32 ADC. Converts the analog voltage into temperature in Celsius.

#include "CMSIS/Device/ST/STM32L4xx/Include/stm32l476xx.h"
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

// Set priority for ADC1, ADC2, and ADC3
void ADC_NVIC_Init(){

    // Set ADC1 & 2 to be higher priority
    // Possibly allocate temperature and water level sensors to ADC1_2)
    NVIC_SetPriority(ADC1_2_IRQn,1);
    NVIC_SetPriority(ADC3_IRQn, 3);

    // Enable interrupt lines for ADCs
    NVIC_EnableIRQ(ADC1_2_IRQn);
    NVIC_EnableIRQ(ADC3_IRQn);
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

// Set up high and low threshlods for ADC to read
void ADC_Watchdog_Init(){
    
    // Initialized temporary low/high thresholds for AWD1
    uint32_t low_threshold;
    uint32_t high_threshold;

    
    
    ADC1->CFGR |= ADC_CFGR_AWD1EN;                  // Enable AWD1 monitoring for regular ADC group
    ADC1->CFGR |= (5U << ADC_CFGR_AWD1CH_Pos);      // Configure AWD1 to monitor channel 5

    // Enable AWD1 interrupt
    ADC1->IER |= ADC_IER_AWD1IE_Msk;
    
    // set low and high thresholds for AWD1
    ADC1->TR1 |= (low_threshold << ADC_TR1_LT1_Pos);

    // select channel __ for AWD1
    ADC1->TR1 |= (high_threshold << ADC_TR1_HT1_Pos);

}

// ADC1 interrupt handler
void ADC1_IRQHandler(){
    // After end of timer, read ADC value
    // If ADC value is high_threshold -> EXTI0 -> lED & Buzzer
    // Elif ADC value is low_threshold -> EXTI1 -> LED
    // Store read value in array
}

// Set up timer for periodic interrupts 
//(TIM6 -> 16 bit periodic ADC sampling)
void TIM6_Init(){
    // setup TIM6
}


// Convert ADC reading to Celsius
float ADC_ReadTemperature(uint8_t sensor)
{
    uint16_t value;
    float voltage;
    float temperature;

    value = ADC_Read(sensor);

    // Convert ADC value to voltage (note 12 bit resolution)
    voltage = ((float)value * 3.3f) / 4095.0f;

    // TMP36 temperature formula
    temperature = (voltage - 0.5f) * 100.0f;

    return temperature;
}