#include "pig_latin.h"

#include <stdio.h>

int isvowel(char c)
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

void modify_word(const char *phrase, int *i, char *modified, int *j)
{
    int word_end = *i;

    while(phrase[word_end] >= 'a' && phrase[word_end] <= 'z')
        word_end++;

    if (isvowel(phrase[*i]) || \
        (phrase[*i] == 'y' && (phrase[*i + 1] == 0 || phrase[*i + 1] == 't')) || \
         (phrase[*i] == 'x' && phrase[*i + 1] != 0 && phrase[*i + 1] == 'r')){
            while(*i < word_end)
                modified[(*j)++] = phrase[(*i)++];
    }
    else {
        int word_init = *i;

        while (phrase[*i] != 0 && \
            ((!isvowel(phrase[*i]) && !(*i != word_init && phrase[*i] == 'y')) || \
             (phrase[*i] == 'u' && phrase[*i - 1] == 'q')))
                    (*i)++;
        for (int k = *i; k < word_end; k++)
            modified[(*j)++] = phrase[k];
        while (word_init < *i)
            modified[(*j)++] = phrase[word_init++];
        *i = word_end - 1;
    }
}

char *translate(const char *phrase)
{
    int phrase_len = 0, num_words = 0;
    char *modified = 0;
    
    if (!phrase)
        return 0;

    while (phrase[phrase_len] != 0){
        if (phrase[phrase_len] >= 'a' && phrase[phrase_len] <= 'z' && \
            (phrase_len == 0 || \
             phrase[phrase_len - 1] < 'a' || phrase[phrase_len -1] > 'z'))
                num_words++;
        phrase_len++;
    }

    modified = (char *)malloc((phrase_len + 1 + 2 * num_words) * sizeof(char));
    if (!modified)
        return 0;

    for (int i = 0, j = 0; i < phrase_len; i++){
        if (phrase[i] >= 'a' && phrase[i] <= 'z' && \
            (i == 0 || phrase[i - 1] < 'a' || phrase[i - 1] > 'z')){
                modify_word(phrase, &i, modified, &j);
                modified[j++] = 'a';
                modified[j++] = 'y';
        }
        else
            modified[j++] = phrase[i];
    }
    modified[phrase_len + 2 * num_words] = 0;

    return modified;
}