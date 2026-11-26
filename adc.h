// Declares the functions used to read the three TMP36 temperature sensors using the STM32 ADC.

#ifndef ADC_H
#define ADC_H

#include <stdint.h>


// Initialize the ADC and analog input pins
void ADC_Init(void);

// Initialize ADC priority and interrupt lines
void ADC_NVIC_Init();

// Initialize ADC watchdog timer
void ADC_Watchdog_Init();

// Read the ADC value from a sensor
uint16_t ADC_Read(uint8_t sensor);

// Convert ADC reading to temperature in Celsius
float ADC_ReadTemperature(uint8_t sensor);

#endif