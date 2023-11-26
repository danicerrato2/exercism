#ifndef ALL_YOUR_BASE_H
#define ALL_YOUR_BASE_H

#include <stddef.h>
#include <stdint.h>
#include <math.h>

#define DIGITS_ARRAY_SIZE 64

size_t rebase(
		int8_t digits[],
		int base_in,
		int base_out,
		size_t base_in_number_len);

void clear_number(int8_t digits[]);

#endif
