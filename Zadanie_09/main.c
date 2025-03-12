#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*Zrobione podpunkty z zadania pierwszego:

(obowiazkowe) a) W pliku zestaw2zad1.txt znajdują się dane hipotetycznych graczy Dungeons & Dragons w formacie Comma Separated Values:
każda linijka to kolejno imię gracza, imię postaci, klasa postaci, poziom postaci oraz ilość punktów życia postaci; odseparowane przecinkami.
Należy napisać strukturę przechowującą takie dane. Następnie należy użyć funkcji fscanf i innych funkcji związanych z obsługą plików w C do
wczytania tych danych do tablicy o założonej z góry wielkości.

b) Przy użyciu funkcji zarządzających pamięcią calloc/realloc/free tablicę alokować
dynamicznie, i dynamicznie rozszerzać tablicę, gdy skończy się miejsce na dane.

(obowiazkowe) c) Zaimplementować funkcję implementującą wyszukiwanie połówkowe. Jako klucz wyszukiwania użyć imienia gracza, po którym
 dane już są posortowane w pliku.

(obowiazkowe) d) Zaimplementować jednokierunkową listę wskaźnikową. Wykorzystać tę strukturę do przechowywania danych zamiast tablicy,
poprzez dodawanie elementów na koniec listy.

(obowiazkowe) e) Zaimplementować funkcję implementującą na takiej liście wyszukiwanie liniowe. Dlaczego nie możemy użyć połówkowego?

f) Napisać funkcję pozwalającą ’wcisnąć’ nowy element na n-te miejsce w środku listy.

(trudne) g) Zmodyfikować funkcje z poprzednich podpunktu, by móc ’wcisnąć’ nowy element do posortowanej listy tak, by poprzednik był mniejszy,
 a następnik większy od dodawanego elementu. Jako klucz, wedle którego porównujemy, wykorzystać imię postaci. Następnie wykorzystać tę funkcję,
 by posortować dane przez wstawianie.
*/
struct person {
    char name[20];
    char character_name[20];
    char character_class[20];
    int character_level;
    int character_hp;
};

typedef struct node {
    struct person dane;
    struct node *next;
} nodes;

nodes *first; /* pierwszy element listy */
nodes *sortowanie;

void wypisz_liste(nodes *lista) {
    nodes *wsk = lista;
    wsk = wsk->next;/*pomijamy pierwszy element, bo to jest tylko wartownik*/
    while (wsk != NULL) {
        printf("%s %s %s %d %d\n", wsk->dane.name, wsk->dane.character_name, wsk->dane.character_class,
               wsk->dane.character_level, wsk->dane.character_hp); /* 3 */
        wsk = wsk->next;
    }
}

void dodaj_do_listy(nodes *lista, FILE *dane_do_listy) {
    nodes *wsk, *nowy;
    wsk = lista;

    while (wsk->next != NULL) {
        wsk = wsk->next; /* przesuwamy wsk aż znajdziemy ostatni element */
    }

    nowy = (nodes *) malloc(sizeof(nodes));
    fscanf(dane_do_listy, "%[^,],%[^,],%[^,],%d,%d\n", nowy->dane.name, nowy->dane.character_name,
           nowy->dane.character_class, &nowy->dane.character_level, &nowy->dane.character_hp);
    nowy->next = NULL;
    wsk->next = nowy; /* podczepiamy nowy element do ostatniego z listy */
    wsk = nowy;
}

