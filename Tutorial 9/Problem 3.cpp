/*  TP 16/17 (LV 9, Zadatak 3)
	Vrsit ce se provjera na prepisivanje tutorijala.



Proširite klasu iz prethodnog zadatka tako što ćete dodati novu metodu nazvanu “DajBrojIspisa” koja daje 
kao rezultat broj koliko puta je do trenutka poziva metode objekat (vektor) nad kojim je primijenjena 
ispisan na ekran (pozivom metode “Ispisi”). Na primjer, ako se izvrše naredbe   
Vektor3d v1, v2;  
v1.Postavi(3, 4, 2); 
v2.Postavi(2, 0, 5);  
v1.Ispisi(); v1.Ispisi(); v1.Ispisi(); v2.Ispisi(); v2.Ispisi();  
std::cout << std::endl;  std::cout << "Objekat v1 je ispisan " << v1.DajBrojIspisa() << "puta , a objekat v2 "     
<< v2.DajBrojIspisa() << " puta" << std::endl;   
posljednja naredba treba da proizvede ispis “Objekat v1 je ispisan 3 puta, a objekat v2 2 puta”. 
Implementaciju klase možete mijenjati sa ciljem da ovo postignete, ali ništa u interfejsu ne smijete 
izmijeniti (osim dodavanja nove metode). Posebno, sve metode koje su inspektori moraju i dalje ostati 
inspektori. 
*/
#include <iostream>
#include <cmath>

class Vektor3d {
    double koordinate[3];
    mutable int br_ispisa = 0;
    public:
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
