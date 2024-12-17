#include "ws2812.h"
#include "ws2812.pio.h"
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

// Predefined colors
const RGB_t WS2812_COLOR_RED = {255, 0, 0};
const RGB_t WS2812_COLOR_GREEN = {0, 255, 0};
const RGB_t WS2812_COLOR_BLUE = {0, 0, 255};
const RGB_t WS2812_COLOR_WHITE = {255, 255, 255};
const RGB_t WS2812_COLOR_BLACK = {0, 0, 0};

// LED strip state
static RGB_t led_strip[WS2812_NUM_LEDS];
PIO pio = pio0 ;
uint sm;

void ws2812_init(void) {

    // Load the PIO program
    uint offset = pio_add_program(pio, &ws2812_program);

    // Claim an unused state machine
    sm = pio_claim_unused_sm(pio, true);

    // Initialize the state machine with the program
    ws2812_program_init(pio, sm, offset, WS2812_GPIO_PIN, 800000);

    // Clear the LED strip initially
    ws2812_clear();
}
void ws2812_set_led(uint16_t led_num, RGB_t color) {
    if (led_num < WS2812_NUM_LEDS) {
        led_strip[led_num] = color;
    }
}

void ws2812_fill(RGB_t color) {
    for (uint16_t i = 0; i < WS2812_NUM_LEDS; i++) {
        ws2812_set_led(i, color);
    }
}

void ws2812_clear(void) {
    ws2812_fill(WS2812_COLOR_BLACK);
    ws2812_show();
}

void ws2812_show(void) {
    for (uint16_t i = 0; i < WS2812_NUM_LEDS; i++) {
        uint32_t encoded_color =
            ((uint32_t)led_strip[i].green << 16) |
            ((uint32_t)led_strip[i].red << 8) |
            (uint32_t)led_strip[i].blue;

        // Send the encoded color to the WS2812
        pio_sm_put_blocking(pio, sm, encoded_color << 8u);
    }
}
