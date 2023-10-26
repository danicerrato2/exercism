#ifndef MEETUP_H
#define MEETUP_H

#include <string.h>

int meetup_day_of_month(unsigned int year, unsigned int month, const char *week,
                        const char *day_of_week);

int IsLeapYear(unsigned int year);
void moveToYear(unsigned int year, unsigned int *date, unsigned int *dateWeekday);
void moveToMonth(unsigned int month, unsigned int *date, unsigned int *dateWeekday);
void moveToWeekday(const char *day_of_week, unsigned int *date, unsigned int *dateWeekday);
void moveToWeek(const char *week, unsigned int *date);

#endif
