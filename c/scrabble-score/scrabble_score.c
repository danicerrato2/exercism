#include "scrabble_score.h"

const int letter_points[NUM_LETTERS] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

unsigned int score(const char *word) {
	unsigned int score = 0;

	for (int i = 0; word[i] != 0; i++) {
		score += letter_points[tolower(word[i]) - 'a']; 
	}

	return score;
}