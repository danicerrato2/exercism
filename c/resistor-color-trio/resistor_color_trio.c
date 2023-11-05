#include "resistor_color_trio.h"

resistor_value_t color_code(resistor_band_t colors[])
{
    resistor_unit_t units;
    uint32_t value, zeros;

    switch (colors[2]) {
        case 9:
            units = GIGAOHMS;
            break;
        case 8:
        case 7:
        case 6:
            units = MEGAOHMS;
            break;
        case 5:
        case 4:
        case 3:
            units = KILOOHMS;
            break;
        case 2:
        case 1:
        case 0:
            units = OHMS;
            break;
    }

    zeros = colors[2] % 3;
    value = (colors[0] * 10 + colors[1]) * pow(10, zeros);
    if (value > 1000) {
        value /= 1000;
        units++;
    }
    
    return (resistor_value_t) {.value = value, .unit = units};
}