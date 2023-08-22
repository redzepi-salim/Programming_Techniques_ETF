/* 
    TP 16/17 (LV 7, Zadatak 1)
	Vrsit ce se provjera na prepisivanje tutorijala.


Napišite program koji traži od korisnika da unese niz rečenica, pri čemu se broj rečenica prethodno unosi 
sa tastature (rečenice neće biti duže od 1000 karaktera). Za svaku unesenu rečenicu dinamički alocirajte 
prostor tačno onolike veličine koliko je minimalno potrebno da se zapamti ta rečenica, uz vođenje 
evidencije o adresi svake alocirane rečenice u dinamički alociranom nizu pokazivača na početke svake 
od rečenica (kojem se također pristupa preko odgovarajućeg pokazivača). Nakon toga, treba ispisati 
unesene rečenice sortirane u abecedni poredak (tačnije rečeno, u rastući poredak po ASCII kodovima). 
Sortiranje obavite ručno, nekim od jednostavnih postupaka za sortiranje koji Vam je poznat (npr. 
BubbleSort, SelectionSort, itd.). Drugim riječima, nemojte koristiti gotove funkcije za sortiranje, 
poput funkcije “sort” iz biblioteke “algorithm”. Dijalog između korisnika i programa treba da izgleda 
poput sljedećeg: 
U slučaju da neka od alokacija ne uspije, program treba tog trenutka da ispiše tekst “Problemi sa 
memorijom” i da prekine dalji rad. Svu memoriju koja je zauzeta tokom rada programa treba osloboditi 
prije završetka programa, bez obzira da li je program završio rad regularno, ili zbog bacanja izuzetka. 
*/
#include <iostream>
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
    for(int i=0; i<broj_recenica; i++) {
        for(int j=i; j<broj_recenica; j++) {
            if(std::strcmp(recenice[i], recenice[j]) > 0) {
                char *temp = recenice[i];
                recenice[i] = recenice[j];
                recenice[j] = temp;
            }
        }
    }
    std::cout << "\nSortirane recenice: ";
    for(int i=0; i<broj_recenica; i++) std::cout << recenice[i] << std::endl;
    for(int i=0; i<broj_recenica; i++) delete[] recenice[i];
    delete[] recenice;
	return 0;
}
