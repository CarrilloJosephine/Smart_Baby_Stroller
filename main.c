// Main program for the Smart Baby Stroller. Reads temperature sensors and controls the LEDs, fan, buzzer, and emergency stop.

#include "stm32l476xx.h"
#include "led.h"
#include "temperature.h"
#include "adc.h"
#include "systick.h"
#include "button.h"
#include "buzzer.h"
#include "fan.h"
#include "emergency.h"
#include "safety.h"

int main(void)
{
    float sensor1 = 0.0f;
    float sensor2 = 0.0f;
    float sensor3 = 0.0f;

    float average = 0.0f;
    float maximum = 0.0f;
    float minimum = 0.0f;

    int state = 1;
    int sensor_fault = 1;
    int emergency_active = 0;

    uint32_t last_read = 0;
    uint32_t now;

    // Initialize components
    SysTick_Init();
    LED_Init();
    ADC_Init();
    Button_Init();
    Buzzer_Init();
    Fan_Init();
    Emergency_Init();

    LED_AllOff();
    Fan_Off();
    Buzzer_Off();

    while (1)
    {
        // 1. Read temperature sensors
        now = SysTick_Millis();

        if ((uint32_t)(now - last_read) >= 1000U)
        {
            last_read = now;

            sensor1 = ADC_ReadTemperature(1);
            sensor2 = ADC_ReadTemperature(2);
            sensor3 = ADC_ReadTemperature(3);

            // 2. Calculate temperature
            average = Temperature_Average(sensor1, sensor2, sensor3);
            maximum = Temperature_Max(sensor1, sensor2, sensor3);
            minimum = Temperature_Min(sensor1, sensor2, sensor3);

            // 3. Check sensor safety
            sensor_fault = Safety_CheckSensors(sensor1, sensor2, sensor3);

            // 4. Determine temperature state
            if (sensor_fault == 0)
            {
                if (maximum > 28.0f)
                {
                    state = 3;
                }
                else if (minimum < 16.0f)
                {
                    state = 0;
                }
                else
                {
                    state = Temperature_State(maximum);
                }
            }

            // 5. Control LEDs
            if (sensor_fault)
            {
                LED_AllOff();
            }
            else if (state == 0)
            {
                LED_Blue();
            }
            else if (state == 1)
            {
                LED_Green();
            }
            else if (state == 2)
            {
                LED_Yellow();
            }
            else
            {
                LED_Red();
            }
        }

        // 6. Control fan
        emergency_active = Emergency_IsActive();

        if (emergency_active || sensor_fault)
        {
            Fan_Off();
        }
        else if (state == 2)
        {
            Fan_Low();
        }
        else if (state == 3)
        {
            Fan_High();
        }
        else
        {
            Fan_Off();
        }

        // 7. Update silence button
        Button_Update();

        // 8. Control buzzer
        if (emergency_active)
        {
            Buzzer_Off();
        }
        else if (sensor_fault)
        {
            Buzzer_Fault();
        }
        else if (state == 0)
        {
            Buzzer_Slow();
        }
        else if (state == 3)
        {
            Buzzer_Fast();
        }
        else
        {
            Buzzer_Off();
        }
    }
}
