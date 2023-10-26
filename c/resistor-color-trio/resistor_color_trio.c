#include "resistor_color_trio.h"

resistor_value_t color_code(resistor_band_t colors[])
{
    uint32_t value = (colors[0] * 10 + colors[1]) * pow(10, colors[2]);
    
    return (resistor_value_t) {
        .value = value < 1000 ? value : value / 1000,
        .unit = value < 1000 ? OHMS : KILOOHMS
    };
}