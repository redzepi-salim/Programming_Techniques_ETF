/*  TP 16/17 (LV 9, Zadatak 5)
	Vrsit ce se provjera na prepisivanje tutorijala.



Definirajte i implementirajte klasu “Sat” koja ima potpuno isti interfejs i potpuno isto ponašanje kao 
klasa iz prethodnog zadatka, samo čija se interna struktura umjesto tri atributa koja čuvaju trenutni broj 
sati, minuta i sekundi sastoji samo od jednog atributa, koji čuva ukupan broj sekundi (npr. umjesto 
informacije “3 sata, 20 minuta, 15 sekundi” čuva se samo informacija koja kaže 12015 sekundi). Mada će ovo 
možda tražiti izmjenu implementacije svih (ili skoro svih) metoda klase (pri tipičnim izvedbama, metoda 
“Postavi” će se sasvim neznatno izmijeniti, metode “Sljedeci”, “Prethodni” i “PomjeriZa” kao i prijateljska 
funkcija “BrojSekundiIzmedju” odnosno statička metoda “Razmak” bitno će se pojednostaviti, metode “DajSate”, 
“DajMinute”, “DajSekunde” će se zakomplicirati, dok će se metoda “Ispisi” možda zakomplicirati, a možda će 
i ostati potpuno ista, ako ste je pametno realizirali), pokažite da će testni program iz prethodnog zadatka 
bez ikakve prepravke raditi sa ovako modificiranom klasom. Savjet: da biste vršili što manje prepravki, 
probajte se prilikom rješavanja zadatka 4 u realizaciji funkcija članica što je god moguće više oslanjati 
na druge funkcije članice, a što manje na to šta su zaista atributi klase. 
*/
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>

class Sat {
    int sek;
    public:
    static bool DaLiJeIspravno(int sat, int min, int sek) {
        if(sat < 0 || sat > 23) return false;
        else if(min < 0 || min > 59) return false;
        else if(sek < 0 || sek > 59) return false;
        return true;
    }
    void Postavi(int sati, int minute, int sekunde) {
        if(!DaLiJeIspravno(sati, minute, sekunde)) throw std::domain_error("Neispravno virijeme");
        sek = sati*3600 + minute*60 + sekunde;
    }
    void PostaviNormalizirano(int sati, int minute, int sekunde) {
        while (sekunde < 0) {
			sekunde = sekunde + 60;
			if(minute == 0) {
				minute = 59;
				if(sati == 0) sati = 23;
			}
			else minute--;
		}
		if(sekunde > 59) {
			minute = minute + sekunde / 60;
			sekunde = sekunde % 60;
		}
		while (minute < 0) {
			minute = minute + 60;
			if(sati == 0) sati = 23;
			else sati--;
		}
		if(minute > 59) {
			sati = sati + minute / 60;
			minute = minute % 60;
		}
		while (sati < 0) {
			sati += 24;
		}
		if(sati > 23) {
			sati = sati % 24;
		}
        Postavi(sati, minute, sekunde);
    }
    Sat &PomjeriZa(int x) {
        if(x > 0) for(int i=0; i<x; i++) Sljedeci();
        if(x < 0) for(int i=0; i<std::abs(x); i++) Prethodni();
        return *this;
    }
    Sat &Sljedeci() {
        sek++;
        PostaviNormalizirano(DajSate(), DajMinute(), DajSekunde());
        return *this;
    }
    Sat &Prethodni() {
        sek--;
        PostaviNormalizirano(DajSate(), DajMinute(), DajSekunde());
        return *this;
    }
    void Ispisi() const { std::cout << std::setfill('0') << std::setw(2) << DajSate() << ":" << std::setw(2) << DajMinute() << ":" << std::setw(2) << DajSekunde(); }
    int DajSate() const { return sek / 3600; }
    int DajMinute() const { return (sek % 3600) / 60; }
    int DajSekunde() const { return sek % 60; }
    static int Razmak(const Sat &s1, const Sat &s2) { return s1.DajSate()*3600 + s1.DajMinute()*60 + s1.DajSekunde() - (s2.DajSate()*3600 + s2.DajMinute()*60 + s2.DajSekunde()); }
    friend int BrojSekundiIzmedju(const Sat &s1, const Sat &s2);
};

int BrojSekundiIzmedju(const Sat &s1, const Sat &s2) { return s1.DajSate()*3600 + s1.DajMinute()*60 + s1.DajSekunde() - (s2.DajSate()*3600 + s2.DajMinute()*60 + s2.DajSekunde()); }

int main ()
{
    Sat s1, s2;
	s1.Postavi(1,1,1);
	s2.Postavi(2,2,2);
	std::cout << Sat::DaLiJeIspravno(1,1,1) << Sat::DaLiJeIspravno(24,0,0) << std::endl;
	s1.Ispisi();
	std::cout << std::endl;
	s2.Ispisi();
	std::cout << std::endl;
	s2.PostaviNormalizirano(122, 122, 122);
	s2.Ispisi();
	std::cout << std::endl;
	s1.Sljedeci().Ispisi();
	std::cout << std::endl;
	s1.Prethodni().Ispisi();
	std::cout << std::endl;
	s1.PomjeriZa(10).Ispisi();
	std::cout << std::endl;
	std::cout << Sat::Razmak(s1, s2) << "  " << BrojSekundiIzmedju(s1, s2) << std::endl;
	return 0;
}
