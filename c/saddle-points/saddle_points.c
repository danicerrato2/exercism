#include "saddle_points.h"

int is_valid_point(saddle_point_t point, uint8_t rows, uint8_t columns, uint8_t matrix[rows][columns])
{
    int is_valid = 1;

    for (uint8_t i = 0; i < rows && is_valid; i++){
        if (matrix[i][point.column] < matrix[point.row][point.column])
            is_valid = 0;
    }
    for (uint8_t j = 0; j < columns && is_valid; j++){
        if (matrix[point.row][j] > matrix[point.row][point.column])
            is_valid = 0;
    }
    return is_valid;
}


saddle_points_t *append_saddle_point(saddle_points_t *saddle_points, saddle_point_t point)
{
    if (!saddle_points)
        return 0;

    saddle_points_t *extended_points = (saddle_points_t *)malloc(sizeof(saddle_points_t) + (saddle_points->count + 1) * sizeof(saddle_point_t));
    if (!saddle_points)
        return 0;

    for (size_t i = 0; i < saddle_points->count; i++){
        extended_points->points[i].row = saddle_points->points[i].row;
        extended_points->points[i].column = saddle_points->points[i].column;
    }
    extended_points->points[saddle_points->count].row = point.row + 1;
    extended_points->points[saddle_points->count].column = point.column + 1;
    extended_points->count = saddle_points->count + 1;

    free_saddle_points(saddle_points);

    return extended_points;
}


saddle_points_t *saddle_points(uint8_t rows, uint8_t columns, uint8_t matrix[rows][columns])
{    
    saddle_points_t *saddle_points = (saddle_points_t *)malloc(sizeof(saddle_points_t));
    if (!saddle_points)
        return 0;

    saddle_points->count = 0;
    for (uint8_t i = 0; i < rows; i++){
        for (uint8_t j = 0; j < columns; j++){
            if (is_valid_point((saddle_point_t){i, j}, rows, columns, matrix)){
                saddle_points = append_saddle_point(saddle_points, (saddle_point_t){i, j});
                if (!saddle_points)
                    return 0;
            }                
        }
    }

    return saddle_points;
}


void free_saddle_points(saddle_points_t *saddle_points)
{
    if (saddle_points)
        free(saddle_points);
}
