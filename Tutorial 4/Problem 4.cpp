//TP 2021/2022: LV 4, Zadatak 4

/*Napišite generičku funkciju “UnosBroja” sa tri parametra. Funkcija treba da omogući pouzdano unošenje 
brojeva u program, uz potpunu detekciju grešaka pri unosu (uključujući i situacije kada ima viška unijetih 
znakova iza broja, poput unosa “123xy”). Prvi i drugi parametar su tipa “string”. Pri tome, prvi parametar 
predstavlja tekst koji se ispisuje korisniku kao obavijest da treba unijeti broj (prompt), dok je drugi 
parametar tekst koji se ispisuje korisniku kao upozorenje u slučaju da unos nije ispravan. Treći parametar 
je referenca na proizvoljni numerički tip, a predstavlja promjenljivu u koju će se smjestiti uneseni broj. 
Na primjer, funkcija se može pozvati na sljedeći način:   
UnosBroja("Unesi prvi broj: ", "Neispravan unos!\n", prvi_broj);   
Funkcija treba da traži unos od korisnika sve dok unos ne bude ispravan, i tek nakon toga ona završava sa 
radom. Napisanu funkciju demonstrirajte u testnom programu koji od korisnika traži da unese realni broj 𝑥 i 
cijeli broj 𝑛, a zatim računa i ispisuje vrijednost stepena 𝑥 , ne koristeći pri tome funkciju “pow”. 
Dijalog između programa i korisnika treba izgledati poput sljedećeg: */

#include <iostream>
#include <cmath>
#include <string>

template <typename NumerickiTip>
void UnosBroja(std::string s1, std::string s2, NumerickiTip &x) {
    std::cout << s1;
    while(!(std::cin >> x) || char(std::cin.peek()) != '\n') {
        std::cout << s2 << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << s1;
    }
}

int main ()
{
    double x, a=1;
    UnosBroja("Unesite bazu: \n", "Neispravan unos, pokusajte ponovo... ", x);
    int n;
    UnosBroja("Unesite cjelobrojni eksponent: \n", "Neispravan unos, pokusajte ponovo... ", n);
    if(n < 0) {
        std::cout << x;
        for(int i=0; i<-n; i++) a *=x;
        std::cout << " na " << n << " iznosi " << 1./a;
    }
    else if(n > 0) {
        std::cout << x;
        for(int i=0; i<n; i++) a *= x;
        std::cout << " na " << n << " iznosi " << a;
    }
    else std::cout << x << " na " << n << " iznosi " << x;
	return 0;
}
