#ifndef SERVO_H
#define SERVO_H
#include "hardware/gpio.h"
#include <stdint.h>

#define SERVO_PIN 15

// Initialize the servo motor
void Servo_Init();

// Set the servo angle (0 to 180 degrees)
void Servo_SetAngle(uint8_t angle);

#endif