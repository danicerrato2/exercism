#ifndef WORDY_H
#define WORDY_H

#include <stdbool.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

bool answer(const char *question, int *result);

int ReadNumber(const char *question, int *i, char *operation, int *result);
int ReadOperation(const char *question, int *i, char *operation);

#endif
