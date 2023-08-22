/*  TP 16/17 (LV 10, Zadatak 1)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)


Definirajte i implementirajte klasu “StedniRacun”. U klasi treba da postoji konstruktor koji postavlja 
stanje računa za zadanu početnu vrijednost (realni broj), ili na nulu ukoliko se nikakva početna 
vrijednost ne zada. U slučaju da je početna vrijednost negativna, konstruktor treba baciti izuzetak tipa 
“logic_error” uz prateći tekst “Nedozvoljeno pocetno stanje”. Metode “Ulozi“ i “Podigni“ imaju parametar 
koji je realni broj, a simuliraju ulaganje zadanog iznosa odnosno podizanje zadanog iznosa s računa. Pri 
tome, podizanje je dozvoljeno jedino ukoliko je iznos koji se podiže manji ili jednak od trenutnog stanja 
računa, u suprotnom se baca izuzetak tipa “logic_error” uz prateći tekst “Transakcija odbijena”. Metoda 
“DajStanje” nema parametara, a daje kao rezultat trenutno stanje računa. Konačno, metoda “ObracunajKamatu” 
ima realni parametar koji predstavlja kamatnu stopu u procentima, a uvećava glavnicu (trenutno stanje) za 
iznos kamate koja se dobija množenjem glavnice s kamatnom stopom. Kamatna stopa mora biti pozitivna, u 
suprotnom se baca izuzetak tipa “logic_error” uz prateći tekst “Nedozvoljena kamatna stopa”. Sve metode 
koje su inspektori obavezno deklarirajte kao takve. Obavezno napišite i testni program u kojem ćete 
testirati sve elemente razvijene klase (naročito trebate testirati mogu li se inspektori korektno pozvati 
nad konstantnim objektima tipa “StedniRacun”). 
*/
#include <iostream>
#include <stdexcept>
#include <cmath>

class StedniRacun {
    double iznos;
    public:
    StedniRacun(double x = 0) {
        if(x < 0) throw std::logic_error("Nedozvoljeno pocetno stanje");
        iznos = x;
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
};

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
	return 0;
}
