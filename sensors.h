#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#define V_OUT_H
#define V_REF_H


// Calculate ADC output based off output voltage with reference
float ADC_Value( int V_out, int V_Ref);
/* Formula for ADC register value given a voltage output (V)
    ADC_val = (V_out/V_ref)*4095
        V_out --> refer to TMP36 formula
        V_ref --> reference voltage (+3.3V, +5V from STM32 board)
*/

#endif

