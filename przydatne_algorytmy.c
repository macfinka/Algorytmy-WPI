#include <stdio.h>
#include <limits.h>

void abs(int *a)
{
    if(*a<0)
        *a=-*a;
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

/* MergeSort */
void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 =  r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; ++i)
        L[i] = arr[l+i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[m+1+j];

    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i];
            ++i;
        }
        else
        {
            A[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1)
    {
        A[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2)
    {
        A[k] = R[j];
        ++j;
        ++k;
    }
}

void mergesort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;

        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}
/* koniec MergeSort */

// mergesort lepszy, ale jakby ktoś był uparty
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

// korzysta z biblioteki <limits.h>
int checkoverflow(int a, int b)
{
    if(a > INT_MAX-b)
        return -1;
    else
        return a+b;
}

int NWD(int n, int m)
{
    if (m == 0)
        return n;

    bool mparz = (m % 2 == 0); // jeśli pracujemy w czystym rasowo C,
    bool nparz = (n % 2 == 0); // zamieniamy bool na int albo dodajemy bibliotekę stdbool.h

    if (mparz && nparz)
        return 2 * NWD(m / 2, n / 2);
    else if (!mparz && nparz)
        return NWD(m, n / 2);
    else if (mparz && !nparz)
        return NWD(m / 2, n);
    else
        return NWD(n - m, n);
}

int lider(int A[], int n)
{
    int kand = A[0];
    int licznik = 1;

    for(int i = 1; i < n; ++i)
    {
        if(A[i] == kand)
            ++licznik;
        else
            --licznik;

        if(licznik == 0)
        {
            kand = A[i];
            licznik = 1;
        }
    }

    int ile = 0;
    for(int i = 0; i < n; ++i)
    {
        if(kand == A[i])
            ++ile;
    }

    if(ile > n/2)
        return kand;
    else
        return -1;
}

int lewy_binsearch(int A[], int n, int szukana)
{
    int left = 0, mid, right = n-1;

    while(left < right)
    {
        mid = (left+right)/2;

        if(A[mid] > szukana)
            left = mid+1;
        else
            right = mid;
    }

    return left;
}

int prawy_binsearch(int A[], int n, int szukana)
{
    int left = 0, mid, right = n-1;

    while(left < right)
    {
        mid = (left+right+1)/2;

        if(A[mid] > szukana)
            right = mid-1;
        else
            left = mid;
    }

    return right;
}

int max_ciagu_bitonicznego(int A[], int n)
{
    int left = 0, mid, right = n-1;

    while(left < right)
    {
        mid = (left+right)/2;

        if(A[mid] > A[mid+1])
            right = mid;
        else if(A[mid] < A[mid+1])
            left = mid+1;

            /* dla ciągu słabo bitonicznego */
        else if(A[mid] == A[mid+1])
        {
            int i = 2;
            while(A[mid] == A[mid+i])
                ++i;

            if(A[mid] < A[mid+1])
                left = mid+i;
            else
                right = mid;
        }
    }

    return A[mid];
}

// procedura podaje, które liczby z zakresu od 1 do n są liczbami pierwszymi
void sito_Erastotenesa(int A[], int n)
{
    for(int i=0; i<n; ++i)
    {
        A[i] = 1;
    }
    A[0] = A[1] = 0;
    for(int i=2; i*i<n; ++i)
    {
        if(A[i] == 1)
            for(int w=i*i; w<n; w+=i)
                A[w] = 0;
    }
}

void rozklad_na_czynniki_pierwsze(int A[], int n, int x)
{
    for(int i=0; i<n; ++i)
        A[i] = 1;

    A[0] = A[1] = 0;
    for(int i=2; i<n; ++i)
    {
        if (A[i] == 1)
            for (int w = i; w < n; w += i)
                A[w] = i;
    }

    while(x > 1)
    {
        printf("%d ", A[x]);
        x /= A[x];
    }
}

int przesuniecie_cykliczne_tablicy(int A[], int n, int k)
{
    if(A[0] < A[n-1])
        return 0;

    int b = A[0];
    int left = 0, mid, right = n-1;

    while(left < k)
    {
        mid = (left+right+1)/2;

        if(A[mid] >= b)
            left = mid;
        else
            right = mid-1;
    }

    return left+1;
}

// typ bool zwracający 0 jeśli wykraczamy poza zakres bitu przy zmianie znaku liczby binarnej na przeciwny
int minus_zamien(int A[], int n)
{
    int znak = A[n-1];

    for(int i=0; i<n; ++i) // pętla robi "negatyw"
        A[i] = 1-A[i];

    int przeniesienie = 1, i = 0;
    while(przeniesienie && i<n) //pętla dodaje 1
    {
        A[i] += przeniesienie;
        if(A[i] > 1)
            A[i] = 0;
        else
            przeniesienie = 0;
    }

    if(znak == A[n-1])
    {
        if(!przeniesienie)
            return 0; // FALSE
        else
            return 1; // TRUE
    }
    else
        return 1; // TRUE
}