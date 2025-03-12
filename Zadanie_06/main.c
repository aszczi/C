#include <stdio.h>

/*Co ciekawe, renesansowcy mieli odrobinę racji. Złoty podział faktycznie pojawia sie w naturze, gdyż jest on w pewnym sensie
 najbardziej niewymierną liczbą rzeczywistą, trudniejszą do przybliżenia niż większość liczb transcendentalnych. Tym ciekawsze
 jest, że każdą liczbę naturalną da się zapisać w tak zwanym złotym systemie liczbowym (ang. c) w skończonej
 reprezentacji - mimo tak niewymiernej podstawy systemu liczbowego! Proszę napisać program przeliczający podaną dziesiętną liczbę
 naturalną do złotego systemu liczbowego i wypisujący ją na ekran. Hint: opis algorytmu da się znaleźć na artykule z Wikipedii*/



    void zloty_system_liczbowy(float liczba) {
        float fi = 1.61803398874989484820458683436563811772030917980576286213544862270526046281890;
        float potega_fi = 1;
        int ktora_potega = 0;

        /*wyznaczamy najwieksza potega fi jest mniejsza od naszej liczby*/
        if (liczba > 1) {
            while (liczba > (potega_fi * fi)) {
                potega_fi *= fi;
                ktora_potega++;
            }
        }
        else if (liczba == 1){
            printf("1");
            return;
        } else {
            ktora_potega = 0;
            printf("0,");

                while (liczba < potega_fi) {
                    potega_fi /= fi;
                    ktora_potega--;
                }
                potega_fi=1;
        }

        /*zapisujemy liczbe w golden ratio base*/
        while (liczba > 0.0 ) {

            if (liczba >= potega_fi) {
                printf("%d", 1);
                liczba -= potega_fi;
            } else {
                printf("%d", 0);
            }

            if (ktora_potega == 0) {
                printf(",");
                 potega_fi = 1;
            }

            potega_fi /= fi;
            ktora_potega--;
        }
    }


    int main() {
        float liczba;


        printf("Podaj jaka liczbe chcesz zapisac w zlotym systemie liczbowym: \n");
        scanf("%f", &liczba);

        printf("Twoja liczba w zlotym systemie liczbowym to: \n");
        zloty_system_liczbowy(liczba);

        return 0;
    }
