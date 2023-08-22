//TP 2016/2017: LV 1, Zadatak 4

/*U numerologiji starih Grka, svi prirodni brojevi su se dijelili u tri kategorije, prema tome kakva 
im je suma svih njihovih djelilaca (ne računajući njega samog). Oni brojevi kod kojih je ta suma manja 
od samog broja nazivali su se manjkavi (engl. deficient), oni kod kojih je ta suma veća od samog broja 
nazivali su se obilni (engl. abudant), dok su oni brojevi koji su jednaki sumi svih svojih djelilaca 
(bez njega samog) nazivali savršeni (engl. perfect). Recimo, broj 49 je manjkav: njegovi djelioci su 1 i 7, 
pri čemu je 1 + 7 = 8 < 49. Isto tako, broj 42 je obilan: njegovi djelioci su 1,2, 3, 6, 7, 14 i 21, pri 
čemu je 1 + 2 + 3 + 6 + 7 + 14 + 21 = 54 > 42. Konačno, 28 je primjer savršenog broja: njegovi djelioci su 
1, 2, 4, 7 i 14, a vrijedi 1 + 2 + 4 + 7 + 14 = 28.   Napišite program koji traži da se sa tastature unese 
prirodan broj 𝑛. U slučaju da korisnik unese nešto što nije prirodan broj (što uključuje i situaciju kada 
uneseni podatak uopće nije broj), treba ispisati poruku upozorenja, i ponoviti unos. Ukoliko je unos 
ispravan, program treba da ispita i ispiše da li je uneseni broj manjkav, obilan ili savršen. Nakon toga, 
program treba da traži unos novog broja i da ponavlja postupak sve dok se kao broj ne unese nula. Dijalog 
između programa i korisnika trebao bi izgledati poput sljedećeg: */

#include <iostream>
#include <cmath>
int main ()
{
    double n;
    for(;;) {
        std::cout << "Unesite prirodan broj ili 0 za kraj: ";
        std::cin >> n;
        while(!std::cin || n < 0 || std::fabs(n - int(n)) > 0.0001) {
            std::cout << "Niste unijeli prirodan broj!" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Unesite prirodan broj ili 0 za kraj: ";
            std::cin >> n;
        }
        if(std::fabs(n) < 0.0001) {
            std::cout << "Dovidjenja!";
            break;
        }
        int suma = 0;
        for(int i=1; i<int(n); i++) {
            if(int(n)%i == 0) suma += i;
        }
        if(suma < n) std::cout << "Broj " << n << " je manjkav!" << std::endl;
        else if(suma > n) std::cout << "Broj " << n << " je obilan!" << std::endl;
        else std::cout << "Broj " << n << " je savrsen!" << std::endl;
    }
	return 0;
}
