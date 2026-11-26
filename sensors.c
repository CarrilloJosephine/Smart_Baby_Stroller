// Smart Baby Stroller
// STM32 NUCLEO-L476RG
// Reading and Analyzing ADC outputs

#include "sensors.h"
#include <./CMSIS/Device/ST/STM32L4xx/Include/stm32l476xx.h>

float ADC_Value(int V_out, int V_Ref){
    float ADC_val = (V_out/V_Ref)*4095;
    return ADC_val;
}