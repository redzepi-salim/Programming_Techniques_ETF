/*  TP 2018/2019: LV 5, Zadatak 4
	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.
			  
			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!


Izmijenite prethodni program tako što ćete umjesto niza koristiti dek (pri tome uklonite i ograničenje na 
max. 1000 elementata kao i dio “(max. 100)” u prvoj rečenici dijaloga) i što ćete umjesto imenovanih 
funkcija kao parametre koje šaljete funkcijama iz biblioteke “algorithm” koristiti anonimne (lambda) 
funkcije. Prilagodite dijalog između korisnika i programa tako da se umjesto varijacija riječi “niz” 
javljaju varijacije riječi “dek”. 
*/
#include <iostream>
#include <algorithm>
#include <deque>
#include <cmath>

int main ()
{
    int n;
    std::cout << "Unesite broj elemenata: ";
    std::cin >> n;
    std::deque<int> d(n);
    std::cout << "Unesite elemente: ";
    std::for_each(d.begin(), d.end(), [](int &x) { std::cin >> x; });
    std::cout << "Najveci element deka je " << *std::max_element(d.begin(), d.end()) << std::endl;
    std::cout << "Najmanji element deka se pojavljuje " << std::count(d.begin(), d.end(), *std::min_element(d.begin(), d.end())) << " puta u deku" << std::endl;
    std::cout << "U deku ima " << std::count_if(d.begin(), d.end(), [](int x) {if((std::sqrt(x) - std::floor(std::sqrt(x))) < 1e-7) return true; return false;}) << " brojeva koji su potpuni kvadrati" << std::endl;
    std::deque<int> br_cifara(n);
    std::transform(d.begin(), d.end(), br_cifara.begin(), [](int x) {if (x == 0) return 1; return int(std::log10(std::abs(x))) + 1;});
    std::cout << "Prvi element sa najmanjim brojem cifara je " << *std::find(d.begin(), d.end(), d.at(std::min_element(br_cifara.begin(), br_cifara.end()) - br_cifara.begin())) << std::endl;
    std::cout << "Elementi koji nisu trocifreni su: ";
    std::deque<int> nisu_trocif(n);
    std::deque<int>::iterator x = std::remove_copy_if(d.begin(), d.end(), nisu_trocif.begin(), [](int p) {if(int(std::log10(std::abs(p))) + 1 == 3) return true; return false;});
    std::for_each(nisu_trocif.begin(), x, [](int p) { std::cout << p << " "; });
	return 0;
}
