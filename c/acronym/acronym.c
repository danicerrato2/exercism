#include "acronym.h"

char *abbreviate(const char *phrase)
{
    char *acronym = NULL;
    int num_letters = 0;

    if (!phrase)
        return 0;

    for (int i = 0; phrase[i] != 0; i++)
        if (i != 0 && isalpha(phrase[i]) && !isalpha(phrase[i - 1]) && phrase[i - 1] != '\'')
            num_letters++;

    if (num_letters == 0)
        return 0;

    acronym = (char *)calloc(num_letters + 2, sizeof(char));
    if (!acronym)
        return 0;

    num_letters = 0;
    if (isalpha(phrase[0]))
        acronym[num_letters++] = phrase[0];
    for (int i = 0; phrase[i] != 0; i++)
        if (i != 0 && isalpha(phrase[i]) && !isalpha(phrase[i - 1]) && phrase[i - 1] != '\'')
            acronym[num_letters++] = toupper(phrase[i]);

    return acronym;
}