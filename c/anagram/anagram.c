#include "anagram.h"

enum anagram_status validate_candidate(const char *subject, const char *candidate, size_t subject_len) {
	size_t letter_pos = 0;
	int same_word = 1, *used_letters = calloc(subject_len, sizeof(int));

	for (size_t i = 0; letter_pos != subject_len && i < subject_len; i++) {
		for (letter_pos = 0; letter_pos < subject_len; letter_pos++) {
			if (used_letters[letter_pos] == 0 && tolower(subject[i]) == tolower(candidate[letter_pos])) {
				used_letters[letter_pos] = i + 1;
				break;
			}
		}
	}

	if (letter_pos != subject_len) {
		for (size_t i = 0; same_word == 1 && i < subject_len; i++) {
			if ((int)i != used_letters[i] - 1) {
				same_word = 0;
			}
		}
	}

	free(used_letters);
	return letter_pos != subject_len && same_word != 1 ? IS_ANAGRAM : NOT_ANAGRAM;
}

void find_anagrams(const char *subject, struct candidates *candidates) {
	size_t subject_len = strlen(subject);

	for (size_t i = 0; i < candidates->count; i++) {
		if (strlen(candidates->candidate[i].word) == subject_len) {
			candidates->candidate[i].is_anagram = 
				validate_candidate(subject, candidates->candidate[i].word, subject_len);
		} else {
			candidates->candidate[i].is_anagram = NOT_ANAGRAM;
		}
	}
}
