#include "rational_numbers.h"

rational_t add(rational_t r1, rational_t r2)
{
    rational_t result = \
        {r1.numerator * r2.denominator + r2.numerator * r1.denominator,
        r1.denominator * r2.denominator};
    return reduce(result);
}


rational_t subtract(rational_t r1, rational_t r2)
{
    rational_t result = \
        {r1.numerator * r2.denominator - r2.numerator * r1.denominator,
        r1.denominator * r2.denominator};
    return reduce(result);
}


rational_t multiply(rational_t r1, rational_t r2)
{
    rational_t result = \
        {r1.numerator * r2.numerator, r1.denominator * r2.denominator};
    return reduce(result);
}


rational_t divide(rational_t r1, rational_t r2)
{
    rational_t result = \
        {r1.numerator * r2.denominator, r2.numerator * r1.denominator};
    return reduce(result);
}


rational_t absolute(rational_t r)
{
    rational_t result = {abs(r.numerator), abs(r.denominator)};
    return reduce(result);
}


rational_t exp_rational(rational_t r, int16_t n)
{
    rational_t result;

    if (n >= 0){
        result.numerator = pow(r.numerator, n);
        result.denominator = pow(r.denominator, n);
    } else {
        result.numerator = pow(r.denominator, -n);
        result.denominator = pow(r.numerator, -n);
    }

    return reduce(result);
}


float exp_real(uint8_t x, rational_t r)
{
    rational_t reduced = reduce(r);

    return pow(pow(x, reduced.numerator), 1.0/reduced.denominator);
}


rational_t reduce(rational_t r)
{
    rational_t result = {abs(r.numerator), abs(r.denominator)};
    int gcd = 1, positive_denom = 1;

    for (int i = 2; i <= result.numerator && i <= result.denominator; i++){
        if (result.numerator % i == 0 && result.denominator % i == 0)
            gcd *= i;
    }
    if (result.numerator == 0)
        gcd *= result.denominator;

    if (r.denominator < 0)
        positive_denom = -1;
    
    result.numerator = positive_denom * r.numerator / gcd;
    result.denominator = positive_denom * r.denominator / gcd;
    
    return result;
}