#include "typedef.h"
#include "gpio_common.h"
#include "timer_func.h"

BYTE timer_delay(LWORD u32_time_ms, BYTE u08_ospeedr)
{
    LWORD u32_delay_time_us = 0;
    switch(u08_ospeedr)
    {
        case LOW_SPEED_2MHZ:
            u32_delay_time_us = u32_time_ms * 2000000 / 1000;
            break;
        case MEDIUM_SPEED_25MHZ:
            u32_delay_time_us = u32_time_ms * 25000000 / 1000;
            break;
        case FAST_SPEED_50MHZ:
            u32_delay_time_us = u32_time_ms * 50000000 / 1000;
            break;
        case HIGH_SPEED_100MHZ:
            u32_delay_time_us = u32_time_ms * 100000000 / 1000;
            break;
        default:
            return FUNC_FAIL;
    }

    for(LWORD u32i = 0; u32i < u32_delay_time_us; u32i++)
    {
        __asm__("nop");
    }

    return FUNC_SUCCESS;
}