#include "poly.h"

clock_t start, finish, used_time = 0;    // variables to calulate running time.

void calcTime(void)
{
    used_time = finish - start;
    printf("\nALL DONE!\nTime: %f sec\n\n", (float)used_time / CLOCKS_PER_SEC);
}

int main()
{
    int i;
    int deg1, deg2;        //stores degrees of the polynomial
    int k = 0, l = 0, m = 0;

    printf("Enter the highest degree of polynomial1:");
    scanf("%d", &deg1);        //taking polynomial terms from the user
    for (i = 0; i <= deg1; i += 1)
    {
        //entering values in coefficient of the polynomial terms
        printf("\nEnter the coeff of x^%d :", i);
        scanf("%f", &a[i].coeff);
        //entering values in exponent of the polynomial terms
        a[k++].exp = i;
    }

    //taking second polynomial from the user
    printf("\nEnter the highest degree of polynomial2:");
    scanf("%d", &deg2);
    for (i = 0; i <= deg2; i += 1)
    {
        printf("\nEnter the coeff of x^%d :", i);
        scanf("%f", &b[i].coeff);
        b[l++].exp = i;
    }

    //printing first polynomial
    printf("\nExpression 1 = %.1f", a[0].coeff);
    for (i = 1; i <= deg1; i += 1)
    {
        printf(" + %.1fx^%d", a[i].coeff, a[i].exp);
    }
    //printing second polynomial
    printf("\nExpression 2 = %.1f", b[0].coeff);
    for (i = 1; i <= deg2; i += 1)
    {    
        printf(" + %.1fx^%d", b[i].coeff, b[i].exp);
    }


    start = clock();

    //Adding the polynomials
    m = add(deg1, deg2, a, b, c);

    finish = clock();
    calcTime();

    //printing the sum of the two polynomials
    printf("\nExpression after addition = %.1f", c[0].coeff);
    for (i = 1; i < m; i += 1)
    {
        printf(" + %.1fx^%d", c[i].coeff, c[i].exp);
    }

    m = 0;

    start = clock();

    //deducting the polynomials
    m = deduct(deg1, deg2, a, b, d);

    finish = clock();
    calcTime();
   
    //printing the result of the two polynomials
    printf("\nExpression after deduction = %.1f", d[0].coeff);
    for (i = 1; i < m; i += 1)
    {
        printf(" + %.1fx^%d", d[i].coeff, d[i].exp);
    }

    return 0;
}