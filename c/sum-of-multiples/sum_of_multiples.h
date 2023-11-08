#ifndef SUM_OF_MULTIPLES_H
#define SUM_OF_MULTIPLES_H

#include <stddef.h>

#include <stdlib.h>

unsigned int sum(const unsigned int *factors, const size_t number_of_factors, const unsigned int limit);

int is_in_set(unsigned int *set, unsigned int value, size_t set_size);

#endif
