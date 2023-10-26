#include "pascals_triangle.h"

void free_triangle(uint8_t **triangle, size_t rows)
{
    if (triangle){
        for (size_t i = 0; i < rows; i++)
            if (triangle[i])
                free(triangle[i]);
        free(triangle);
    }
}


uint8_t **create_triangle(size_t rows)
{
    uint8_t **triangle;
    
    if (rows == 0)
        triangle = (uint8_t **)malloc(sizeof(uint8_t *));        
    else    
        triangle = (uint8_t **)malloc(rows * sizeof(uint8_t *));
    if (!triangle)
        return 0;

    for (size_t i = 0; i < rows || i < 1; i++){
        triangle[i] = (uint8_t *)malloc(rows * sizeof(uint8_t));
        if (!triangle[i]){
            free_triangle(triangle, rows);
            return 0;
        }
    }

    for (size_t i = 0; i < 2 && i < rows; i++)
        for (size_t j = 0; j < rows; j++)
            triangle[i][j] = j <= i ? 1 : 0;
    for (size_t i = 2; i < rows; i++){
        triangle[i][0] = 1;
        for (size_t j = 1; j < rows; j++)
            triangle[i][j] = j > i ? 0 : triangle[i - 1][j - 1] + triangle[i - 1][j];
    }

    return triangle;
}