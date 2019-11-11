#ifndef _POLY_ARRAY
#define _POLY_ARRAY

#include <stdio.h>
#include <math.h>
#include <time.h>

struct poly
{
    float coeff;
    int exp;
};

//declaration of polynomials
struct poly a[50], b[50], c[50], d[50];

void calcTime(void);
int add(int deg1, int deg2, struct poly* a, struct poly* b, struct poly* c);
int deduct(int deg1, int deg2, struct poly* a, struct poly* b, struct poly* d);


#endif
