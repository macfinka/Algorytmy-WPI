#include <stdio.h>
#include <stdbool.h>
#include "drzewa.c"

int ile_wierszy(FILE *f) {
    int iw = 0;
    char c = fgetc(f);
    while (!feof(f)) {      // c != EOF
        while (c != '\n' && !feof(f)) {
            c = fgetc(f);
        }
        ++iw;
    }
    return iw;
}

int ile_wierszy_v2(FILE *f) {
    int ile = 0;
    char c;
    while (!feof(f)) {
        if ((c = fgetc(f)) == '\n')
            ++ile;
    }
    return ile + (c != '\n');
}

// sprawdza czy oba pliki mają tyle samo wierszy
bool rowno_wierszy(char *s1, char *s2) {
    FILE *f1 = fopen(s1, "r"), *f2 = fopen(s2, "r");
    int w1 = ile_wierszy(f1);
    int w2 = ile_wierszy(f2);
    fclose(f1);
    fclose(f2);
    return (w1 == w2);
}

bool wiersze(char *s1, char *s2) {
    FILE *f = fopen(s1, "r");
    FILE *g = fopen(s2, "r");
    char c, e;
    int i1 = 0, i2 = 0;
    while (!feof(f) && !feof(g)) {
        if ((c = fgetc(f)) == '\n') ++i1;
        if ((e = fgetc(g)) == '\n') ++i2;
    }
    while (!feof(f) && i1 <= i2 + 1) {
        if ((c = fgetc(f)) == '\n') ++i1;
    }
    while (!feof(g) && i2 <= i1 + 1) {
        if ((e = fgetc(g)) == '\n') ++i2;
    }
    if (c == '\n') ++i1;
    if (e == '\n') ++i2;

    return (i1 == i2);
}

bool czyBialy(char c) {
    return c == ' ' || c == '\n' || c == '\t';
}

void licz(int *slowa, int *wiersze, int *znaki, FILE *plik) {
    bool litera = false;
    *znaki = 0;
    *wiersze = 0;
    *slowa = 0;
    char c;
    while (!feof(plik)) {
        ++(*znaki);
        c = fgetc(plik);
        if (c == '\n')
            ++(*wiersze);
        if (!czyBialy(c))
            litera = true;
        else if (litera) {
            ++(*slowa);
            litera = false;
        }
    }
    if (litera)
        ++(*slowa);
    if (c != '\n')
        ++(*wiersze);
}

void rek_zapisz_drzewo(FILE *f, BST *d) {
    if (d) {
        bool lsyn = (d->lsyn != NULL);
        bool psyn = (d->psyn != NULL);
        fprintf(f, "%d %d %d\n", d->w, lsyn, psyn);
        rek_zapisz_drzewo(f, d->lsyn);
        rek_zapisz_drzewo(f, d->psyn);
    }
}

void zapisz_drzewo(char *nazwa_pliku, BST *d) {
    FILE *f = fopen(nazwa_pliku, "w");
    if (f)
        rek_zapisz_drzewo(f, d);
    fclose(f);
}

BST *rek_odczytaj_drzewo(FILE *f) {
    int w, lsyn, psyn;
    fscanf(f, "%d %d %d", &w, &lsyn, &psyn);
    BST *d = malloc(sizeof(BST));
    d->w = w;
    d->lsyn = lsyn ? rek_odczytaj_drzewo(f) : NULL;
    d->psyn = psyn ? rek_odczytaj_drzewo(f) : NULL;
    return d;
}

BST *odczytaj_drzewo(char *nazwa_pliku) {
    FILE *f = fopen(nazwa_pliku, "r");
    BST *d = NULL;
    if (f && !feof(f))
        d = rek_odczytaj_drzewo(f);
    fclose(f);
    return d;
}

// zapis i odczyt dla plików binarnych
void bin_rek_zapisz_drzewo(FILE *f, BST *d) {
    if (d) {
        int arr[] = {d->w, d->lsyn != NULL, d->psyn != NULL};
        fwrite(arr, sizeof(int), 3, f);
        rek_zapisz_drzewo(f, d->lsyn);
        rek_zapisz_drzewo(f, d->psyn);
    }
}

void bin_zapisz_drzewo(char *nazwa_pliku, BST *d) {
    FILE *f = fopen(nazwa_pliku, "wb");
    if (f)
        rek_zapisz_drzewo(f, d);
    fclose(f);
}

BST *bin_rek_odczytaj_drzewo(FILE *f) {
    int arr[3];
    fread(arr, sizeof(int), 3, f);
    BST *d = malloc(sizeof(BST));
    d->w = arr[0];
    d->lsyn = arr[1] ? rek_odczytaj_drzewo(f) : NULL;
    d->psyn = arr[2] ? rek_odczytaj_drzewo(f) : NULL;
    return d;
}

BST *bin_odczytaj_drzewo(char *nazwa_pliku) {
    FILE *f = fopen(nazwa_pliku, "rb");
    BST *d = NULL;
    if (f && !feof(f))
        d = rek_odczytaj_drzewo(f);
    fclose(f);
    return d;
}