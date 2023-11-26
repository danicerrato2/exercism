#include "all_your_base.h"

void clear_number(int8_t digits[]) {
	for (int i = 0; i < DIGITS_ARRAY_SIZE; i++) {
		digits[i] = 0;
	}
}

size_t rebase(
		int8_t digits[],
		int base_in,
		int base_out,
		size_t base_in_number_len) {

	int number = 0;
	size_t rebase_number_len;

	if (base_in_number_len == 0 || base_in <= 1 || base_out <= 1) {
		return 0;
	}

	for (size_t i = 0; i < base_in_number_len; i++) {
		if (digits[i] < 0 || digits[i] >= base_in) {
			return 0;
		}
		number = number * base_in + digits[i];
	}
	clear_number(digits);

	rebase_number_len = number == 0 ? 1 : log10(number) / log10(base_out) + 1;
	for (size_t i = rebase_number_len - 1; i > 0; i--) {
		digits[i] = number % base_out;
		number /= base_out;
	}
	digits[0] = number;
	
	return rebase_number_len;
}