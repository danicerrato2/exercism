#include "gigasecond.h"

time_t gigasecond_after(time_t init_time)
{
    return init_time + (time_t)1000000000;
}