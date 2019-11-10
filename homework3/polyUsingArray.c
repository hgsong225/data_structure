#include <stdio.h>
#include <math.h>
/*
  This structure is used to store a polynomial term. An array of such terms represents a
  polynomial.
  The "coeff" element stores the coefficient of a term in the polynomial,while
  the "exp"   element stores the exponent.

  Example)
  Expression 1 = 2.0+ 1.0x^1+ 2.0x^2+ 4.0x^3
  Expression 2 = 2.0+ 3.0x^1+ 1.0x^2+ 5.0x^3+ 4.0x^4+ 2.0x^5
  Expression after addition = 4.0+ 4.0x^1+ 3.0x^2+ 9.0x^3+ 4.0x^4+ 2.0x^5
  Expression after deduction = 0.0+ -2.0x^1+ 1.0x^2+ -1.0x^3+ 0.0x^0+ 0.0x^0
*/

struct poly
{
    float coeff;
    int exp;
};

//declaration of polynomials
struct poly a[50], b[50], c[50], d[50];

int main()
{
    int i;
    int deg1, deg2;        //stores degrees of the polynomial
    int k=0, l=0, m=0;

    printf("Enter the highest degree of polynomial1:");
    scanf("%d",&deg1);        //taking polynomial terms from the user
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
       printf("+ %.1fx^%d", a[i].coeff, a[i].exp);
   }
   //printing second polynomial
   printf("\nExpression 2 = %.1f", b[0].coeff);
   for (i = 1; i <= deg2; i += 1)
   {    
        printf("+ %.1fx^%d", b[i].coeff, b[i].exp);
   }

   //Adding the polynomials
   if (deg1 > deg2)
   {
       for (i = 0; i <= deg2; i += 1)
       {
           c[m].coeff = a[i].coeff + b[i].coeff;
           c[m].exp = a[i].exp;
           m += 1;
       }   
       for (i = deg2 + 1; i <= deg1; i += 1)
       {    
           c[m].coeff = a[i].coeff;
           c[m].exp = a[i].exp;
           m += 1;
       }  
   }                              
   else                   
   {                                  
       for (i = 0; i <= deg1; i += 1)
       {                            
           c[m].coeff = a[i].coeff + b[i].coeff;
           c[m].exp = a[i].exp;
           m += 1;
       }          
       for (i=deg1+1;i<=deg2;i++)
       {    
           c[m].coeff = b[i].coeff;
           c[m].exp = b[i].exp;
            m += 1;
       }
   }

   //printing the sum of the two polynomials
   printf("\nExpression after addition = %.1f", c[0].coeff);
   for (i = 1; i < m; i += 1)
   {
       printf("+ %.1fx^%d", c[i].coeff, c[i].exp);
   }

   m = 0;


   //deducting the polynomials
   if (deg1 > deg2)
   {
       for (i = 0; i <= deg2; i += 1)
       {
           d[m].coeff = a[i].coeff - b[i].coeff;
           d[m].exp = a[i].exp;
           m += 1;
       }   
       for (i = deg2 + 1; i <= deg1; i += 1)
       {    
           d[m].coeff = a[i].coeff;
           d[m].exp = a[i].exp;
           m += 1;
       }  
   }                              
   else                   
   {                                  
       for (i = 0; i <= deg1; i += 1)
       {                            
           d[m].coeff = a[i].coeff - b[i].coeff;
           d[m].exp = a[i].exp;
           m += 1;
       }          
       for (i=deg1+1;i<=deg2;i++)
       {    
           c[m].coeff = b[i].coeff;
           c[m].exp = b[i].exp;
            m += 1;
       }
   }
   
   //printing the result of the two polynomials
   printf("\nExpression after deduction = %.1f", d[0].coeff);
   for (i = 1; i < m; i += 1)
   {
       printf("+ %.1fx^%d", d[i].coeff, d[i].exp);
   }

    return 0;
}