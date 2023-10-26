#include "isogram.h"

bool is_isogram(const char phrase[])
{    
    if (phrase == 0)
        return false;

    for (int i = 0; phrase[i] != 0; i++){
        if (phrase[i] != ' ' && phrase[i] != '-'){
            for (int j = i + 1; phrase[j] != 0; j++){
                if (phrase[i] != '-'){
                    if (phrase[i] == phrase[j] || abs(phrase[i] - phrase[j]) == 32)
                        return false;
                }
            }
        }
    }
    
    return true;
}