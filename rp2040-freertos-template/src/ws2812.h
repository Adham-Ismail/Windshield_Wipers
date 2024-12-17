// ws2812.h
#ifndef WS2812_H
#define WS2812_H

#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

// Configuration for WS2812 LED Strip
#define WS2812_NUM_LEDS 8  // Number of LEDs in the strip
#define WS2812_GPIO_PIN 3  // GPIO pin connected to the LED strip data line
extern PIO pio;
extern uint sm;

// Color structure for RGB values
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} RGB_t;

// Initialize the WS2812 LED strip
void ws2812_init(void);

// Set the color of a specific LED
void ws2812_set_led(uint16_t led_num, RGB_t color);

// Set all LEDs to the same color
void ws2812_fill(RGB_t color);

// Clear all LEDs (turn off)
void ws2812_clear(void);

// Update the LED strip with current color values
void ws2812_show(void);

// Predefined color helpers
extern const RGB_t WS2812_COLOR_RED;
extern const RGB_t WS2812_COLOR_GREEN;
extern const RGB_t WS2812_COLOR_BLUE;
extern const RGB_t WS2812_COLOR_WHITE;
extern const RGB_t WS2812_COLOR_BLACK;

#endif // WS2812_H
