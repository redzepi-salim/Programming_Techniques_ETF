/*  TP 16/17 (LV 12, Zadatak 1)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)



Izmijenite klasu “Sat” razvijenu u Zadatku 4 sa Laboratorijske vježbe 9 tako da se umjesto metoda “Sljedeci” i 
“Prethodni” koriste operatori “++” i “--” (pri čemu je potrebno podržati kako prefiksne, tako i postfiksne 
verzije ovih operatora), umjesto metode “PomjeriZa” operatori “+=” i “-=” (pri čemu “s −= n” ima isto 
značenje kao i “s += -n”, umjesto metode “Ispisi” operator “<<”, a umjesto funkcije “BrojSekundiIzmedju” 
ili funkcije “Razmak” operator “-”. Također podržite da su mogući i izrazi oblika “s + n” i “s - n” gdje je 
“s” objekat tipa “Sat” a “n” cijeli broj koji imaju slično dejstvo kao izrazi “s += n” i “s -= n”, samo što 
oni ne modificiraju objekat “s” nego vraćaju kao rezultat novi objekav tipa “Sat” nastao pomjeranjem vremena 
u objektu “s” za “n” sekundi unaprijed odnosno unazad. Testni program prilagodite novom interfejsu klase. 
Radi jednostavnijeg rada, dodajte ovoj klasi konstruktor bez parametara, koji kreira sat inicijaliziran na 
00:00:00, kao i konstruktor sa 3 parametra koji obavlja istu stvar kao i metoda “PostaviNormalizirano”, samo 
odmah prilikom kreiranja objekta. 
*/
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>

class Sat {
    int sat, min, sek;
    public:
    Sat() : sat(0), min(0), sek(0) {}
    Sat(int h, int minute, int s) { PostaviNormalizirano(h, minute, s); }
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
    Sat &operator ++() {
		sek++;
		if(sek == 60) {
			sek = 0;
			min++;
		}
		if(min == 60) {
			min = 0;
			sat++;
		}
		if(sat == 24) sat = 0;
		return *this;
	}
	Sat &operator --() {
		sek--;
		if(sek < 0) {
			sek = 59;
			min--;
		}
		if(min < 0) {
			min = 59;
			sat--;
		}
		if(sat < 0) sat = 23;
		return *this;
	}
	Sat operator +=(int x) {
		if(x > 0) for(int i=0; i<x; i++) this->operator ++();
		else for(int i=0; i<-x; i++) this->operator --();
		return *this;
	}
	Sat operator -=(int x) { return operator +=(-x); }
	friend std::ostream &operator <<(std::ostream &tok, const Sat &s) {
		if(s.sat < 10) tok << 0 << s.sat << ":" ;
		else tok << s.sat << ":" ;
		if(s.min < 10) tok << 0 << s.min << ":" ;
		else tok << s.min << ":" ;
		if(s.sek < 10) tok << 0 << s.sek ;
		else tok << s.sek ;
		return tok;
	}
	int DajSate () const {	return sat; }
	int DajMinute () const { return min; }
	int DajSekunde () const { return sek; }
	int operator -(const Sat &s){
        int sek1(sat * 3600 + min * 60 + sek);
	    int sek2(s.DajSate() * 3600 + s.DajMinute() * 60 + s.DajSekunde());
	    return sek1 - sek2;
    }
	Sat operator +(int n) {
		Sat s(sat, min, sek + n);
		return s;
	}
	Sat operator -(int n) {
		Sat s(sat, min, sek - n);
		return s;
	}
	Sat operator --(int) {
		Sat s(sat, min, sek);
		sek--;
		if(sek < 0) { sek = 59; min--; }
		if(min < 0) { min = 59; sat--; }
		if(sat < 0) sat = 23;
		return s;
	}
	Sat operator ++(int) {
		Sat s(sat, min, sek);
		sek++;
		if(sek == 60) { sek = 0; min++; }
		if(min == 60) { min = 0; sat++; }
		if(sat == 24) { sat = 0; }
		return s;
	}
};

int main ()
{
	Sat s1(1,1,1);
	Sat s2(2,2,2);
	std::cout << s1 << "    " << s2 << std::endl;
	s1++;
	++s2;
	std::cout << s1 << "    " << s2 << std::endl;
	return 0;
}
