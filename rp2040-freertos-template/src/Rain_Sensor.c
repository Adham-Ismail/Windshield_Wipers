// rain_sensor.c - Rain Sensor control implementation

#include "Rain_Sensor.h"
#include "FreeRTOS.h"
#include "pico/stdlib.h"  // Include Pico SDK for GPIO control
#include "hardware/gpio.h" // Include hardware-specific GPIO library
#include "hardware/adc.h"
#include "Servo.h"

#define NO_RAIN 0
#define LIGHT_RAIN 1
#define MOD 2

#define High 1
#define Low 0

void init_rain_sensor() {
    gpio_init(RAIN_SENSOR_PIN);
    gpio_set_dir(RAIN_SENSOR_PIN, GPIO_IN);
    gpio_pull_up(RAIN_SENSOR_PIN);
}

bool read_raindrop_sensor(){
    // return adc_read();
    return gpio_get(RAIN_SENSOR_PIN);
}

void handleRaindrop(uint8_t angle){
    Servo_SetAngle(angle);
    sleep_ms(800);
    Servo_SetAngle(0);
}


void handle_drops(bool reading){
    if(reading){
        handleRaindrop(90);
    }
}
