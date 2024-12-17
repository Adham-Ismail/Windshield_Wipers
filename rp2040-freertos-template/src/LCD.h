#ifndef LCD_H
#define LCD_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define LCD_RS 16
#define LCD_E  17
#define LCD_D4 18
#define LCD_D5 19
#define LCD_D6 20
#define LCD_D7 21

void lcd_send_nibble(uint8_t nibble, bool is_init);
void lcd_send_byte(uint8_t byte, bool is_data, bool is_init);
void update_lcd_temperature(float temperature);
void lcd_command(uint8_t command, bool is_init);
void lcd_data(uint8_t data, bool is_init);
void lcd_init();
void lcd_print(const char *str);
void lcd_clear();
void lcd_set_cursor(uint8_t col, uint8_t row);


#endif // LCD_H