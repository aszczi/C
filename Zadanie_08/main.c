#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*W nauce często natrafimy na sytuacje, w których dokładne modelowanie jakiegoś procesu
statystycznego jest zbyt trudne. Jednocześnie mając opis statystyczny mamy de facto gotowy
przepis, jak 'wylosować' jednego reprezentanta naszego modelu. Z tego faktu korzystają tak
zwane metody Monte Carlo. Ich zasadą działania jest to, że powtórzenie jakiegoś eksperymentu statystycznego
np. 100 lub 1000 razy może być wystarczające, by wyciągnąć jakieś wnioski. Proszę korzystając z metody Monte Carlo
policzyć stałą π -- losujemy punkt na płaszczyźnie z kwadratu jednostkowego x nalezy do [0, 1), y nalezy do [0, 1),
a następnie sprawdzamy, czy trafił w koło x^2 + y^2 < 1. Prawdopodobieństwo trafienia to π/4, zatem wykonując takie
losowanie n razy i dostając k trafień możemy przybliżyć π/4 ~= k/n. Do losowania korzystamy z funkcji srand i rand
z nagłówka stdlib.h. Proszę sprawdzić, ile prób n daje naprawdę porządne przybliżenie wartości π.
Dla chętnych: spróbować znaleźć podobną metodę do znalezienia podstawy logarytmu naturalnego e.*/


int main() {
    double x;
    double y;
    double dlugosc_promienia;
    long long ilosc_trafien=0;
    double prawdopodobienstwo;
    long long i;
    double pi;

    srand(time(NULL));

    for(i = 0; i < 1000000000; i++) {
        x = ((double)rand()/32767.0); /* losowanie liczby z przedzialu [0,1) */
        y = ((double)rand()/32767.0);

        dlugosc_promienia = x*x + y*y;

            if(dlugosc_promienia < 1){
                ilosc_trafien++;
            }

    }


    prawdopodobienstwo = (double)ilosc_trafien/1000000000;
    printf("Prawdopodobienstwo trafienia wewnatrz kola o promieniu 1 wynosi: %f\n", prawdopodobienstwo);
    pi = (double)ilosc_trafien/250000000;
    printf("Przyblizona wartosc liczby pi wynosi: %f\n", pi);

    /*obserwacje: */
    /*przy tysiącu prob otrzymujemy przyblizenie pi do 1 miejsca po przecinku*/
    /*przy milionie prob otrzymujemy przyblizenie pi do 2 miejsc po przecinku*/
    /*przy 100 milionach prob otrzymujemy przyblizenie pi do 3 miejsc po przecinku*/
    /*przy bilionie prob otrzymujemy przyblizenie pi do 4 miejsc po przecinku*/

    return 0;

}
