#include "poly.h"

int add(int deg1, int deg2, struct poly* a, struct poly* b, struct poly* c) {
    int i;
    int m = 0;

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
        for (i = deg1 + 1; i <= deg2; i += 1)
        {    
            c[m].coeff = b[i].coeff;
            c[m].exp = b[i].exp;
            m += 1;
        }
    }

    return m;
}