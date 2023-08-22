/*  TP 16/17 (LV 7, Zadatak 5)
	Vrsit ce se provjera na prepisivanje tutorijala.



Izmijenite prethodni program tako što ćete adresu dinamički alociranog niza dijeljenih pametnih pokazivača 
na stringove umjesto u jedinstvenom pametnom pokazivaču čuvati također u dijeljenom pametnom pokazivaču. 
Vodite računa da ovo, sve dok ne zaživi C++17 standard, nosi i izvjesne komplikacije. Prvo, ukoliko želimo 
da dijeljeni pametni pokazivač pokazuje na dinamički alocirani niz, neophodno je zadati i funkciju koja se 
poziva kada dođe vrijeme za brisanje objekta (tzv. custom deleter), s obzirom da podrazumijevani način 
brisanja nije adekvatan. Drugo, takvi pametni pokazivači ne mogu se neposredno indeksirati, nego je 
neophodna njihova konverzija u “glupe” pokazivače da bismo mogli koristiti indeksaciju. 
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <memory>

int main ()
{
    int broj_recenica;
    std::cout << "Koliko zelite recenica: ";
    std::cin >> broj_recenica;
    std::cin.ignore(10000, '\n');
    std::cout << "Unesite recenice: ";
    try {
        std::shared_ptr<std::shared_ptr<std::string>> recenice(new std::shared_ptr<std::string>[broj_recenica], [](std::shared_ptr<std::string> *p) { delete[] p;});
        try {
            for(int i=0; i<broj_recenica; i++) {
                recenice.get()[i] = std::make_shared<std::string>();
                std::getline(std::cin, *recenice.get()[i]);
            }
            std::sort(recenice.get(), recenice.get() + broj_recenica, [](std::shared_ptr<std::string> s1, std::shared_ptr<std::string> s2) { return *s1 < *s2; });
            std::cout << "\nSortirane recenice: ";
            for(int i=0; i<broj_recenica; i++) std::cout << *recenice.get()[i] << std::endl;
        } catch (...) {
            std::cout << "\nProblemi s memorijom!" << std::endl;
            return 1;
        }
    } catch(...) {
        std::cout << "\nProblemi s memorijom!" << std::endl;
        return 1;
    }
	return 0;
}
