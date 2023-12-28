#ifndef CRYPTO_SQUARE_H
#define CRYPTO_SQUARE_H

#include <string.h>
#include <malloc.h>
#include <ctype.h>

char *ciphertext(const char *input);

int NormalizeInput(const char *input, char *normalizedText, int inputLen);
void CalculateRowsAndColumns(int normalizedTextLen, int *rows, int *columns);
char **BrokeIntoRows(char *normalizedText, int normalizedTextLen, int *dimensions);
void GetCipheredText(char *cipheredText, char **squaredText, int *dimensions);

#endif
