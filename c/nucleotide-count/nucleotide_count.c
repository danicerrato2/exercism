#include "nucleotide_count.h"

char *count(const char *dna_strand)
{
    int counts[4] = {0, 0, 0, 0}, response_len = 12;
    char *response;
    
    if (!dna_strand)
        return 0;

    for (int i = 0; dna_strand[i] != 0; i++){
        switch (dna_strand[i]){
            case 'A':
                counts[0]++;
                break;
            case 'C':
                counts[1]++;
                break;
            case 'G':
                counts[2]++;
                break;
            case 'T':
                counts[3]++;
                break;
            default:
                return (char *)calloc(1, sizeof(char));
        }
    }

    for (int i = 0; i < 4; i++)
        response_len += counts[i] != 0 ? log10(counts[i]) + 1 : 1;
    
    response = (char *)malloc(response_len * sizeof(char));
    if (!response)
        return (char *)calloc(1, sizeof(char));

    sprintf(response, "A:%d C:%d G:%d T:%d", counts[0], counts[1], counts[2], counts[3]);
    
    return response;
}