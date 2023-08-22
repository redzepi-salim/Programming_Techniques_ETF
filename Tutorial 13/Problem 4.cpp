/*  TP 16/17 (LV 13, Zadatak 4)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)



Napravite surogatsku klasu “Student” koja predstavlja polimorfni omotač za proizvoljnu vrstu studenata. 
Preciznije, promjenljive tipa “Student” moraju biti takve da se u njih može smjestiti bilo student bachelor 
studija bilo student master studija (tj. sadržaj promjenjive čiji je tip bilo tip “StudentBachelor” bilo 
tip “StudentMaster”), pa čak i promjenljiva bilo kojeg tipa koji je izveden iz apstraktnog tipa 
“ApstraktniStudent” (što uključuje i tipove koji će eventualno biti kreirani u budućnosti, poput 
“StudentDoktorant” ili “StudentSpecijalizant”). Naravno, sa promjenljivim tipa “Student” mogu se raditi sve 
operacije koje su predviđene da rade sa svim vrstama studenata neovisno od njihovog podtipa (tj. sve 
operacije koje su definirane u interfejsu apstraktne bazne klase “ApstraktniStudent”), mogu se bezbjedno 
kopirati, međusobno dodjeljivati, itd. Na primjer:   
Student s1, s2;  
s1 = StudentBachelor("Dusko", "Dugousko", 1234);   // "s1" je bachelor  
s2 = StudentMaster("Paja", "Patak", 4312, 2015);   // a "s2" master  
s1.RegistrirajIspit(6); 
s1.RegistrirajIspit(9);  
s2.RegistrirajIspit(8);  
s1.IspisiPodatke(); 
s2.IspisiPodatke();  s1 = s2;        // sad je i "s1" master  
s1.IspisiPodatke();   
Obavezno napišite i testni program u kojem ćete testirati funkcionalnost razvijene surogatske klase. 
*/
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>

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
class Student {
	ApstraktniStudent *p_na_student;
	void Test() const {
		if(!p_na_student) throw std::logic_error("Nespecificiran student!");
	}
	
	public:
	Student() : p_na_student(nullptr) {}
	~Student() { delete p_na_student; }
	Student(const ApstraktniStudent &student) : p_na_student(student.DajKopiju()) {}
	Student(const Student &student) {
		if(!student.p_na_student) p_na_student = nullptr;
		else p_na_student = student.p_na_student->DajKopiju();
	}
	Student(Student &&student) {
		p_na_student = student.p_na_student; student.p_na_student=nullptr;
	}
	Student &operator =(const Student &student) {
		ApstraktniStudent *p_na_student_novi = nullptr;
		if(student.p_na_student) p_na_student_novi = student.p_na_student->DajKopiju();
		delete p_na_student;
		p_na_student = p_na_student_novi;
		return *this;
	}
	Student &operator =(Student &&student) {
		std::swap(p_na_student, student.p_na_student);
		return *this;
	}
	std::string DajIme() const { return p_na_student->DajIme(); }
	std::string DajPrezime() const { return p_na_student->DajPrezime(); }
	int DajBrojIndeksa() const { return p_na_student->DajBrojIndeksa(); }
	int DajBrojPolozenih() const { return p_na_student->DajBrojPolozenih(); }
	double DajProsjek() const { return p_na_student->DajProsjek(); }
	void RegistrirajIspit(int ocjena) { p_na_student->RegistrirajIspit(ocjena); }
	void PonistiOcjene() { p_na_student->PonistiOcjene(); }
	void IspisiPodatke() const { p_na_student->IspisiPodatke(); }
};
int main ()
{
	StudentBachelor bachelor("Paja", "Patak", 18618);
	StudentMaster master("Miki", "Maus", 18520, 2017);
	bachelor.IspisiPodatke();
	master.IspisiPodatke();
	std::cout << std::endl;
	Student student(master);
	student.IspisiPodatke();
	return 0;
}
