#include "complex_numbers.h"

complex_t c_add(complex_t a, complex_t b)
{
   return (complex_t) {.real = a.real + b.real, .imag = a.imag + b.imag};
}

complex_t c_sub(complex_t a, complex_t b)
{
   return (complex_t) {.real = a.real - b.real, .imag = a.imag - b.imag};
}

complex_t c_mul(complex_t a, complex_t b)
{
   return (complex_t) {
      .real = a.real * b.real - a.imag * b.imag,
      .imag = a.imag * b.real + a.real * b.imag
   };
}

complex_t c_div(complex_t a, complex_t b)
{
   return (complex_t) {
      .real = (a.real * b.real + a.imag * b.imag) / c_square_abs(b),
      .imag = (a.imag * b.real - a.real * b.imag) / c_square_abs(b)
   };
}

double c_square_abs(complex_t x) {
   return x.real * x.real + x.imag * x.imag;
}

double c_abs(complex_t x)
{
   double sqrt, temp, n = c_square_abs(x);
    
   sqrt = n / 2.0;
   temp = 0;
   while (sqrt != temp){
      temp = sqrt;
      sqrt = (n / temp + temp) / 2.0;
   }

   return sqrt;
}

complex_t c_conjugate(complex_t x)
{
   return (complex_t) {.real = x.real, .imag = -x.imag};
}

double c_real(complex_t x)
{
   return x.real;
}

double c_imag(complex_t x)
{
   return x.imag;
}

complex_t c_exp(complex_t x)
{
   return (complex_t) {
      .real = exp(x.real) * cos(x.imag), .imag = exp(x.real) * sin(x.imag)};
}
