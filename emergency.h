// Declares the functions used to monitor the emergency-stop switch and detect when the fan needs to be disabled.

#ifndef EMERGENCY_H
#define EMERGENCY_H

// Initialize the emergency-stop input
void Emergency_Init(void);

// Check if the emergency stop is active
int Emergency_IsActive(void);

#endif
