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

#define PRESSED     0x0
#define UNPRESSED   0x1

static void led_init(void);
static void button_init(void);

int main(void)
{
  BYTE u08Ret = FUNC_SUCCESS;

  // PA5 settings
  RCC_GPIOX_ENABLE(RCC_LED_GPIO);
  led_init();

  // PC13 settings
  RCC_GPIOX_ENABLE(RCC_BUTTON_GPIO);
  button_init();
  
  while(1)
  {
    BYTE u08_is_pressed = (GET_GPIOX_IDR(GPIO_BUTTON_PORT, PIN13) == PRESSED);
    if(u08_is_pressed)
      SET_GPIOX(GPIO_LED_PORT, PIN5);
    else
      CLEAR_GPIOX(GPIO_LED_PORT, PIN5);
  }

  return u08Ret;
}

static void led_init(void)
{
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
}

static void button_init(void)
{
  // GPIO MODER
  CLEAR_GPIOX_MODER(GPIO_BUTTON_PORT, PIN13);
  SET_GPIOX_MODER(GPIO_BUTTON_PORT, PIN13, INPUT_RESET_STATE);

  // GPIO PUDER
  CLEAR_GPIOX_PUPDR(GPIO_BUTTON_PORT, PIN13);
  SET_GPIOX_PUPDR(GPIO_BUTTON_PORT, PIN13, NO_PULL_UP_PULL_DOWN);
}