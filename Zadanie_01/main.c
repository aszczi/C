#include <stdio.h>

/*Zad 1. Napisać program korzystający z funkcji scanf i printf, by wczytać od użytkownika pojedynczą liczbę całkowitą, a następnie wypisać ją na ekran w formie ,,Oto twoja liczba: <liczba>''.
Wykorzystać okazję, by ustawić swoje środowisko programistyczne, zaznajomić się z kompilatorem gcc, a także dostosować się do standardowego stylu: https://en.wikibooks.
org/wiki/C_Programming/Structure_and_style . Zalecam też pomyśleć, jak uzmysłowić
użytkownikowi, że ma wpisywać liczbę całkowitą. */
int main(void){

    int wczytana_liczba;
    printf("Wpisz liczbe calkowita\n");
    scanf("%d", &wczytana_liczba);
    printf ("Oto twoja liczba: %d", wczytana_liczba);

    return 0;

}