/* TP 2018/2019: LV 5, Zadatak 3
	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.
			  
			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!



Koristeći odgovarajuće funkcije iz biblioteke “algorithm”, napišite program koji će za niz cijelih brojeva 
unesenih sa tastature (broj elemenata niza se prethodno također unosi sa tastature, a neće biti veći od 
1000) ispisati: 
 najveći element niza; 
 koliko puta se u nizu pojavljuje najmanji element; 
 koliko u nizu cijelih brojeva unesenih sa tastature ima brojeva koji su potpuni kvadrati (tj.  brojevi poput 1, 4, 9, 16, 25, 36, itd.); 
 element sa najmanjim brojem cifara (ili prvi od njih, ukoliko ima više elemenata koji imaju isti  najmanji broj cifara).  
Nakon toga, program treba prepisati u drugi niz sve elemente koji nisu trocifreni, i ispisati elemente 
tako formiranog niza. Dijalog između korisnika i programa treba da izgleda poput sljedećeg (zanemarite 
probleme sa bosanskom gramatikom koji mogu dovesti do toga da se svi elementi ispisanih rečenica neće 
lijepo slagati po broju i padežu, što je vidljivo i u datom primjeru): 
*/
#include <iostream>
#include <algorithm>
#include <cmath>

void Unesi(int &p) {
    std::cin >> p;
}

bool PotpunKvadrat(int x) {
    if((std::sqrt(x) - std::floor(std::sqrt(x))) < 1e-7) return true;
    return false;
}

int BrojCifara(int x) {
    if (x == 0) return 1;
    return int(std::log10(std::abs(x))) + 1;
}

bool Trocifreni(int x) {
    if(BrojCifara(x) == 3) return true;
    return false;
}

void Ispisi(int x) {
    std::cout << x << " ";
}

int main ()
{
    int n;
    std::cout << "Unesite broj elemenata (max. 1000): ";
    std::cin >> n;
    int niz[1000];
    std::cout << "Unesite elemente: ";
    std::for_each(niz, niz + n, Unesi);
    std::cout << "Najveci element niza je " << *std::max_element(niz, niz + n) << std::endl;
    std::cout << "Najmanji element niza se pojavljuje " << std::count(niz, niz + n, *std::min_element(niz, niz + n)) << " puta u nizu" << std::endl;
    std::cout << "U nizu ima " << std::count_if(niz, niz + n, PotpunKvadrat) << " brojeva koji su potpuni kvadrati" << std::endl;
    int br_cifara[1000];
    std::transform(niz, niz + n, br_cifara, BrojCifara);
    std::cout << "Prvi element sa najmanjim brojem cifara je " << *std::find(niz, niz + n, niz[std::min_element(br_cifara, br_cifara + n) - br_cifara]) << std::endl;
    std::cout << "Elementi koji nisu trocifreni su: ";
    int nisu_trocif[1000];
    int *x = std::remove_copy_if(niz, niz + n, nisu_trocif, Trocifreni);
    std::for_each(nisu_trocif, x, Ispisi);
	return 0;
}
