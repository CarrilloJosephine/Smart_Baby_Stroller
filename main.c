// Smart Baby Stroller
// STM32 NUCLEO-L476RG
// Main Controller

#include "stm32l476xx.h"
#include "led.h"

// Temporary temperature for testing
// Later, this value will come from our sensors
float temperature = 26.0f;

int main(void)
{
    // Initialize LED pins
    LED_Init();

    while (1)
    {
        // 1. Read temperature sensors
        // We will add the sensor code later


        // 2. Calculate temperature
        // We will calculate the average and maximum
        // temperature from our three sensors later


        // 3. Check emergency switch
        // We will add the emergency stop code later


        // 4. Determine temperature state

        if (temperature < 16.0f)
        {
            // BLUE: Too cold
            LED_Blue();
        }

        else if (temperature <= 24.0f)
        {
            // GREEN: Normal
            LED_Green();
        }

        else if (temperature <= 28.0f)
        {
            // YELLOW: Warm
            LED_Yellow();
        }

        else
        {
            // RED: Too hot
            LED_Red();
        }


        // 5. Control LEDs
        // The LED functions are currently called in Step 4
        // Later, we can move them here


        // 6. Control fan
        // We will add fan control later


        // 7. Control buzzer
        // We will add buzzer control later


        // 8. Check silence button
        // We will add the silence button code later

    }
}