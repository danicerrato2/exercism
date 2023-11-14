#include "say.h"

char *g_units[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
char *g_first_tens[10] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
char *g_rest_tens[10] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
char *g_hundred = " hundred";
char *g_thousands[4] = {"", " thousand", " million", " billion"};

int number_len(int64_t input) {
	int len = 1;

	while (input > 9) {
		len++;
		input /= 10;
	}

	return len;
}

int write_digits(char **ans, int64_t number, int is_hundred) {
	int64_t tens, units;

	if (number == 0) {
		return 0;
	}

	if ((*ans)[0] != 0) {
		strcat(*ans, " ");
	}

	if (is_hundred) {
		strcat(*ans, g_units[number]);
	} else {
		tens = number / 10;
		units = number % 10;

		if (tens > 1) {
			strcat(*ans, g_rest_tens[tens]);
			if (units != 0) {
				strcat(*ans, "-");
				strcat(*ans, g_units[units]);
			}
		} else if (tens == 1) {
			strcat(*ans, g_first_tens[units]);
		} else {
			strcat(*ans, g_units[units]);
		}
	}

	return 1;
}

int say(int64_t input, char **ans) {
	int input_len;
	int64_t pow10;
	
	if (input < 0 || input > 999999999999) {
		return -1;
	}

	*ans = calloc(200, sizeof(char));

	if (input == 0) {
		strcat(*ans, g_units[0]);
		return 0;
	}

	input_len = number_len(input);
	for (int i = input_len - 1; i >= 0; i--) {
		pow10 = pow(10, i);
		if (i % 3 == 2 && write_digits(ans, input / pow10, 1) != 0) {
			strcat(*ans, g_hundred);
			input %= pow10;
		} else if (i % 3 == 0 && write_digits(ans, input / pow10, 0) != 0) {
			strcat(*ans, g_thousands[i / 3]);
			input %= pow10;
		}
	}

	return 0;
}