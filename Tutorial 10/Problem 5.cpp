/*  TP 16/17 (LV 10, Zadatak 5)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)



Izmijenite implementaciju klase razvijene u prethodnom zadatku tako da se informacija o uglu umjesto u 
radijanima interno čuva u tri cjelobrojna atributa koji redom sadrže broj stepeni, minuta i sekundi koje 
čine ugao. Iako će ova izmjena možda tražiti promjenu implementacije gotovo svih metoda klase (ovisno o 
tome kako ste ih pisali), uvjerite se da će nakon te izmjene testni program koji koristi napisanu klasu i 
dalje raditi posve identično, bez ikakvih izmjena. 
*/
#include <iostream>
#include <cmath>
#include <iomanip>

void OsnovniPeriod(int &step, int &min, int &sec){
	while (sec < 0) {
		sec += 60;
		if(min == 0){
			min = 59;
			if(step == 0) step = 59;
		}
		else min--;
	}
	if(sec > 60){
		min += sec / 60;
		sec -= (sec / 60) * 60;
	}
	while (min < 0) {
		min += 60;
		if(step == 0) step = 59;
		else step--;
	}
	if(min > 60){
		step += min / 60;
		min -= (min / 60) * 60;
	}
	while (step < 0) step += 360;
	if(step > 360) step -= (step / 360) * 360;
}

int Sekunde(double rad){
	while (rad >= 8 * atan(1)) rad -= 8 * atan(1);
	while (rad < 0) rad += 8 * atan(1);
	return rad * 3600 * 180. / (4 * atan(1));
}

class Ugao {
    int step, min, sek;
    public:
    Ugao(double radijani = 0) { Postavi(radijani); }
    Ugao (int stepeni, int minute, int sekunde) { Postavi(stepeni, minute, sekunde); }
    void Postavi(double radijani) {
        while(radijani >= 8 * std::atan(1)) radijani -= 8 * std::atan(1);
        while(radijani < 0) radijani += 8 * std::atan(1);
        step = Sekunde(radijani) / 3600;
        min = (Sekunde(radijani) / 60) % 60;
        sek = Sekunde(radijani) % 60;
    }
    void Postavi(int stepeni, int minute, int sekunde) {
        step = stepeni; min = minute; sek = sekunde;
        OsnovniPeriod(step, min, sek);
    }
    double DajRadijane() const { 
        double rad = (step + min / 60. + sek / 3600.) * (4 * atan(1)) / 180.;
		while (rad >= 8 * atan(1)) rad -= 8 * atan(1);
		while (rad < 0) rad += 8 * atan(1);
		return rad;
    }
    void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde) {
        stepeni = step;
        minute = min;
        sekunde = sek;
    }
    int DajStepene() const { return step; }
    int DajMinute() const { return min; }
    int DajSekunde() const { return sek; }
    void Ispisi() const { std::cout << std::fixed << std::setprecision(5) << DajRadijane(); }
    void IspisiKlasicno() const { std::cout << DajStepene() << "deg " << DajMinute() << "min " << DajSekunde() << "sec"; }
    Ugao &SaberiSa(const Ugao &u) {
        double rad = DajRadijane() + u.DajRadijane() + 5e-8;
        while(rad >= 8 * std::atan(1)) rad -= 8 * std::atan(1);
        while(rad < 0) rad += 8 * std::atan(1);
        step = Sekunde(rad) / 3600;
		min = (Sekunde(rad) / 60) % 60;
		sek = Sekunde(rad) % 60;
        return *this;
    }
    Ugao &PomnoziSa(double x) {
        double temp = x * DajRadijane();
		while (temp >= 8 * atan(1)) temp -= 8 * atan(1);
		while (temp < 0) temp += 8 * atan(1);
		step = Sekunde(temp) / 3600;
		min = (Sekunde(temp) / 60) % 60;
		sek = Sekunde(temp) % 60;
		//OsnovniPeriod(step, min, sek);
		return *this;
    }
    friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
    friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);
};

Ugao ZbirUglova(const Ugao &u1, const Ugao &u2) {
    double u = u1.DajRadijane() + u2.DajRadijane() + 5e-8;
    while(u >= 8 * std::atan(1)) u -= 8 * std::atan(1);
    while(u < 0) u += 8 * std::atan(1);
    return u;
}

Ugao ProduktUglaSaBrojem(const Ugao &u1, double x) {
    double temp = u1.DajRadijane() * x;
    while(temp >= 8 * std::atan(1)) temp -= 8 * std::atan(1);
    while(temp < 0) temp += 8 * std::atan(1);
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
