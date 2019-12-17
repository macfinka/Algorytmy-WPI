#include <stdio.h>
#include <stdbool.h>

struct lista 
{
    int w;
    struct lista *nast;
};
typedef struct lista Tlista;

void odwroć_liste(Tlista** l)
{
    Tlista* nl = NULL;
    Tlista* pom;
    while(*l != NULL)
    {
        pom = (*l)->nast;
        (*l)->nast = nl;
        nl = *l;
        *l = pom;
    }
    *l = nl;
}

void dodaj_na_początek(Tlista** l, int w)
{
    Tlista* nowy_element = malloc(sizeof(Tlista));
    nowy_element->nast = *l;
    *l = nowy_element;
    nowy_element->w = w;
}

void zniszcz_listę(Tlista**l)
{
    if(*l == NULL) return;
    Tlista* pom = (*l)->nast;
    while(pom != NULL)
    {
        free(*l);
        *l = pom;
        pom = (*l)->nast;
    }
    free(*l);
    *l = NULL;
}

struct lista_dwustronna
{
    Tlista *początek,*koniec;
};

typedef struct lista_dwustronna Tlista_dwustronna;

Tlista_dwustronna* stwórz_dwustronną()
{
    Tlista_dwustronna* nowa_dwustronna = malloc(sizeof(struct lista_dwustronna));
    nowa_dwustronna->początek = malloc(sizeof(Tlista));
    nowa_dwustronna->koniec = malloc(sizeof(Tlista));
    nowa_dwustronna->początek->nast = nowa_dwustronna->koniec;
    nowa_dwustronna->koniec->nast = nowa_dwustronna->początek;
}

void dodaj_na_początek_dwustronnej(Tlista_dwustronna* dwustronna, int w)
{
    Tlista* nowy_element = malloc(sizeof(Tlista));
    nowy_element->w = w;
    Tlista* pom = dwustronna->początek->nast;
    pom->nast = nowy_element;
    nowy_element->nast = dwustronna->początek;
    dwustronna->początek->nast = nowy_element;
}

void dodaj_na_koniec_dwustronnej(Tlista_dwustronna* dwustronna, int w)
{
    Tlista* nowy_element = malloc(sizeof(Tlista));
    nowy_element->w = w;
    Tlista* pom = dwustronna->koniec->nast;
    dwustronna->koniec->nast = nowy_element;
    nowy_element->nast = pom;
}

void usuń_z_początka_dwustronnej(Tlista_dwustronna* dwustronna)
{
    if(dwustronna->początek->nast->nast == NULL) return;
    Tlista* pom = dwustronna->początek->nast->nast;
    free(pom->nast);
    pom->nast = dwustronna->początek;
    dwustronna->początek->nast = pom;
}

void usuń_z_końca_dwustronnej(Tlista_dwustronna* dwustronna)
{
    if(dwustronna->koniec->nast->nast == NULL) return;
    Tlista* pom = dwustronna->koniec->nast->nast;
    free(dwustronna->koniec->nast);
    dwustronna->koniec->nast = pom;
}

void zniszcz_dwustronną(Tlista_dwustronna** dwustronna)
{
    Tlista* pom  = (*dwustronna)->początek->nast;
    pom->nast = NULL;
    free((*dwustronna)->początek);
    zniszcz_listę(&((*dwustronna)->koniec));
    free(*dwustronna);
    *dwustronna = NULL;
}

bool czy_cykliczna(Tlista* l)
{
    Tlista *szybki=l,*wolny=l;
    while(szybki != NULL && szybki != wolny)
    {
        wolny = wolny -> nast;
        szybki = szybki -> nast;
        if(szybki) szybki = szybki -> nast;
    }
    if(szybki != NULL) return 1;
    return 0;
}


Tlista* daj_pierwszy_element_cyklu(Tlista* l)
{
    Tlista *szybki=l,*wolny=l;
    while(szybki != NULL && szybki != wolny)
    {
        wolny = wolny -> nast;
        szybki = szybki -> nast;
        if(szybki) szybki = szybki -> nast;
    }
    if(szybki == NULL) return NULL;
    wolny = l;
    while(wolny != szybki)
    {
        wolny = wolny -> nast;
        szybki = szybki -> nast;
    }
    return wolny;
}

//Listy bez cyklów
Tlista* czy_dwie_listy_maja_wspolny_koniec(Tlista* l1, Tlista*l2)
{
    Tlista* i1 = l1, *i2 = l2;

    while(i1 != NULL && i2 != NULL)
    {
        i1 = i1 -> nast;
        i2 = i2 -> nast;
    }

    int c1 = 0, c2 = 0;

    while(i1 != NULL)
    {
        c1++;
        i1 = i1 -> nast;
    }

    while(i2 != NULL)
    {
        c2++;
        i2 = i2 -> nast;
    }

    i1 = l1;
    i2 = l2;

    while(c1 > 0)
    {
        c1--;
        i1 = i1 -> nast;
    }

    while(c2 > 0)
    {
        c2--;
        i2 = i2 -> nast;
    }

    while(i1 != NULL && i2 != NULL && i1 != i2)
    {
        i1 = i1 -> nast;
        i2 = i2 -> nast;
    }
    if(i1 != NULL) return i1;
    return NULL;
}

//Listy z cyklami
Tlista* czy_dwie_listy_maja_wspolny_koniec_z_cyklami(Tlista* l1, Tlista*l2)
{
    Tlista* i1 = daj_pierwszy_element_cyklu(l1), *i2 = daj_pierwszy_element_cyklu(l2);
    if(i1 == i2)
    {
        Tlista* p = i1;
        i1 = l1;
        i2 = l2;

        while(i1 != p && i2 != p)
        {
            i1 = i1 -> nast;
            i2 = i2 -> nast;
        }

        int c1 = 0, c2 = 0;

        while(i1 != p)
        {
            c1++;
            i1 = i1 -> nast;
        }

        while(i2 != p)
        {
            c2++;
            i2 = i2 -> nast;
        }

        i1 = l1;
        i2 = l2;

        while(c1 > 0)
        {
            c1--;
            i1 = i1 -> nast;
        }

        while(c2 > 0)
        {
            c2--;
            i2 = i2 -> nast;
        }

        while(i1 != p && i2 != p && i1 != i2)
        {
            i1 = i1 -> nast;
            i2 = i2 -> nast;
        }
        if(i1 != p) return i1;
        return p;
    }
    else
    {
        Tlista* p = i1;
        p = p -> nast;
        while(p != i1)
        {
            if(p == i2) return i2;
            p = p -> nast;
        }
        return NULL;
    }
}