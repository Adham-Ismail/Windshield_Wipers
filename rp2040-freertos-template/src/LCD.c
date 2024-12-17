#include "lcd.h"
#include "FreeRTOS.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdio.h>


void lcd_clear(){
    lcd_command(0x01, false); // Clear display command
    sleep_ms(2);              // Wait for clearing to complete
}
void lcd_set_cursor(uint8_t col, uint8_t row) {
    uint8_t row_offsets[] = {0x00, 0x40}; // Offsets for rows 0 and 1
    if (row > 1) row = 1;  // Clamp to row 1 (16x2 display)
    lcd_command(0x80 | (col + row_offsets[row]), false);
}
void lcd_print(const char *str) {
    while (*str) {
        lcd_data(*str++, true);
    }
}
void update_lcd_temperature(float temperature) {
    char buffer[16];  // Buffer to hold the formatted string
    snprintf(buffer, sizeof(buffer), "Temp: %.2f°C", temperature); // Format temperature
    lcd_clear();      // Clear the LCD before updating
    lcd_set_cursor(0, 0); // Set cursor to the first row
    lcd_print(buffer); // Display the formatted temperature on the LCD
}

void lcd_send_nibble(uint8_t nibble, bool is_init) {
    gpio_put(LCD_D4, (nibble >> 0) & 1);
    gpio_put(LCD_D5, (nibble >> 1) & 1);
    gpio_put(LCD_D6, (nibble >> 2) & 1);
    gpio_put(LCD_D7, (nibble >> 3) & 1);

    gpio_put(LCD_E, 1);  // Pulse Enable pin
    busy_wait_us(1);  // Wait for command to process
    gpio_put(LCD_E, 0);
    if(is_init){
        sleep_ms(1);
    }else{
        sleep_us(50);
    }
}

void lcd_send_byte(uint8_t byte, bool is_data, bool is_init) {
    gpio_put(LCD_RS, is_data);
    lcd_send_nibble(byte >> 4, is_init);  // Send higher nibble
    lcd_send_nibble(byte & 0x0F, is_init);  // Send lower nibble
}

void lcd_command(uint8_t command, bool is_init) {
    lcd_send_byte(command, false, is_init);  // RS = 0 for command
}

void lcd_data(uint8_t data, bool is_init) {
    lcd_send_byte(data, true, is_init);  // RS = 1 for data
}

void lcd_init() {
    // Set pins as output
    gpio_init(LCD_RS);
    gpio_init(LCD_E);
    gpio_init(LCD_D4);
    gpio_init(LCD_D5);
    gpio_init(LCD_D6);
    gpio_init(LCD_D7);

    gpio_set_dir(LCD_RS, GPIO_OUT);
    gpio_set_dir(LCD_E, GPIO_OUT);
    gpio_set_dir(LCD_D4, GPIO_OUT);
    gpio_set_dir(LCD_D5, GPIO_OUT);
    gpio_set_dir(LCD_D6, GPIO_OUT);
    gpio_set_dir(LCD_D7, GPIO_OUT);

    sleep_ms(50);  // Wait for LCD to power up

    // Initialization sequence
    lcd_send_nibble(0x03, true);
    sleep_ms(5);
    lcd_send_nibble(0x03, true);
    sleep_us(200);
    lcd_send_nibble(0x03, true);
    lcd_send_nibble(0x02, true);  // Switch to 4-bit mode

    lcd_command(0x28, true);  // Function set: 4-bit, 2 line, 5x7 dots
    lcd_command(0x0C, true);  // Display ON, Cursor OFF
    lcd_command(0x01, true);  // Clear display
    sleep_ms(2);  // Wait for clear to complete
    lcd_command(0x06, true);  // Entry mode: Increment cursor
}
