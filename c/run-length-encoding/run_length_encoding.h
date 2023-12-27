#ifndef RUN_LENGTH_ENCODING_H
#define RUN_LENGTH_ENCODING_H

#include <string.h>
#include <malloc.h>
#include <stdio.h>

char *encode(const char *text);
char *decode(const char *data);

#endif
