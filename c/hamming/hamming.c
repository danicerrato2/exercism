#include "hamming.h"

int compute(const char *lhs, const char *rhs)
{
    int i = 0, diffs = 0;
    
    for (; lhs[i] && rhs[i]; i++){
        if (lhs[i] != rhs[i])
            diffs++;
    }

    if ((lhs[i] && !rhs[i]) || (!lhs[i] && rhs[i]))
        return -1;

    return diffs;
}