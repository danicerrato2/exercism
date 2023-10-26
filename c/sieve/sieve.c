#include "sieve.h"

uint32_t sieve(uint32_t limit, uint32_t *primes, size_t max_primes)
{
    if (limit < 2)
        return 0;
    
    int numbers[limit];
    uint32_t num_primes = 0;

    for (uint32_t i = 0; i < limit; i++)
        numbers[i] = 1;
    numbers[0] = 0;

    for (uint32_t number = 2; number <= limit; number++){
        if (numbers[number - 1] == 0)
            continue;
        for (uint32_t i = 2; i * number <= limit; i++)
            numbers[number * i - 1] = 0;
        primes[num_primes++] = number;
    }

    if (num_primes > max_primes)
        return max_primes;
    return num_primes;
}