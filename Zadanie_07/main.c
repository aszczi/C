#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


/* program wczytujący ciąg znaków w tzw. dice notation. Przykładowo, rzut
trzema koścmi sześciościennymi, czterema ośmiościennymi, jedną dwunastościenną oraz z modyfikatorem
 minus jeden zapisujemy 3d6 + 4d8 + 1d12 - 1. Ciąg znaków najpierw zawiera
dowolną ilość dowolnieściennych kości dodawanych do siebie, a na samym końcu opcjonalnie
odejmowany bądź dodawany modyfikator całkowity. Następnie program ma rzucić koścmi
-- czyli wygenerować losowe liczby dla każdej z kości korzystając z funkcji srand i rand z
nagłówka stdlib.h.
Zadanie można zrobić na wiele sposobów -- np. idąc znak po znaku w ciągu znaków -- ale
podpowiem, że najbardziej czytelną i zwięzłą będzie skorzystanie z funkcji strtok i innych
funkcji z nagłówka string.h*/

int rzut_koscia (int sciany) {
    return rand() % sciany + 1;
}


void usun_spacje(char *tekst) {
    int i, j;

    for (i = 0, j = 0; tekst[i] != '\0'; i++) {
        if (tekst[i] != ' ') {
            tekst[j++] = tekst[i];
        }
    }

    tekst[j] = '\0';
}
void lista_operacji(char* tekst, char* operacje)
{
    int i = 0;
    int j = 1;
    operacje[0] = '+';
    for (i = 0; tekst[i] != '\0'; i++) {
        if (tekst[i] == '+' || tekst[i] == '-') {
            operacje[j] = tekst[i];
            j++;
        }
    }
   // return operacje;
}

int main() {

    int k=0;
    int i=0; // liczniki petli
    int j=0;
    char dice_notation[100];
    int ilosc_rzutow;
    int ilosc_scian;
    char *token;
    char operacje[100];
    int suma = 0;
    int rzut;


    printf("Podaj ile razy i jakimi koscmi chcesz rzucic w dice notation\n");
    scanf("%[^\n]s", dice_notation);

    usun_spacje(dice_notation);
    lista_operacji(dice_notation, operacje);



    srand(time(NULL));

    printf("Wyniki rzutow: \n");
    j=0;

    do {

               if (k==0){
                   token = strtok(dice_notation, "d+-");/* dzieli stringa na tokeny, zwraca pierwszy token*/
               }else{
                   token = strtok(NULL, "d+-");
               }  /*w pierwszym tokenie mamy ilosc rzutow*/


               if (token == NULL) {
                   break;
               }

               ilosc_rzutow = atoi(token);
               token = strtok(NULL, "d+-"); /*w drugim tokenie mamy ilosc scian*/

                if (token == NULL) {
                  printf("%d\n", ilosc_rzutow);
                      if(operacje[j] == '+'){

                        suma += ilosc_rzutow;

                        }else if (operacje[j] == '-'){

                            suma -= ilosc_rzutow;
                        }
                    break;
                }

               ilosc_scian = atoi(token);

                    for (i=0; i<ilosc_rzutow; i++) {
                        rzut=rzut_koscia(ilosc_scian);
                        printf("%d\n", rzut);
                        if(operacje[j] == '+'){
                            suma += rzut;
                        }else if(operacje[j] == '-'){
                            suma -= rzut;
                        }
                    } j++;

               k++;

    } while(token != NULL);

    printf("suma: %d", suma);
    return 0;
}
