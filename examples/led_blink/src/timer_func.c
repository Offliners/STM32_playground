#include "typedef.h"
#include "gpio_common.h"
#include "timer_func.h"

BYTE timer_delay(LWORD time_ms, BYTE speed)
{
    LWORD delay_time_us = 0;
    switch(speed)
    {
        case LOW_SPEED_2MHZ:
            delay_time_us = time_ms * 2000000 / 1000;
            break;
        case MEDIUM_SPEED_25MHZ:
            delay_time_us = time_ms * 25000000 / 1000;
            break;
        case FAST_SPEED_50MHZ:
            delay_time_us = time_ms * 50000000 / 1000;
            break;
        case HIGH_SPEED_100MHZ:
            delay_time_us = time_ms * 100000000 / 1000;
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