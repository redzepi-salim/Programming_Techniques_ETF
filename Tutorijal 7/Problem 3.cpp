/*  TP 16/17 (LV 7, Zadatak 3)
	Vrsit ce se provjera na prepisivanje tutorijala.



Izmijenite prethodni program (dakle, program iz Zadatka 2), tako što ćete rečenice umjesto u dinamički 
alociranim nizovima znakova čuvati u dinamički alociranim objektima tipa “string”. Također uklonite 
ograničenje da rečenice mogu biti duge najviše 1000 znakova. 
*/
#include <iostream>
#include <algorithm>
#include <string>

int main ()
{
    int broj_recenica;
    std::cout << "Koliko zelite recenica: ";
    std::cin >> broj_recenica;
    std::cin.ignore(10000, '\n');
    std::cout << "Unesite recenice: ";
    std::string **recenice = nullptr;
    try {
        recenice = new std::string*[broj_recenica]{};
        int brojac = 0;
        try {
            for(int i=0; i<broj_recenica; i++) {
                recenice[i] = new std::string{};
                std::getline(std::cin, *recenice[i]);
                brojac++;
            }
            std::sort(recenice, recenice + broj_recenica, [](std::string *s1, std::string *s2) { return *s1 < *s2; });
            std::cout << "\nSortirane recenice: ";
            for(int i=0; i<broj_recenica; i++) std::cout << *recenice[i] << std::endl;
            for(int i=0; i<broj_recenica; i++) delete recenice[i];
            delete[] recenice;
        } catch (...) {
            std::cout << "\nProblemi s memorijom!" << std::endl;
            for(int i=0; i<brojac; i++) delete recenice[i];
            delete[] recenice;
            return 1;
        }
    } catch(...) {
        std::cout << "\nProblemi s memorijom!" << std::endl;
        return 1;
    }
	return 0;
}
