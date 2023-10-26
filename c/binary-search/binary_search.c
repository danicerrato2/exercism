#include "binary_search.h"

const int *binary_search(int value, const int *arr, size_t length)
{
    size_t left = 0, right = length, mid = -1;

    if (length == 0)
        return 0;
    
    do {
        mid = (right + left) / 2;
        if (arr[mid] == value)
            return &arr[mid];
        if (arr[mid] < value)
            left = mid + 1;
        else
            right = mid - 1;
    } while (left != right);

    if (arr[left] == value)
        return &arr[left];
    return 0;
}