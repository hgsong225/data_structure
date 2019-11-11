#include "poly.h"

int deduct(int deg1, int deg2, struct poly* a, struct poly* b, struct poly* d) {
    int i;
    int m = 0;

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
        for (i = deg1 + 1; i <= deg2; i += 1)
        {    
            d[m].coeff = b[i].coeff;
            d[m].exp = b[i].exp;
            m += 1;
        }
    }

    return m;
}