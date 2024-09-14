## Led blink
This example toggles GPIOA to make the LED on the STM32 board blink every second

### Memory Map
First, locate the base address of AHB1 in the memory map.

```c
#define GET_ADDR(x) (x)

#define PERIPHERAL_BASE         (0x40000000)
#define AHB1_OFFSET             (0x00020000)
#define PERIPHERAL_AHB1_BASE    GET_ADDR(PERIPHERAL_BASE + AHB1_OFFSET)
```

![AHB1 addr](./img/AHB1_addr.png)

## General-purpose Input/Output (GPIO)
### GPIOA Address
Next, find the address of GPIOA in AHB1.

```c
#define GPIOA_OFFSET    (0x00000000)
#define GPIOA           GET_ADDR(PERIPHERAL_AHB1_BASE + GPIOA_OFFSET)
```

![GPIOA addr](./img/GPIOA_addr.png)

### GPIO Register - MODER
Initialize MODER of GPIOA, then set MODER5 (pin5) to General purpose output mode.

![GPIOA MODER Register](./img/GPIOA_moder_reg.png)
```c
// GPIOx_MODER (0x00)
#define GPIO_MODER_OFFSET           0x00
#define INPUT_RESET_STATE           0x00
#define GENERAL_PURPOSE_OUTPUT_MODE 0x01
#define ALTERNATE_FUNCTION_MODE     0x10
#define ANALOG_MODE                 0x11

#define CLEAR_MODER(pin)                    (~((0x11) << (2 * (pin))))
#define CLEAR_GPIOX_MODER(gpiox, pin)       WRITE_REG_LWORD(gpiox, GPIO_MODER_OFFSET, READ_REG_LWORD(gpiox, GPIO_MODER_OFFSET) & CLEAR_MODER(pin))
#define SET_MODER(pin, moder)               ((moder) << (2 * (pin)))
#define SET_GPIOX_MODER(gpiox, pin, moder)  WRITE_REG_LWORD(gpiox, GPIO_MODER_OFFSET, READ_REG_LWORD(gpiox, GPIO_MODER_OFFSET) | SET_MODER(pin, moder))

CLEAR_GPIOX_MODER(GPIO_LED_PORT, PIN5);
SET_GPIOX_MODER(GPIO_LED_PORT, PIN5, GENERAL_PURPOSE_OUTPUT_MODE);
```

### GPIO Register - PUDER
Initialize PUDER of GPIOA, then set MODER5 (pin5) to General purpose output mode.

![GPIOA PUDER Register](./img/GPIOA_puder_reg.png)

```c
// GPIOx_PUPDR (0x0C)
#define GPIO_PUPDR_OFFSET           0x0C
#define NO_PULL_UP_PULL_DOWN        0x00
#define PULL_UP                     0x01
#define PULL_DOWN                   0x10
#define PUPDR_RESERVED              0x11

#define CLEAR_PUPDR(pin)                    (~((0x11) << (2 * (pin))))
#define CLEAR_GPIOX_PUPDR(gpiox, pin)       WRITE_REG_LWORD(gpiox, GPIO_PUPDR_OFFSET, READ_REG_LWORD(gpiox, GPIO_PUPDR_OFFSET) & CLEAR_PUPDR(pin))
#define SET_PUPDR(pin, pupdr)               ((pupdr) << (2 * (pin)))
#define SET_GPIOX_PUPDR(gpiox, pin, pupdr)  WRITE_REG_LWORD(gpiox, GPIO_PUPDR_OFFSET, READ_REG_LWORD(gpiox, GPIO_PUPDR_OFFSET) | SET_PUPDR(pin, pupdr))

CLEAR_GPIOX_PUPDR(GPIO_LED_PORT, PIN5);
SET_GPIOX_PUPDR(GPIO_LED_PORT, PIN5, NO_PULL_UP_PULL_DOWN);
```

### GPIO Register - GPIOx_ODR
To toggle the LED, it is necessary to read the value of this register and perform an XOR operation.

![GPIOA OD Register](./img/GPIOA_odr.png)

```c
#define GPIO_ODR_OFFSET           0x14

#define TOGGLE_GPIOX(gpiox, pin)            WRITE_REG_LWORD(gpiox, GPIO_ODR_OFFSET, READ_REG_LWORD(gpiox, GPIO_ODR_OFFSET) ^ (0x1 << (pin)))
```

## Reset and Clock Control (RCC)
### RCC Address
Find the address of RCC in AHB1.

```c
#define RCC_OFFSET      (0x00003800)
#define RCC             GET_ADDR(PERIPHERAL_AHB1_BASE + RCC_OFFSET)
```

![RCC Address](./img/RCC_addr.png)

### RCC Register - RCC_AHB1ENR
Enable RCC GPIOA.

![AHB1 RCC](./img/AHB1_RCC.png)

```c
#define RCC_GPIOA_ENABLE(gpiox)     WRITE_REG_LWORD(RCC, RCC_AHB1ENR_OFFSET, READ_REG_LWORD(RCC, RCC_AHB1ENR_OFFSET) | (GPIOX_ENABLE << RCC_GPIOX_TABLE[RCC_GPIOA]))
#define RCC_GPIOA_DISABLE(gpiox)    WRITE_REG_LWORD(RCC, RCC_AHB1ENR_OFFSET, READ_REG_LWORD(RCC, RCC_AHB1ENR_OFFSET) & (~(GPIOX_ENABLE << RCC_GPIOX_TABLE[RCC_GPIOA])))
```

## Delay Function

```c
BYTE timer_delay(LWORD time_ms, BYTE speed)
{
    LWORD delay_time_us = 0;
    switch(speed)
    {
        case LOW_SPEED_2MHZ:
            delay_time_us = time_ms * 2000000 / 1000;
            break;
        case MEDIUM_SPEED_25MHZ:
            delay_time_us = time_ms * 2500000 / 1000;
            break;
        case FAST_SPEED_50MHZ:
            delay_time_us = time_ms * 5000000 / 1000;
            break;
        case HIGH_SPEED_100MHZ:
            delay_time_us = time_ms * 10000000 / 1000;
            break;
        default:
            return FUNC_FAIL;
    }

    for(LWORD i = 0; i < delay_time_us; i++)
    {
        __asm__("nop");
    }

    return FUNC_SUCCESS;
}

u08Ret |= timer_delay(1000, GET_SPPEDR(GPIO_LED_PORT, PIN5));
```