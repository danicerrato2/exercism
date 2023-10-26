#ifndef PHONE_NUMBER_H
#define PHONE_NUMBER_H

#include <stdlib.h>

char *phone_number_clean(const char *input);
char *check_number(char *phone_number, int num_digits, const char *input);

#endif
