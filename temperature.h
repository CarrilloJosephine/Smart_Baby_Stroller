// Declares the functions used to calculate temperature readings from three sensors and determine the temperature state.

#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#define V_OUT_H

/* In order to figure out the temperature average, the voltage has to be sampled from every ADC registe*/
/* Formula for TMP36 reading temperature (C) in relation voltage output (V):
    T = (V_out/0.01) - 0.5
        T--> temperature in Celsius
    */

// Calculate temperature based off a given input
long int Calculate_Temp(int V_out);

// Calculate ADC value based off reference voltage and temperature
long int ADC_Val();

// Calculate the average temperature
float Temperature_Average(float t1, float t2, float t3);

// Find the highest temperature
float Temperature_Max(float t1, float t2, float t3);

// Find the lowest temperature
float Temperature_Min(float t1, float t2, float t3);

// Determine the temperature state
int Temperature_State(float temperature);

#endif
