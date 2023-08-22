/*  TP 16/17 (LV 11, Zadatak 1)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)



Napravite klasu “NeobicnaKlasa” kod koje direktna i kopirajuća inicijalizacija cijelim brojem proizvode 
različite efekte. Konkretno, pokušaj direktne odnosno kopirajuće inicijalizacije treba da proizvedu na 
ekran ispis “Direknta inicijalizacija” odnosno “Kopirajuća inicijalizacija”. Na primjer:   
NeobicnaKlasa k1(5);   // Proizvodi ispis "Direktna inicijalizacija"  
NeobicnaKlasa k2 = 5;   // Proizvodi ispis "Kopirajuca inicijalizacija" 
*/
#include <iostream>

class NeobicnaKlasa {
    public:
    explicit NeobicnaKlasa(int &&x) { std::cout << "Direktna inicijalizacija" << std::endl; }
    NeobicnaKlasa(const int &x) { std::cout << "Kopirajuca inicijalizacija" << std::endl; }
};
int main ()
{
    NeobicnaKlasa a(5);
    NeobicnaKlasa b = 5;
	return 0;
}
