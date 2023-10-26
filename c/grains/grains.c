#include "grains.h"

uint64_t square(uint8_t index)
{
    if (index == 0)
        return 0;
    return pow(2, index - 1);
}


uint64_t total(void)
{
    return square(65ull) - 1;
}