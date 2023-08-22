/*  TP 16/17 (LV 9, Zadatak 2)
	Vrsit ce se provjera na prepisivanje tutorijala.



Izmijenite implementaciju klase razvijene u prethodnom zadatku tako da se za čuvanje koordinata vektora 
umjesto tri privatna atributa “x”, “y” i “z” koji su tipa realnih brojeva koristi jedan privatni atribut 
nazvan “koordinate” koji je tipa niza od tri realna elementa. Izmjenu treba izvesti tako da zaglavlja svih 
metoda unutar interfejsa klase ostanu neizmijenjena. Demonstrirajte da će testni program napisan u 
prethodnom zadatku raditi bez ikakvih izmjena sa ovako izmijenjenom klasom. Ovo zapravo ilustrira osnovnu
poentu razdvajanja interfejsa od implementacije: projektant klase može u potpunosti izmijeniti način kako 
je interno organizirana klasa a da korisnik klase to uopće ne primijeti, sve dok interfejs ostaje isti. 
*/
#include <iostream>
#include <cmath>

class Vektor3d {
    double koordinate[3];
    public:
    void Postavi(double x, double y, double z) {
        koordinate[0] = x; koordinate[1] = y; koordinate[2] = z;
    }
    void Ocitaj(double &x, double &y, double &z) const {
        x = koordinate[0]; y = koordinate[1]; z = koordinate[2];
    }
    void Ispisi() const {
        std::cout << "{" << koordinate[0] << "," << koordinate[1] << "," << koordinate[2] << "}";
    }
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
