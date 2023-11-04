#include "meetup.h"

#include <stdio.h>

#define TEENTH_MIN 13
#define TEENTH_MAX 19

char *descriptors[] = {"first", "second", "third", "fourth", "last", "teenth"};
char *weekdays[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
unsigned int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

unsigned int sumDays, toCheck; 
int upOrDown;

int IsLapYear(unsigned int year) {
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

void moveToYear(unsigned int year, unsigned int *date, unsigned int *dateWeekday) {
	upOrDown = year < date[2] ? -1 : 1;
	while (date[2] != year) {
		toCheck = upOrDown == -1 ? date[2] : date[2] + 1;
		sumDays = IsLapYear(toCheck) ? 366 % 7 : 365 % 7;
		*dateWeekday = (*dateWeekday + 7 + upOrDown * sumDays) % 7;
		date[2] += upOrDown; 
	}
}

void moveToMonth(unsigned int month, unsigned int *date, unsigned int *dateWeekday) {
	upOrDown = month < date[1] ? -1 : 1;
	while (date[1] != month) {
		toCheck = upOrDown == -1 ? date[1] - 1 : date[1];
		sumDays = toCheck == 2 && IsLapYear(date[2]) ? 29 % 7 : monthDays[toCheck - 1] % 7;
		*dateWeekday = (*dateWeekday + 7 + upOrDown * sumDays) % 7;
		date[1] += upOrDown;
	}
}

void moveToWeekday(const char *day_of_week, unsigned int *date, unsigned int *dateWeekday) {
	while (strcmp(day_of_week, weekdays[*dateWeekday]) != 0) {
		date[0]++;
		*dateWeekday = (*dateWeekday + 1) % 7;
	}
}

void moveToWeek(const char *week, unsigned int *date) {
	int i = 0;
	unsigned int actualMonthDays = date[1] == 2 && IsLapYear(date[2]) ? 29 : monthDays[date[1] - 1];

	while (strcmp(week, descriptors[i++]) != 0 
			&& !(date[0] >= TEENTH_MIN && date[0] <= TEENTH_MAX && strcmp(week, descriptors[5]) == 0)
			&& !(date[0] > actualMonthDays - 7)) {
		date[0] += 7;
	}
}

int meetup_day_of_month(unsigned int year, unsigned int month, const char *week, const char *day_of_week){
	unsigned int date[] = {1, 3, 2023};
	unsigned int dateWeekday = 2; // Wednesday

	moveToYear(year, date, &dateWeekday);
	moveToMonth(month, date, &dateWeekday);
	moveToWeekday(day_of_week, date, &dateWeekday);
	moveToWeek(week, date);

	return date[0];
}
