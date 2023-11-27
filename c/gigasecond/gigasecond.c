#include "gigasecond.h"

void gigasecond(time_t before, char *after, int buffer_size) {
    time_t time_after =  before + (time_t)1000000000;

    strftime(after, buffer_size, "%F %T", gmtime(&time_after));
}