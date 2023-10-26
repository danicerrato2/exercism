#include "clock.h"

clock_t clock_create(int hour, int minute)
{
    clock_t clock;

    if (minute > 0){
        hour += (int)minute / 60;
        minute %= 60;
    }
    while (minute < 0){
        minute += 60;
        hour--;
    }
    if (hour > 0)
        hour %= 24;
    while (hour < 0)
        hour += 24;

    clock.text[0] = '0' + (int)(hour / 10);
    clock.text[1] = '0' + hour % 10;
    clock.text[2] = ':';
    clock.text[3] = '0' + (int)(minute / 10);
    clock.text[4] = '0' + minute % 10;
    clock.text[5] = 0;

    return clock;
}


clock_t clock_add(clock_t clock, int minute_add)
{
    int hour = (clock.text[0] - '0') * 10 + (clock.text[1] - '0');
    int minute = (clock.text[3] - '0') * 10 + (clock.text[4] - '0');
    return clock_create(hour, minute + minute_add);
}


clock_t clock_subtract(clock_t clock, int minute_subtract)
{
    int hour = (clock.text[0] - '0') * 10 + (clock.text[1] - '0');
    int minute = (clock.text[3] - '0') * 10 + (clock.text[4] - '0');
    return clock_create(hour, minute - minute_subtract);
}


bool clock_is_equal(clock_t a, clock_t b)
{
    return strncmp(a.text, b.text, MAX_STR_LEN) == 0;
}
