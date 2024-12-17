#include "servo.h"
#include "FreeRTOS.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdint.h>
#include <stdio.h>

#define PWM_WRAP (125000000 / 8 / 50) 

void Servo_Init() {
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM); 

    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN); 
    pwm_config config = pwm_get_default_config();    

    pwm_config_set_wrap(&config, PWM_WRAP);         
    pwm_config_set_clkdiv(&config, 8.0f);           
    pwm_init(slice_num, &config, true);            
}

void Servo_SetAngle(uint8_t angle) {
    if (angle > 180) angle = 180; 
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN); 
    uint16_t duty_cycle = (angle * (PWM_WRAP / 180)) + (PWM_WRAP / 20); 
    pwm_set_gpio_level(SERVO_PIN, duty_cycle);       
}