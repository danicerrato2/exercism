#include "darts.h"

uint8_t score(coordinate_t dart_pos)
{
    float radius = sqrt(dart_pos.x * dart_pos.x + dart_pos.y * dart_pos.y);

    if (radius > 10)
        return 0;
    else if (radius > 5)
        return 1;
    else if (radius > 1)
        return 5;
    else
        return 10;
}