// Declares the functions used to control the four temperature indicator LEDs.

#ifndef LED_H
#define LED_H

// Initialize the LED pins
void LED_Init(void);

// Turn off all LEDs
void LED_AllOff(void);

// Turn on the selected temperature LED
void LED_Blue(void);
void LED_Green(void);
void LED_Yellow(void);
void LED_Red(void);

#endif
