/*  TP 16/17 (LV 9, Zadatak 1)
	Vrsit ce se provjera na prepisivanje tutorijala.



Definirajte i implementirajte klasu “Vektor3d” u skladu sa deklaracijom i implementacijom koja je prikazana 
na Predavanju 9_b (treba uključiti sve što je za tu klasu razvijeno, uključujući i prijateljsku funkciju 
“ZbirVektora”), s tim što ćete dodati još tri nove metode “PostaviX”, “PostaviY” i “PostaviZ” koje treba 
da omoguće neovisnu izmjenu pojedinačnih koordinata vektora. Napišite i mali testni program u kojem ćete 
demonstrirati sve elemente iz interfejsa razvijene klase. 
*/
#include <iostream>
#include <cmath>

class Vektor3d {
    double x, y, z;
    public:
    void Postavi(double x, double y, double z) {
        Vektor3d::x = x; Vektor3d::y = y; Vektor3d::z = z;
    }
    void Ocitaj(double &x, double &y, double &z) const {
        x = Vektor3d::x; y = Vektor3d::y; z = Vektor3d::z;
    }
    void Ispisi() const {
        std::cout << "{" << x << "," << y << "," << z << "}";
    }
    void PostaviX(double x) { Vektor3d::x = x; }
    void PostaviY(double y) { Vektor3d::y = y; }
    void PostaviZ(double z) { Vektor3d::z = z; }
    double DajX() const { return x; }
    double DajY() const { return y; }
    double DajZ() const { return z; }
    double DajDuzinu() const { return std::sqrt(x*x + y*y + z*z); }
    Vektor3d &PomnoziSaSkalarom(double s) {
        x *= s; y *= s; z *= s;
        return *this;
    }
    Vektor3d &SaberiSa(const Vektor3d &v) {
        x += v.x; y += v.y; z += v.z;
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
