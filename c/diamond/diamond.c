#include "diamond.h"

char **make_diamond(const char letter) {
	char **diamond;
	int num_letters = letter - 'A' + 1, diamond_size = num_letters * 2 - 1;

	diamond = calloc(diamond_size + 1, sizeof(char *));
	for (int i = 0; i < diamond_size; i++) {
		diamond[i] = calloc(diamond_size + 1, sizeof(char));
		for (int j = 0; j < diamond_size; j++) {
			if (j == - i + (num_letters - 1) || j == i + (num_letters - 1)) {
				diamond[i][j] = 'A' + i;
			} else if (j == i - (num_letters - 1) || j == - i + ((diamond_size - 1) + (num_letters - 1))) {
				diamond[i][j] = 'A' + diamond_size - i - 1;
			} else {
				diamond[i][j] = ' ';
			}
		}
	}
	
	return diamond;
}

void free_diamond(char **diamond) {
	if (diamond) {
		for (int i = 0; diamond[i] != 0; i++) {
			free(diamond[i]);
		}
		free(diamond);
	}
}