
// Declares the functions used to control the cooling fan using PWM.

#ifndef FAN_H
#define FAN_H

// Initialize the fan PWM output
void Fan_Init(void);

// Turn the fan off
void Fan_Off(void);

// Run the fan at low speed
void Fan_Low(void);

// Run the fan at high speed
void Fan_High(void);

#endif
