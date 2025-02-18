#ifndef LIB_H
#define LIB_H

#include"pico/stdlib.h"
#include"hardware/adc.h"
#include"hardware/pwm.h"
#include"hardware/i2c.h"
#include"inc/ssd1306.h"
#include"inc/font.h"

#define BUTTON_A 5
#define LED_R 13
#define LED_G 11 
#define LED_B 12
#define I2C_PORT i2c1
#define DISPLAY_SDA 14
#define DISPLAY_SCL 15
#define JS_BUTTON 22
#define JS_X 26
#define JS_Y 27
#define ENDERECO 0x3C

extern volatile bool led_state;

void init_buttons(); //ok
void button_a_callback(uint pino, uint32_t events); //ok
void button_j_callback(uint pino, uint32_t events);

void set_led_pwm(); //ok
void set_brightness(uint pino, uint16_t level); //ok

void init_display(); //ok 
void update_display();    

// funçoes separadas para quadrado e borda

void init_joystick(); //ok i guess ??
void joystick_handler(); // ok i guess ?? x2

uint16_t absfor(int16_t x);

#endif