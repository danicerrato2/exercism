#ifndef PALINDROME_PRODUCTS_H
#define PALINDROME_PRODUCTS_H

#include <malloc.h>
#include <stdio.h>
#include <math.h>

#define MAXERR 100

typedef struct factors {
   int factor_a;
   int factor_b;
   struct factors *next;
} factor_t;

struct product {
   int smallest;
   int largest;
   factor_t *factors_sm;
   factor_t *factors_lg;
   char error[MAXERR];
};

typedef struct product product_t;

product_t *get_palindrome_product(int from, int to);
void free_product(product_t *p);

factor_t *get_factors(int value, int from, int to);
int is_palindrome(int value);

#endif
