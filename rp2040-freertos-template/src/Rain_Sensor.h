// rain_sensor.h - Header file for Rain Sensor control

#ifndef RAIN_SENSOR_H
#define RAIN_SENSOR_H

#include <stdbool.h>
#include <stdint.h>


#define RAIN_SENSOR_PIN 0 // Update this to match your GPIO pin for the rain sensor

// Initialize the rain sensor
void init_rain_sensor();

// Function to read analog value from RainDrop module
bool read_raindrop_sensor();

void handleRaindrop(uint8_t angle);

void handle_drops(bool reading);

bool is_rain_detected();


#endif // RAIN_SENSOR_H
