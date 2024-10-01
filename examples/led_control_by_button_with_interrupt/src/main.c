#include "typedef.h"
#include "rcc_common.h"
#include "gpio_common.h"
#include "syscfg_common.h"
#include "nvic_common.h"
#include "exti_common.h"
#include "timer_func.h"

#if defined(NUCLEO_F446RE)
  #define RCC_LED_GPIO        (RCC_GPIOA)   
  #define GPIO_LED_PORT       (GPIOA)       
  #define PIN5                (5)
  #define RCC_BUTTON_GPIO     (RCC_GPIOC)   
  #define GPIO_BUTTON_PORT    (GPIOC)
  #define PIN13               (13)
  #define RCC_SYSCFG_PORT     (RCC_SYSCFG)
  #define EXTI_BUTTON_PORT    (EXTI_GPIOC)
  #define NVIC_BUTTON_IRQ     (NVIC_EXTI15_10)
#else
  #error "Your STM32 board is not NUCLEO-F446RE!"
#endif

#define LOW_DELAY_TIME_MS  (1000)
#define FAST_DELAY_TIME_MS (200)

LWORD gu32_delay_time_ms = LOW_DELAY_TIME_MS;

static void led_init(void);
static void button_init(void);
static void exti_init(void);
void exti15_10_isr(void);

int main(void)
{
  BYTE u08Ret = FUNC_SUCCESS;

  led_init();
  button_init();
  exti_init();

  while(1)
  {
    TOGGLE_GPIOX(GPIO_LED_PORT, PIN5);
    u08Ret |= timer_delay(gu32_delay_time_ms, GET_OSPEEDR(GPIO_LED_PORT, PIN5));
  }

  return u08Ret;
}

static void led_init(void)
{
  // RCC enable
  RCC_AHB1_ENABLE(RCC_LED_GPIO);

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
  // RCC enable
  RCC_AHB1_ENABLE(RCC_BUTTON_GPIO);

  // GPIO MODER
  CLEAR_GPIOX_MODER(GPIO_BUTTON_PORT, PIN13);
  SET_GPIOX_MODER(GPIO_BUTTON_PORT, PIN13, INPUT_RESET_STATE);

  // GPIO PUDER
  CLEAR_GPIOX_PUPDR(GPIO_BUTTON_PORT, PIN13);
  SET_GPIOX_PUPDR(GPIO_BUTTON_PORT, PIN13, NO_PULL_UP_PULL_DOWN);
}

static void exti_init(void)
{
  // RCC enable
  RCC_APB2_ENABLE(RCC_SYSCFG_PORT);

  // SYSCFG EXTI
  CLEAR_SYSCFG_EXTICR4_EXTIx(PIN13);
  SET_SYSCFG_EXTICR4_EXTIx(PIN13, EXTI_BUTTON_PORT);

  // NVIC trigger sourse
  SET_INTERRUPT_ENABLE(NVIC_BUTTON_IRQ);

  // EXTI trigger type
  SET_EXTI_FALLING_MODE(PIN13);

  // EXTI IMR & EMR
  ENABLE_EXTI_INTERRUPT_AND_EVENT(PIN13);
}

void exti15_10_isr(void)
{
  if(GET_EXTI_FLAG_STATUS(PIN13))
  {
    CLEAR_EXTI_FLAG_STATUS(PIN13);

    if(gu32_delay_time_ms == LOW_DELAY_TIME_MS)
      gu32_delay_time_ms = FAST_DELAY_TIME_MS;
    else
      gu32_delay_time_ms = LOW_DELAY_TIME_MS;
  }
}