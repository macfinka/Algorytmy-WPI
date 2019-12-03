#include <stdio.h>

// K 8 - 12.12.2018
void wymagania(int a[], int n, int *c, int *m)
{
    int k = 0, y = 0, x = n-1;

    while(a[y] != 1)
        ++y;
    while(a[x] != 1)
        --x;

    k = x+1;
    *c = 1;

    do{
        k /= 2;
        ++(*c);
    } while(k > 0);

    *m = x-y+1;
}

// K 8 - 12.12.2012
void przeksztalc(int a[], int n1, int b[], int n2, int *ok)
{
    *ok = 1;
    int znak = a[n1-1];
    if(n1 <= n2)
    {
        int i=0;

        for(; i < n2; ++i)
            b[i] = a[i];

        for(; i < n1; ++i)
            b[i] = znak;
    }
    else
    {
        int i = 0;

        for(; i < n2; ++i)
            b[i] = a[i];

        int x = i;
        for(; i < n1 && *ok; ++i)
            if(a[i] != a[x])
                *ok = 0;
    }
}