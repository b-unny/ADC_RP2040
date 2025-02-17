#include"lib.h"

void init_buttons()
{
  gpio_init(BUTTON_A);
  gpio_set_dir(BUTTON_A, GPIO_IN);
  gpio_pull_up(BUTTON_A);
  gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, 1, &button_a_callback);
  
  gpio_init(JS_BUTTON);
  gpio_set_dir(JS_BUTTON, GPIO_IN);
  gpio_pull_up(JS_BUTTON);
  gpio_set_irq_enabled_with_callback(JS_BUTTON, GPIO_IRQ_EDGE_FALL, 1, &button_js_callback);
}

void button_a_callback(uint pino, uint32_t events)
{
  slepp_ms(10);
  uint led_on = (pwm_get_gpio_level(LED_R) > pwm_get_gpio_level(LED_B)) ? LED_R : LED_B;
  pwm_set_gpio_level(led_on, pwm_get_gpio_level(led_on) > 0 ? 0 : 2048);

}

void button_js_callback(uint pino, uint32_t events)
{
  sleep_ms(10);
  pwm_set_gpio_level(LED_G, pwm_get_gpio_level(LED_G) > 0 ? 0 : 2048);
  
  /* TODO Modificar a borda do display para indicar quando foi pressionado
     alternando entre diferentes estilosde borda a cada novo acionamento. */
}

void set_led_pwm( )
{
  for(int pino=11; i<13; pino++){
    gpio_set_funtion(pino, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_slice_to_num(pino);
    
    pwm_config config = pwm_get_default_config();
    
    pwm_config_set_wrap(&config, 4095);
    pwm_init(slice, &config, 1);
  } 
}

void set_brightness(uint pino, uint16_t level)
{
  uint slive = pwm_gpio_to_slice_num(pino);
  pwm_set_gpio_level(pino, level);
}

void init_dispaly()
{
  i2c_init(I2C_PORT, 400*1000);
  gpio_set_function(DISPLAY_SDA, GPIO_FUNC_I2C);
  gpio_set_function(DISPLAY_SCL, GPIO_FUNC_I2C;
  gpio_pull_up(DISPLAY_SDA);
  gpio_pull_up(DISPLAY_SCL);
  
  ssd1306_t ssd;
  ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
  ssd1306_config(&ssd); // Configura o display
  ssd1306_send_data(&ssd); // Envia os dados para o display
  // Limpa o display. O display inicia com todos os pixels apagados.
  ssd1306_fill(&ssd, false); 
  ssd1306_send_data(&ssd);
  
}

void init_joystick()
{
  adc_init();
  adc_gpio_init(JS_X);
  adc_gpio_init(JS_Y);
}

void joystick_handler()
{
  // vai receber os valores do potenciometro -> brightness = level
  // mandara o nivel para funçao 'set_brightness"

  adc_select_input(0);
  uint16_t abs1 = abs(adc_read() - 2048);
  set_brightness(JS_X, abs1);
    
  adc_select_input(1);
  uint16_t abs2 = abs(adc_read() - 2048);
  set_brightness(JS_Y, abs2);
}

uint16_t abs(uint16_t x)
{
  return (x<0) ? -x: x); 
}

void update_display()
{
  // TODO toda logica T-T
}

