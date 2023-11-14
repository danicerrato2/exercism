#ifndef SAY_H
#define SAY_H

#include <stdint.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

int say(int64_t input, char **ans);

int number_len(int64_t input);
int write_digits(char **ans, int64_t number, int is_hundred);

#endif
