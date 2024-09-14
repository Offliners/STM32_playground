#include "typedef.h"
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
  BYTE u08Ret = FUNC_SUCCESS;

  // Enable clock
  RCC_GPIOX_ENABLE(RCC_LED_GPIO);

  // GPIOA & Pin5 settings
  // GPIO MODER
  CLEAR_GPIOX_MODER(GPIO_LED_PORT, PIN5);
  SET_GPIOX_MODER(GPIO_LED_PORT, PIN5, GENERAL_PURPOSE_OUTPUT_MODE);
  
  // GPIO OTYPER
  SET_GPIOX_OTYPER_PP(GPIO_LED_PORT, PIN5);

  // GPIO OSPEEDR
  CLEAR_GPIOX_OSPEEDR(GPIO_LED_PORT, PIN5);
  SET_GPIOX_OSPEEDR(GPIO_LED_PORT, PIN5, LOW_SPEED_2MHZ);

  // GPIO PUDER
  CLEAR_GPIOX_PUPDR(GPIO_LED_PORT, PIN5);
  SET_GPIOX_PUPDR(GPIO_LED_PORT, PIN5, NO_PULL_UP_PULL_DOWN);


  // Led starts blinking
  while(1)
  {
    // toggle led2 
    TOGGLE_GPIOX(GPIO_LED_PORT, PIN5);

    // time delay (unit: ms)
    u08Ret |= timer_delay(1000, GET_OSPEEDR(GPIO_LED_PORT, PIN5));
    if(u08Ret)
      break;
  }

  return u08Ret;
}