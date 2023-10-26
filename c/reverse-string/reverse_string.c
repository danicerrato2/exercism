#include "reverse_string.h"

char *reverse(const char *value)
{
    if (!value)
        return 0;
    
    int size = 0;

    while (value[size] != 0)
        size++;

    char *reversed_string = (char *)malloc(size * sizeof(char));

    if (!reversed_string)
        return 0;

    for (int i = 0; i < size; i++)
        reversed_string[i] = value[size - 1 - i];

    return reversed_string;
}