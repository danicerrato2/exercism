#include "largest_series_product.h"

int only_numbers(char *digits, size_t numDigits) {
	for (size_t i = 0; i < numDigits; i++) {
		if (digits[i] < '0' || digits[i] > '9') {
			return 0;
		}
	}
	return 1;
}

int64_t largest_series_product(char *digits, size_t span) {
	int64_t largest = 0, currentProduct;
	size_t numDigits = strlen(digits);

	if (numDigits < span || !only_numbers(digits, numDigits)) {
		return -1;
	}

	for (size_t i = 0; i <= numDigits - span; i++) {
		currentProduct = 1;
		for (size_t j = 0; j < span; j++) {
			currentProduct *= digits[i + j] - '0';
		}
		if (currentProduct > largest) {
			largest = currentProduct;
		}
	}

	return largest;
}