/*  TP 16/17 (LV 9, Zadatak 4)
	Vrsit ce se provjera na prepisivanje tutorijala.



Definirajte i implementirajte klasu “Sat” koja predstavlja digitalni sat. Implementacija klase treba se 
zasnivati na tri cjelobrojna privatna atributa koji čuvaju trenutni broj sati, minuta i sekundi. Interfejs 
klase treba da sadrži sljedeće elemente. Na prvom mjestu, tu je statička funkcija članica (metoda) 
“DaLiJeIspravno”, koja prima tri cjelobrojna parametra koji respektivno predstavljaju broj sati minuta i 
sekundi, a koja vraća logičku vrijednost “tačno” ili “netačno”, ovisno od toga da li ti parametri mogu 
predstavljati ispravno vrijeme ili ne (sati moraju biti u opsegu od 0 do 23 a minute i sekunde u opsegu od 
0 do 59 uključivo). Metoda “Postavi” također prima tri cjelobrojna parametra, a vrši postavljanje sata na 
iznos sati, minuta i sekundi koji je zadan putem parametara. Ova metoda baca izuzetak tipa “domain_error” 
uz prateći tekst “Neispravno vrijeme” ukoliko se proslijede neispravni parametri. Slična je i metoda 
“PostaviNormalizirano”, samo što ona nikada ne baca izuzetak, nego vrši “normalizaciju” eventualno 
neispravno zadanog vremena (prelijevom viška sekundi u minute, viška minuta u sate i viška sati u novi dan). 
Recimo, ukoliko se zada 25 sati, 150 minuta i 290 sekundi, to treba normalizirati u 3 sata, 34 minute i 50 
sekundi. Normalizacija treba da radi i za negativne vrijednosti parametara, tako da se 0 sati, 0 minuta i 
−1 sekunda normalizira u 23 sata, 59 minuta i 59 sekundi. Metoda “Sljedeci” bez parametara treba da poveća 
vrijeme zapamćeno u satu za 1 sekundu (npr. ukoliko je tekuće vrijeme “12:48:59”, nakon poziva ove metode 
vrijeme treba da postane “12:49:00”). Slično, metoda “Prethodni” (koja također nema parametara) treba da 
smanji vrijeme zapamćeno u satu za 1 sekundu, dok metoda “PomjeriZa” predstavlja generalizaciju prethodne 
dvije metode tako što vrši pomak tekućeg vremena za broj sekundi koji je zadan putem cjelobrojnog parametra 
(pomjeranje je unazad ukoliko se proslijedi negativna vrijednost kao parametar). Sve ove tri metode također 
vraćaju kao rezultat izmijenjeni objekat, sa ciljem da se omogući kaskadno pozivanje poput “s.Sljedeci().
Sljedeci()”. Metoda “Ispisi” ispisuje stanje sata u obliku “hh : mm : ss ”. Metode “DajSate”, “DajMinute” 
i “DajSekunde” vraćaju kao rezultat trenutni broj sati, minuta i sekundi u tekućem vremenu. Sve ove metode 
su bez parametara. Sve metode koje su po svojoj prirodi inspektori obavezno treba deklarirati kao takve 
(da bi se omogućio njihov poziv nad konstantnim objektima). Pored navedenih elemenata, potrebno je još 
realizirati i prijateljsku funkciju nazvanu “BrojSekundiIzmedju”, kao i statičku metodu (tj. statičku 
funkciju članicu) nazvanu “Razmak”. Obje ove funkcije rade potpuno istu stvar, a funkcionalnost je 
duplirana čisto sa ciljem da se upoznate sa dva različita pristupa istom problemu. Ove funkcije primaju 
kao parametre dva objekta tipa “Sat”, a vraćaju kao rezultat broj sekundi između vremena zapisanih u prvom 
i drugom parametru (rezultat je pozitivan ukoliko je vrijeme u prvom parametru veće nego vrijeme u drugom 
parametru, a negativan u suprotnom), Obavezno napišite i testni program u kojem će se upotrebiti svi 
elementi interfejsa napisane klase. 
*/
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>

class Sat {
    int sat, min, sek;
    public:
    static bool DaLiJeIspravno(int sat, int min, int sek) {
        if(sat < 0 || sat > 23) return false;
        else if(min < 0 || min > 59) return false;
        else if(sek < 0 || sek > 59) return false;
        return true;
    }
    void Postavi(int sati, int minute, int sekunde) {
        if(!DaLiJeIspravno(sati, minute, sekunde)) throw std::domain_error("Neispravno virijeme");
        sat = sati; min = minute; sek = sekunde;
    }
    void PostaviNormalizirano(int sati, int minute, int sekunde) {
        if(sati < 0) sati = 24 - std::fabs(sati % 24);
        if(minute < 0) {
            minute = 60 - std::fabs(minute % 60);
            sati--;
        }
        if(sekunde < 0) {
            if(minute == 0) {
                if(sati == 0) sati = 23;
                else sati--;
                minute = 59;
            }
            else {
                minute--;
                sekunde = 60 - std::fabs(sekunde % 60);
            }
        }
        if(sekunde > 59) {
            minute = minute + sekunde / 60;
            sekunde = sekunde % 60;
        }
        if(minute > 59) {
            sati = sati + minute / 60;
            minute = minute % 60;
        }
        if(sati > 23) sati = sati % 24;
        sat = sati; min = minute; sek = sekunde;
    }
    Sat &PomjeriZa(int x) {
        if(x > 0) {
            sek += x;
            if(sek > 59) {
                min = min + sek / 60;
                sek = sek % 60;
            }
            if(min > 59) {
                sat = sat + min / 60;
                min = min % 60;
            }
            if(sat > 23) sat = sat % 24;
        }
        else if(x < 0) {
            sek += x;
            if(sek < 0) {
                min--;
                min = min + sek / 60;
                sek = 60 + sek % 60;
            }
            if(min < 0) {
                sat--;
                sat = sat + min / 60;
                min = 60 + min % 60;
            }
            if(sat < 0) sat = 24 + sat % 24;
        }
        return *this;
    }
    Sat &Sljedeci() { return PomjeriZa(1); }
    Sat &Prethodni() { return PomjeriZa(-1);}
    void Ispisi() const { std::cout << std::setfill('0') << std::setw(2) << sat << ":" << std::setw(2) << min << ":" << std::setw(2) << sek; }
    int DajSate() const { return sat; }
    int DajMinute() const { return min; }
    int DajSekunde() const { return sek; }
    static int Razmak(const Sat &s1, const Sat &s2) { return s1.sat*3600 + s1.min*60 + s1.sek - (s2.sat*3600 + s2.min*60 + s2.sek); }
    friend int BrojSekundiIzmedju(const Sat &s1, const Sat &s2);
};

int BrojSekundiIzmedju(const Sat &s1, const Sat &s2) { return s1.sat*3600 + s1.min*60 + s1.sek - (s2.sat*3600 + s2.min*60 + s2.sek); }

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
