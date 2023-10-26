#include "pythagorean_triplet.h"

triplets_t *append_triplet(triplets_t *triplets, triplet_t new_triplet)
{
    if (!triplets)
        return 0;

    triplets_t *extended_triplets = (triplets_t *)malloc(sizeof(triplets_t) + (triplets->count + 1) * sizeof(triplet_t));
    if (!extended_triplets)
        return 0;

    extended_triplets->count = triplets->count;

    for (int i = 0; i < extended_triplets->count; i++){
        extended_triplets->triplets[i].a = triplets->triplets[i].a;
        extended_triplets->triplets[i].b = triplets->triplets[i].b;
        extended_triplets->triplets[i].c = triplets->triplets[i].c;
    }

    extended_triplets->triplets[extended_triplets->count].a = new_triplet.a;
    extended_triplets->triplets[extended_triplets->count].b = new_triplet.b;
    extended_triplets->triplets[extended_triplets->count].c = new_triplet.c;

    extended_triplets->count++;

    free_triplets(triplets);
    
    return extended_triplets;
}

triplets_t *triplets_with_sum(int sum)
{
    int a = 1, b;
    float c, root;
    triplets_t *triplets = (triplets_t *)malloc(sizeof(triplets_t));

    if (!triplets)
        return 0;

    triplets->count = 0;

    do {
        c = 0;
        for (b = a + 1; a + b + c <= sum; b++){
            root = sqrt(a*a + b*b);
            c = floor(root);
            if (c > b && c == root && a*a + b*b == (int)c*(int)c && a + b + (int)c == sum)
                triplets = append_triplet(triplets, (triplet_t){a, b, (int)c});
        }
        a++;
    } while (a + b < sum);

    return triplets;
}


void free_triplets(triplets_t *triplets)
{
    if (triplets)
        free(triplets);
}