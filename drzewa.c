#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

struct TWezel {
    int w;
    struct TWezel *lsyn, *psyn;
};
typedef struct TWezel drzewo;

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

drzewo *wstaw(drzewo *t, int x) {
    if (t == NULL) {
        drzewo *wynik = malloc(sizeof(drzewo));
        wynik->w = x;
        wynik->lsyn = wynik->psyn = NULL;
        return wynik;
    } else {
        if (t->w > x)
            t->lsyn = wstaw(t->lsyn, x);
        else if (t->w < x)
            t->psyn = wstaw(t->psyn, x);
        return t;
    }
}

int min_wartosc(drzewo *t) {
    drzewo *pom = t;
    while (pom->lsyn) {
        pom = pom->lsyn;
    }
    return pom->w;
}

drzewo *usun(drzewo *t, int x) {
    if (t == NULL)
        return NULL;
    if (t->w == x) {
        if (t->lsyn && t->psyn) {
            t->w = min_wartosc(t->psyn);
            t->psyn = usun(t->psyn, t->w);
            return t;
        } else {
            drzewo *wynik = (t->lsyn == NULL ? t->psyn : t->lsyn);
            free(t);
            return wynik;
        }
    } else if (t->w > x) {
        t->lsyn = usun(t->lsyn, x);
    } else {
        t->psyn = usun(t->psyn, x);
    }
    return t;
}

int wysokosc(drzewo *t) {
    if (t == NULL)
        return -1;
    else
        return 1 + max(wysokosc(t->lsyn), wysokosc(t->psyn));
}

void czysc_drzewo(drzewo *t) {
    if (t) {
        czysc_drzewo(t->lsyn);
        czysc_drzewo(t->psyn);
        free(t);
    }
}

void wypisz_infiksowo(drzewo *t) {
    if (t->lsyn)
        wypisz_infiksowo(t->lsyn);
    printf("%d ", t->w);
    if (t->psyn)
        wypisz_infiksowo(t->psyn);
    printf("\n");
}

drzewo *usunLiscie(drzewo *d) {
    if (d == NULL)
        return NULL;
    else if (d->lsyn == NULL && d->psyn == NULL) {
        free(d);
        return NULL;
    } else {
        d->lsyn = usunLiscie(d->lsyn);
        d->psyn = usunLiscie(d->psyn);
        return d;
    }
}

void oberwij_liscie(drzewo *d) {
    while (d != NULL) {
        d = usunLiscie(d);
        wypisz_infiksowo(d);
    }
}

drzewo *odrzuc(drzewo *d, int a, int b) {
    if (d == NULL)
        return NULL;
    d->lsyn = odrzuc(d->lsyn, a, b);
    d->psyn = odrzuc(d->psyn, a, b);
    if (d->w > b) {
        assert(d->psyn == NULL);
        drzewo *res = d->lsyn;
        free(d);
        return res;
    } else if (d->w < a) {
        assert(d->lsyn == NULL);
        drzewo *res = d->psyn;
        free(d);
        return res;
    } else
        return d;
}

int main() {
    drzewo *t = NULL;
    int x;
    while (x != -1) {
        scanf("%d", &x);
        t = wstaw(t, x);
    }
    wypisz_infiksowo(t);
    return 0;
}