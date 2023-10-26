#ifndef SADDLE_POINTS_H
#define SADDLE_POINTS_H

#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint8_t row;
    uint8_t column;
} saddle_point_t;

typedef struct {
    size_t count;
    saddle_point_t points[];
} saddle_points_t;

saddle_points_t *saddle_points(uint8_t rows, uint8_t columns, uint8_t matrix[rows][columns]);
void free_saddle_points(saddle_points_t *saddle_points);
int is_valid_point(saddle_point_t point, uint8_t rows, uint8_t columns, uint8_t matrix[rows][columns]);
saddle_points_t *append_saddle_point(saddle_points_t *saddle_points, saddle_point_t point);

#endif
