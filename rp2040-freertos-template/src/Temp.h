#ifndef TEMP_H
#define TEMP_H

#include "stdio.h"
#include "FreeRTOS.h"
#include "hardware/adc.h"

// Pin configuration for LM35
#define Temp_PIN 26               // GPIO pin connected to LM35
#define Temp_ADC_CHANNEL 0        // ADC channel for LM35

// Initialize the LM35 module
void temp_init(void);

// Read the raw ADC value from the LM35
uint16_t temp_read_adc(void);

// Convert the ADC value to a temperature in Celsius
float calculate_temperature(uint16_t adc_value);

#endif // TEMP_H
