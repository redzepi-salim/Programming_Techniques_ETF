//TP 2016/2017: LV 1, Zadatak 1

/*Neka je dat bazen oblika kvadra dimenzije 𝑎 × 𝑏 × 𝑐 i keramičke pločice oblika kvadrata dimenzija 
𝑑 × 𝑑. Napišite program koji prvo zahtijeva od korisnika da unese dužinu, širinu i dubinu bazena 
(tj. 𝑎, 𝑏 i 𝑐) u metrima,  kao i širinu keramičke pločice 𝑑 u centimetrima. Program zatim treba 
da ispita da li je bazen moguće popločati takvim pločicama, a da se pri tome niti jedna pločica 
ne treba lomiti (debljinu pločice zanemariti). Ukoliko to nije moguće, treba ispisati odgovarajući 
komentar. Ukoliko jeste, treba ispisati koliko je pločica potrebno za popločavanje (naravno, 
popločavaju se zidovi i dno bazena). Slijede primjeri dva dijaloga između programa i korisnika. 
Radi autotestiranja, dijalozi bi trebali izgledati tačno kako je prikazano, uključujući i mjesta 
gdje se prelazi u novi red i prazne redove, samo se brojevi koje unosi korisnik mogu razlikovati 
(iza posljednje rečenice također je potreban prelazak u novi red). Afrikati poput “č”, “ć” itd. 
se ne koriste u ispisu zbog činjenice da nije sasvim jednostavno podesiti da se oni ispravno 
prikazuju (to će vrijediti i ubuduće). 
Za unos podataka i ispis rezultata koristite objekte “cin” i “cout” iz biblioteke “iostream”. 
Koristite isključivo cjelobrojni tip podataka (tačnije tip “int”). Pretpostavite da su ulazni 
podaci smisleni (tj. ne morate testirati da li je korisnik unio smislene podatke). */

#include <iostream>
#include <cmath>
#include <ostream>
int main ()
{
    int a, b, c;
    std::cout << "Unesite duzinu, sirinu i dubinu bazena u metrima: ";
    std::cin >> a >> b >> c;
    int d;
    std::cout << "Unesite sirinu plocice u centimetrima: ";
    std::cin >> d;
    int prvi_zid = a*c*10000, drugi_zid = b*c*10000, pod = a*b*10000;
    if((a*100)%d==0 && (b*100)%d==0 && (c*100)%d==0) {
        std::cout << std::endl << "Za poplocavanje bazena dimenzija " << a << "x" << b << "x" << c << "m sa plocicama dimenzija " << d << "x" << d << "cm potrebno je " << (2*prvi_zid + 2*drugi_zid + pod)/(d*d) << " plocica." << std::endl;
    }
    else {
    std::cout << std::endl << "Poplocavanje bazena dimenzija " << a << "x" << b << "x" << c << "m sa plocicama dimenzija " << d << "x" << d << "cm \nnije izvodljivo bez lomljenja plocica!" << std::endl;
    }
	return 0;
}
