#include "minesweeper.h"

char count_mines(const char **minefield, size_t row, size_t column, size_t rows) {
	int mines = 0;

	if (row > 0 && column > 0 && minefield[row - 1][column - 1] == '*')
		mines++;
	if (row > 0 && minefield[row - 1][column] == '*')
		mines++;
	if (row > 0 && minefield[row - 1][column + 1] != 0 && minefield[row - 1][column + 1] == '*')
		mines++;
	if (column > 0 && minefield[row][column - 1] == '*')
		mines++;
	if (minefield[row][column + 1] != 0 && minefield[row][column + 1] == '*')
		mines++;
	if (row + 1 < rows && column > 0 && minefield[row + 1][column - 1] == '*')
		mines++;
	if (row + 1 < rows && minefield[row + 1][column] == '*')
		mines++;
	if (row + 1 < rows && minefield[row + 1][column + 1] != 0 && minefield[row + 1][column + 1] == '*')
		mines++;
	
	return mines == 0 ? ' ' : '0' + mines;
}

char **annotate(const char **minefield, const size_t rows) {
	size_t columns = 0;
	char **annotation;

	if (rows == 0) {
		return NULL;
	}

	while (minefield[0][columns] != 0) {
		columns++;
	}

	annotation = calloc(rows + 1, sizeof(char *));
	for (size_t i = 0; i < rows; i++) {
		annotation[i] = calloc(columns + 1, sizeof(char));
		for (size_t j = 0; j < columns; j++) {
			annotation[i][j] = minefield[i][j] == ' ' ? count_mines(minefield, i, j, rows) : minefield[i][j];
		}
	}

	return annotation;
}

void free_annotation(char **annotation) {
	if (annotation) {
		for (int i = 0; annotation[i] != 0; i++) {
			free(annotation[i]);
		}
		free(annotation);
	}
}
