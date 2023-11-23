#include "sublist.h"

int compare_list(int *biggest, int *smallest, size_t biggest_size, size_t smallest_size) {
	size_t i, j;

	for (i = 0; i < biggest_size; i++) {
		j = 0;
		while (i + j < biggest_size
				&& j < smallest_size
				&& biggest[i + j] == smallest[j]) {
			j++;
		}
		if (j == smallest_size) {
			if (i + j == biggest_size && i == 0) {
				return 0;
			}
			if (i + j < biggest_size || i != 0) {
				return 1;
			}
		}
	}
	return -1;
}

comparison_result_t check_lists(
		int *list_to_compare,
		int *base_list,
		size_t list_to_compare_element_count,
		size_t base_list_element_count) {

	int result = -1;

	if (base_list_element_count == 0) {
		return list_to_compare_element_count > 0 ? SUPERLIST : EQUAL;
	}
	if (list_to_compare_element_count == 0) {
		return SUBLIST;
	}

	if (base_list_element_count >= list_to_compare_element_count) {
		result = compare_list(base_list, list_to_compare, base_list_element_count, list_to_compare_element_count);
		if (result == 1) {
			return SUBLIST;
		}
	} else {
		result = compare_list(list_to_compare, base_list, list_to_compare_element_count, base_list_element_count);
		if (result == 1) {
			return SUPERLIST;
		}
	}

	return result == 0 ? EQUAL : UNEQUAL;
}