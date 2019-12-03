#include <stdio.h>
#include <limits.h>

/* PRZYDATNE ALGORYTMY */

void abs(int a)
{
    if(a<0)
        a=-a;
}

int max3(int a, int b, int c)
{
    int max;

    if(a>b)
    {
        if(a>c)
            max = a;
        else
            max = c;
    }
    else
    {
        if(b>c)
            max = b;
        else
            max = c;
    }

    return max;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubblesort(int A[], int n)
{
    for(int i=0; i<n-1; ++i)
    {
        for(int j=0; j<n-1-i; ++j)
        {
            if(A[j] > A[j+1])
                swap(&A[j], &A[j+1]);
        }
    }
}

int checkoverflow(int a, int b)
{
    if(a > INT_MAX-b)
        return -1;
    else
        return a+b;
}

/* ZADANIA */

// 14.11.2013 - ZADANIE 2

int ModBwA(int A[], int B[], int n)
{
    int l=1, p=n, s, w=0;

    while(l<p)
    {
        A[s]=(l+p)/2;
        if(A[s]>0)
            l=s+1;
        else
            p=s;
    }

    int i=l;

    l=1;
    p=n;

    while(l<p)
    {
        B[s]=(l+p)/2;
        if(B[s]>0)
            l=s+1;
        else
            p=s;
    }

    int x=0, y=0;
    ++p;

    while(i<=n && w=0)
    {
        if(l>0)
        {
            if(abs(B[l])<A[i])
                --l;
            else if(abs(B[l])>A[i])
                x=1;
            else
                w=1;
        }
        else
            x=1;

        if(p<=n)
        {
            if(abs(B[p])<A[i])
                ++p;
            else if(abs(B[p])>A[i])
                y=1;
            else
                w=1;
        }
        else
            y=1;

        if(x && y)
        {
            x=0;
            y=0;
            ++i;
        }
    }

    return w;
}

// 15.11.2012 ZADANIE 1

void f_minval(int P[], int n, int minval)
{
    // nie jestem tego pewien, może być błąd dla jakiegoś kontrprzykładu

    int a=0, b=n-1, s;

    while(a<b)
    {
        s=(a+b)/2;
        if(P[s]<0)
            a=s+1;
        else
            b=s;
    }
    --a;

    minval=abs(P[a]+P[b]);

    while((a>=0 || b<n) && minval!=0)
    {
        if(abs(P[a]+P[b])<minval)
            minval=abs(P[a]+P[b]);

        if(a>=0 && abs(P[a])<P[b])
            --a;
    }

    if(abs(P[a-1]+P[a])<minval)
        minval=abs(P[a-1]+P[a]);
    if(abs(P[b]+P[b+1]<minval))
        minval=abs(P[b]+P[b+1]);
}

// 15.11.2018 ZADANIE 1 - plateau

int max1(int A[], int n)
{
    int d=1, g=1, m=1;

    for(int i=1; i<n; ++i)
    {
        if((A[i]+1)/2 == (A[i-1]+1)/2)
            ++g;
        else
            g=1;

        if(A[i]/2 == A[i-1]/2)
            ++d;
        else
            d=1;

        m = max3(m, g, d);
    }

    return m;
}

// 15.11.2018 ZADANIE 2

void f_k_bliskie(int A[], int n, int k, int k_bliskie)
{
    int i=0, j=n-1;
    k_bliskie=0;

    while(i<j && k_bliskie==0)
    {
        int x=A[i]-A[j];

        if(x>k)
        {
            --j;
            if(A[j]-A[j-1]<=k && A[j]-A[j-1]>=-k)
                k_bliskie=1;
        }
        else if(x<-k)
        {
            ++i;
            if(A[i-1]-A[i]<=k && A[i-1]-A[i]>=-k)
            {
                k_bliskie=1;
            }
        }
        else
            k_bliskie=1;
    }
}

// 16.11.2017 ZADANIE 1

void funkcja1_17(int A[], int n)
{
    /* to jest jeden ze sposobów
     * drugi został wrzucony przez Walenia jako zadanie 20
     * podobno sposoby są identyczne, ale ten Walenia bardziej czytelny
     * link:
     * https://www.mimuw.edu.pl/~walen/teaching/2019-wp/20191118-wpi-rozwiazania-zadan.pdf
     */

    int p=d=0;
    int roznica_laczna=0;

    for(int i=0; i<n; ++i)
    {
        if(A[i]==0)
            ++roznica_laczna;
        else
            --roznica_laczna;
    }

    int roznica_aktualna=0, i=0, max=0, czy=0;

    while(!czy && i<n)
    {
        if(A[i]==0)
            ++roznica_aktualna;
        else
            --roznica_aktualna;

        if(roznica_aktualna>1 && roznica_aktualna>roznica_laczna && roznica_aktualna<max)
        {
            czy=1;
            if(i+1<n-1)
                d=i+1;
            roznica_laczna=roznica_aktualna;
        }
        if(roznica_aktualna>max)
            max=roznica_aktualna;
    }

    i=0;
    czy=0;

    while(!czy && i<d)
    {
        if(A[i]==0)
            ++roznica_aktualna;
        else
            --roznica_aktualna;

        if(roznica_aktualna==roznica_laczna)
        {
            p=i;
            czy=1;
        }
    }
}

// 16.11.2017 ZADANIE 2

void funkcja2_17(int A[], int n, int k)
{
    int i=0, j=n-1, x, wynik=0;

    while(i<j)
    {
        x=A[i]+A[j];

        if(x>k)
            --j;
        else if(x<k)
            ++i;
        else
        {
            ++i;
            --j;
            ++wynik;
        }
    }
}

// 24.11.2016 ZADANIE 1

int ilerosnacych(int C[], int n)
{
    int ile0=0, ile01=0, ile012=0;

    for(int i=0; i<n; ++i)
    {
        if(C[i]==0)
            ++ile0;
        else if(C[i]==1)
            ile01+=ile0;
        else
            ile012+=ile01;
    }

    return ile012;
}

// 24.11.2016 ZADANIE 2

void niewieksze(int A[], int n, int B[], int m)
{
    for(int i=0; i<n; ++i)
    {
        if(A[i]<0)
            ++B[0];
        else if(A[i]<m)
            ++B[A[i]];
    }

    for(int i=1; i<m; ++i)
    {
        B[i]+=B[i-1];
    }
}