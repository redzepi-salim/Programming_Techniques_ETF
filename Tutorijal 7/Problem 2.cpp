/* 
    TP 16/17 (LV 7, Zadatak 2)
    Vrsit ce se provjera na prepisivanje tutorijala.



Izmijenite prethodni program, ali tako što ćete umjesto ručnog sortiranja koristiti funkciju “sort” iz 
biblioteke “algorithm”, uz pogodnu funkciju kriterija implementiranu kao lambda funkcija. 
*/
#include <iostream>
#include <algorithm>
#include <cstring>

int main ()
{
    int broj_recenica;
    std::cout << "Koliko zelite recenica: ";
    std::cin >> broj_recenica;
    std::cin.ignore(10000, '\n');
    std::cout << "Unesite recenice: ";
    char **recenice = nullptr;
    try {
        recenice = new char*[broj_recenica]{};
        try {
            for(int i=0; i<broj_recenica; i++) {
                char radni_prostor[1000];
                std::cin.getline(radni_prostor, sizeof radni_prostor);
                recenice[i] = new char[std::strlen(radni_prostor) + 1]{};
                std::strcpy(recenice[i], radni_prostor);
            }
        } catch (...) {
            std::cout << "\nProblemi s memorijom!" << std::endl;
            for(int i=0; i<broj_recenica; i++) delete[] recenice[i];
            delete[] recenice;
            return 1;
        }
    } catch(...) {
        std::cout << "\nProblemi s memorijom!" << std::endl;
        return 1;
    }
    std::sort(recenice, recenice + broj_recenica, [](const char *s1, const char *s2) { return std::strcmp(s1, s2) < 0; });
    std::cout << "\nSortirane recenice: ";
    for(int i=0; i<broj_recenica; i++) std::cout << recenice[i] << std::endl;
    for(int i=0; i<broj_recenica; i++) delete[] recenice[i];
    delete[] recenice;
	return 0;
}
