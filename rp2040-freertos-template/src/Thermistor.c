#include "Thermistor.h"
#include "FreeRTOS.h"
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include <stdio.h>

// Constants for the Steinhart-Hart equation
#define A 0.001129148
#define B 0.000234125
#define C 0.0000000876741
#define R25 10000       // Resistance of thermistor at 25°C
#define ADC_MAX 4095.0f // 12-bit ADC maximum value
#define V_REF 3.3f      // Reference voltage for the ADC

// Convert the raw ADC value to resistance
static float thermistor_adc_to_resistance(uint16_t adc_value) {
    if (adc_value == 0) {
        return INFINITY; // Open circuit or invalid
    } else if (adc_value == ADC_MAX) {
        return 0.0f; // Indicates voltage is equal to V_REF
    }

    float voltage = (adc_value / ADC_MAX) * V_REF;
    return (V_REF / voltage - 1.0f) * R25;
}

// Convert resistance to temperature in Celsius using Steinhart-Hart
float thermistor_calculate_temperature(uint16_t adc_value) {
    float resistance = thermistor_adc_to_resistance(adc_value);

    // Check for invalid resistance values
    if (!isfinite(resistance) || resistance <= 0) {
        return NAN; // Return Not-a-Number to indicate an error
    }

    float logR = log(resistance);
    float tempK = 1.0f / (A + B * logR + C * pow(logR, 3));
    return tempK - 273.15f; // Convert Kelvin to Celsius
}

// Initialize the thermistor (ADC setup)
void thermistor_init(void) {
    adc_gpio_init(THERMISTOR_PIN); // Enable GPIO for ADC
    adc_init();                   // Initialize ADC hardware
    adc_select_input(THERMISTOR_ADC_CHANNEL); // Configure the ADC channel
}

// Read raw ADC value from the thermistor
uint16_t thermistor_read_adc(void) {
    return adc_read();
}
