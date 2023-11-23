#include "palindrome_products.h"

factor_t *get_factors(int value, int from, int to) {
	factor_t *factor, *aux;

	factor = calloc(1, sizeof(factor_t));
	aux = factor;
	for (int divisor = from, quotient = to; divisor < quotient; divisor++) {
		quotient = value / divisor;
		if (quotient <= to && value % divisor == 0) {
			aux->factor_a = divisor;
			aux->factor_b = quotient;
			aux->next = calloc(1, sizeof(factor_t));
			aux = aux->next;
		}
	}

	return factor;
}

int is_palindrome(int value) {
	int is_valid = 1;

	if (value >= 0 && value <= 9) {
		return is_valid;
	}

	for (int pow10, num_digits = log10(value) + 1; is_valid && num_digits > 1; num_digits -= 2) {
		pow10 = pow(10, num_digits - 1);
		if (value / pow10 == value % 10) {
			value %= pow10;
			value /= 10;
		} else {
			is_valid = 0;
		}
	}

	return is_valid;
}

product_t *get_palindrome_product(int from, int to) {
	product_t *product = calloc(1, sizeof(product_t));
	int distance, min_value, max_value;

	if (from > to) {
		sprintf(product->error, "invalid input: min is %d and max is %d", from, to);
		return product;
	}

	product->largest = 0;
	product->smallest = to * to + 1;

	distance = to - from;
	for (int i = 0; i <= distance; i++) {
		for (int j = 0; from + i <= to - j && j <= i; j++) {
			min_value =	(from + i) * (from + j);
			max_value = (to - i) * (to - j);
			if (is_palindrome(min_value)) {
				if (min_value < product->smallest) {
					product->smallest = min_value;
				}
				if (min_value > product->largest) {
					product->largest = min_value;	
				}
			}
			if (is_palindrome(max_value)) {
				if (max_value < product->smallest) {
					product->smallest = max_value;
				}
				if (max_value > product->largest) {
					product->largest = max_value;	
				}
			}
		}
	}

	if (product->largest == 0) {
		sprintf(product->error, "no palindrome with factors in the range %d to %d", from, to);
		return product;
	}

	product->factors_sm = get_factors(product->smallest, from, to);
	product->factors_lg = get_factors(product->largest, from, to);

	return product;
}

void free_product(product_t *p) {
	factor_t *aux, *aux2;
	if (p) {
		aux = p->factors_lg;
		while (aux != NULL) {
			aux2 = aux->next;
			free(aux);
			aux = aux2;
		}
		aux = p->factors_sm;
		while (aux != NULL) {
			aux2 = aux->next;
			free(aux);
			aux = aux2;
		}
		free(p);
	}
}