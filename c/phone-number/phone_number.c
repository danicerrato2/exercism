#include "phone_number.h"

#define MAX_DIGITS 10

char *check_number(char *phone_number, int num_digits, const char *input)
{
    int wrong_number = 0;
    
    for (int i = 0; input[i] != 0; i++)
        if (input[i] >= '0' && input[i] <= '9')
            wrong_number = 1;

    if (num_digits != MAX_DIGITS)
        wrong_number = 1;

    if (wrong_number == 0 && (phone_number[0] < '2' || phone_number[3] < '2'))
        wrong_number = 1;

    for (int i = 0; wrong_number != 0 && i < MAX_DIGITS; i++)
        phone_number[i] = '0';

    return phone_number;
}

char *phone_number_clean(const char *input)
{
    char *phone_number;
    int num_digits = 0, i = 0;

    phone_number = (char *)calloc(MAX_DIGITS + 1, sizeof(char));
    if (!phone_number)
        return 0;
    
    while (input[i] != 0 && num_digits < MAX_DIGITS){
        if (input[i] >= '0' && input[i] <= '9')
            phone_number[num_digits++] = input[i];
        if (phone_number[0] == '1')
            phone_number[--num_digits] = 0;
        i++;
    }

    return check_number(phone_number, num_digits, input + i);
}