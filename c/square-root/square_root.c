#include "square_root.h"

uint64_t square_root(unsigned int n)
{
    double sqrt, temp;
    
    sqrt = n / 2.0;
    temp = 0;
    while (sqrt != temp){
        temp = sqrt;
        sqrt = (n / temp + temp) / 2.0;
    }

    if (sqrt - (int)sqrt == 0.0)
        return sqrt;
    return 0;   
}