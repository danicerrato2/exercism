#ifndef ETL_H
#define ETL_H

#include <stddef.h>

#include <malloc.h>
#include <ctype.h>

typedef struct {
   int value;
   const char *keys;
} legacy_map;

typedef struct {
   char key;
   int value;
} new_map;

int convert(const legacy_map *input, const size_t input_len, new_map **output);

void sort_output(new_map **output, int num_keys);

#endif
