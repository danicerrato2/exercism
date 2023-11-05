#include "bob.h"

#define QUESTION "Sure."
#define YELL "Whoa, chill out!"
#define YELL_QUESTION "Calm down, I know what I'm doing!"
#define SILENT "Fine. Be that way!"
#define ANYTHING_ELSE "Whatever."

int isSpace(char character) {
	return character == ' ' || character == '\t' || character == '\r' || character == '\n';
}

char *answer(int isQuestion, int hasLetters, int allCapitals, int isSilent) {
	if (isSilent) {
		return SILENT;
	}
	if (isQuestion && hasLetters && allCapitals) {
		return YELL_QUESTION;
	}
	if (hasLetters && allCapitals) {
		return YELL;
	}
	if (isQuestion) {
		return QUESTION;
	}
	return ANYTHING_ELSE;
}

char *hey_bob(char *greeting) {
	int isQuestion = 0, hasLetters = 0, allCapitals = 1, isSilent = 1;
	int i = 0;

	for (; greeting[i] != 0; i++) {
		if ((hasLetters == 0 || allCapitals == 1) && greeting[i] >= 'a' && greeting[i] <= 'z') {
			allCapitals = 0;
			hasLetters = 1;
		} else if (hasLetters == 0 && greeting[i] >= 'A' && greeting[i] <= 'Z') {
			hasLetters = 1;
		}
		if (!isSpace(greeting[i])) {
			isSilent = 0;
		}
	}
	i--;
	while (i >= 0 && isSpace(greeting[i])) {
		i--;
	}
	if (i >= 0 && greeting[i] == '?') {
		isQuestion = 1;
	}

	return answer(isQuestion, hasLetters, allCapitals, isSilent);
}