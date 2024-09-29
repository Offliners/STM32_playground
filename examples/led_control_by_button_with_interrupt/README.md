## Led Control by Button with Interrupt
This example uses an external interrupt (button press) to change the LED toggle timing.

## GPIOA Configuration
Same as [Example 1 - Led Blink](../led_blink/README.md)

## GPIOC Configuration
Same as [Example 2 - Led Control by Button](../led_control_by_button/README.md)

## Reset and Clock Control (RCC)
Enable RCC SYSCFG to make External Interrupt (EXTI) working.

![RCC SYSCFG](./img/RCC_SYSCFG.png)

```c
#define RCC_APB2_ENABLE(clken)     WRITE_REG_LWORD(RCC, RCC_APB2ENR_OFFSET, READ_REG_LWORD(RCC, RCC_APB2ENR_OFFSET) | (CLK_ENABLE << RCC_APB2_TABLE[clken]))
#define RCC_APB2_DISABLE(clken)    WRITE_REG_LWORD(RCC, RCC_APB2ENR_OFFSET, READ_REG_LWORD(RCC, RCC_APB2ENR_OFFSET) & (~(CLK_ENABLE << RCC_APB2_TABLE[clken])))

RCC_APB2_ENABLE(RCC_SYSCFG_PORT);
```

## External Interrupt (EXTI) Configuration
### External Interrupt/Event GPIO mapping
Since there aren't many EXTI lines, several GPIO ports share the same EXTI.

In this example, we use the button (PC13) for the external interrupt, so EXTI13 is utilized.

![External Interrupt/Event GPIO mapping](./img/EXTI_GPIO_Mapping.png)

### SYSCFG Configuration for EXTI13
Find the address of SYSCFG in APB2.

![SYSCFG address](./img/SYSCFG_addr.png)

```c
#define SYSCFG_OFFSET    (0x00003800)
#define SYSCFG           GET_ADDR(PERIPHERAL_APB2_BASE + SYSCFG_OFFSET)
```

