#include "resistor_color.h"

resistor_band_t band_colors[] = {BLACK, BROWN, RED, ORANGE, YELLOW, GREEN, BLUE, VIOLET, GREY, WHITE};


uint16_t color_code(resistor_band_t color)
{
    return color;
}


resistor_band_t *colors()
{
    return band_colors;
}