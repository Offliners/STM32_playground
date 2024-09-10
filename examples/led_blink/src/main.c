#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "timer_func.h"

#if defined(NUCLEO_F446RE)
  #define RCC_LED_GPIO  (RCC_GPIOA)   // Reset and Clock Control (RCC) port
  #define GPIO_LED_PORT (GPIOA)       // General Purpose Input Output (GPIO) port
  #define GPIO_LED_PIN  (GPIO5)       // General Purpose Input Output (GPIO) pin
#else
  #error "Your STM32 board is not NUCLEO-F446RE!"
#endif

int main(void)
{
  // Enable clock
  rcc_periph_clock_enable(RCC_LED_GPIO);

  // Set LED pin to output push-pull
  gpio_mode_setup(GPIO_LED_PORT, GPIO_MODE_OUTPUT, GPIO_OSPEED_2MHZ, GPIO_LED_PIN);

  // Led starts blinking
  while(true)
  {
    // Led on / off
    gpio_toggle(GPIO_LED_PORT, GPIO_LED_PIN);
    
    // 2000000 / GPIO_OSPEED_2MHZ = 1Hz
    timer_delay(2000000, GPIO_OSPEED_2MHZ);
  }

  return 0;
}

