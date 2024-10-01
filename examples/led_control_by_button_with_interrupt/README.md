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

### RCC Register - RCC_APB2ENR
And then enable RCC SYSCFG.

![SYSCFG address](./img/RCC_APB2ENR.png)

```c
#define RCC_APB2_ENABLE(clken)     WRITE_REG_LWORD(RCC, RCC_APB2ENR_OFFSET, READ_REG_LWORD(RCC, RCC_APB2ENR_OFFSET) | (CLK_ENABLE << RCC_APB2_TABLE[clken]))

// RCC enable
RCC_APB2_ENABLE(RCC_SYSCFG_PORT);
```

### SYSCFG EXTI Setup
Because we use the button (PC13) for the external interrupt, we need to write 0010 at EXTI13 for PC13.
![SYSCFG_EXTICR4](./img/SYSCFG_EXTICR4.png)

```c
#define CLEAR_SYSCFG_EXTICR4_EXTIx(EXTIx)           WRITE_SYSCFG_EXTICR4(READ_SYSCFG_EXTICR4() & (~(0xF << ((EXTIx % 4) * 4))))
#define SET_SYSCFG_EXTICR4_EXTIx(EXTIx, EXTI_GPIOx) WRITE_SYSCFG_EXTICR4(READ_SYSCFG_EXTICR4() | (EXTI_GPIOX_TABLE[EXTI_GPIOx] << ((EXTIx % 4) * 4)))

// SYSCFG EXTI
CLEAR_SYSCFG_EXTICR4_EXTIx(PIN13);
SET_SYSCFG_EXTICR4_EXTIx(PIN13, EXTI_BUTTON_PORT);
```

## Nested Vectored Interrupt Controller (NVIC)

In the Reference Manual, we can find the EXTI13 interrupt request (IRQ) at Position 40 through the vector table. To enable this IRQ, we need to first configure the NVIC_ISERx.

![NVIC vector table](./img/NVIC_vector_table.png)

### NVIC address
The NVIC registers are located in the Cortex M4 Internal Peripherals, so we need to refer to the Cortex-M4 Devices Generic User Guide.

![NVIC address](./img/NVIC_addr.png)

```c
// Cortex M4 Internal Peripherals
#define CORTEX_M4_INTERNAL_PERIPHERALS  (0xE0000000)

// NVIC
#define NVIC_OFFSET                     (0x0000E100)
#define NVIC_BASE                       GET_ADDR(CORTEX_M4_INTERNAL_PERIPHERALS + NVIC_OFFSET)
```

### NVIC_ISERx Register
There are 8 NVIC_ISER (0 ~ 7) registers, each with 32 bits. Since we want to enable NVIC_EXTI15_10 (Position 40), we need to set the 8th bit of NVIC_ISER1 to 1.
![NVIC_ISERx](./img/NVIC_ISERx.png)

```c
// Interrupt Set-enable Registers
#define NVIC_ISER_OFFSET     (0x00000000)
#define NVIC_ISER            GET_ADDR(NVIC_BASE + NVIC_ISER_OFFSET)

// NVIC_ISER0
#define NVIC_ISER0_OFFSET          0x00

#define READ_NVIC_ISERx(ISERx)                READ_REG_LWORD(NVIC_ISER, NVIC_ISER0_OFFSET + (ISERx)*4)
#define WRITE_NVIC_ISERx(ISERx, u32Value)     WRITE_REG_LWORD(NVIC_ISER, NVIC_ISER0_OFFSET + (ISERx)*4, READ_NVIC_ISERx(ISERx) | (u32Value))

#define SET_INTERRUPT_ENABLE(interrupt)       WRITE_NVIC_ISERx(NVIC_TABLE[interrupt] / 32, 1 << (NVIC_TABLE[interrupt] % 32))    

// NVIC trigger sourse
SET_INTERRUPT_ENABLE(NVIC_BUTTON_IRQ);
```

### EXTI Trigger Type
After enabling this IRQ, the next step is to select the trigger type. Since the user button is pressed low, the trigger should be set to falling mode. To set PIN13 to falling mode, you need to disable EXTI_RTSR and enable EXTI_FTSR.

![EXTI Trigger Type](./img/EXTI_RTSR_and_FTSR.png)

```c
// EXTI_RTSR (0x08)
#define EXTI_RTSR_OFFSET            0x08
#define READ_EXTI_RTSR()            READ_REG_LWORD(EXTI, EXTI_RTSR_OFFSET)
#define WRITE_EXTI_RTSR(u32Value)   WRITE_REG_LWORD(EXTI, EXTI_RTSR_OFFSET, u32Value)

// EXTI_FTSR (0x0C)
#define EXTI_FTSR_OFFSET            0x0C
#define READ_EXTI_FTSR()            READ_REG_LWORD(EXTI, EXTI_FTSR_OFFSET)
#define WRITE_EXTI_FTSR(u32Value)   WRITE_REG_LWORD(EXTI, EXTI_FTSR_OFFSET, u32Value)

// Set Trigger Type to Falling moode
#define SET_EXTI_FALLING_MODE(line) {                        \
    WRITE_EXTI_RTSR(READ_EXTI_RTSR() & (~(1 << line)));      \
    WRITE_EXTI_FTSR(READ_EXTI_FTSR() | (1 << (line)));       \
}

// EXTI trigger type
SET_EXTI_FALLING_MODE(PIN13);
```

### 