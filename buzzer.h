// Declares the functions used to control the buzzer for temperature and sensor warnings.


#ifndef BUZZER_H
#define BUZZER_H

// Initialize the buzzer GPIO pin
void Buzzer_Init(void);

// Turn off the buzzer
void Buzzer_Off(void);

// Slow beeping for cold temperatures
void Buzzer_Slow(void);

// Fast beeping for hot temperatures
void Buzzer_Fast(void);

// Warning beeps for sensor errors
void Buzzer_Fault(void);

#endif
