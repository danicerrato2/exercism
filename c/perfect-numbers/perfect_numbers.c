#include "perfect_numbers.h"

int classify_number(int number) {
	int divisor, quotient, sum;

	if (number <= 0) {
		return ERROR;
	}
	if (number == 1) {
		return DEFICIENT_NUMBER;
	}

	divisor = 2;
	quotient = number;
	sum = 1;
	while (divisor < quotient) {
		if (number % divisor == 0) {
			quotient = number / divisor;
			sum += quotient == divisor ? divisor : divisor + quotient;
		}
		divisor++;
	}

	if (sum > number) return ABUNDANT_NUMBER;
	if (sum < number) return DEFICIENT_NUMBER;
	return PERFECT_NUMBER;
}