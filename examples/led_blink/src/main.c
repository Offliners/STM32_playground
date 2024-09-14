#include "rcc_common.h"
#include "gpio_common.h"
#include "timer_func.h"

#if defined(NUCLEO_F446RE)
  #define RCC_LED_GPIO  (RCC_GPIOA)   // Reset and Clock Control (RCC) port
  #define GPIO_LED_PORT (GPIOA)       // General Purpose Input Output (GPIO) port
  #define PIN5          (5)           // General Purpose Input Output (GPIO) pin
#else
  #error "Your STM32 board is not NUCLEO-F446RE!"
#endif

int main(void)
{
  // Enable clock
  RCC_GPIOA_ENABLE(RCC_LED_GPIO);

  // Initial GPIO
  RESET_GPIOA_MODER();
  RESET_GPIOA_PUDER();

  // GPIOA & Pin5 settings
  CLEAR_GPIOX_MODER(GPIO_LED_PORT, PIN5);
  SET_GPIOX_MODER(GPIO_LED_PORT, PIN5, GENERAL_PURPOSE_OUTPUT_MODE);
  CLEAR_GPIOX_PUPDR(GPIO_LED_PORT, PIN5);
  SET_GPIOX_PUPDR(GPIO_LED_PORT, PIN5, NO_PULL_UP_PULL_DOWN);

  // Led starts blinking
  while(1)
  {
    // toggle led2 
    TOGGLE_GPIOX(GPIO_LED_PORT, PIN5);

    // 2000000 / GPIO_OSPEED_2MHZ = 1Hz
    timer_delay(2000000);
  }

  return FUNC_SUCCESS;
}