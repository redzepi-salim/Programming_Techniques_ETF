/*  TP 16/17 (LV 11, Zadatak 2)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)



Korisnik klase “StedniRacun” iz Zadatka 1 sa Laboratorijske vježbe 10 želi da u svakom trenutku u programu 
može dobiti informaciju koliko je štednih računa (tj. objekata tipa “StedniRacun”) ukupno kreirano od 
početka programa, i koliko ih je trenutno aktivno (tj. koliko ima trenutuno “živih” varijabli tipa 
“StedniRacun”). Tu informaciju želi da dobije putem dvije funkcije članice “DajBrojKreiranih” i 
“DajBrojAktivnih” koje se koriste kao u sljedećem primjeru:   
StedniRacun s1, s2(100);  { StedniRacun s3(50); }        // Nakon "}", "s3" više ne postoji...  
std::cout << StedniRacun::DajBrojKreiranih()    << " " << StedniRacun::DajBrojAktivnih();     // Ispisuje "3 2"  
Proširite klasu “StedniRacun” razvijenu na prethodnoj laboratorijskoj vježbi stvarima koje su neophodne da 
se podrži ova funkcionalnost. 
*/
#include <iostream>
#include <stdexcept>
#include <cmath>

class StedniRacun {
    double iznos;
    static int br_aktivnih, br_svih;
    public:
    StedniRacun() { iznos = 0; br_aktivnih++; br_svih++; }
    StedniRacun(const StedniRacun &r) {
        if(r.iznos < 0) throw std::domain_error("Nedozvoljeno pocetno stanje");
        iznos = r.iznos;
        br_aktivnih++;
        br_svih++;
    }
    explicit StedniRacun(double x) {
        if(x < 0) throw std::logic_error("Nedozvoljeno pocetno stanje");
        iznos = x;
        br_svih++;
        br_aktivnih++;
    }
    void Ulozi(double x) { 
        if(std::fabs(x) > iznos && x < 0) throw std::logic_error("Transakcija odbijena");
        iznos += x;
    }
    void Podigni(double x) {
        if(x > iznos) throw std::logic_error("Transakcija odbijena");
        iznos -= x;
    }
    double DajStanje() const { return iznos; }
    void ObracunajKamatu(double stopa) {
        if(stopa < 0) throw std::logic_error("Nedozvoljena kamatna stopa");
        iznos += iznos * (stopa / 100);
    }
    static int DajBrojKreiranih() { return br_svih; }
    static int DajBrojAktivnih() { return br_aktivnih; }
    ~StedniRacun() { br_aktivnih--; }
};

int StedniRacun::br_svih = 0;
int StedniRacun::br_aktivnih = 0;

int main ()
{
    StedniRacun racun;
	racun.Ulozi(150);
	std::cout << "Stanje: " << racun.DajStanje() << std::endl;
	racun.Ulozi(50);
	std::cout << "Stanje nakon ulaganja: " << racun.DajStanje() << std::endl;
	racun.Podigni(100);
	std::cout << "Stanje nakon podizanja: " << racun.DajStanje() << std::endl;
	const StedniRacun stedni(20);
	std::cout << "Stanje: " << stedni.DajStanje() << std::endl;
	std::cout << StedniRacun::DajBrojKreiranih() << "  " << StedniRacun::DajBrojAktivnih() << std::endl;
	return 0;
}
