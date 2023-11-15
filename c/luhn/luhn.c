#include "luhn.h"

bool luhn(const char *num) {
	int num_len, stripped_num_len, sum;
	int *stripped_num;
	bool valid_number = true;

	num_len = strlen(num);

	stripped_num = calloc(num_len, sizeof(int));
	stripped_num_len = 0;
	for (int i = 0; valid_number && i < num_len; i++) {
		if (num[i] >= '0' && num[i] <= '9') {
			stripped_num[stripped_num_len++] = num[i] - '0';
		} else if (num[i] != ' ') {
			valid_number = false;
		}
	}

	valid_number &= stripped_num_len >= 2;

	if (valid_number) {
		for (int i = stripped_num_len - 2; i >= 0; i -= 2) {
			stripped_num[i] = stripped_num[i] < 5 ? stripped_num[i] * 2 : stripped_num[i] * 2 - 9;
		}

		sum = 0;
		for (int i = 0; i < stripped_num_len; i++) {
			sum += stripped_num[i];
		}
	}

	free(stripped_num);
	return valid_number && sum % 10 == 0;
}