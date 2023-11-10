#include "etl.h"

void sort_output(new_map **output, int num_keys) {
	new_map aux_map;

	for (; num_keys > 0; num_keys--) {
		for (int i = 0; i < num_keys - 1; i++) {
			if ((*output)[i].key > (*output)[i + 1].key) {
				aux_map = (*output)[i];
				(*output)[i] = (*output)[i + 1];
				(*output)[i + 1] = aux_map;
			}
		}
	}
}

int convert(const legacy_map *input, const size_t input_len, new_map **output) {
	int num_new_keys = 0;

	if (input_len == 0) {
		return 0;
	}

	for (size_t i = 0; i < input_len; i++) {
		while (input[i].keys[num_new_keys] != 0) {
			num_new_keys++;
		}
	}

	*output = malloc(num_new_keys * sizeof(new_map));
	num_new_keys = 0;
	for (size_t i = 0; i < input_len; i++) {
		for (int j = 0; input[i].keys[j] != 0; j++, num_new_keys++) {
			(*output)[num_new_keys].value = input[i].value;
			(*output)[num_new_keys].key = tolower(input[i].keys[j]);
		}
	}

	sort_output(output, num_new_keys);
	
	return num_new_keys;
}