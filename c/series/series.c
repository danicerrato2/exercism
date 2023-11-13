#include "series.h"

slices_t slices(char *input_text, unsigned int substring_length) {
	slices_t result;
	unsigned int input_len;

	input_len = strlen(input_text);
	if (input_len < substring_length || substring_length == 0) {
		return (slices_t) {.substring_count = 0, .substring = malloc(sizeof(char *))};
	}

	result.substring_count = input_len + 1 - substring_length;
	result.substring = malloc(result.substring_count * sizeof(char *));

	for (unsigned int i = 0; i < result.substring_count; i++) {
		result.substring[i] = calloc(substring_length + 1, sizeof(char));
		for (unsigned int j = 0; j < substring_length; j++) {
			result.substring[i][j] = input_text[i + j];
		}
	}

	return result;
}