void wyszukiwanie_polowkowe(struct person tablica[100], int lines) {
    char szukane[20];
    printf("\nPodaj imie gracza, ktorego szukasz:\n");
    scanf("%s", szukane);
    int lewy = 0;
    int prawy = lines - 1;
    int srodek;
    int znaleziono = 0;
    int i = 0;

    while (lewy <= prawy) {
        srodek = (lewy + prawy) / 2;
        if (strcmp(szukane, tablica[srodek].name) == 0) { /* porownujemy wpisane dane z danymi z pliku*/
            znaleziono = 1;
            /*jesli jest tylko jedno wystapienie to tyle potrzebujemy do szukania*/
            if (strcmp(szukane, tablica[srodek + 1].name) != 0 &&
                strcmp(szukane, tablica[srodek - 1].name) != 0) {
                printf("%s %s %s %d %d\n", tablica[srodek].name, tablica[srodek].character_name,
                       tablica[srodek].character_class, tablica[srodek].character_level,
                       tablica[srodek].character_hp);
                break;
            }
            /*jesli jest wiecej wystapien to trzeba znalezc pierwsze wystapienie*/
            while (strcmp(szukane, tablica[srodek - 1].name) == 0) {
                srodek--;
            }
            /*mamy juz srodek ustawiony na na pewno pierwsze wystapienie szukanego imienia
            teraz trzeba wypisac wszystkie wystapienia*/
            for (i = srodek; strcmp(szukane, tablica[i].name) == 0; i++) {
                printf("%s %s %s %d %d\n", tablica[srodek].name, tablica[srodek].character_name,
                       tablica[srodek].character_class, tablica[srodek].character_level,
                       tablica[srodek].character_hp);
                srodek++;
            }
            break;

        } else if (strcmp(szukane, tablica[srodek].name) < 0) {
            prawy = srodek - 1;
        } else {
            lewy = srodek + 1;
        }

    }

    if (znaleziono == 0) {
        printf("Nie znaleziono gracza %s\n", szukane);
    }
}

void wyszukiwanie_liniowe(nodes *lista) {
    char szukane[20];
    printf("\nPodaj imie gracza, ktorego szukasz:\n");
    scanf("%s", szukane);
    int znaleziono = 0;

    nodes *wsk = lista;
    wsk = wsk->next; /*pomijamy pierwszy element, bo to jest tylko wartownik*/
    while (wsk != NULL) {
        if (strcmp(szukane, wsk->dane.name) == 0) {
            while (strcmp(szukane, wsk->dane.name) == 0) {
                printf("%s %s %s %d %d\n", wsk->dane.name, wsk->dane.character_name, wsk->dane.character_class,
                       wsk->dane.character_level, wsk->dane.character_hp);
                wsk = wsk->next;
                znaleziono = 1;
            }
            break;
        }
        wsk = wsk->next;
    }

    if (znaleziono == 0) {
        printf("Nie znaleziono gracza %s\n", szukane);
    }
}

void nowy_element_nte_miejsce(nodes *lista) {
    nodes *wsk, *nowy;
    wsk = lista;
    int n;
    printf("\nPodaj na ktore miejsce chcesz wstawic element:\n");
    scanf("%d", &n);
    int i;

    for (i = 1; i < n; i++) {
        wsk = wsk->next; /* przesuwamy wsk aż znajdziemy element przed n-tym*/
    }

    nowy = (nodes *) malloc(sizeof(nodes));
    printf("\nPodaj dane nowej postaci:\n");
    scanf("%s %s %s %d %d", nowy->dane.name, nowy->dane.character_name, nowy->dane.character_class,
          &nowy->dane.character_level, &nowy->dane.character_hp);
    nowy->next = wsk->next;
    wsk->next = nowy;

}


void dodaj_element_posortowany(nodes **first, struct person osoba) {
    nodes *obecny = *first;
    nodes *nowy = (nodes *) malloc(sizeof(nodes));
    nowy->dane = osoba;
    nowy->next = NULL;

    /* Sprawdamy czy wstawiamy na początek*/
    if (*first == NULL || strcmp(osoba.character_name, (*first)->dane.character_name) < 0) {
        nowy->next = *first;
        *first = nowy;
        return;
    }

    /* Szukamy miejsca do wstawienia */
    while (obecny->next != NULL && strcmp(osoba.character_name, obecny->next->dane.character_name) > 0) {
        obecny = obecny->next;
    }

    nowy->next = obecny->next;
    obecny->next = nowy;
}

void sortowanie_przez_wstawianie(nodes **first) {
    nodes *posortowane = NULL;
    nodes *obecny = *first;

    while (obecny != NULL) {
        nodes *next = obecny->next;

        dodaj_element_posortowany(&posortowane, obecny->dane);

        obecny = next;
    }

    *first = posortowane;
}


