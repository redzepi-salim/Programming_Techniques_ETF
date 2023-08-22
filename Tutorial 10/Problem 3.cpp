/*  TP 16/17 (LV 10, Zadatak 3)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)



Klase “Vektor3d” iz zadataka 1, 2 i 3 s prethodnog tutorijala, imaju nekoliko nedostataka. Na prvom mjestu, 
objekti tipa “Vektor3d” rađaju se s nasumičnim početnim sadržajem, Proširite klasu iz Zadatka 3. s 
prethodnog tutorijala konstruktorom bez parametara koji kreira vektor čije su sve tri koordinate postavljene 
na 0, kao i konstruktorom s tri parametra koji obavlja istu funkciju kao i “Postavi” s tri parametra, samo 
odmah pri kreiranju objekta. Dalje, brojanje ispisa je imalo “bag” (koji tada nismo znali ispraviti) što 
pri kopiranju objekta, novokreirana kopija nasljeđuje brojač ispisa od svog originala. Recimo, ako se 
izvrši nešto poput   
Vektor3d v1; v1.Postavi(1,2,3); v1.Ispisi(); v1.Ispisi(); v1.Ispisi()  
Vektor3d v2(v1); v2.Ispisi(); v2.Ispisi();   tada će poziv “v2.DajBrojIspisa()” 
dati vrijednost 5, iako je objekat “v2” ispisan samo dva puta. Izvršite korekcije koje su potrebne da se 
ispravi ovaj bag (odgovor kako to uraditi krije se u elementima koji su uvedeni na Predavanju 10). 
*/
#include <iostream>
#include <cmath>

class Vektor3d {
    double koordinate[3];
    mutable int br_ispisa = 0;
    public:
    Vektor3d (double x = 0, double y = 0, double z = 0) { Postavi(x, y, z); }
    Vektor3d(const Vektor3d &v) { Postavi(v.DajX(), v.DajY(), v.DajZ()); }
    void Postavi(double x, double y, double z) {
        koordinate[0] = x; koordinate[1] = y; koordinate[2] = z;
    }
    void Ocitaj(double &x, double &y, double &z) const {
        x = koordinate[0]; y = koordinate[1]; z = koordinate[2];
    }
    void Ispisi() const {
        std::cout << "{" << koordinate[0] << "," << koordinate[1] << "," << koordinate[2] << "}";
        br_ispisa++;
    }
    int DajBrojIspisa() const { return br_ispisa; }
    void PostaviX(double x) { koordinate[0] = x; }
    void PostaviY(double y) { koordinate[1] = y; }
    void PostaviZ(double z) { koordinate[2] = z; }
    double DajX() const { return koordinate[0]; }
    double DajY() const { return koordinate[1]; }
    double DajZ() const { return koordinate[2]; }
    double DajDuzinu() const { return std::sqrt(koordinate[0]*koordinate[0] + koordinate[1]*koordinate[1] + koordinate[2]*koordinate[2]); }
    Vektor3d &PomnoziSaSkalarom(double s) {
        koordinate[0] *= s; koordinate[1] *= s; koordinate[2] *= s;
        return *this;
    }
    Vektor3d &SaberiSa(const Vektor3d &v) {
        koordinate[0] += v.koordinate[0]; koordinate[1] += v.koordinate[1]; koordinate[2] += v.koordinate[2];
        return *this;
    }
    friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2);
};

Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2) {
    Vektor3d v3;
    v3.Postavi(v1.DajX() + v2.DajX(), v1.DajY() + v2.DajY(), v1.DajZ() + v2.DajZ());
    return v3;
}

int main ()
{
    Vektor3d v1, v2;
	v1.Postavi(1,1,1);
	v2.Postavi(2,2,2);
	std::cout << v1.DajDuzinu() << std::endl;
	ZbirVektora(v1, v2).Ispisi();
	v1.PomnoziSaSkalarom(4).Ispisi();
	v1.SaberiSa(v2).Ispisi();
	return 0;
}
