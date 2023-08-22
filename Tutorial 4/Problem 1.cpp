//TP 2021/2022: LV 4, Zadatak 1

/*Napišite funkciju “Cifre” koja treba da ima 3 parametra “n”, “c_min” i “c_max”, pri čemu parametar 
“n” predstavlja neki cijeli broj, a tip mu je “long long int”. Funkcija treba da pronađe najmanju i 
najveću cifru u parametru “n” i da smjesti pronađene cifre u parametre “c_min” i “c_max” (ovi parametri 
trebaju biti tipa “int”, jer su vrijednosti cifri svakako ograničene na opseg od 0 do 9). Pored toga, 
funkcija treba da kao rezultat vrati broj cifara u parametru “n”. Na primjer, naredbe   
Cifre(372324412645, a, b);  
e = Cifre(-54746639, c, d);   
treba da u promjenljive “a” i “b” odnosno “c” i “d” (pod uvjetom da su propisno deklarirane) smjesti 
brojeve 1 i 7, odnosno 3 i 9, jer su upravo to najmanja i najveća cifra u broju 372324412645 odnosno 
broju −45746639. Pored toga, u promjenljivu “e” smjestiće se broj 8 (broj cifara u broju −45746639). 
Funkcija ne smije koristiti nikakve pomoćne nizove ili vektore (samo individualne promjenljive), kao ni 
nepredznačne tipove podataka. Napišite i kratki testni program u kojem ćete demonstrirati napisanu funkciju. 
*/

#include <iostream>
#include <cmath>

int Cifre(long long int n, int &c_min, int &c_max) {
    int br_cifara = 0;
    c_min = 9;
    c_max = 0;
    do {
        int x = std::fabs(n%10);
        if(x > c_max) c_max = x;
        else if(x < c_min) c_min = x;
        n = n/10;
        br_cifara++;
    } while(n != 0);
    return br_cifara;
}

int main ()
{
    long long int n;
    std::cout << "Unesite broj: ";
    std::cin >> n;
    int a, b;
    int br_cifara = Cifre(n, a, b);
    std::cout << "Broj " << n << " ima " << br_cifara << " cifara, najveca je " << b << " a najmanja " << a << ".";
	return 0;
}
