#ifndef THERMISTOR_H
#define THERMISTOR_H

#include "pico/stdlib.h"
#include "hardware/adc.h"

// Define the GPIO pin connected to the thermistor's analog output
#define THERMISTOR_PIN 27

// Thermistor-specific constants
#define THERMISTOR_ADC_CHANNEL 1 // Corresponds to GPIO26 (ADC0)

// Initialize the thermistor module
void thermistor_init(void);

// Read the raw ADC value from the thermistor
uint16_t thermistor_read_adc(void);

// Convert the ADC value to a temperature in Celsius
float thermistor_calculate_temperature(uint16_t adc_value);

#endif // THERMISTOR_H