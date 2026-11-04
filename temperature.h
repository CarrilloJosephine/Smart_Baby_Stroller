#ifndef TEMPERATURE_H
#define TEMPERATURE_H

// Calculate average temperature
float Temperature_Average(float t1, float t2, float t3);

// Find highest temperature
float Temperature_Max(float t1, float t2, float t3);

// Find lowest temperature
float Temperature_Min(float t1, float t2, float t3);

// Determine temperature state
int Temperature_State(float temperature);

#endif