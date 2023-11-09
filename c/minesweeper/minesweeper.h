#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <stddef.h>

#include <stdlib.h>

char **annotate(const char **minefield, const size_t rows);
void free_annotation(char **annotation);

char count_mines(const char **minefield, size_t row, size_t column, size_t rows);

#endif
