#ifndef LDR_H
#define LDR_H

#include "pico/stdlib.h"

// Define the GPIO pin for the LDR sensor
#define LDR_PIN 2

// Function declarations
void ldr_init();
bool ldr_read();
void handle_ldr(bool val);

#endif // LDR_SENSOR_H
