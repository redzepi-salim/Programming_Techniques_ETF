//TP 2018/2019: Tutorijal 8, Zadatak 2

/*Prepravite program za obradu učenika sa Predavanja 8_a, koji koristi vektor pokazivača na dinamički 
alocirane objekte tipa “Ucenik” tako da se umjesto običnih pokazivača koriste pametni pokazivači (obični 
pokazivači se ne smiju pojaviti nigdje u programu). Upute za ovu prepravku date su na predavanjima. */

#include <iostream>
#include <iomanip>
#include <string>
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
void UnesiJednogUcenika(std::shared_ptr<Ucenik> p_ucenik){
    std::cout << "  Ime: " ; std::cin >> p_ucenik->ime;
    std::cout << "  Prezime: " ; std::cin >> p_ucenik->prezime;
    std::cout << "  Datum rodjenja (D/M/G): " ;
    UnesiDatum(p_ucenik->datum_rodjenja);
    UnesiOcjene(p_ucenik->ocjene, BrojPredmeta);
}
void UnesiUcenike(std::vector<std::shared_ptr<Ucenik>> &p_ucenici){
    for(int i=0; i<p_ucenici.size(); i++){
        std::cout << "Unesite podatke za " << i + 1 << ". ucenika: " << std::endl;
        p_ucenici[i] = std::make_shared<Ucenik>();
        UnesiJednogUcenika(p_ucenici[i]);
    }
}
void ObradiJednogUcenika(std::shared_ptr<Ucenik> p_ucenik){
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
void ObradiUcenike(std::vector<std::shared_ptr<Ucenik>> &p_ucenici){
    for(std::shared_ptr<Ucenik> p_ucenik : p_ucenici) ObradiJednogUcenika(p_ucenik);
    std::sort(p_ucenici.begin(), p_ucenici.end(), [](std::shared_ptr<const Ucenik> p_u1, std::shared_ptr<const Ucenik> p_u2){
        return p_u1->prosjek > p_u2->prosjek;
    });
}
void IspisiJednogUcenika(std::shared_ptr<const Ucenik> p_ucenik){
    std::cout << "Ucenik " << p_ucenik->ime << " " << p_ucenik->prezime << " rodjen " ;
    IspisiDatum(p_ucenik->datum_rodjenja);
    if(p_ucenik->prolaz) {
        std::cout << " ima prosjek " << std::setprecision(3) << p_ucenik->prosjek << std::endl;
    }
    else std::cout << " mora ponavljati razred" << std::endl;
}
void IspisiIzvjestaj(const std::vector<std::shared_ptr<Ucenik>> &p_ucenici){
    std::cout << std::endl;
    for(std::shared_ptr<const Ucenik> p_ucenik : p_ucenici){
        IspisiJednogUcenika(p_ucenik);
    }
}
int main ()
{
    int broj_ucenika;
    std::cout << "Koliko ima ucenika: " ;
    std::cin >> broj_ucenika;
    try {
        std::vector<std::shared_ptr<Ucenik>> p_ucenici(broj_ucenika);
        try {
            UnesiUcenike(p_ucenici);
        }
        catch (...) {
            throw;
        }
        ObradiUcenike(p_ucenici);
        IspisiIzvjestaj(p_ucenici);
    }
    catch (...) {
        std::cout << "Problemi sa memorijom..." << std::endl;
    }
	return 0;
}
