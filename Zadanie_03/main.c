#include <stdio.h>
#include <stdlib.h> /*calloc, free */

#define MAX 1000000000
void sito(int n) {
    int *tab;
    int i, j, nr_indeksu;
    int licznik = 0;



    /* alokujemy pamiec dla tablicy */
    tab = (int *)calloc(MAX, sizeof(int));
    if (tab == NULL) {
        printf("Blad alokacji pamieci.");
        return;
    }


    /* inicjalizujemy tablice*/
    for (i = 0; i < MAX; i++) {
        tab[i] = i;
    }

tab[0]=0;
tab[1]=0;

    /*wykreslamy wielokrotnosci liczb pierwszych*/
    for (i = 2; i < MAX; i++) {
        if (tab[i] != 0) {
            nr_indeksu = i;
            licznik++;
            for (j = i * i; j < MAX; j += i) {
                tab[j] = 0;
            }
        }
        if (licznik == n) {
            break;
        }
    }

    /* wypisywanie n liczb pierwszych*/
    for (i = 2; i <= nr_indeksu; i++) {
        if (tab[i] != 0) {
            printf("%d\n", tab[i]);
        }
    }

    /* zwalniamy pamiec*/
    free(tab);
}

int main() {
    int n;


    printf("Wpisz ile najmniejszych liczb pierwszych chcesz wypisac: \n");
    scanf("%d", &n);
    sito(n);

    return 0;
}