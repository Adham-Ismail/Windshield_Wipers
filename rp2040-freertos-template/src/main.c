#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "led.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "Servo.h"
#include "LCD.h"
#include "Rain_Sensor.h"
#include "ldr.h"
#include "Temp.h"
#include "adc_temperature.h"

#define Interval 4000000

static bool wipers_on = false;       // Global flag for wipers state
static bool lights_on = false;       // Global flag for lights state
static uint64_t last_update_time = 0;

// Function to initialize all components
void init_components() {
    stdio_init_all();  // Debugging
    lcd_init();        // LCD
    init_leds();       // LEDs
    init_rain_sensor();//rain drop
    temp_sensor_init(); // Temperature sensor
    ldr_init();       // LDR
    Servo_Init();      // Servo
}


void rain_task(void *pvParameters) {
    while (1) {
        bool is_raining = read_raindrop_sensor(); // Read rain sensor state

        if (!is_raining) {
            wipers_on = true;
            Servo_SetAngle(90); // Set servo to rain position
            sleep_ms(1000);         // Wait for the wipers to move
            Servo_SetAngle(0);  // Reset servo to default position
            sleep_ms(1000);
            wipers_on = false;
        }
        Servo_SetAngle(0);

        vTaskDelay(pdMS_TO_TICKS(100)); // Shorter delay for better responsiveness
    }
}


void ldr_task(void *pvParameters) {
    while (1) {
        bool light_detected = ldr_read(); // Read LDR sensor state

        if (light_detected) {
            lights_on = true;
            turn_on_white_1();
            turn_on_white_2();
        } else {
            lights_on = false;
            turn_off_white_1();
            turn_off_white_2();
        }

        vTaskDelay(pdMS_TO_TICKS(100)); // Shorter delay for better responsiveness
    }
}

void lcd_update_task(void *pvParameters) {
    while (1) {
        float temperature = read_temperature();

        // Update temperature on first row
        char temp_message[16];
        snprintf(temp_message, sizeof(temp_message), "Temp: %.2fC", temperature);
        lcd_set_cursor(0, 0);
        lcd_print(temp_message);

        // Update second row based on state flags
        lcd_set_cursor(0, 1);

        if (wipers_on) {
            lcd_print("Wipers: ON     ");
        } else if (lights_on) {
            lcd_print("Lights: ON     ");
        } else {
            lcd_print("Team 63        ");
        }

        vTaskDelay(pdMS_TO_TICKS(200)); // Update every 200 ms
    }
}

int main()
{
    init_components();

    // lcd_clear();
    // lcd_set_cursor(0, 0); // First row
    // lcd_print("TEAM 63");
    // lcd_set_cursor(0, 1); // Second row
    // lcd_print("WindshieldWipers");

    xTaskCreate(rain_task, "Rain_Task", 256, NULL, 2, NULL);
    xTaskCreate(ldr_task, "LDR_Task", 256, NULL, 2, NULL);
    xTaskCreate(lcd_update_task, "Update_LCD_Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    
    while(1){};
}