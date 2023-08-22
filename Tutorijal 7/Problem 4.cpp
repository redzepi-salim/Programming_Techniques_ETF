/*  TP 16/17 (LV 7, Zadatak 4)
	Vrsit ce se provjera na prepisivanje tutorijala.



Izmijenite prethodni program tako što ćete adrese dinamički alociranih objekata tipa “string” umjesto u 
običnim pokazivačima čuvati u dijeljenim pametnim pokazivačima, dok ćete adresu dinamički alociranog niza 
takvih pokazivača čuvati u odgovarajućem jedinstvenom pametnom pokazivaču (jedinstveni pametni pokazivač 
je ovdje odabran zbog činjenice da je pogodniji za čuvanje adresa dinamički alociranih nizova, a svakako 
neće više različitih pokazivača pokazivati na ovaj dinamički alocirani niz). Savjet: iskoristite “typedef” 
ili “using” deklaraciju da uvedete prikladno ime za tip dijeljenih pametnih pokazivača na stringove, inače 
ćete imati vrlo glomazne i nečitke konstrukcije. Također, na jednom mjestu će Vam vjerovatno trebat i 
konverzija pametnih u “glupe” pokazivače. 
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
        std::unique_ptr<std::shared_ptr<std::string>[]> recenice(new std::shared_ptr<std::string>[broj_recenica]);
        try {
            for(int i=0; i<broj_recenica; i++) {
                recenice[i] = std::make_shared<std::string>();
                std::getline(std::cin, *recenice[i]);
            }
            std::sort(recenice.get(), recenice.get() + broj_recenica, [](std::shared_ptr<std::string> s1, std::shared_ptr<std::string> s2) { return *s1 < *s2; });
            std::cout << "\nSortirane recenice: ";
            for(int i=0; i<broj_recenica; i++) std::cout << *recenice[i] << std::endl;
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
