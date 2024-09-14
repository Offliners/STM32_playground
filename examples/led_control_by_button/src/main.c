#include "typedef.h"
#include "rcc_common.h"
#include "gpio_common.h"

#if defined(NUCLEO_F446RE)
  #define RCC_LED_GPIO      (RCC_GPIOA)
  #define GPIO_LED_PORT     (GPIOA)
  #define PIN5              (5)
  #define RCC_BUTTON_GPIO   (RCC_GPIOC)
  #define GPIO_BUTTON_PORT  (GPIOC)
  #define PIN13             (13)
#else
  #error "Your STM32 board is not NUCLEO-F446RE!"
#endif

int main(void)
{
  BYTE u08Ret = FUNC_SUCCESS;


  return u08Ret;
}