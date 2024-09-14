#include "typedef.h"
#include "timer_func.h"

void timer_delay(LWORD time_us)
{
    for(LWORD i = 0; i < time_us; i++)
    {
        __asm__("nop");
    }
}