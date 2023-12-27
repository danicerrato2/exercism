#include "atbash_cipher.h"

char *atbash_encode(const char *input) {
	char *encodedText;
	int inputLen, encodedLen;

	inputLen = strlen(input);
	encodedLen = inputLen + (inputLen / 5);
	encodedText = calloc(encodedLen + 1, sizeof(char));

	for (int i = 0, j = 0, groupLetters = 0; i < inputLen; i++) {
		if (isalnum(input[i])) {
			if (groupLetters != 0 && groupLetters % 5 == 0) {
				encodedText[j++] = ' ';
				groupLetters = 0;
			}
			encodedText[j++] = isalpha(input[i]) ? 'z' - (tolower(input[i]) - 'a') : input[i];
			groupLetters++;
		}
	}

	return encodedText;
}

char *atbash_decode(const char *input) {
	char *decodedText;
	int inputLen;

	inputLen = strlen(input);
	decodedText = calloc(inputLen, sizeof(char));

	for (int i = 0, j = 0; i < inputLen; i++) {
		if (isalnum(input[i])) {
			decodedText[j++] = isalpha(input[i]) ? 'z' - (tolower(input[i]) - 'a') : input[i];
		}
	}

	return decodedText;
}