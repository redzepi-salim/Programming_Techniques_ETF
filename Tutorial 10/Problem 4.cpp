/*  TP 16/17 (LV 10, Zadatak 4)
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
#include <iomanip>

int Sekunde(double rad){
	while (rad >= 8 * atan(1)) rad -= 8 * atan(1);
	while (rad < 0) rad += 8 * atan(1);
	return rad * 3600 * 180. / (4 * atan(1));
}

class Ugao {
    double rad;
    public:
    Ugao(double radijani = 0) { Postavi(radijani); }
    Ugao (int stepeni, int minute, int sekunde) { Postavi(stepeni, minute, sekunde); }
    void Postavi(double radijani) {
        rad = radijani; 
        while(rad >= 8 * std::atan(1)) rad -= 8 * std::atan(1);
        while(rad < 0) rad += 8 * std::atan(1);
    }
    void Postavi(int stepeni, int minute, int sekunde) {
        rad = (stepeni + minute/60. + sekunde/3600.) * (4 * std::atan(1) / 180);
        while(rad >= 8 * std::atan(1)) rad -= 8 * std::atan(1);
        while(rad < 0) rad += 8 * std::atan(1);
    }
    double DajRadijane() const { return rad; }
    void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde) {
        stepeni = int(rad * 180 / (4 * std::atan(1)));
        minute = int((rad * 180 / (4 * std::atan(1)) - stepeni) * 60);
        sekunde = int(((rad * 180 / (4 * std::atan(1)) - stepeni) * 60 - minute) * 60);
    }
    int DajStepene() const { return Sekunde(rad) / 3600; }
    int DajMinute() const { return (Sekunde(rad) / 60) % 60; }
    int DajSekunde() const { return Sekunde(rad) % 60; }
    void Ispisi() const { std::cout << std::fixed << std::setprecision(5) << rad; }
    void IspisiKlasicno() const { std::cout << DajStepene() << "deg " << DajMinute() << "min " << DajSekunde() << "sec"; }
    Ugao &SaberiSa(const Ugao &u) {
        rad = rad + u.rad + 5e-8;
        while(rad >= 8 * std::atan(1)) rad -= 8 * std::atan(1);
        while(rad < 0) rad += 8 * std::atan(1);
        return *this;
    }
    Ugao &PomnoziSa(double x) {
        rad *= x;
        while(rad >= 8 * std::atan(1)) rad -= 8 * std::atan(1);
        while(rad < 0) rad += 8 * atan(1);
        return *this;
    }
    friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
    friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);
};

Ugao ZbirUglova(const Ugao &u1, const Ugao &u2) {
    Ugao u = u1.rad + u2.rad;
    while(u.rad >= 8 * std::atan(1)) u.rad -= 8 * std::atan(1);
    while(u.rad < 0) u.rad += 8 * std::atan(1);
    return u;
}

Ugao ProduktUglaSaBrojem(const Ugao &u1, double x) {
    Ugao temp = u1.rad * x;
    while(temp.rad >= 8 * std::atan(1)) temp.rad -= 8 * std::atan(1);
    while(temp.rad < 0) temp.rad += 8 * std::atan(1);
    return temp;
}

int main ()
{
    Ugao u1(10, 15, 20), u2(12, 12, 12), u3;
	u3.Postavi(50);
	u2.Postavi(991, 111, 111);
	u2.Ispisi();
	std::cout << std::endl;
	u1.IspisiKlasicno();
	std::cout << std::endl;
	Ugao u(u1);
	std::cout << u.DajStepene() << " " << u.DajMinute() << " " << u.DajSekunde() << std::endl;
	Ugao zbir = ZbirUglova(u1, u2);
	zbir.Ispisi();
	std::cout << std::endl;
	Ugao produkt = ProduktUglaSaBrojem(u1, 4);
	produkt.Ispisi();
	std::cout << std::endl;
	u2.SaberiSa(u1).Ispisi();
	std::cout << std::endl;
	u2.PomnoziSa(4).Ispisi();
	return 0;
}
