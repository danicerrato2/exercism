#include "roman_numerals.h"

char *thousands[] = {"", "M", "MM", "MMM"};
char *hundreds[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
char *tens[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
char *units[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

char *to_roman_numeral(unsigned int number) {
	char *romanNumber = malloc(15 * sizeof (char));
	
	strcat(romanNumber, thousands[number / 1000]);
	number %= 1000;
	strcat(romanNumber, hundreds[number / 100]);
	number %= 100;
	strcat(romanNumber, tens[number / 10]);
	number %= 10;
	strcat(romanNumber, units[number]);

	return romanNumber;
}