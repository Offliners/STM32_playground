#ifndef _EXTI_COMMON_H_
#define _EXTI_COMMON_H_

#include "typedef.h"
#include "memorymap.h"

#define EXTI_OFFSET         (0x00003C00)
#define EXTI                GET_ADDR(PERIPHERAL_APB2_BASE + EXTI_OFFSET)


// EXTI_IMR (0x00)
#define EXTI_IMR_OFFSET             0x00
#define READ_EXTI_IMR()             READ_REG_LWORD(EXTI, EXTI_IMR_OFFSET)
#define WRITE_EXTI_IMR(u32Value)    WRITE_REG_LWORD(EXTI, EXTI_IMR_OFFSET, u32Value)


// EXTI_EMR (0x04)
#define EXTI_EMR_OFFSET             0x04
#define READ_EXTI_EMR()             READ_REG_LWORD(EXTI, EXTI_EMR_OFFSET)
#define WRITE_EXTI_EMR(u32Value)    WRITE_REG_LWORD(EXTI, EXTI_EMR_OFFSET, u32Value)


// EXTI_RTSR (0x08)
#define EXTI_RTSR_OFFSET            0x08
#define READ_EXTI_RTSR()            READ_REG_LWORD(EXTI, EXTI_RTSR_OFFSET)
#define WRITE_EXTI_RTSR(u32Value)   WRITE_REG_LWORD(EXTI, EXTI_RTSR_OFFSET, u32Value)


// EXTI_FTSR (0x0C)
#define EXTI_FTSR_OFFSET            0x0C
#define READ_EXTI_FTSR()            READ_REG_LWORD(EXTI, EXTI_FTSR_OFFSET)
#define WRITE_EXTI_FTSR(u32Value)   WRITE_REG_LWORD(EXTI, EXTI_FTSR_OFFSET, u32Value)


// EXTI_FTSR (0x14)
#define EXTI_PR_OFFSET              0x14
#define READ_EXTI_PR()              READ_REG_LWORD(EXTI, EXTI_PR_OFFSET)
#define WRITE_EXTI_PR(u32Value)     WRITE_REG_LWORD(EXTI, EXTI_PR_OFFSET, u32Value)


// Enable interrupt and event
#define ENABLE_EXTI_INTERRUPT_AND_EVENT(line) {             \
    WRITE_EXTI_IMR(READ_EXTI_IMR() | (1 << (line)));        \
    WRITE_EXTI_EMR(READ_EXTI_EMR() | (1 << (line)));        \
}


// Set Trigger Type to Rising moode
#define SET_EXTI_RISING_MODE(line) {                        \
    WRITE_EXTI_RTSR(READ_EXTI_RTSR() | (1 << (line)));      \
    WRITE_EXTI_FTSR(READ_EXTI_FTSR() & (~(1 << line)));     \
}

// Set Trigger Type to Falling moode
#define SET_EXTI_FALLING_MODE(line) {                        \
    WRITE_EXTI_RTSR(READ_EXTI_RTSR() & (~(1 << line)));      \
    WRITE_EXTI_FTSR(READ_EXTI_FTSR() | (1 << (line)));       \
}


// Check the EXTI flag set by EXTI interrupt
#define GET_EXTI_FLAG_STATUS(line)      (READ_EXTI_PR() & (1 << line))

// Clear the EXTI flag
#define CLEAR_EXTI_FLAG_STATUS(line)    (WRITE_EXTI_PR((1 << line)))

#endif