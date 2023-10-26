#include "high_scores.h"

int32_t latest(const int32_t *scores, size_t scores_len)
{
    if (!scores || scores_len == 0)
        return -1;
    
    return scores[scores_len - 1];
}


int32_t personal_best(const int32_t *scores, size_t scores_len)
{
    int32_t max = 0;
    
    if (!scores || scores_len == 0)
        return -1;

    for (size_t i = 0; i < scores_len; i++)
        max = max < scores[i] ? scores[i] : max;
    
    return max;
}


size_t personal_top_three(const int32_t *scores, size_t scores_len, int32_t *output)
{
    size_t num_tops = 0;
    int32_t aux;
    
    if (!scores || !output || scores_len == 0)
        return -1;

    for (size_t i = 0; i < scores_len; i++){
        if (num_tops < 3)
            output[num_tops++] = scores[i];
        else if (scores[i] > output[num_tops - 1])
            output[num_tops - 1] = scores[i];
        else
            continue;

        for (size_t j = num_tops; j > 1; j--) {
            if (output[j - 1] > output[j - 2]){
                aux = output[j - 1];
                output[j - 1] = output[j - 2];
                output[j - 2] = aux;
            }
        }
    }
    
    return num_tops;
}