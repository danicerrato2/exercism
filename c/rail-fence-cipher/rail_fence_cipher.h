#ifndef RAIL_FENCE_CIPHER_H
#define RAIL_FENCE_CIPHER_H

#include <stddef.h>
#include <malloc.h>

char *encode(char *text, size_t rails);

char *decode(char *ciphertext, size_t rails);

#endif
