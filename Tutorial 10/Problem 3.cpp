/*  TP 16/17 (LV 10, Zadatak 3)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)



Definirajte i implementirajte klasu “Ugao” (ili “Kut”, u skladu s Vašim jezičkim opredjeljenjem) koja 
omogućava rad s uglovima (kutovima) u ravni. Klasa treba da ima sljedeći interfejs:   
Ugao(double radijani = 0);  
Ugao(int stepeni, int minute, int sekunde);  
void Postavi(double radijani);  
void Postavi(int stepeni, int minute, int sekunde); 
 double DajRadijane() const;  
 void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde);  
 int DajStepene() const;  
 int DajMinute() const;  
 int DajSekunde() const;  
 void Ispisi() const;  
 void IspisiKlasicno() const;  
 Ugao &SaberiSa(const Ugao &u);  
 Ugao &PomnoziSa(double x);  
 friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);  
 friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);   
 Konstruktor s jednim parametrom postavlja vrijednost ugla u radijanima (ovaj parametar ima podrazumijevanu 
 vrijednost 0 što omogućava da se ovaj konstruktor koristi i kao konstruktor bez parametara, pri čemu se 
 kreira prazan ugao od 0 radijana), dok konstruktor s tri parametra postavlja vrijednost ugla u 2
 stepenima, minutama i sekundama. Pri tome se svi uglovi reduciraju na opseg od 0 do 2π odnosno od 0 do 
 360 ° tako da se, na primjer, ugao od 5π/2 odnosno 450 ° automatski reducira na vrijednost π/2 odnosno 
 90 °, dok se ugao od −π/4 odnosno −45 ° automatski reducira na vrijednost 315 ° odnosno 7π/4. 
 Konstruktor s jednim parametrom treba podržavati automatsku konverziju realnih brojeva u objekte tipa 
 “Ugao” (ili “Kut”). Dvije metode “Postavi” (s jednim i tri parametra) obavljaju isti posao kao i 
 konstruktori s jednim odnosno tri parametra respektivno, a služe za naknadnu promjenu ugla. Metoda 
 “DajRadijane” vraća vrijednost ugla izraženu u radijanima. Metoda “OcitajKlasicneJedinice” očitava 
 vrijednost ugla u stepenima, minutama i sekundama i smješta očitane vrijednosti u odgovarajuće parametre 
 metode. Metode “DajStepene”, “DajMinute” i “DajSekunde” omogućavaju da se istim ovim informacijama 
 pristupi neovisno, a ne isključivo “u paketu”. Metoda “Ispisi” ispisuje vrijednost ugla u radijanima, 
 dok metoda “IspisiKlasicno” ispisuje vrijednost ugla u stepenima, minutama i sekundama u obliku poput 
 “23deg 8min 47sec”. Metoda “SaberiSa” dodaje ugao zadan parametrom na ugao nad kojim je primijenjena i 
 usput vraća kao rezultat tako modificiran ugao. Metoda “PomnoziSa” množi ugao nad kojim je primijenjena 
 s brojem koji je zadan parametrom i usput vraća kao rezultat tako modificiran ugao. Obje ove metode 
 trebaju obezbijediti da nakon izvršene operacije rezultat bude reduciran na opseg 0 − 2π (0 − 360 °). 
 Konačno, dvije prijateljske funkcije “ZbirUglova” i “ProduktUglaSaBrojem” vraćaju kao rezultat novi ugao 
 koji je jednak zbiru uglova zadanih parametrima, odnosno produktu ugla i broja koji su zadani putem 
 parametara. Implementaciju klase treba zasnovati na jednom privatnom atributu koji čuva vrijednost ugla 
 u radijanima (realan broj). Napišite i kratki testni program u kojem ćete demonstrirati da svi elementi 
 napisane klase rade u skladu sa specifikacijama. Posebno treba provjeriti da li radi sabiranje objekata 
 tipa “Ugao” (ili “Kut”) s realnim brojem.
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
