#ifndef LED_H
#define LED_H

// Initialize LED pins
void LED_Init(void);

// Turn off all LEDs
void LED_AllOff(void);

// Individual LED controls
void LED_Blue(void);
void LED_Green(void);
void LED_Yellow(void);
void LED_Red(void);

#endif