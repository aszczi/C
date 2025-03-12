#include <stdio.h>

/* Zad 2. Napisać program wczytujący datę urodzenia użytkownika (w formacie DD-MM-RRRR) i
wypisujący na jej podstawie (przy użyciu operacji arytmetycznych oraz pętli while i instrukcji warunkowej if) liczbę numerologiczną daty urodzenia danej osoby. Uwzględnić
istnienie liczb mistrzowskich.
*/
//liczby mistrzowskie to 11 22 33 i wowczas mamy chyba podac je całe?
//najwieksza mozliwa data: 29-09-9999 -> 56

int sumowanie(char* tablica){
        int sum=0;
    sum = ((int)tablica[0] - 48) + ((int)tablica[1] -48) + ((int)tablica[3] -48) + ((int)tablica[4]-48) + ((int)tablica[6]-48)
            + ((int)tablica[7]-48) + ((int)tablica[8] -48) + ((int)tablica[9]-48);
    return sum;
}

int suma_koncowa(int suma){
    int suma_koncowa=0;

        while(suma >= 10){
            if(suma == 11 || suma == 22 || suma == 33) {
                return suma;
            }else{
                suma_koncowa = suma_koncowa + suma%10;
                suma = suma/10;
            }
        }
        suma_koncowa = suma_koncowa + suma;
    return suma_koncowa;
}

int main() {

//stworz tablice 10 elementowa
char data1[10];
int data[11];
printf("Podaj swoja date urodzenia (w formacie DD-MM-RRRR)\n");


int licznik =0;
for(licznik =0; licznik < 10; licznik++) {
    scanf("%c", &data1[licznik]);
}
    int pierwsza_suma = sumowanie(data1);
    int finalna_suma = suma_koncowa(pierwsza_suma);
    printf("Twoja liczba numerologiczna to: %d", finalna_suma);
    return 0;
}
