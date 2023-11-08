#include "sum_of_multiples.h"

int is_in_set(unsigned int *set, unsigned int value, size_t set_size) {
    int is_in_set = 0;

    for (size_t i = 0; i < set_size && is_in_set == 0; i++) {
        if (set[i] == value) {
            is_in_set = 1;
        }
    }

    return is_in_set;
}

unsigned int sum(const unsigned int *factors, const size_t number_of_factors, const unsigned int limit) {
    unsigned int *multiples_set, energy_points = 0;
    int total_multiples = 0;

    for (size_t i = 0; i < number_of_factors; i++) {
        if (factors[i] != 0) {
            total_multiples += (limit - 1) / factors[i];
        }
    }

    multiples_set = calloc(total_multiples, sizeof(unsigned int));
    total_multiples = 0;
    for (size_t i = 0; i < number_of_factors; i++) {
        unsigned int factor = factors[i];
        for (; factor != 0 && factor < limit; factor += factors[i], total_multiples++) {
            multiples_set[total_multiples] = is_in_set(multiples_set, factor, total_multiples) ? 0 : factor;
        }
    }

    for (int i = 0; i < total_multiples; i++) {
        energy_points += multiples_set[i];
    }

    free(multiples_set);

    return energy_points;
}