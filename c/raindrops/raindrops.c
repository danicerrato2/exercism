#include "raindrops.h"

char *convert(char result[], int drops)
{
    int result_len = 0;

    if (drops % 3 == 0)
        for (int i = 0; i < 5; i++)
            result[result_len++] = "Pling"[i];
    if (drops % 5 == 0)
        for (int i = 0; i < 5; i++)
            result[result_len++] = "Plang"[i];
    if (drops % 7 == 0)
        for (int i = 0; i < 5; i++)
            result[result_len++] = "Plong"[i];
    if (result_len == 0){
        int aux_drops;

        aux_drops = drops;
        do {
            drops /= 10;
            result_len++;
        } while (drops > 0);

        while (result_len-- > 0){
            result[result_len] = '0' + (aux_drops % 10);
            aux_drops /= 10;
        }
        result[result_len] = '0' + aux_drops;
    }

    return 0;
}