#include <stdio.h>
#include <time.h> /*uzywamy do pomiaru czasu*/

/*W sztuce renesansowej bardzo powszechny był pogląd, iż zarówno w naturze jak i w dziełach
sztuki najbardziej estetycznym i najczęściej występującym stosunkiem długości jest tak
zwany złoty podział. Możemy go uzyskać, obliczając ciąg Fibonacciego i dzieląc kolejne
elementy ciągu przez siebie, przez co ciągowi Fibonacciego przypisywano prawie że boski
przyimek. Jednak nie jest to jedyny ciąg z taką własnością, co spróbujemy sobie udowodnić.
Proszę napisać program liczący N-ty wyraz ciągu Lucasa. Obliczenia należy powtórzyć
w kilku odrębnych funkcjach: jednej funkcji zwracającej typ int i liczącej ciąg iteracyjnie
(np. pętlą while), jednej funkcji zwracającej typ long i liczącej ciąg iteracyjnie, oraz jednej
funkcji zwracającej typ long i liczącej ciąg rekurencyjnie. Porównać, jak daleko możemy
policzyć korzystając z różnych typów oraz jak szybko następuje wykonanie każdej z funkcji
(jak mierzyć czas w pierwszej odpowiedzi). Wreszcie, proszę napisać funkcję która policzy
stosunek liczby N-tej do N-1-ej i wypisze go na ekran, wraz z wartością złotego podziału
z np. Wikipedii. W tym celu niezbędne będzie skorzystanie z typu zmiennoprzecinkowego
float bądź double.*/

int lucas_iteracyjnie_int(int n) {
    int wyraz_pierwszy = 2;
    int wyraz_drugi = 1;
    int suma_poprzednich_wyrazow;
    int i = 2;


    if (n < 1) {
        return 0;
    }else if (n == 1){
        return wyraz_pierwszy;
    }else if (n == 2) {
        return wyraz_drugi;
    }

    while (i < n) {
        suma_poprzednich_wyrazow = wyraz_drugi + wyraz_pierwszy;
        wyraz_pierwszy = wyraz_drugi;
        wyraz_drugi = suma_poprzednich_wyrazow;
        i++;
    }

    return suma_poprzednich_wyrazow;
}

long lucas_iteracyjnie_long(int n) {
    long wyraz_pierwszy = 2;
    long wyraz_drugi = 1;
    long suma_poprzednich_wyrazow;
    int i = 2;


    if (n < 1) {
        return 0;
    }else if (n == 1){
        return wyraz_pierwszy;
    }else if (n == 2) {
        return wyraz_drugi;
    }

    while (i < n) {
        suma_poprzednich_wyrazow = wyraz_drugi + wyraz_pierwszy;
        wyraz_pierwszy = wyraz_drugi;
        wyraz_drugi = suma_poprzednich_wyrazow;
        i++;
    }

    return suma_poprzednich_wyrazow;
}

long lucas_rekurencyjnie_long(int n) {
    long wyraz_pierwszy = 2;
    long wyraz_drugi = 1;


    if (n < 1) {
        return 0;
    }else if (n == 1){
        return wyraz_pierwszy;
    }else if (n == 2) {
        return wyraz_drugi;
    }

    return lucas_rekurencyjnie_long(n - 1) + lucas_rekurencyjnie_long(n - 2);
}

void lucas_stosunek_kolejnych_wyrazow(int n) {
    float fi= 1.61803398874989484820458683436563811772030917980576286213544862270526046281890;
    float stosunek=(float)lucas_iteracyjnie_long(n)/(float)lucas_iteracyjnie_long(n - 1);

    printf("stosunek n-tego wyrazu do n-1: %f\n", stosunek);
    printf("wartosc zlotego podzialu z wikipedii: %f\n", fi);
};

int main() {
    int n; /*wyraz ciagu lucasa, ktory chcemy policzyc*/
    clock_t start, end;    /*zmienne do mierzenia czasu*/
    float czas_wykonania;
    long najwieksza_liczba_long=-1;
    int najwieksza_liczba_int=-1;
    long i=0; /*iterator*/


    printf("Wpisz, ktory wyraz ciagu lucasa chcesz policzyc: ");
    scanf("%d", &n);

    /*mierzymy czasy wykonania dla kazdej funkcji*/

    start=clock();
    int iter_int = lucas_iteracyjnie_int(n);
    end=clock();
    czas_wykonania = (float)(end-start)/CLOCKS_PER_SEC;
    printf("czas wykonania iteracyjnie na intach: %f\n", czas_wykonania);

    start=clock();
    long iter_long = lucas_iteracyjnie_long(n);
    end=clock();
    czas_wykonania = (float)(end-start)/CLOCKS_PER_SEC;
    printf("czas wykonania iteracyjnie na longach: %f\n", czas_wykonania);

    start=clock();
    long rec_long = lucas_rekurencyjnie_long(n);
    end=clock();
    czas_wykonania = (float)(end-start)/CLOCKS_PER_SEC;
    printf("czas wykonania rekurencyjnie na longach: %f\n", czas_wykonania);


    printf("liczone iteracyjnie na intach: %d\n", iter_int);
    printf("liczone iteracyjnie na longach: %ld\n", iter_long);
    printf("liczone rekurencyjnie na longach: %ld\n", rec_long);
    lucas_stosunek_kolejnych_wyrazow(n);

    /*sprawdzamy najwieksza liczbe jaka mozemy policzyc za pomoca long*/
    while(i>=0){
        najwieksza_liczba_long++;
        i = lucas_iteracyjnie_long(najwieksza_liczba_long);

    }
    printf("maksymalna wartosc jaka mozemy wyliczyc za pomoca long to %ld, poniewaz dla %ld wyrazu przekraczamy zakres longa\n", najwieksza_liczba_long-1, najwieksza_liczba_long);

    i=0;

    /*sprawdzamy najwieksza liczbe jaka mozemy policzyc za pomoca int*/
    while(i>=0){

        najwieksza_liczba_int++;
        i = lucas_iteracyjnie_int(najwieksza_liczba_int);

    }
    printf("maksymalna wartosc jaka mozemy wyliczyc za pomoca int to %d, poniewaz dla %d wyrazu przekraczamy zakres int\n", najwieksza_liczba_int-1, najwieksza_liczba_int);


    return 0;
}
