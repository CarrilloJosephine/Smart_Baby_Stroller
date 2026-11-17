// Checks the three temperature sensors for invalid readings. Returns an error if a sensor reports an unexpected temperature.
 
#include "safety.h"
#include <math.h>

// Check all three temperature sensors
int Safety_CheckSensors(float t1, float t2, float t3)
{
    // Check for invalid numbers
    if (!isfinite(t1) || !isfinite(t2) || !isfinite(t3))
    {
        return 1;
    }

    // Check sensor 1
    if (t1 < -10.0f || t1 > 60.0f)
    {
        return 1;
    }

    // Check sensor 2
    if (t2 < -10.0f || t2 > 60.0f)
    {
        return 1;
    }

    // Check sensor 3
    if (t3 < -10.0f || t3 > 60.0f)
    {
        return 1;
    }

    // All sensor readings passed
    return 0;
}
