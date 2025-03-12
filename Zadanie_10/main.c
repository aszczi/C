#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*a) Napisać funkcję, która otrzymuje na wejściu macierz 2x2 (przechowywaną jako tablicę dwuwymiarową) oraz stałą i mnoży macierz przez stałą.
b) Napisać funkcję, która otrzymuje na wejściu dwie macierze 2x2 i dodaje je ze sobą.
c) Tensor Einsteina to Gμν = Rμν - 1/2 gμν R, gdzie Rμν to tensor Ricciego (opisujący odchył ’objętości’ przestrzeni od płaskiej),
 gμν to tensor metryczny (opisujący geometrię czasoprzestrzeni), a R to skalar Ricciego. W tym równaniu tensor Ricciego oraz
 tensor metryczny to zwykłe, dwuwymiarowe, kwadratowe macierze. Należy przechować następujące macierze: gμν = [1, 0, (enter) 0, 1/4] oraz
 Rμν = [1, 0, (enter) 0, 1/4]. Przyjąć stałą R = 2. Wreszcie, wyliczyć macierz Gμν poprzez wykorzystanie wzoru i wcześniej zaimplementowanych operacji.
d) Zmodyfikować funkcje z poprzednich podpunktu, by działały na n-wymiarowych tablicach i alokowały je dynamicznie używając funkcji
malloc/calloc/free. Ponownie wykonać obliczenie Gμν
e) Napisać funkcję mnożącą dwie macierze nxn
f) Tensor Ricciego i skalar Ricciego nie bez powodu mają tę samą nazwę. Skalar tak naprawdę wyliczany jest z tensora.
 By to zrobić, musimy: zaimplementować funkcję, która odwróci nam macierz gμν przy użyciu eliminacji Gaussa-Jordana.
 Odwróconą macierz musimy pomnożyć macierzowo przez macierz Rμν. Wreszcie, musimy wziąć ślad wynikowej macierzy - sumę
 elementów na przekątnej. Wynik to będzie liczba, będąca skalarem Ricciego R. Korzystając z niej możemy obliczyć poprawnie
 macierz Gμν. Zweryfikować, że podana wcześniej wartość R jest poprawna*/


struct macierz {
    double tablica[2][2];
};

struct dowolna_macierz {
    double **tablica;
};

struct macierz mnozenie_przez_stala(double tab[2][2], double stala) {
    int i, j;
    struct macierz m;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            m.tablica[i][j] = tab[i][j] * stala;
        }
    }
    return m;
}

struct macierz dodawanie_macierzy(double tab1[2][2], double tab2[2][2]) {
    struct macierz m;
    int i, j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            m.tablica[i][j] = tab1[i][j] + tab2[i][j];
        }
    }
    return m;
}

struct dowolna_macierz mnozenie_przez_stala_dowolna(double **tab, double stala) {
    int i, j;
    struct dowolna_macierz m;
    int n = sqrt(sizeof(tab));

    m.tablica = malloc(n * sizeof(double *));
    for (i = 0; i < n; i++) {
        m.tablica[i] = malloc(n * sizeof(double));
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            m.tablica[i][j] = tab[i][j] * stala;
        }
    }
    return m;
}


struct dowolna_macierz dodawanie_macierzy_dowolnej(double **tab1, double **tab2) {
    struct dowolna_macierz m;
    int i, j;
    int n = sqrt(sizeof(tab1));

    m.tablica = malloc(n * sizeof(double *));
    for (i = 0; i < n; i++) {
        m.tablica[i] = malloc(n * sizeof(double));
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            m.tablica[i][j] = tab1[i][j] + tab2[i][j];
        }
    }
    return m;
}

struct dowolna_macierz mnozenie_macierzy_dowolnej(double **tab1, double **tab2) {
    struct dowolna_macierz m;
    int i, j, k;
    int n = sqrt(sizeof(tab1));

    m.tablica = malloc(n * sizeof(double *));
    for (i = 0; i < n; i++) {
        m.tablica[i] = malloc(n * sizeof(double));
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            m.tablica[i][j] = 0;
            for (k = 0; k < n; k++) {
                m.tablica[i][j] += tab1[i][k] * tab2[k][j];
            }
        }
    }
    return m;
}

struct dowolna_macierz odwracanie_macierzy(double **tab) {
    struct dowolna_macierz m;
    int i, j, k, ii, jj;

    int n = sqrt(sizeof(tab));

    /* inicjalizujemy macierz jednostkowa*/
    m.tablica = malloc(n * sizeof(double *));
    for (i = 0; i < n; i++) {
        m.tablica[i] = malloc(n * sizeof(double));
        for (j = 0; j < n; j++) {
            if (i == j) {
                m.tablica[i][j] = 1.0;
            } else {
                m.tablica[i][j] = 0.0;
            }
        }
    }