int main() {
    int i;
    int lines = 0;
    char c;

    /*wczytywanie danych z pliku*/
    FILE *dane;
    dane = fopen("zestaw2zad1.txt", "r");
    if (dane == NULL) {
        printf("Blad przy odczycie pliku\n");
        return 1;
    } else {
        while ((c = fgetc(dane)) != EOF) {        /*zliczanie ilosci linii w pliku*/
            if (c == '\n') lines++;
        }

        rewind(dane); /* bo chcemy czytac plik od poczatku*/

        /*-----------------------------------------------wykonane na tablicy znakow-----------------------------------------------*/

        /*tworzenie tablicy struktur statycznie, jak z podpunktu a*/
        struct person tablica[100];

        /*tworzenie tablicy struktur dynamicznie (to do podpunktu b)*/
        /*struct person *tablica = (struct person*)calloc(5, sizeof(struct person));*/
        /* calloc prezydzielajacy tylko 5 elementow (to za malo ponieważ chcemy wczytac wiecej danych z pliku)*/

        /*powiekszanie rozmiaru tablicy dynamicznej o n elementow*/
        /*int aktualny_rozmiar = 5;
        int n; //n - liczba elementow o jaka chcemy powiekszyc tablice
        aktualny_rozmiar += n;
        tablica = (struct person*)realloc(tablica, aktualny_rozmiar * sizeof(struct person));*/ /*

        /*wczytywanie danych do tablicy struktur*/
        for (i = 0; i < lines; i++) {
            fscanf(dane, "%[^,],%[^,],%[^,],%d,%d\n", tablica[i].name, tablica[i].character_name,
                   tablica[i].character_class, &tablica[i].character_level, &tablica[i].character_hp);
        }

        /*wypisywanie danych z tablicy struktur*/
        printf("Wypisywanie danych z tablicy struktur:\n");
        for (i = 0; i < lines; i++) {
            printf("%s %s %s %d %d\n", tablica[i].name, tablica[i].character_name, tablica[i].character_class,
                   tablica[i].character_level, tablica[i].character_hp);
        }

        /*wyszukiwanie połówkowe*/
        wyszukiwanie_polowkowe(tablica, lines);

        /*zwalnianie pamieci  (do podpunktu b)*/
        /*  free(tablica);*/

        /*-----------------------------------------------wykonane na liscie jednokierunkowej-----------------------------------------------*/
        /*tworzenie listy jednokierunkowej*/
        first = malloc(sizeof(nodes));
        nodes *first_copy = first;
        first->next = NULL;
        sortowanie = malloc(sizeof(nodes));
        nodes *sortowanie_copy = sortowanie;
        sortowanie->next = NULL;

        rewind(dane);

        /*wczytywanie danych do listy jednokierunkowej*/
        for (i = 0; i < lines; i++) {
            dodaj_do_listy(first_copy, dane);
        }
        printf("\nWypisywanie danych z listy:\n");
        wypisz_liste(first);

        /*wyszukiwanie liniowe - musimy uzyc takiego, poniewaz nie mamy dostepu do srodkowego elementu listy
        (nie mozemy przesuwac sie tak swobodnie po liscie, tylko liniowo) */
        wyszukiwanie_liniowe(first);

        /*dodawanie elementu na n-te miejsce*/
        nowy_element_nte_miejsce(first_copy);
        printf("\nLista po dodaniu elementu na n-te miejsce:\n");
        wypisz_liste(first_copy);

        /*sortowanie przez wstawianie*/
        sortowanie_przez_wstawianie(&first_copy);
        printf("\nLista po sortowaniu przez wstawianie:\n");
        wypisz_liste(first_copy);

        /*dodawanie elementu posortowanego*/
        struct person Kamil = {"Kamil", "Camillo", "czarodziej", 1, 1};
        dodaj_element_posortowany(&first_copy, Kamil);
        printf("\nLista po dodaniu elementu posortowanego:\n");
        wypisz_liste(first_copy);
    }
    fclose(dane);

    return 0;
}