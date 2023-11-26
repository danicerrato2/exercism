#ifndef SCRABBLE_SCORE_H
#define SCRABBLE_SCORE_H

#include <ctype.h>

#define NUM_LETTERS 26
const int letter_points[NUM_LETTERS] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

unsigned int score(const char *word);

#endif
