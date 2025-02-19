#include<stdio.h>
#include"lib.h"

int main()
{
  stdio_init_all();
  init_buttons();
  init_leds_pwm(true);
  init_display();
  init_joystick();
  
  gpio_init(LED_G);
  gpio_set_dir(LED_G, GPIO_OUT);
  gpio_pull_up(LED_G);
  
  while(1)
  {
    joystick_handler();
    bordas(&ssd);
    ssd1306_show(&ssd);
    sleep_ms(5);
    
    /*adc_select_input(0);
    printf("valor ACD0 eixo x: %d\n", adc_read());
    
    adc_select_input(1);
    printf("valor ADC1 eixo y: %d\n", adc_read());*/
    
  }
}