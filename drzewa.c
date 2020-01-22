#include <stdio.h>
#include <stdlib.h>

struct TBST {
    int w;
    struct TBST *lsyn, *psyn;
};
typedef struct TBST BST;

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

BST *wstaw(BST *t, int x) {
    if (t == NULL) {
        BST *wynik = (BST*)malloc(sizeof(BST));
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

int min_wartosc(BST *t) {
    BST *pom = t;
    while (pom->lsyn) {
        pom = pom->lsyn;
    }
    return pom->w;
}

BST *usun(BST *t, int x) {
    if (t == NULL)
        return NULL;
    if (t->w == x) {
        if (t->lsyn && t->psyn) {
            t->w = min_wartosc(t->psyn);
            t->psyn = usun(t->psyn, t->w);
            return t;
        } else {
            BST *wynik = (t->lsyn == NULL ? t->psyn : t->lsyn);
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

int wysokosc(BST *t) {
    if (t == NULL)
        return -1;
    else
        return 1 + max(wysokosc(t->lsyn), wysokosc(t->psyn));
}

void czysc_drzewo(BST *t) {
    if (t) {
        czysc_drzewo(t->lsyn);
        czysc_drzewo(t->psyn);
        free(t);
    }
}

void wypisz_infiksowo(BST *t) {
    if (t->lsyn)
        wypisz_infiksowo(t->lsyn);
    printf("%d ", t->w);
    if (t->psyn)
        wypisz_infiksowo(t->psyn);
    printf("\n");
}

int main() {
    BST *t = NULL;
    int x;
    while (x != -1) {
        scanf("%d", &x);
        t = wstaw(t, x);
    }
    wypisz_infiksowo(t);
    return 0;
}