#include "armstrong_numbers.h"

bool is_armstrong_number(int candidate)
{
    int sum = 0, num_len = -1, candidate_copy = candidate;

    if (candidate < 0)
        return false;
    if (candidate == 0)
        return true;
    
    num_len = ceil(log10(candidate));
    while (candidate > 9)
    {
        sum += pow(floor(candidate % 10), num_len);
        candidate /= 10;
    }
    sum += pow(candidate, num_len);
    
    return candidate_copy == sum;
}