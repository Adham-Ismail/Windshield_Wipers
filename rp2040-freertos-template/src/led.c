// led.c - LED Driver Implementation

#include "led.h"
#include "FreeRTOS.h"
#include "pico/stdlib.h"  // Include Pico SDK for GPIO control

// Initialize the LED GPIOs
void init_leds() {
    gpio_init(WHITE_LED_1_PIN);
    gpio_set_dir(WHITE_LED_1_PIN, GPIO_OUT);
    gpio_init(WHITE_LED_2_PIN);
    gpio_set_dir(WHITE_LED_2_PIN, GPIO_OUT);
}

// Turn on the White LEDs
void turn_on_white_1() {
    gpio_put(WHITE_LED_1_PIN, 1);
}

void turn_on_white_2() {
    gpio_put(WHITE_LED_2_PIN, 1);
}

// Turn on the White LEDs
void turn_off_white_1() {
    gpio_put(WHITE_LED_1_PIN, 0);
}

void turn_off_white_2() {
    gpio_put(WHITE_LED_2_PIN, 0);
}


// Custom delay function using Pico SDK
void delay_ms(int milliseconds) {
    sleep_ms(milliseconds);
}
