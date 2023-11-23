#include "nth_prime.h"

int is_prime(uint32_t value) {
	if (value % 2 == 0) {
		return 0;
	}
	for (uint32_t divisor = 3, value_sqrt = sqrt(value); divisor <= value_sqrt; divisor += 2) {
		if (value % divisor == 0) {
			return 0;
		}
	}
	return 1;
}

uint32_t nth(uint32_t n) {
	uint32_t number;

	switch (n) {
		case 0:
			return 0;
		case 1:
			return 2;
		default:
			for (n -= 1, number = 3; n > 0 ; number += 2) {
				if (is_prime(number)) {
					n--;
				}
			}
	}
	return number - 2;
}
