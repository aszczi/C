#include <stdio.h>
#include <string.h>

/*Napisać program tym razem wczytujący imię oraz nazwisko użytkownika (dla uproszczenia
bez polskich znaków) i wypisujący na jej podstawie (najlepiej korzystając z wartości
 odpowiadających literom w tabeli wartości ASCII) liczbę numerologiczną pełnego nazwiska
danej osoby. Obliczyć także oddzielnie liczbę imienia i liczbę nazwiska. Program powinien
dawać sobie radę z podawaniem także więcej niż pierwszego imienia (np. format <pierwsze
imię> <drugie imię> <nazwisko>). W tym celu muszą państwo zaznajomić się z ciągami
znaków (ang. string) i podstawowymi na nich operacjami w C, najczęściej do znalezienia
w pliku nagłówkowym string.h.

 !!! i potrzebujemy jeszcze funkcji ktora bedzie liczyla liczbe numerologiczna z całości !!!
 */


int liczba_numerologiczna(int dlugosc_wyrazu, char * wyraz){
    int suma=0;
    int i;
    int suma_koncowa=0;

    for(i=0; i<dlugosc_wyrazu; i++){
        if(wyraz[i] != ' '){
            suma += wyraz[i];
        }

    }


    while(suma >= 10){
        if(suma == 11 || suma == 22 || suma == 33) {
            return suma;
            } else {
                suma_koncowa += suma%10;
                suma = suma/10;
            }

        if (suma < 10){
            suma_koncowa += suma;
            suma=suma_koncowa;
            suma_koncowa=0;
        }
    }


            return suma;

}



int main() {

    char imie[100];
    int liczba_nazwiska;
    int liczba_imienia;
    int liczba_numerologiczna_calosci;
    char * ost_wyraz;
    int i;

    printf("Wpisz swoje imie/imiona i nazwisko: \n");
    scanf("%[^\n]s", imie);

    liczba_numerologiczna_calosci = liczba_numerologiczna(strlen(imie), imie);
    printf("Liczba numerologiczna calosci: %d\n", liczba_numerologiczna_calosci);

    ost_wyraz =( strrchr( imie, ' ' )); /*ostatni wyraz na poczastku ktorego jest jeszce spacja*/
    ost_wyraz++;   /*przesuwamy wskaznik na pierwsza litere ostatniego wyrazu aby nie miec juz tej spacji.*/

    liczba_nazwiska = liczba_numerologiczna(strlen(ost_wyraz), ost_wyraz);
    printf("Liczba numerologiczna nazwiska: %d\n", liczba_nazwiska);

    ost_wyraz--; /*wskaznik jest ustawiony spowrotem na spacji*/
    *ost_wyraz= '\0'; /*zamieniamy spacje na znak konca stringa*/

    while(ost_wyraz=( strrchr( imie, ' ' ))){
         /*wskaznik jest ustawiony na ostatniej spacji, jesli nie ma juz spacji to wskaznik bedzie nullem czyli petla sie zakonczy*/

        ost_wyraz++; /*wskaznik jest ustawiony na 1 literze wyrazu*/

        liczba_imienia = liczba_numerologiczna(strlen(ost_wyraz), ost_wyraz);

        printf("liczba numerologiczna imienia %s: %d\n", ost_wyraz, liczba_imienia);

        ost_wyraz--; /*wskaznik jest ustawiony na spacji*/
        *ost_wyraz = '\0'; /*zamieniamy spacje na znak konca stringa*/

    }


    liczba_imienia = liczba_numerologiczna(strlen(imie), imie);
    printf("liczba numerologiczna pierwszego imienia: %d\n", liczba_imienia);



return 0;

}
