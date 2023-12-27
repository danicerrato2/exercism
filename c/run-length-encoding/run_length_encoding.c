#include "run_length_encoding.h"

char *encode(const char *text) {
	char lastChar[1], *encodedText, *toConcat;
	int numRepetitions, textSize, i;

	textSize = strlen(text);
	encodedText = calloc(textSize, sizeof(char));
	toConcat = calloc(textSize, sizeof(char));

	i = 0;
	while (i < textSize) {
		lastChar[0] = text[i];
		numRepetitions = 0;
		while (i < textSize && text[i] == lastChar[0]) {
			numRepetitions++;
			i++;
		}
		if (numRepetitions == 1) {
			sprintf(toConcat, "%c", lastChar[0]);
		} else {
			sprintf(toConcat, "%d%c", numRepetitions, lastChar[0]);
		}
		strcat(encodedText, toConcat);
	}

	return encodedText;
}

char *decode(const char *data) {
	char *decodedData;
	int numRepetitions, i, currentSize;

	decodedData = calloc(1, sizeof(char));

	i = 0;
	currentSize = 0;
	while (data[i] != 0) {
		numRepetitions = 0;
		while (data[i] >= '0' && data[i] <= '9') {
			numRepetitions = numRepetitions * 10 + data[i] - '0'; 
			i++;
		}
		decodedData = realloc(decodedData, (currentSize + numRepetitions + 1) * sizeof(char));
		for (int j = 0; j < numRepetitions - 1; j++) {
			decodedData[currentSize++] = data[i];
		}
		decodedData[currentSize++] = data[i];
		i++;
	}

	return decodedData;
}