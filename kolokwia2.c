#include <stdio.h>
#include <stdlib.h>
#include <struktury.c>
#include <algorytmy PChW na stosach>

// K2 Zadanie 4 - 20.12.2018
// aby uruchomić należy wywołać w main "SW(tu, tam, n)"

void przenies(int n,int s,int d)
{
    printf("przenosze nr %d z %d na %d\n",n,s,d);
}

void czysc(int tu[],int cel,int n){
    for(int i = n; i >= 0; i--){
        if(tu[i] != cel){
            czysc(tu,6-cel-tu[i],i-1);
            przenies(i,tu[i],cel);
            tu[i] = cel;
        }
    }
}

void SpelniamyMarzenia(int tu[],int tam[],int n)
{
    for(int i = n-1; i >= 0; i--){
        if(tu[i]!=tam[i]){
            czysc(tu,6-tu[i]-tam[i],i-1);
            przenies(i,tu[i],tam[i]);
        }
    }
}

// K2 Zadanie 1 - 21.12.2017
int elitarny_mimuw (int *A, int n)
{
    if (n == 1) return (A[0] == 0);
    int  l = 0, p = n - 1, licznik = 0;
    while (l < p)
    {
        int s = (l + p) / 2;
        if (s > A[s] && abs (A[s] - s) > abs (A[s+1] - s - 1))
            l = s + 1;
        else p = s;
    }
    if (A[l] == l) ++licznik;
    l = 0, p = n - 1;
    while (l < p)
    {
        int s = (l + p) / 2;
        if (s < A[s] && abs (A[s] - s) > abs (A[s+1] - s - 1))
            l = s + 1;
        else p = s;
    }
    if (A[l] == l) ++licznik;

    return licznik;
}

// K2 Zadanie 2 - 21.12.2017

void wypisz(int* pom, int n){
    for(int i = 0; i < 2*n; i++){
        printf("%d", pom[i]);
    }
    printf("\n");
}

void uzupelnij(int* pom, int start, int n, int wrt){
    for(int i = start; i < 2*n; i++){
        pom[i] = wrt;
    }
}

void rek(int* pom, int n, int i, int ileJed){
    if(ileJed == 0){
        uzupelnij(pom, i, n, 0);
        wypisz(pom, n);
    } else if(2*n - i == ileJed){
        uzupelnij(pom, i, n, 1);
        wypisz(pom, n);
    } else {
        pom[i] = 0;
        rek(pom, n, i+1, ileJed);
        pom[i] = 1;
        rek(pom, n, i+1, ileJed-1);
    }
}

void rek_v2(int* pom, int n, int i, int ileJed, int ileZer){
    if(ileJed < n){
        pom[i] = 1;
        rek_v2(pom, n, i+1,ileJed + 1, ileZer);
    }
    if(ileZer < n){
        pom[i] = 0;
        rek_v2(pom, n, i+1, ileJed, ileZer + 1);
    }
    if(i == 2*n)
        wypisz(pom, n);
}


void ZeraJedynki(int n){
    int* pom = (int*) malloc(2*n * sizeof(int));
    //rek(pom, n, 0, n);
    rek_v2(pom,n, 0, 0, 0);
    free(pom);
}

// K2 Zadanie 1 - 20.12.2012

void bez_srednich(Tlista *l){
    if(l != NULL)
        return;
    int last_val = l->w;
    l = l->nast;
    while (l->nast){
        if(2*l->w == last_val + l->nast->w){
            last_val = l->w;
            Tlista *temp = l;
            l = l->nast;
            free(temp);
        } else {
            last_val = l->w;
            l = l->nast;
        }
    }
}

// K3 Zadanie 6 - 17.01.2019
// by Szymon Piątek

void *czysc(Tlista *l){
    Tstact *s;
    Init(s);
    odwroc(l);
    Tlista *temp = l;
    Push(s, INT_MIN);
    while (l != NULL){
        if(l->w % 2 == 0 && l->w >= Top(s))
            Push(s, l->w);
        l = l->nast;
    }
    l = temp;
    odwroc(l);
    Tstack *do_usuniecia;
    int min_np = INT_MAX;
    while (l != NULL){
        if(l->w >= Top(s) && l->w <= min_np)
            Push(do_usuniecia, l);
        if(l->w % 2 == 1){
            if (l->w > min_np)
                min_np = l->w;
        } else {
            if(l->w == Top(s))
                Pop(s);
        }
        l = l->nast;
    }
    Clear(s);
    l = temp;
    odwroc(l);
    temp = l;

    Tlista *wynik = (Tlista*)malloc(sizeof(Tlista));
    while (l != NULL){
        if(!Empty(do_usuniecia)){
            if(l != Top(do_usuniecia))
                wstawZA(wynik, l->w);
            else
                Pop(do_usuniecia);
        }
        else
            wstawZA(wynik, l->w);
        l = l->nast;
        free(temp);
        l = wynik;
        free(wynik);
        Clear(do_usuniecia);
    }
}

// K2 Zadanie 1 - 2013

void dodaj(int *wartosc, int *ilosc, int liczba){

    for (int i = 0; i < (*ilosc); ++i) liczba *= 10;
    *wartosc = (*wartosc) + liczba;
    ++(*ilosc);
}

void bin(int n, int wartosc, int ilosc){
    wartosc = 0;
    ilosc = 0;

    if(n <= 0)
        return;

    int pop = n % 2;
    n /= 2;

    while(n){
        if(pop == 0){
            dodaj(&wartosc, &ilosc, 2);
            while(n%2==0){
                dodaj(&wartosc, &ilosc, 1);
                n/=2;
            }

        } else {
            dodaj(&wartosc, &ilosc, 1); // pop == 1
            pop = n % 2;
        }
        n /= 2;
    }
    if(pop)
        dodaj(&wartosc, &ilosc, pop);

    printf("%d %d", ilosc, wartosc);
}

// K2 Zadanie 2 - 2013

// Rozwiązanie 1
void podzial(int A[], int n, int ile1, int index){
    if(index == 2*n){
        wypisz(A, 2*n);
        return;
    }
    if(ile1 > n)
        return;
    if(index - ile1 < ile1){
        for (int i = 1; i < 2; ++i) {
            A[index] = i;
            podzial(A, n, ile1 + (i == 1), index + 1);
        }
    } else if(index - ile1 == ile1){
        A[index] = 1;
        podzial(A, n, ile1 + 1, index + 1);
    }
}

void Hanoi1(int n){
    int A[n];
    podzial(A, n, 0, 0);
}

// Rozwiązanie 2
void pomHanoi(int tab[], int n, int gdzie, int ile1, int ile2){
    if(gdzie == 2*n)
        wypisz(tab, 2*n);
    else{
        if(ile1 > ile2){
            tab[gdzie] = 2;
            pomHanoi(tab, n, gdzie + 1, ile1 + 1, ile2 + 1);
            if(ile1 < n){
                tab[gdzie] = 1;
                pomHanoi(tab, n, gdzie + 1, ile1 + 1, ile2 + 1);
            }
        } else {
            tab[gdzie] = 1;
            pomHanoi(tab, n, gdzie + 1, ile1 + 1, ile2 + 1);
        }
    }
}

void Hanoi2(int n){
    int tab[n];
    pomHanoi(tab, n, 0, 0, 0);
}