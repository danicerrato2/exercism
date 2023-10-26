#include "rail_fence_cipher.h"

char *encode(char *text, size_t rails)
{
    if (!text || rails == 0)
        return 0;
    
    size_t freq = (rails - 1) * 2, text_len = 0;

    while (text[text_len] != 0)
        text_len++;
    
    char cipherer[rails][text_len], *ciphered_text;

    for (size_t i = 0; i < rails; i++)
        for (size_t j = 0; j < text_len; j++)
            cipherer[i][j] = '.';

    for (size_t i = 0, j = 0; j < text_len; j++){
        cipherer[i][j] = text[j];
        i += (j % freq) < rails - 1 ? 1 : -1;
    }

    ciphered_text = (char *)malloc((text_len + 1) * sizeof(char));
    if (!ciphered_text)
        return 0;

    for (size_t i = 0, k = 0; i < rails; i++)
        for (size_t j = 0; j < text_len; j++)
            if (cipherer[i][j] != '.')
                ciphered_text[k++] = cipherer[i][j];
    ciphered_text[text_len] = 0;

    return ciphered_text;
}


char *decode(char *ciphertext, size_t rails)
{
    if (!ciphertext || rails == 0)
        return 0;
    
    size_t freq = (rails - 1) * 2, text_len = 0;

    while (ciphertext[text_len] != 0)
        text_len++;
    
    char cipherer[rails][text_len], *text;

    for (size_t i = 0; i < rails; i++)
        for (size_t j = 0; j < text_len; j++)
            cipherer[i][j] = '.';

    for (size_t i = 0, j = 0; j < text_len; j++){
        cipherer[i][j] = '?';
        i += (j % freq) < rails - 1 ? 1 : -1;
    }

    for (size_t i = 0, k = 0; i < rails; i++)
        for (size_t j = 0; j < text_len; j++)
            if (cipherer[i][j] == '?')
                cipherer[i][j] = ciphertext[k++];

    text = (char *)malloc((text_len + 1) * sizeof(char));
    if (!text)
        return 0;

    for (size_t i = 0, j = 0; j < text_len; j++){
        text[j] = cipherer[i][j];
        i += (j % freq) < rails - 1 ? 1 : -1;
    }
    text[text_len] = 0;

    return text;
}