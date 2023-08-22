/*  TP 16/17 (LV 10, Zadatak 2)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)


Definirajte i implementirajte klasu “Krug” koja predstavlja krug, te klasu “Valjak” koja se oslanja na 
klasu “Krug”. Jedini atribut klase “Krug” je poluprečnik kruga (tipa “double”). Konstruktor ove klase 
omogućava da se poluprečnik zada putem parametra, pri čemu nije moguće kreirati objekte tipa “Krug” a da se 
parametar ne zada. Također, ne smije biti dozvoljena automatska pretvorba realnih brojeva u objekte tipa 
“Krug”. Treba podržati i metodu “Postavi” koja radi istu stvar kao konstruktor, samo što omogućava naknadnu ž
izmjenu poluprečnika već kreiranog objekta. U oba slučaja, ukoliko je poluprečnik negativan ili nula, treba 
baciti izutetak tipa “domain_error” uz prateći tekst “Neispravan poluprecnik”. Metode “DajPoluprecnik”, 
“DajObim” i “DajPovrsinu” bez parametara daju respektivno kao rezultat poluprečnik, obim i površinu kruga 
nad kojim su pozvani (uzmite da je π = 4 ∙ arc tan 1). Metoda “Skaliraj” prima kao parametar realni broj 
(faktor skaliranja) i množi poluprečnik s faktorom skaliranja. Izuzetak tipa “domain_error” uz prateći 
tekst “Neispravan faktor skaliranja” baca se ukoliko je faktor skaliranja negativan ili nula. Konačno, 
metoda “Ispisi” nema parametara, a ispisuje podatke o krugu u formatu “R=… O=… P=…” gdje se umjesto tri 
tačke nalaze informacije o poluprečniku, obimu i površini respektivno. Klasa “Valjak” treba da ima dva 
atributa; “baza” tipa “Krug” i “visina” tipa “double”. Konstruktor klase “Valjak” zahtijeva dva parametra 
koji redom predstavljaju poluprečnik baze i visinu valjka. Primjerci ove klase također se ne mogu kreirati 
bez zadavanja pomenutih informacija. Za nju također treba podržati i funkciju “Postavi” koja radi istu 
stvar kao konstruktor, samo što omogućava naknadnu izmjenu već kreiranog objekta. U oba slučaja, ukoliko 
su poluprečnik baze ili visina negativni, treba baciti izuzetak tipa “domain_error” uz prateći tekst 
“Neispravan poluprecnik” ili “Neispravna visina” (u slučaju da su oba parametra negativna, prednost treba 
dati prvom tekstu). Metode “DajBazu”, “DajPoluprecnikBaze”, “DajVisinu”, “DajPovrsinu” i “DajZapreminu” 
nemaju parametara a redom vraćaju kao rezultat bazu (kao objekat tipa “Krug”), poluprečnik baze, visinu, 
površinu odnosno zapreminu valjka (valjda znate da je površina valjka dvostruka površina baze plus obim 
baze pomnožen s visinom, dok je zapremina valjka površina baze pomnožena s visinom). I za ovu klasu je 
podržana “Skaliraj” koja kao parametar prima faktor skaliranja i množi poluprečnik baze te visinu s 
faktorom skaliranja, uz bacanje izuzetka tipa “domain_error” uz prateći tekst “Neispravan faktor skaliranja” 
ukoliko je faktor skaliranja negativan ili nula. Konačno, metoda bez parametara “Ispisi” ispisuje podatke 
o valjku u formatu “R=… H=… P=… V=…”, gdje umjesto tri tačke treba respektivno smjestiti informacije o 
poluprečniku baze, visini, površini i zapremini valjka. Sve metode koje su inspektori obavezno deklarirajte 
kao takve. Obavezno napišite i testni program u kojem ćete testirati sve elemente razvijenih klasa 
(naročito trebate testirati mogu li se inspektori korektno pozvati nad konstantnim objektima tipa “Krug” i 
“Valjak”). 
*/
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>

class Krug {
    double r;
    public:
    explicit Krug(double x) { Postavi(x); }
    void Postavi(double x) {
        if(x <= 0) throw std::domain_error("Neispravan poluprecnik");
        r = x;
    }
    double DajPoluprecnik() const { return r; }
    double DajObim() const { return 2 * r * 4 * std::atan(1); }
    double DajPovrsinu() const { return r * r * 4 * std::atan(1); }
    void Skaliraj(double x) {
        if(x <= 0) throw std::domain_error("Neispravan faktor skaliranja");
        r *= x;
    } 
    void Ispisi() const { std::cout << std::fixed << std::setprecision(5) << "R=" << DajPoluprecnik() << " O=" << DajObim() << " P=" << DajPovrsinu(); }
};

class Valjak {
    Krug baza;
    double h;
    public:
    Valjak (double r, double h) : baza(r) {
        if(r <= 0) throw std::domain_error("Neispravan poluprecnik");
        if(h <= 0) throw std::domain_error("Neispravna visina");
        Valjak::h = h;
    }
    void Postavi(double r, double h) {
        if(r <= 0) throw std::domain_error("Neispravan poluprecnik");
        if(h <= 0) throw std::domain_error("Neispravna visina");
        Valjak::h = h;
        baza.Postavi(r);
    }
    Krug DajBazu() const { return baza; }
    double DajPoluprecnikBaze() const { return baza.DajPoluprecnik(); }
    double DajVisinu() const { return h; }
    double DajPovrsinu() const { return 2 * baza.DajPovrsinu() + baza.DajObim() * h; }
    double DajZapreminu() const { return baza.DajPovrsinu() * h; }
    void Skaliraj(double x) {
        if(x <= 0) throw std::domain_error("Neispravan faktor skaliranja");
        baza.Skaliraj(x);
        h *= x;
    }
    void Ispisi() const { std::cout << std::fixed << std::setprecision(5) << "R=" << DajPoluprecnikBaze() << " H=" << DajVisinu() << " P=" << DajPovrsinu() << " V=" << DajZapreminu(); }
};

int main ()
{
    Krug krug(5);
	krug.Ispisi();
	std::cout << krug.DajPoluprecnik() << " " << krug.DajPovrsinu() << " " << krug.DajObim() << std::endl;
	Valjak valjak(8, 4);
	std::cout << valjak.DajPoluprecnikBaze() << " " << valjak.DajPovrsinu() << " " << valjak.DajVisinu() << " " << valjak.DajZapreminu() << std::endl;
	valjak.DajBazu().Ispisi();
	std::cout << std::endl;
	valjak.Ispisi();
	return 0;
}
