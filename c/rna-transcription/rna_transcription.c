#include "rna_transcription.h"

char *to_rna(const char *dna)
{
    int dna_size = 0;
    char *rna = 0;

    if (!dna || dna[0] == 0)
        return (char *)calloc(1, sizeof(char));

    while (dna[dna_size] != 0)
        dna_size++;

    rna = (char *)malloc((dna_size + 1) * sizeof(char));
    if (!rna)
        return (char *)calloc(1, sizeof(char));

    for (int i = 0; i < dna_size; i++){
        switch (dna[i]) {
            case 'A':
                rna[i] = 'U';
                break;
            case 'C':
                rna[i] = 'G';
                break;
            case 'G':
                rna[i] = 'C';
                break;
            case 'T':
                rna[i] = 'A';
                break;
            default:
                return (char *)calloc(1, sizeof(char));
        }
    }

    return rna;
}