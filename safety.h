// Declares the function used to check temperature sensor readings for errors.

#ifndef SAFETY_H
#define SAFETY_H

// Check if any temperature reading is invalid
int Safety_CheckSensors(float t1, float t2, float t3);

#endif
