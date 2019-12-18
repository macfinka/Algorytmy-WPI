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
        return false;
    else if(l->w == x)
        return true;
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
Tlista *nowy(int x, Tlista *a)
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
        lista = nowy(tab[i], ogon);
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
            // po doadaniu tej linijki funkcja usuwa z listy l1 tyle elementów ile ich występuje w liście l2
            // l2 = l2->nast;
        }
    }
    koniec->nast = l1;
    l1 = atrapa->nast;
    free(atrapa);
    return l1;
}

// grupowanie kolorów z nieposortowanej listy
Tlista *flaga_holenderska(Tlista *l){
    Tlista *niebieskie = nowy(42, NULL), *koniec_n = niebieskie;
    Tlista *biale = nowy(50, NULL), *koniec_b = biale;
    Tlista *czerwone = nowy(45, NULL), *koniec_c = czerwone;

    while (l){
        if(l->w < 0){
            koniec_n->nast = l;
            koniec_n = koniec_n->nast;
        } else if(l->w == 0){
            koniec_b->nast = l;
            koniec_b = koniec_b->nast;
        } else{
            koniec_c->nast = l;
            koniec_c = koniec_c->nast;
        }
        l = l->nast;
    }
    koniec_c->nast = NULL;
    koniec_b->nast = czerwone->nast;
    koniec_n->nast = biale->nast;
    l = niebieskie->nast;
    free(niebieskie);
    free(czerwone);
    free(biale);
    return l;
}

// sprawdza czy listy się spotykają (wystarczy sprawdzić czy ostatni element jest taki sam)
bool wspolne(Tlista *l1, Tlista *l2){
    if(!l1 || !l2)
        return false;
    while (l1->nast) l1 = l1->nast;
    while (l2->nast) l2 = l2->nast;
    return (l1 == l2);
}

// zwraca długość listy
int dlugosc_listy(Tlista *l){
    int licznik = 0;
    while (l != NULL){
        ++licznik;
        l = l->nast;
    }
    return licznik;
}

// zwraca wskaźnik na pierwszy wspólny element w obu listach
Tlista *pierwszy_wspolny(Tlista *l1, Tlista *l2){
    int n1 = dlugosc_listy(l1);
    int n2 = dlugosc_listy(l2);
    if(n1 > n2){
        while (n1 > n2){
            l1 = l1->nast;
            --n1;
        }
    } else{
        while (n1 < n2){
            l2 = l2->nast;
            --n2;
        }
    }
    while (l1 != l2){
        l1 = l1->nast;
        l2 = l2->nast;
    }
    return l1;
}

/* Stos */

typedef struct lista Tstack;

bool Empty(Tstack *s){
    return (s == NULL);
}

void Init(Tstack *s){
    s = NULL;
}

void Push(Tstack **s, int x){
    Tstack *pom;
    pom = (Tstack*)malloc(sizeof(Tstack));
    pom->nast = *s;
    pom->w = x;
    *s = pom;
}

// niedokończone
bool czy_lista_cykliczna(Tlista *l){
    if(l == NULL)
        return false;
    Tstack s; Init(s);
    Tstack p; Init(p);
    Tlista temp;
    bool wynik = false;
    while (l != NULL){
        temp = l;
        l = l->nast;
        temp.nast = NULL;
        Push(s, temp);
    }
    while (!Empty(s)){
        Push(p, pop(s));
        if(top(p) == temp){
            wynik = true;
        }
    }
}

// niedokończone
bool czy_poprawne_nawiasy(char *nawiasy){
    int i = 0, flag = 1;
    Tstack *s;
    Init(s);
    char t = nawiasy[i];
    while (t != '\0' && flag){
        if(t == '(' || t == '[')
            Push(s, t);
        else{
            if(Empty(s))
                flag = 0;
            else{
                char c;
                Pop(s, &c);
            }
        }
    }
}

int max_odl(int n, int A[]){
    Tstack *s;
    Init(s);
    Push(s, n - 1);
    int last = n - 1;
    for (int i = n - 2; i >= 0; --i) {
        if(A[i] > A[Top(last)]){
            Push(s, i);
            last = i;
        }
    }
    bool flag = true;
    int i = 0, wynik = 0;
    while (!Empty(s) && flag){
        int w;
        Top(s, &w);
        if(A[i] <= A[w]){
            if(w - i > wynik)
                wynik = w - i;
            Pop(s, &w);
        } else {
            ++i;
            flag = n-1-i > wynik;
        }
    }
    Clear(s);
    return wynik;
}

/* Drzewa */

typedef struct wezel{
    int w;
    struct wezel *lsyn;
    struct wezel *psyn;
} Td;

// funkcja liczy ilość węzłów
int wezly(Td* d){
    if(d == NULL)
        return -1;
    else
        return max(wezly(d->lsyn), wezly(d->psyn)) + 1;
}