    // eliminacja Gaussa-Jordana
    for (i = 0; i < n; i++) {
        double skala = tab[i][i];
        //------------------
        ii = 1;

        //bo nie mozemy podzielic przez zero
        while (skala == 0) {
            skala = tab[i + ii][j];

            if (skala != 0) {
                for (jj = j; jj < n; jj++) {
                    tab[i][jj] += tab[i + ii][jj];

                    m.tablica[i][jj] += m.tablica[i + ii][jj];
                }
            }
            ii++;
        }


        for (j = 0; j < n; j++) {
            tab[i][j] /= skala;
            m.tablica[i][j] /= skala;
        }

        /* chcemy wyzerowac kolejne elementy w kolumnie*/
        for (k = 0; k < n; k++) {
            if (k != i) {
                double wspolczynnik = tab[k][i];
                for (j = 0; j < n; j++) {
                    tab[k][j] -= wspolczynnik * tab[i][j];
                    m.tablica[k][j] -= wspolczynnik * m.tablica[i][j];
                }
            }
        }
    }

    return m;
}


int main() {
    double gv[2][2] = {{1, 0},
                       {0, 0.25}}; /*tensor metryczny gμν*/
    double Rv[2][2] = {{1, 0},
                       {0, 0.25}}; /* tensor Ricciego Rμν*/
    double R = 2; /*skalar Ricciego*/

    struct macierz m1 = mnozenie_przez_stala(gv, R);
    struct macierz m2 = mnozenie_przez_stala(m1.tablica, -0.5);
    struct macierz Gv = dodawanie_macierzy(Rv, m2.tablica); /*Tensor Einsteina*/

    printf("Obliczane za pomoca macierzy 2x2:\n");
    printf("%f %f\n%f %f\n", Gv.tablica[0][0], Gv.tablica[0][1], Gv.tablica[1][0], Gv.tablica[1][1]);

    double **gv1 = malloc(4 * sizeof(double *));
    gv1[0] = malloc(2 * sizeof(double));
    gv1[1] = malloc(2 * sizeof(double));
    gv1[0][0] = 1;
    gv1[0][1] = 0;
    gv1[1][0] = 0;
    gv1[1][1] = 0.25;

    double **Rv1 = malloc(4 * sizeof(double *));
    Rv1[0] = malloc(2 * sizeof(double));
    Rv1[1] = malloc(2 * sizeof(double));
    Rv1[0][0] = 1;
    Rv1[0][1] = 0;
    Rv1[1][0] = 0;
    Rv1[1][1] = 0.25;


    printf("\nObliczane za pomoca macierzy o wymiarze n:\n");
    struct dowolna_macierz test1 = mnozenie_przez_stala_dowolna(gv1, R);
    struct dowolna_macierz test2 = mnozenie_przez_stala_dowolna(test1.tablica, -0.5);
    struct dowolna_macierz test3 = dodawanie_macierzy_dowolnej(Rv1, test2.tablica);
    printf("%f %f\n%f %f\n", test3.tablica[0][0], test3.tablica[0][1], test3.tablica[1][0], test3.tablica[1][1]);

    printf("\nMnozenie macierzy gμν × Rμν:\n");
    struct dowolna_macierz macierz_wymnozona = mnozenie_macierzy_dowolnej(gv1, Rv1);
    printf("%f %f\n%f %f\n", macierz_wymnozona.tablica[0][0], macierz_wymnozona.tablica[0][1],
           macierz_wymnozona.tablica[1][0], macierz_wymnozona.tablica[1][1]);

    printf("\nObliczanie skalaru Ricciego:\n");
    printf("najpierw odwracamy macierz gμν:\n");
    struct dowolna_macierz odwrocona = odwracanie_macierzy(gv1);
    printf("%f %f\n%f %f\n", odwrocona.tablica[0][0], odwrocona.tablica[0][1], odwrocona.tablica[1][0],
           odwrocona.tablica[1][1]);
    printf("teraz mnozymy odwrocona macierz przez Rμv:\n");
    struct dowolna_macierz macierz_wymnozona2 = mnozenie_macierzy_dowolnej(odwrocona.tablica, Rv1);
    printf("%f %f\n%f %f\n", macierz_wymnozona2.tablica[0][0], macierz_wymnozona2.tablica[0][1],
           macierz_wymnozona2.tablica[1][0], macierz_wymnozona2.tablica[1][1]);
    double R2 = macierz_wymnozona2.tablica[0][0] + macierz_wymnozona2.tablica[1][1];
    printf("po dodaniu elementow po przekatnej otrzymujemy skalar Ricciego R rowny: %f\n", R2);

    /* zwalnianie pamieci */
    free(gv1);
    free(Rv1);
    free(test1.tablica);
    free(test2.tablica);
    free(test3.tablica);
    free(macierz_wymnozona.tablica);

    return 0;
}
