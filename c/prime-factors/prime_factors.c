#include "prime_factors.h"

int is_prime(uint64_t value) {
	for (int divisor = 2, quotient = value; divisor < quotient; divisor++) {
		if (value % divisor == 0) {
			return 0;
		}
		quotient = value / divisor;
	}
	return 1;
}

size_t find_factors(uint64_t n, uint64_t factors[static MAXFACTORS]) {
	uint64_t prime_number = 2;
	int num_factors = 0;

	while (num_factors < MAXFACTORS && n > 1 && n % prime_number == 0) {
		factors[num_factors++] = prime_number;
		n /= prime_number;
	}

	prime_number = 3;
	while (num_factors < MAXFACTORS && n > 1) {
		while (num_factors < MAXFACTORS && n % prime_number == 0) {
			factors[num_factors++] = prime_number;
			n /= prime_number;
		}
		prime_number += 2;
		while (!is_prime(prime_number)) {
			prime_number += 2;
		}
	}

	return num_factors;
}