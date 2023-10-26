#include "beer_song.h"

char *verse1 = "%u bottle%s of beer on the wall, %u bottle%s of beer.";
char *verse2 = "Take one down and pass it around, %u bottle%s of beer on the wall.";
char *verse2_1 = "Take it down and pass it around, no more bottles of beer on the wall.";

char *verses_end[] = {
    "No more bottles of beer on the wall, no more bottles of beer.",
    "Go to the store and buy some more, 99 bottles of beer on the wall."
};

void recite(uint8_t start_bottles, uint8_t take_down, char **song)
{
    char *with_s1, *with_s2;
    uint16_t i, lines;
    
    lines = (uint16_t)take_down * 3 - 2;
    for (i = 0; i < lines && start_bottles > 0; i += 3, start_bottles--){
        with_s1 = start_bottles == 1 ? "" : "s";
        with_s2 = start_bottles - 1 == 1 ? "" : "s";
        sprintf(song[i], verse1, start_bottles, with_s1, start_bottles, with_s1);
        if (start_bottles != 1)
            sprintf(song[i + 1], verse2, start_bottles - 1, with_s2);
        else
            sprintf(song[i + 1], "%s", verse2_1);
        if (i + 2 < lines)
            sprintf(song[i + 2], "%s", "");
    }
    if (start_bottles == 0 && i < lines){
        sprintf(song[i], "%s", verses_end[0]);
        sprintf(song[i + 1], "%s", verses_end[1]);
    }
}