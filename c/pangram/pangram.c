#include "pangram.h"

#define NUM_LETTERS 26

bool is_pangram(const char *sentence)
{   
    bool used_letters[NUM_LETTERS], all_used = true;

    if (!sentence)
        return false;
    
    for (int i = 0; i < NUM_LETTERS; i++)
        used_letters[i] = false;

    for (int i = 0; sentence[i] != 0; i++)
        if (sentence[i] >= 'a' && sentence[i] <= 'z')
            used_letters[sentence[i] - 'a'] = true;
        else if (sentence[i] >= 'A' && sentence[i] <= 'Z')
            used_letters[sentence[i] - 'A'] = true;

    for (int i = 0; i < NUM_LETTERS; i++)
        all_used &= used_letters[i];

    return all_used;
}