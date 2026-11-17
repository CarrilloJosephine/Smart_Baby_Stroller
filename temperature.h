// Declares the functions used to calculate temperature readings from three sensors and determine the temperature state.

#ifndef TEMPERATURE_H
#define TEMPERATURE_H

// Calculate the average temperature
float Temperature_Average(float t1, float t2, float t3);

// Find the highest temperature
float Temperature_Max(float t1, float t2, float t3);

// Find the lowest temperature
float Temperature_Min(float t1, float t2, float t3);

// Determine the temperature state
int Temperature_State(float temperature);

#endif
