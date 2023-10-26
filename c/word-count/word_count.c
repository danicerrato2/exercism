#include "word_count.h"

int __strncmp(const char *sentence_word, char *saved_word, int sentence_word_size)
{
    int i;

    for (i = 0; i < sentence_word_size && saved_word[i] != 0; i++)
        if (tolower(sentence_word[i]) != saved_word[i])
            return -1;
    if ((i == sentence_word_size && saved_word[i] != 0) || i != sentence_word_size)
        return -1;
    return 0;
}


void __strncpy(char *dest, const char *word, int word_size)
{
    for (int i = 0; i < word_size; i++)
        dest[i] = tolower(word[i]);
    dest[word_size] = 0;
}



int count_words(const char *sentence, word_count_word_t *words)
{
    int num_words = 0, from = 0, word_size = 0, i = 0;

    if (!sentence || !words)
        return 0;

    while (1){
        while (sentence[from] != 0 && !isalnum(sentence[from]))
            from++;

        if (sentence[from] == 0)
            break;
        
        word_size = from + 1;
        while (sentence[word_size] != 0 && (isalnum(sentence[word_size]) || (sentence[word_size] == '\'' && isalpha(sentence[word_size + 1]))))
            word_size++;
        
        word_size -= from;
        if (word_size > MAX_WORD_LENGTH)
            return EXCESSIVE_LENGTH_WORD;

        for (i = 0; i < num_words; i++){
            if (__strncmp(sentence + from, words[i].text, word_size) == 0){
                words[i].count++;
                break;
            }
        }

        if (i == num_words){
            num_words++;
            if (num_words > MAX_WORDS)
                return EXCESSIVE_NUMBER_OF_WORDS;
            __strncpy(words[i].text, sentence + from, word_size);
            words[i].count = 1;
        }
    
        from += word_size;
    }

    return num_words;
}