#ifndef ATBASH_CIPHER_H
#define ATBASH_CIPHER_H

#include <malloc.h>
#include <string.h>
#include <ctype.h>

char *atbash_encode(const char *input);
char *atbash_decode(const char *input);

#endif
