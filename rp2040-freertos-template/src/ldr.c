#include "ldr.h"
#include "FreeRTOS.h"
#include "led.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"


// Handle LDR in the main loop
void handle_ldr(bool val) {
    if (val) {
        turn_on_white_1(); // Turn on LEDs based on light level
        turn_on_white_2();
    } else {
        turn_off_white_1();
        turn_off_white_2();
    }
}

// Initialize LDR sensor
void ldr_init() {
    gpio_init(LDR_PIN);            // Initialize GPIO pin
    gpio_set_dir(LDR_PIN, GPIO_IN); // Set as input
}

// Read LDR sensor value
bool ldr_read() {
    return gpio_get(LDR_PIN); // Return GPIO state
}
