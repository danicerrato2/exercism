#include "binary.h"

int convert(const char *input)
{
    int bin_digits = 0, value = 0;

    while (input[bin_digits] != 0){
        if (input[bin_digits] != '0' && input[bin_digits] != '1')
            return INVALID;
        bin_digits++;
    }

    for (int i = 0; i < bin_digits; i++)
        value += (input[bin_digits - i - 1] - '0') << i;

    return value;
}