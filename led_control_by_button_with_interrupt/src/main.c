#include "typedef.h"
#include "rcc_common.h"
#include "gpio_common.h"
#include "timer_func.h"
#include <libopencm3/stm32/exti.h>
#include <libopencm3/cm3/nvic.h>

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

/* User button (B1) connected to PC13. */
#define RCC_BUTTON_GPIO (RCC_GPIOC)
#define GPIO_BUTTON_PORT (GPIOC)
#define GPIO_BUTTON_PIN (GPIO13)
#define EXTI_BUTTON_SOURCE (EXTI13)
#define NVIC_BUTTON_IRQ (NVIC_EXTI15_10_IRQ)

#define DELAY_VALUE_A ((uint32_t)500000)
#define DELAY_VALUE_B ((uint32_t)200000)


static void button_setup(void)
{
  /* Set button pin to input floating. */
  gpio_mode_setup(GPIO_BUTTON_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_BUTTON_PIN);

  /* Set up interrupt. */
  nvic_enable_irq(NVIC_BUTTON_IRQ);
  exti_select_source(EXTI_BUTTON_SOURCE, GPIO_BUTTON_PORT);
  exti_set_trigger(EXTI_BUTTON_SOURCE, EXTI_TRIGGER_FALLING);
  exti_enable_request(EXTI_BUTTON_SOURCE);
}

static void rcc_setup(void)
{
  rcc_periph_clock_enable(RCC_LED_GPIO);
  rcc_periph_clock_enable(RCC_BUTTON_GPIO);
  rcc_periph_clock_enable(RCC_SYSCFG); /* For EXTI. */
}

int main(void)
{
  BYTE u08Ret = FUNC_SUCCESS;

  led_init();
  button_init();

  while(1)
  {
    gpio_toggle(GPIO_LED_PORT, PIN5);
    u08Ret |= timer_delay(delay_value);
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

void exti15_10_isr(void)
{
  if (exti_get_flag_status(EXTI_BUTTON_SOURCE)) /* Check EXTI line. */
  {
    exti_reset_request(EXTI_BUTTON_SOURCE);

    if (delay_value == DELAY_VALUE_A)
    {
      delay_value = DELAY_VALUE_B;
    }
    else
    {
      delay_value = DELAY_VALUE_A;
    }
  }
}