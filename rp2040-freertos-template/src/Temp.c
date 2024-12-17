#include "Temp.h"
#include "FreeRTOS.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include <stdio.h>

// Constants for LM35
#define ADC_MAX 4095.0f      // 12-bit ADC maximum value
#define V_REF 3.3f           // Reference voltage for the ADC
#define TEMP_SCALE 100.0f    // LM35 outputs 10 mV per °C -> Scale: 1/0.01 = 100

// Initialize the LM35 module
void temp_init(void) {
    adc_gpio_init(Temp_PIN);      // Enable GPIO for ADC
    adc_init();                   // Initialize ADC hardware
    adc_select_input(Temp_ADC_CHANNEL); // Configure the ADC channel
}

// Read the raw ADC value from the LM35
uint16_t temp_read_adc(void) {
    return adc_read();
}

// Convert the ADC value to a temperature in Celsius
float calculate_temperature(uint16_t adc_value) {
    float voltage = (adc_value / ADC_MAX) * V_REF; // Convert ADC value to voltage
    float temperature = voltage / 0.01;     // Convert voltage to temperature
    return temperature;
}
