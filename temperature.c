// Smart Baby Stroller
// STM32 NUCLEO-L476RG
// Temperature Processing Module

#include "temperature.h"

// Calculate average temperature
float Temperature_Average(float t1, float t2, float t3)
{
    return (t1 + t2 + t3) / 3.0f;
}

// Find highest temperature
float Temperature_Max(float t1, float t2, float t3)
{
    float max = t1;

    if (t2 > max)
    {
        max = t2;
    }

    if (t3 > max)
    {
        max = t3;
    }

    return max;
}

// Find lowest temperature
float Temperature_Min(float t1, float t2, float t3)
{
    float min = t1;

    if (t2 < min)
    {
        min = t2;
    }

    if (t3 < min)
    {
        min = t3;
    }

    return min;
}

// Determine temperature state
int Temperature_State(float temperature)
{
    if (temperature < 16.0f)
    {
        return 0; // BLUE
    }
    else if (temperature <= 24.0f)
    {
        return 1; // GREEN
    }
    else if (temperature <= 28.0f)
    {
        return 2; // YELLOW
    }
    else
    {
        return 3; // RED
    }
}