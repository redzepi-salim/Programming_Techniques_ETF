//TP 2018/2019: Tutorijal 8, Zadatak 3

/*Prepravite program za obradu učenika sa Predavanja 8_a, koji koristi vektor pokazivača na dinamički 
alocirane objekte tipa “Ucenik” tako da se umjesto vektora pokazivača na učenike koristi dinamički 
alocirani niz (običnih) pokazivača na učenike (biblioteku i tip “vector” nije dozvoljeno koristiti). 
Upute za ovu prepravku date su na predavanjima. */

#include <iostream>
#include <iomanip>
#include <string>
#include <new>
#include <vector>
#include <algorithm>
#include <memory>

const int BrojPredmeta = 8;
struct Datum {
    int dan, mjesec, godina;
};
struct Ucenik {
    std::string ime, prezime;
    Datum datum_rodjenja;
    int ocjene[BrojPredmeta];
    double prosjek;
    bool prolaz;
};

void OslobodiMemoriju(Ucenik **p_ucenici, int broj_ucenika){
    for(int i=0; i<broj_ucenika; i++) delete p_ucenici[i];
}
void UnesiDatum(Datum &datum){
    char znak;
    std::cin >> datum.dan >> znak >> datum.mjesec >> znak >> datum.godina;
}
void UnesiOcjene(int ocjene[], int broj_predmeta){
    for(int i=0; i<broj_predmeta; i++){
        std::cout << "  Ocjena iz " << i + 1 << ". predmeta: " ;
        std::cin >> ocjene[i];
    }
}
void UnesiJednogUcenika(Ucenik *p_ucenik){
    std::cout << "  Ime: " ; std::cin >> p_ucenik->ime;
    std::cout << "  Prezime: " ; std::cin >> p_ucenik->prezime;
    std::cout << "  Datum rodjenja (D/M/G): " ;
    UnesiDatum(p_ucenik->datum_rodjenja);
    UnesiOcjene(p_ucenik->ocjene, BrojPredmeta);
}
void UnesiUcenike(Ucenik **p_ucenici, int broj_ucenika){
    for(int i=0; i<broj_ucenika; i++){
        std::cout << "Unesite podatke za " << i + 1 << ". ucenika: " << std::endl;
        p_ucenici[i] = new Ucenik ();
        UnesiJednogUcenika(p_ucenici[i]);
    }
}
void ObradiJednogUcenika(Ucenik *p_ucenik){
    double suma_ocjena = 0;
    p_ucenik->prosjek = 1;
    p_ucenik->prolaz = false;
    for(int ocjena : p_ucenik->ocjene){
        if(ocjena == 1) return;
        suma_ocjena += ocjena;
    }
    p_ucenik->prolaz = true;
    p_ucenik->prosjek = suma_ocjena / BrojPredmeta;
}
void IspisiDatum(const Datum &datum){
    std::cout << datum.dan << "/" << datum.mjesec << "/" << datum.godina ;
}
void ObradiUcenike(Ucenik **p_ucenici, int broj_ucenika){
    for(int i=0; i<broj_ucenika; i++) ObradiJednogUcenika(p_ucenici[i]);
    std::sort(p_ucenici, p_ucenici + broj_ucenika, [](Ucenik *p_u1, Ucenik *p_u2){
        return p_u1->prosjek > p_u2->prosjek;
    });
}
void IspisiJednogUcenika(Ucenik *p_ucenik){
    std::cout << "Ucenik " << p_ucenik->ime << " " << p_ucenik->prezime << " rodjen " ;
    IspisiDatum(p_ucenik->datum_rodjenja);
    if(p_ucenik->prolaz) {
        std::cout << " ima prosjek " << std::setprecision(3) << p_ucenik->prosjek << std::endl;
    }
    else std::cout << " mora ponavljati razred" << std::endl;
}
void IspisiIzvjestaj(Ucenik *const *p_ucenici, int broj_ucenika){
    std::cout << std::endl;
    for(int i=0; i<broj_ucenika; i++){
        IspisiJednogUcenika(p_ucenici[i]);
    }
}
int main ()
{
    int broj_ucenika;
    std::cout << "Koliko ima ucenika: " ;
    std::cin >> broj_ucenika;
    Ucenik **ucenici = nullptr;
    try {
        ucenici = new Ucenik*[broj_ucenika]{};
        try {
            UnesiUcenike(ucenici, broj_ucenika);
        }
        catch (...) {
            OslobodiMemoriju(ucenici, broj_ucenika);
            throw;
        }
        ObradiUcenike(ucenici, broj_ucenika);
        IspisiIzvjestaj(ucenici, broj_ucenika);
        OslobodiMemoriju(ucenici, broj_ucenika);
    }
    catch (...) {
        std::cout << "Problemi sa memorijom..." << std::endl;
    }
    delete[] ucenici;
	return 0;
}
