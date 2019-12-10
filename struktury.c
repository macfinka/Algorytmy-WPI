#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* Lista */

// tworzenie typu struktury "lista"
struct lista
{
    int w;
    struct lista *nast;
};
typedef struct lista Tlista;
/* LUB
typedef struct lista
{
    int w;
    struct lista *nast;
} Tlista;
*/

// wyszukiwanie w liście
bool jest_x(Tlista *l, int x)
{
    if(!l)
        return 0;
    else if(l->w == x)
        return 1;
    else
        return(jest_x(l->nast, x));
}

// wyszukiwanie iteracyjne
bool jest_x_iter(Tlista *l, int x)
{
    while(l != NULL && l->w != x)
        l = l->nast;
    return (l != NULL);
}

// wstawianie elementu na koniec listy
void wstawZA(Tlista *wsk, int x)
{
    /* wsk != NULL */
    Tlista *pom;
    pom = (Tlista*)malloc(sizeof(Tlista));
    pom->nast = wsk->nast;
    pom->w = x;
    wsk->nast = pom;
}

// wstawianie elementu na początek listy
Tlista *nowy(Tlista *a, int x)
{
    Tlista *wynik = (Tlista*)malloc(sizeof(Tlista));
    if(wynik != NULL)
    {
        wynik->w = x;
        wynik->nast = a;
    }
    return wynik;
}

Tlista *przepisz(int tab[], int n)
{
    Tlista *lista;
    Tlista *ogon = NULL;

    for(int i = n-1; i >= 0; --i)
    {
        lista = nowy(tab[i], &ogon);
        ogon = lista;
    }
    return ogon;
}

// zwraca wskaźnik na odwróconą listę (rekurencyjnie)
Tlista *odwroc(Tlista *p)
{
    if(p == NULL || p->nast == NULL)
        return p;
    Tlista *wynik = odwroc(p->nast);
    (p->nast)->nast = p;
    p->nast = NULL;
    return wynik;
}

// zwraca wskaźnik na odwróconą listę (iteracyjnie)
Tlista *odwroc_it(Tlista *p)
{
    Tlista *wynik, *nastepny;
    wynik = NULL;
    nastepny = p;
    wynik->nast = NULL;
    while(nastepny != NULL)
    {
        p = nastepny;
        nastepny = nastepny->nast;
        p->nast = wynik;
        wynik = p;
    }
    return wynik;
}

// scala dwie posortowane listy w jedną posortowaną listę
Tlista *scal(Tlista *l1, Tlista *l2)
{
    Tlista *atrapa = nowy(0, NULL);
    Tlista *koniec = atrapa;
    while(l1 != NULL && l2 != NULL)
    {
        if(l1->w > l2->w)
        {
            koniec->nast = l2;
            l2 = l2->nast;
        }
        else
        {
            koniec->nast = l1;
            l1 = l1->nast;
        }
        koniec = koniec->nast;
    }
    koniec->nast = !l1 ? l2 : l1;
    l1 = atrapa->nast;
    free(atrapa);
    return l1;
}

// usuwa z listy l1 wszystkie elementy z listy l2
// obie listy są posortowane
Tlista *usun(Tlista *l1, Tlista *l2)
{
    Tlista *atrapa = nowy(0, NULL);
    Tlista *koniec = atrapa;
    while(l1 != NULL && l2 != NULL)
    {
        if(l1->w > l2->w)
            l2 = l2->nast;
        else if(l1->w < l2->w)
        {
            koniec->nast = l1;
            koniec = koniec->nast;
            l1 = l1->nast;
        }
        else
        {
            Tlista *temp = l1;
            l1 = l1->nast;
            free(temp);
            // l2 = l2->nast;
        }
    }
    koniec->nast = l1;
    l1 = atrapa->nast;
    free(atrapa);
    return l1;
}