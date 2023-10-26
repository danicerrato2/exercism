#include "allergies.h"

bool is_allergic_to(allergen_t allergen_code, int score)
{
    if (allergen_code > ALLERGEN_COUNT)
        return false;
    
    allergen_list_t list = get_allergens(score);

    return list.allergens[allergen_code];
}


allergen_list_t get_allergens(int score)
{
    allergen_list_t list;
    list.count = 0;

    while (score > 255)
        score -= 256;

    for (int i = ALLERGEN_COUNT - 1; i >= 0; i--){
        if (score >= pow(2, i)){
            score -= pow(2, i);
            list.allergens[i] = true;
            list.count++;
        }
        else
            list.allergens[i] = false;
    }

    return list;
}