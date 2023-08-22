/*  TP 16/17 (LV 13, Zadatak 2)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)



Definirajte i implementirajte apstraktnu baznu klasu “ApstraktniStudent”, kao i dvije konkretne klase 
“StudentBachelor” i “StudentMaster” izvedene iz bazne klase “ApstraktniStudent”. Bazna klasa 
“ApstraktniStudent” posjeduje privatne atribute koji čuvaju podatke o imenu i prezimenu studenta 
(oba su tipa “string”), broju indeksa (cijeli broj), broju položenih ispita (cijeli broj) i prosječnoj 
ocjeni (realan broj), i nikave druge atribute. Konstruktor klase inicijalizira ime i prezime studenta, 
te broj indeksa na vrijednosti zadane parametrima, dok se broj položenih ispita i prosječna ocjena 
inicijaliziraju respektivno na 0 i 5. Klasa dalje posjeduje trivijalne pristupne metode “DajIme”, 
“DajPrezime”, “DajBrojIndeksa”, “DajBrojPolozenih” i “DajProsjek” koje vraćaju vrijednosti svih 
odgovarajućih atributa. Metoda “RegistrirajIspit” sa jednim parametrom, služi za registraciju novog ispita. 
Ona povećava broj položenih ispita za jedinicu i ažurira prosječnu ocjenu u skladu sa ocjenom iz 
novopoloženog ispita, koja se zadaje kao parametar (u slučaju neispravne ocjene, baca se izuzetak tipa 
“domain_error” uz prateći tekst “Neispravna ocjena”). Ocjena 5 se prihvata kao legalna, ali se ignorira 
(tj. niti se ažurira prosjek, niti se povežava broj položenih ispita). Metoda “PonistiOcjene” bez 
parametara poništava sve registrirane ocjene (tj. dovodi objekat u stanje kakvo je bilo odmah nakon 
kreiranja objekta). Konačno, klasa sadrži i apstraktne metode “IspisiPodatke” i “DajKopiju” bez parametara. 
Metoda “DajKopiju” će biti potrebna za polimorfno kopiranje u kopirajućem konstruktoru klase “Fakultet” u 
narednom zadatku, a njene implementacije u izvedenim klasama treba da obezbijede kreiranje identične kopije 
objekta nad kojim su pozvane, uz vraćanje adrese novokreirane kopije kao rezultata.   
Izvedena klasa “StudentBachelor” razlikuje se od bazne klase “ApstraktniStudent” samo po tome što sadrži 
konkretnu implementaciju apstraktnih metoda “IspisiPodatke” i “DajKopiju”. Metoda “DajKopiju” treba da 
kreira identičnu kopiju objekta tipa “StudentBachelor” nad kojim je pozvana, dok metoda “IspisiPodatke” u 
ovoj klasi treba ispisati podatke o studentu u obliku   
Student bachelor studija <ime> <prezime>, sa brojem indeksa <indeks>,   ima prosjek <prosjek>.   
Izvedena klasa “StudentMaster” razlikuje se od bazne klase 
“ApstraktniStudent” prvo po tome što sadrži dodatni atribut koji čuva informaciju kada je student završio 
prvi stepen studija (bachelor studij), kao i dodatni parametar u konstruktoru koji omogućava postavljanje 
ovog atributa. Naravno, metodu “DajKopiju” u ovoj klasi treba implementirati tako da kreira identičnu 
kopiju objekta tipa “StudentMaster” nad kojim je pozvana, dok implementacija metode “IspisiPodatke” u ovoj 
klasi treba da ispisuje podatke o studentu u sljedećem obliku:   
Student master studija <ime> <prezime>, sa brojem indeksa <indeks>,   zavrsio bachelor studij godine <godina>, ima prosjek <prosjek>.   
Sve metode koje treba da budu inspektori obavezno deklarirajte kao takve. Napišite i mali testni program u 
kojem ćete testirati klase “StudentBachelor” i “StudentMaster” (naravno, primjerke klase “ApstraktniStudent” 
ne možete ni kreirati, jer je apstraktna). 
*/
#include <iostream>
#include <string>
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
int main ()
{
	StudentBachelor bachelor("Paja", "Patak", 18618);
	StudentMaster master("Miki", "Maus", 18520, 2017);
	bachelor.IspisiPodatke();
	master.IspisiPodatke();
	return 0;
}
