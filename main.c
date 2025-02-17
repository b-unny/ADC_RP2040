#include<stdio.h>
#include"lib.h"

int main()
{
  stdio_init_all():
  init_buttons();
  set_led_pwm();
  init_displays();
  init_joystick();
  
  while(1)
  {
    joystick_handler():
    sleep_ms(5);
  }
}