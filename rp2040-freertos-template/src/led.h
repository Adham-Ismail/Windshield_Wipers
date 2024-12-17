// led.h - LED Driver Header File

#ifndef LED_H
#define LED_H

// GPIO pin definitions for the LEDs
#define WHITE_LED_1_PIN 13
#define WHITE_LED_2_PIN 14


// Function prototypes
void init_leds();
void turn_on_white_1();
void turn_on_white_2();
void turn_off_white_1();
void turn_off_white_2();
void delay_ms(int milliseconds);

#endif // LED_H
