// Calculates the average, highest, and lowest temperatures from three TMP36 sensors. Determines the temperature warning state.

#include "temperature.h"


//Calculate temperature based of input voltage

long int Calculate_Temp(int V_out){
    /* In order to figure out the temperature average, the voltage has to be sampled from every ADC register*/
    /* Formula for TMP36 reading temperature (C) in relation voltage output (V): */
    long int temp = (V_out/0.01)- 0.05;
    return temp;                            // T= temperature in Celsius
}

// Calculate average temperature
float Temperature_Average(float t1, float t2, float t3)
{
    return (t1 + t2 + t3) / 3.0f;
}

// Find the highest temperature
float Temperature_Max(float t1, float t2, float t3)
{
    float maximum = t1;

    if (t2 > maximum)
    {
        maximum = t2;
    }

    if (t3 > maximum)
    {
        maximum = t3;
    }

    return maximum;
}

// Find the lowest temperature
float Temperature_Min(float t1, float t2, float t3)
{
    float minimum = t1;

    if (t2 < minimum)
    {
        minimum = t2;
    }

    if (t3 < minimum)
    {
        minimum = t3;
    }

    return minimum;
}

// Determine temperature state
int Temperature_State(float temperature)
{
    if (temperature < 16.0f)
    {
        return 0;  // Cold
    }
    else if (temperature <= 24.0f)
    {
        return 1;  // Normal
    }
    else if (temperature <= 28.0f)
    {
        return 2;  // Warm
    }
    else
    {
        return 3;  // Hot
    }
}
