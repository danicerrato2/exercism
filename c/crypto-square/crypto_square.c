#include "crypto_square.h"

char *ciphertext(const char *input) {
	int inputLen, normalizedTextLen, dimensions[2];
	char *normalizedText, **squaredText, *cipheredText;

	inputLen = strlen(input);
	normalizedText = calloc(inputLen + 1, sizeof(char));
	if (inputLen == 0) {
		return normalizedText;
	}

	normalizedTextLen = NormalizeInput(input, normalizedText, inputLen);
	if (normalizedTextLen == 0) {
		return normalizedText;
	}

	CalculateRowsAndColumns(normalizedTextLen, &dimensions[0], &dimensions[1]);
	cipheredText = calloc((dimensions[0] + 1) * dimensions[1], sizeof(char));
	if (dimensions[0] == 0 || dimensions[1] == 0) {
		return cipheredText;
	}

	squaredText = BrokeIntoRows(normalizedText, normalizedTextLen, dimensions);
	GetCipheredText(cipheredText, squaredText, dimensions);

	free(normalizedText);
	for (int i = 0; i < dimensions[0]; i++) {
		free(squaredText[i]);
	}
	free(squaredText);

	return cipheredText;
}

int NormalizeInput(const char *input, char *normalizedText, int inputLen) {
	int j = 0;

	for (int i = 0; i < inputLen; i++) {
		if (isalnum(input[i])) {
			normalizedText[j++] = tolower(input[i]);
		}
	}

	return j;
}

void CalculateRowsAndColumns(int normalizedTextLen, int *rows, int *columns) {
	int foundedColumns = 0;

	for (int c = 1; foundedColumns == 0 && c <= normalizedTextLen; c++) {
		for (int r = c - 1; foundedColumns == 0 && r <= c; r++) {
			if (r * c >= normalizedTextLen) {
				*rows = r;
				*columns = c;
				foundedColumns = 1;
			}
		}
	}
}

char **BrokeIntoRows(char *normalizedText, int normalizedTextLen, int *dimensions) {
	char **squaredText = calloc(dimensions[0], sizeof(char *));
	
	for (int i = 0; i < dimensions[0]; i++) {
		squaredText[i] = calloc(dimensions[1] + 1, sizeof(char));
		for (int j = 0; j < dimensions[1]; j++) {
			squaredText[i][j] = i * dimensions[1] + j < normalizedTextLen ? normalizedText[i * dimensions[1] + j] : ' ';
		}
	}

	return squaredText;
}

void GetCipheredText(char *cipheredText, char **squaredText, int *dimensions) {
	int k = 0;

	for (int j = 0; j < dimensions[1]; j++) {
		for (int i = 0; i < dimensions[0]; i++) {
			cipheredText[k++] = squaredText[i][j];
		}
		if (j + 1 < dimensions[1]) {
			cipheredText[k++] = ' ';
		}
	}
}