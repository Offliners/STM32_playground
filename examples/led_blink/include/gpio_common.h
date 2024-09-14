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


// GPIOx_OTYPER (0x04)
#define GPIO_OTYPER_OFFSET          0x04
#define OUTPUT_PUSH_PULL            0x0
#define OUTPUT_OPEN_DRAIN           0x1

#define RESET_GPIOX_OTYPER_PATTERN  0x00000000
#define RESET_GPIOA_OTYPER()                WRITE_REG_LWORD(GPIOA, GPIO_OTYPER_OFFSET, RESET_GPIOX_OTYPER_PATTERN)
#define SET_GPIOX_OTYPER_PP(gpiox, pin)     WRITE_REG_LWORD(GPIOA, GPIO_OTYPER_OFFSET, READ_REG_LWORD(gpiox, GPIO_OTYPER_OFFSET) & (~(OUTPUT_PUSH_PULL << (pin))))
#define SET_GPIOX_OTYPER_OD(gpiox, pin)     WRITE_REG_LWORD(GPIOA, GPIO_OTYPER_OFFSET, READ_REG_LWORD(gpiox, GPIO_OTYPER_OFFSET) | (OUTPUT_OPEN_DRAIN << (pin)))


// GPIOx_OSPEEDR (0x08)
#define GPIO_OSPEEDR_OFFSET         0x08
#define LOW_SPEED_2MHZ              0x00
#define MEDIUM_SPEED_25MHZ          0x01
#define FAST_SPEED_50MHZ            0x10
#define HIGH_SPEED_100MHZ           0x11

#define RESET_GPIOX_OSPEEDR_PATTERN 0x00000000
#define RESET_GPIOA_OSPEEDR()                   WRITE_REG_LWORD(GPIOA, GPIO_OSPEEDR_OFFSET, RESET_GPIOX_OSPEEDR_PATTERN)
#define CLEAR_OSPEEDR(pin)                      (~((0x11) << (2 * (pin))))
#define CLEAR_GPIOX_OSPEEDR(gpiox, pin)         WRITE_REG_LWORD(gpiox, GPIO_OSPEEDR_OFFSET, READ_REG_LWORD(gpiox, GPIO_OSPEEDR_OFFSET) & CLEAR_OSPEEDR(pin))
#define SET_OSPEEDR(pin, speed)                 ((speed) << (2 * (pin)))
#define SET_GPIOX_OSPEEDR(gpiox, pin, speed)    WRITE_REG_LWORD(gpiox, GPIO_OSPEEDR_OFFSET, READ_REG_LWORD(gpiox, GPIO_OSPEEDR_OFFSET) | SET_OSPEEDR(pin, speed))
#define GET_SPPEDR(gpiox, pin)                  ((READ_REG_LWORD(gpiox, GPIO_OSPEEDR_OFFSET) & (0x11 << (2 * (pin)))) >> (2 * (pin)))


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