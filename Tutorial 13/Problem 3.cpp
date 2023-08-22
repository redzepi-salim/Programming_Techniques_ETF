/*  TP 16/17 (LV 13, Zadatak 3)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)



Napravite klasu “Fakultet” koja čuva polimorfnu kolekciju podataka izvedenih iz bazne klase “ApstraktniStudent” 
(to mogu biti klase “StudentBachelor” i “StudentMaster”, ali može biti i bilo koja druga novonapisana klasa 
izvedena iz klase “ApstraktniStudent”). Podaci se čuvaju u dinamički alociranim objektima čije se adrese 
čuvaju u vektoru (običnih) pokazivača na objekte nekog od tipova izvedenih iz tipa “ApstraktniStudent”, i 
taj vektor je jedini privatni atribut ove klase. Primjerci klase “Fakultet” moraju se moći kreirati ne 
navodeći nikakve dopunske informacije. Dalje, klasa treba imati destruktor koji oslobađa sve resurse koje 
su objekti tipa “Fakultet” zauzli tokom svog života, zatim kopirajući konstruktor i kopirajući operator 
dodjele koji omogućavaju da se objekti tipa “Fakultet” mogu sigurno kopirati i međusobno dodjeljivati 
korištenjem strategije dubokog kopiranja (za potrebe kreiranja kopija individualnih objekata pohranjenih u 
kolekciji koristite funkciju “DajKopiju”), te pomjerajući konstruktor i pomjerajući operator dodjele koji 
optimiziraju postupak kopiranja za slučaj kada su u igri privremeni objekti. Predviđene su dvije metode 
istog imena “UpisiStudenta” koje služe za upis novog studenta, od kojih jedna ima tri, a druga četiri 
parametra. Metoda sa tri parametra upisuje studenta bachelor studija, pri čemu su parametri broj indeksa, 
ime i prezime, dok metoda sa četiri parametra upisuje studenta master studija, pri čemu četvrti dodatni 
parametar predstavlja godinu kada je student završio bachelor studij. Obje metode bacaju izuzetak tipa 
“logic_error” uz prateći tekst “Student sa zadanim brojem indeksa vec postoji” ukoliko student sa zadanim 
brojem indeksa već postoji. Njoj je suprotna metoda “ObrisiStudenta” koja briše studenta sa brojem indeksa 
koji se zadaje kao parametar. U slučaju da student sa zadanim brojem indeksa ne postoji, treba baciti 
izuzetak tipa “logic_error” uz prateći tekst “Student sa zadanim brojem indeksa ne postoji”. Predviđen je i 
preklopljeni operator “[]” koji vraća referencu na studenta sa zadanim brojem indeksa (ukoliko takav ne 
postoji, baca se isti izuzetak kao u prethodnom slučaju). Pri tome, ako se ovaj operator primijeni na 
konstantni objekat tipa “Fakultet”, treba vratiti referencu na konstantni objekat, da se onemogući njegova 
izmjena (povratni tip ne smije prosto biti ne-referenca tipa “ApstraktniStudent”, jer bi se kopiranjem 
nekog objekta u privremeni objekat tog tipa koji se vraća iz funkcije izgubile specifičnosti objekta koji se 
kopira). Zahvaljujući ovom operatoru, moguće je vršiti manipulacije nad studentima pohranjenim u kolekciji, 
bez potrebe da za tu svrhu dodajemo nove metode. Recimo, ako je “etf” neki objekat tipa “Fakultet”, trebaju 
biti moguće konstrukcije poput   
etf[14922].RegistrirajIspit(8); 
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
class ApstraktniStudent {
	protected:
	std::string ime, prezime;
	int br_indexa, br_polozenih;
	double prosjek;
	
	public:
	ApstraktniStudent(std::string ime, std::string prezime, int br_indexa) : ime(ime), prezime(prezime), br_indexa(br_indexa), br_polozenih(0), prosjek(5) {}
	virtual ~ApstraktniStudent() {}
	std::string DajIme() const { return ime; }
	std::string DajPrezime() const { return prezime; }
	int DajBrojIndeksa() const { return br_indexa; }
	int DajBrojPolozenih() const { return br_polozenih; }
	double DajProsjek() const { return prosjek; }
	void RegistrirajIspit(int ocjena) {
		if(ocjena < 5 || ocjena >10) throw std::domain_error("Neispravna ocjena");
		if(ocjena == 5) return;
		double suma = prosjek * br_polozenih;
		prosjek = (suma + ocjena) / (++br_polozenih);
	}
	void PonistiOcjene() { br_polozenih = 0; prosjek = 5; }
	virtual void IspisiPodatke() const = 0;
	virtual ApstraktniStudent* DajKopiju() const = 0;
};
class StudentBachelor: public ApstraktniStudent {
	public:
	StudentBachelor(std::string ime, std::string prezime, int br_indexa) : ApstraktniStudent(ime, prezime, br_indexa) {}
	void IspisiPodatke() const override {
		std::cout << "Student bachelor studija " << DajIme() << " " << DajPrezime() << ", sa brojem indeksa " << DajBrojIndeksa() << "," << std::endl << "ima prosjek " << DajProsjek() << "." << std::endl;
	}
	ApstraktniStudent* DajKopiju() const override { return new StudentBachelor(*this); }
};
class StudentMaster: public ApstraktniStudent {
	int godina_diplomiranja;
	public:
	StudentMaster(std::string ime, std::string prezime, int br_indexa, int godina_diplomiranja) : ApstraktniStudent(ime, prezime, br_indexa), godina_diplomiranja(godina_diplomiranja) {}
	ApstraktniStudent* DajKopiju() const override { return new StudentMaster(*this); }
	void IspisiPodatke() const override {
		std::cout << "Student master studija " << DajIme() << " " << DajPrezime() << ", sa brojem indeksa " << DajBrojIndeksa() << "," << std::endl << "zavrsio bachelor studij godine " << godina_diplomiranja << ",ima prosjek " << DajProsjek() << "." << std::endl;
	} 
};
class Fakultet {
	std::vector<ApstraktniStudent*> studenti;
	public:
	~Fakultet() { for(int i=0; i<studenti.size(); i++) delete studenti[i]; }
	Fakultet() =default;
	Fakultet (const Fakultet &fakultet) {
		studenti.resize(fakultet.studenti.size());
		for(int i=0; i<fakultet.studenti.size(); i++) studenti[i] = fakultet.studenti[i]->DajKopiju();
	}
	Fakultet(Fakultet &&fax) {
		studenti = std::move(fax.studenti);
	}
	Fakultet &operator =(Fakultet fax) {
		std::swap(studenti, fax.studenti);
		return *this;
	}
	void UpisiStudenta(std::string ime, std::string prezime, int br_indexa) {
		for(int i=0; i<studenti.size(); i++) {
			if(studenti[i]->DajBrojIndeksa() == br_indexa) throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
		}
		studenti.push_back(new StudentBachelor(ime, prezime, br_indexa));
	}
	void UpisiStudenta(std::string ime, std::string prezime, int br_indexa, int godina_diplomiranja) {
		for(int i=0; i<studenti.size(); i++) {
			if(studenti[i]->DajBrojIndeksa() == br_indexa) throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
		}
		studenti.push_back(new StudentMaster(ime, prezime, br_indexa, godina_diplomiranja));
	}
	void ObrisiStudenta(int br_indexa) {
		int i;
		for(i=0; i<studenti.size(); i++) {
			if(studenti[i]->DajBrojIndeksa() == br_indexa) {
				delete studenti[i];
				studenti.erase(studenti.begin() + i);
				break;
			}
		}
		if(i == studenti.size()) throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
	}
	ApstraktniStudent &operator [](int br_indexa) const {
		for(int i=0; i<studenti.size(); i++) if(studenti[i]->DajBrojIndeksa() == br_indexa) return *studenti[i];
		throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
	}
	void IspisiSveStudente() const {
		auto temp = studenti;
		std::sort(temp.begin(), temp.end(), [](ApstraktniStudent *p1, ApstraktniStudent *p2) {
		if(p1->DajProsjek() == p2->DajProsjek()) return p1->DajBrojIndeksa() < p2->DajBrojIndeksa();
		return p1->DajProsjek() > p2->DajProsjek();
		});
		for(int i=0; i<temp.size(); i++) temp[i]->IspisiPodatke();
	}
};
int main ()
{
	StudentBachelor bachelor("Paja", "Patak", 18618);
	StudentMaster master("Miki", "Maus", 18520, 2017);
	bachelor.IspisiPodatke();
	master.IspisiPodatke();
	Fakultet fax;
	std::cout << std::endl;
	fax.UpisiStudenta("Salim", "Redžepi", 18618);
	fax.IspisiSveStudente();
	return 0;
}
