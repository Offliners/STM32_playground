#ifndef _GPIO_COMMON_H_
#define _GPIO_COMMON_H_

#include "memorymap.h"

#define GPIOA_OFFSET    (0x00000000)
#define GPIOA           GET_ADDR(PERIPHERAL_AHB1_BASE + GPIOA_OFFSET)

// GPIOx_MODER (0x00)
#define GPIO_MODER_OFFSET           0x00
#define INPUT_RESET_STATE           0x00
#define GENERAL_PURPOSE_OUTPUT_MODE 0x01
#define ALTERNATE_FUNCTION_MODE     0x10
#define ANALOG_MODE                 0x11

#define RESET_GPIOA_MODER_PATTERN   0xA8000000
#define RESET_GPIOA_MODER()                 WRITE_REG_LWORD(GPIOA, GPIO_MODER_OFFSET, RESET_GPIOA_MODER_PATTERN)
#define CLEAR_MODER(pin)                    (~((0x11) << (2 * (pin))))
#define CLEAR_GPIOX_MODER(gpiox, pin)       WRITE_REG_LWORD(gpiox, GPIO_MODER_OFFSET, READ_REG_LWORD(gpiox, GPIO_MODER_OFFSET) & CLEAR_MODER(pin))
#define SET_MODER(pin, moder)               ((moder) << (2 * (pin)))
#define SET_GPIOX_MODER(gpiox, pin, moder)  WRITE_REG_LWORD(gpiox, GPIO_MODER_OFFSET, READ_REG_LWORD(gpiox, GPIO_MODER_OFFSET) | SET_MODER(pin, moder))

// GPIOx_PUPDR (0x0C)
#define GPIO_PUPDR_OFFSET           0x0C
#define NO_PULL_UP_PULL_DOWN        0x00
#define PULL_UP                     0x01
#define PULL_DOWN                   0x10
#define PUPDR_RESERVED              0x11

#define RESET_GPIOA_PUDER_PATTERN   0x64000000
#define RESET_GPIOA_PUDER()                 WRITE_REG_LWORD(GPIOA, GPIO_PUPDR_OFFSET, RESET_GPIOA_PUDER_PATTERN)
#define CLEAR_PUPDR(pin)                    (~((0x11) << (2 * (pin))))
#define CLEAR_GPIOX_PUPDR(gpiox, pin)       WRITE_REG_LWORD(gpiox, GPIO_PUPDR_OFFSET, READ_REG_LWORD(gpiox, GPIO_PUPDR_OFFSET) & CLEAR_PUPDR(pin))
#define SET_PUPDR(pin, pupdr)               ((pupdr) << (2 * (pin)))
#define SET_GPIOX_PUPDR(gpiox, pin, pupdr)  WRITE_REG_LWORD(gpiox, GPIO_PUPDR_OFFSET, READ_REG_LWORD(gpiox, GPIO_PUPDR_OFFSET) | SET_PUPDR(pin, pupdr))

// GPIOx_ODR (0x14)
#define GPIO_ODR_OFFSET           0x14

// GPIO set/clear/toggle
#define SET_GPIOX(gpiox, pin)               WRITE_REG_LWORD(gpiox, GPIO_ODR_OFFSET, READ_REG_LWORD(gpiox, GPIO_ODR_OFFSET) | (0x1 << (pin)))
#define CLEAR_GPIOX(gpiox, pin)             WRITE_REG_LWORD(gpiox, GPIO_ODR_OFFSET, READ_REG_LWORD(gpiox, GPIO_ODR_OFFSET) & (~(0x1 << (pin))))
#define TOGGLE_GPIOX(gpiox, pin)            WRITE_REG_LWORD(gpiox, GPIO_ODR_OFFSET, READ_REG_LWORD(gpiox, GPIO_ODR_OFFSET) ^ (0x1 << (pin)))

#endif