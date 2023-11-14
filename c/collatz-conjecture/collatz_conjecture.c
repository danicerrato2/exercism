#include "collatz_conjecture.h"

int steps(int start) {
	int steps;

	if (start <= 0) {
		return ERROR_VALUE;
	}

	for (steps = 0; start != 1; steps++) {
		start = start % 2 == 0 ? start / 2 : 3 * start + 1;
	}

	return steps;
}
