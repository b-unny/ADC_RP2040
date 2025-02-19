#include "lib.h"

volatile bool led_pwm_state = true; // true poruqe no main inicializo com true tbm
volatile bool led_grn_state = false;
const uint32_t wrap =  4096;
const float clkdiv = 4.0f;
ssd1306_t ssd;

void init_buttons()
{
  gpio_init(BUTTON_A);
  gpio_set_dir(BUTTON_A, GPIO_IN);
  gpio_pull_up(BUTTON_A);
  
  gpio_init(JS_BUTTON);
  gpio_set_dir(JS_BUTTON, GPIO_IN);
  gpio_pull_up(JS_BUTTON);
  
  gpio_set_irq_enabled_with_callback(JS_BUTTON, GPIO_IRQ_EDGE_FALL, true, &buttons_callback);
  gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &buttons_callback);
}

void buttons_callback(uint pino, uint32_t events)
{
  sleep_ms(5);
  
  if(pino==BUTTON_A)
  {
     led_pwm_state = !led_pwm_state;
     init_leds_pwm(led_pwm_state);
  }
  else if(pino==JS_BUTTON)
  {
    led_grn_state = !led_grn_state;
    gpio_put(LED_G, led_grn_state);
    
    /* TODO Modificar a borda do display para indicar quando foi pressionado
     alternando entre diferentes estilos de borda a cada novo acionamento. */
  }
  
}

void init_leds_pwm(bool state)
{
  for(int pino = 12; pino <= 13; pino++){
        gpio_set_function(pino, GPIO_FUNC_PWM);
	uint slice = pwm_gpio_to_slice_num(pino);
	pwm_set_clkdiv(slice, clkdiv);
	pwm_set_wrap(slice, wrap);
	pwm_set_enabled(slice, state);
  } // inicializa os leds red e blue como pwm

}

void set_brightness(uint pino, uint16_t level)
{
  if(pwm_gpio_to_slice_num(pino) < 0) return;
  if(level < 100) level = 0;
  
  uint slice = pwm_gpio_to_slice_num(pino);
  pwm_set_gpio_level(pino, level);
}

void init_display()
{
  i2c_init(I2C_PORT, 400 * 1000);
  gpio_set_function(DISPLAY_SDA, GPIO_FUNC_I2C);
  gpio_set_function(DISPLAY_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(DISPLAY_SDA);
  gpio_pull_up(DISPLAY_SCL);
  
  ssd1306_init(&ssd, WIDTH, HEIGHT, false, ENDERECO, I2C_PORT); // Inicializa o display
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
  adc_select_input(0);
  uint16_t abs1 = absfor(adc_read() - 2140) * 2;
  set_brightness(LED_R, abs1);
    
  adc_select_input(1); 
  uint16_t abs2 = absfor(adc_read() - 1940) * 2;
  set_brightness(LED_B, abs2);
  
  // TODO descobrir os valores do ponto 0 dos eixos x e y, substituir e adicionar um desconto
  
  void quadrado(abs1, abs2);
}

uint16_t absfor(int16_t x)
{
  return (x < 0) ? -x : x;
}

void bordas(ssd1306_t *ssd)
{
  // Dimensões da tela OLED
    uint8_t width = 128;
    uint8_t height = 64;

    if(led_grn_state) 
      ssd1306_rect(ssd, 0, 0, width, height, true, false);
      // Borda externa (estilo 1)
    else
      ssd1306_rect(ssd, 2, 2, width - 4, height - 4, true, false);
      // Borda interna (estilo 2) - Uma linha dupla
}
void quadrado(uint8_t abs1, uint8_t abs2)
{
  uint8_t box_size = 10;
  uint8_t x = (abs1 * (128 - box_size)) / 4095;
  uint8_t y = (abs2 * (64 - box_size)) / 4095;
  ssd1306_rect(&ssd, y, x, box_size, box_size, true, true);
}