/*  TP 16/17 (LV 13, Zadatak 1)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)



Definirajte apstraktnu baznu klasu “Lik”, koja predstavlja temelj za hijerarhijsku izgradnju porodice klasa 
koje predstavljaju geometrijske likove. Klasa ne sadrži nikakve atribute, nego samo apstraktne metode 
“IspisiSpecificnosti”, “DajObim” i “DajPovrsinu”, kao i (konkretnu) metodu “Ispisi” koja ispisuje podatke 
o liku pozivajući metode “IspisiSpecificnosti”, “DajObim” i “DajPovrsinu” (tačan format ispisa biće vidljiv 
iz primjera dijaloga između programa i korisnika). Zatim, iz klase “Lik” izvedite konkretne klase “Krug”, 
“Pravougaonik” i “Trougao”. U sve tri klase dodajte atribute koji su neophodni za specifikaciju primjeraka 
te klase (poluprečnik za krug, te dužine stranica za pravougaonik odnosno trougao), zatim odgovarajući 
konstruktor koji inicijalizira atribute i baca izuzetak tipa “domain_error” uz prateći tekst “Neispravni 
parametri” u slučaju da su parametri besmisleni (poput poluprečnika koji je negativan ili 0, ili dužina 
stranica od kojih se ne može formirati trougao), te konkretne metode “IspisiSpecificnosti”, “DajObim” i 
“DajPovrsinu” koje ispisuju specifične podatke o konkretnom liku, odnosno vraćaju kao rezultat obim i 
površinu konkretnog lika. Sa tako definiranim klasama napravite program koji prvo traži da se sa tastature 
unese broj likova. Nakon toga, korisnik treba da unosi sa tastature podatke o svakom liku u sljedećem 
formatu:   
K 𝑟  − Krug radijusa 𝑟 (npr. K5)  
P𝑎,𝑏 − Pravougaonik sa stranicama 𝑎 i 𝑏 (npr. P3,2)  
T𝑎,𝑏,𝑐 − Trougao sa stranicama 𝑎, 𝑏 i 𝑐 (npr. T3,4,5)   
Nakon svakog unesenog podatka, program treba dinamički kreirati odgovarajući objekat, i smjestiti pametni 
pokazivač na njega u vektor (čiji su elementi pametni pokazivači na likove). U slučaju neispravnog unosa, 
ispisuje se poruka o greški i traži se ponovni unos za isti lik. Po okončanju unosa svih podataka, program 
treba ispisati podatke o svim unesenim likovima, koristeći poziv metode “Ispisi”. Dijalog između korisnika 
i programa trebao bi izgledati poput sljedećeg: 
*/
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <cmath>

class  Lik {
	public:
	virtual ~ Lik() {}
	virtual void IspisiSpecificnosti() const =0;
	virtual double DajObim() const =0;
	virtual double DajPovrsinu() const =0;
	void Ispisi() const {
		IspisiSpecificnosti();
		std::cout << "Obim: " << DajObim() << " Povrsina: " << DajPovrsinu() << std::endl;
	}
};
class Krug: public Lik {
	double r;
	static constexpr double pi = 4 * atan(1);    
	public:
	Krug(double pol) {
		if(pol <= 0) throw std::domain_error("Neispravni parametri");
		r = pol;
	}
	virtual double DajObim() const { return 2 * pi * r; }
	virtual double DajPovrsinu() const { return r * r * pi; }
	virtual void IspisiSpecificnosti() const {
		std::cout << "Krug poluprecnika " << r << std::endl;
	}
};
class Pravougaonik: public Lik {
	double a, b;
	public:
	Pravougaonik(double x, double y) {
		if(x <= 0 || y <= 0) throw std::domain_error("Neispravni parametri");
		a = x; b = y;
	}
	virtual double DajObim() const { return 2 * (a + b); }
	virtual double DajPovrsinu() const { return a * b; }
	virtual void IspisiSpecificnosti() const {
		std::cout << "Pravougaonik sa stranicama duzine " << a << " i " << b << std::endl;
	}
};
class Trougao: public Lik {
	double a, b, c;
	public:
	Trougao (double x, double y, double z) {
		if(x <= 0 || y <= 0 || z <= 0) throw std::domain_error("Neispravni parametri");
		if(x + y <= z) throw std::domain_error("Neispravni parametri");
		if(x + z <= y) throw std::domain_error("Neispravni parametri");
		if(y + z <= x) throw std::domain_error("Neispravni parametri");
		a = x; b = y; c = z;
	}
	virtual double DajObim() const { return a + b + c; }
	virtual double DajPovrsinu() const {
		double s = (a + b + c) / 2;
		return std::sqrt(s * (s - a) * (s - b) * (s - c));
	}
	virtual void IspisiSpecificnosti() const {
		std::cout << "Trougao sa stranicama duzine " << a << ", " << b << " i " << c << std::endl;
	}
};
int main ()
{
	int br_likova;
	std::cout << "Koliko zelite likova: " ;
	std::cin >> br_likova;
	std::vector<std::shared_ptr<Lik>> lik(br_likova);
	for(int i=0; i<br_likova; i++) {
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Lik " << i + 1 << ": " ;
		char slovo, zarez(',');
		std::cin >> slovo;
		if(slovo == 'P') {
			double a, b;
			std::cin >> a >> zarez >> b;
			if(!std::cin || zarez != ',' || std::cin.peek() != '\n') {
				std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
				i--;
				continue;
			}
			try {
				lik[i] = std::make_shared<Pravougaonik>(a, b);
			}
			catch (...) {
				std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
				i--;
				continue;
			}
		}
		else if(slovo == 'K') {
			double r;
			std::cin >> r;
			if(!std::cin || std::cin.peek() != '\n') {
				std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
				i--;
				continue;
			}
			try {
				lik[i] = std::make_shared<Krug>(r);
			}
			catch (...) {
				std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
				i--;
				continue;
			}
		}
		else if(slovo == 'T') {
			double a, b, c;
			char znak;
			std::cin >> a >> znak >> b >> znak >> c;
			if(!std::cin || znak != ',' || std::cin.peek() != '\n') {
				std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
				i--;
				continue;
			}
			try {
				lik[i] = std::make_shared<Trougao>(a, b, c);
			}
			catch (...) {
				std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
				i--;
				continue;
			}
			
		}
		else {
			std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
			i--;
		}
	}
	std::cout << std::endl;
	for(auto x : lik) x->Ispisi();
	return 0;
}
