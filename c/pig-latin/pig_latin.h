#ifndef PIG_LATIN_H
#define PIG_LATIN_H

#include <malloc.h>

char *translate(const char *phrase);

int isvowel(char c);
void modify_word(const char *phrase, int *i, char *modified, int *j);

#endif
