/*  TP 16/17 (LV 11, Zadatak 3)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)



Definirajte i implementirajte klasu “Tim” koja predstavlja jedan tim u fudbalskom prvenstvu. Klasa 
posjeduje privatne atribute “ime_tima”, “broj_odigranih”, “broj_pobjeda”, “broj_nerijesenih”, 
“broj_poraza”, “broj_datih”, “broj_primljenih” i “broj_poena”. Ovi atributi redom predstavljaju 
ime tima (do 20 znakova), broj odigranih utakmica, broj pobjeda, broj neriješenih utakmica, broj poraza, 
ukupan broj datih i primljenih golova, te broj poena za razmatrani tim. Atribut “ime_tima” treba izvesti 
kao klasični niz znakova. Klasa treba da ima sljedeći interfejs:   
Tim(const char ime[]);  
void ObradiUtakmicu(int broj_datih, int broj_primljenih);  
const char *DajImeTima() const;  
int DajBrojPoena() const;  
int DajGolRazliku() const;  
void IspisiPodatke() const;   
Konstruktor treba da postavi ime tima na vrijednost zadanu parametrom, a sve ostale atribute klase na 
nulu. Ukoliko je ime tima predugačko, treba baciti izuzetak tipa “range_error” uz prateći tekst “Predugacko 
ime tima”. Metoda “ObradiUtakmicu” treba da na osnovu rezultata utakmice koji joj se prenosi kao parametar 
(u vidu broja datih i primljenih golova sa posmatrane utakmice) ažurira ne samo atribute koje broje golove, 
nego i atribute koji broje odigrane utakmice, broj pobjeda, poraza i neriješenih utakmica, kao i broj 
bodova. Pri tome se za pobjedu dodjeljuju 3 boda, za neriješen rezultat 1 bod, dok se za poraz ne 
dodjeljuju nikakvi bodovi. U slučaju da se kao neki od parametara pošalje negativan broj, treba baciti 
izuzetak tipa tipa “range_error” uz prateći tekst “Neispravan broj golova”. Metode “DajImeTima”, 
“DajBrojPoena” i “DajGolRazliku” treba da vrate respektivno ime tima (tačnije, pokazivač na prvi znak 
imena), broj poena, kao i gol razliku (tj. razliku između ukupnog broja datih i primljenih golova) za 
posmatrani tim (ove metode treba implementirati unutar deklaracije klase). Konačno, metoda “IspisiPodatke” 
treba da ispiše na ekran sve podatke o timu u jednom redu, i to sljedećim redom: ime tima, broj utakmica, 
broj pobjeda, broj neriješenih utakmica, broj poraza, broj datih golova, broj primljenih golova i broj 
poena. Pri ispisu, za ime tima zauzmite prostor od 20 znakova, u kojem ime treba da bude ispisano poravnato 
ulijevo, a za sve brojne podatke prostor od 4 znaka na ekranu, pri čemu ispis svakog brojčanog podatka 
treba biti poravnat udesno unutar predviđenog prostora. Napišite i kratki testni program u kojem ćete 
demonstrirati napisanu klasu. 
*/
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <iomanip>

class Tim {
    char ime_tima[20];
    int broj_odigranih, broj_pobjeda, broj_nerijesenih, broj_poraza, broj_datih, broj_primljenih, broj_poena;
    public:
    Tim(const char *ime) : broj_odigranih(0), broj_pobjeda(0), broj_nerijesenih(0), broj_poraza(0), broj_datih(0), broj_primljenih(0), broj_poena(0) {
        if(std::strlen(ime) > 20) throw std::range_error("Predugacko ime tima");
        std::strcpy(ime_tima, ime);
    }
    void ObradiUtakmicu(int broj_datih, int broj_primljenih) {
        if(broj_datih < 0 || broj_primljenih < 0) throw std::range_error("Neispravan broj golova");
        Tim::broj_datih += broj_datih;
        Tim::broj_primljenih += broj_primljenih;
        broj_odigranih++;
        if(broj_datih > broj_primljenih) {
            broj_pobjeda++;
            broj_poena += 3;
        }
        else if(broj_datih < broj_primljenih) broj_poraza++;
        else if(broj_datih == broj_primljenih) {
            broj_nerijesenih++;
            broj_poena += 1;
        }
    }
    const char *DajImeTima() const { return ime_tima; }
    int DajBrojPoena() const { return broj_poena; }
    int DajGolRazliku() const { return broj_datih - broj_primljenih; }
    void IspisiPodatke() const { std::cout << std::setw(20) << std::left << ime_tima << std::setw(4) << std::right << broj_odigranih  << std::setw(4) << broj_pobjeda  << std::setw(4) << broj_nerijesenih  << std::setw(4) << broj_poraza  << std::setw(4) << broj_datih  << std::setw(4) << broj_primljenih << std::setw(4) << broj_poena << std::endl; }
};

int main ()
{
    Tim t1 = "Sarajevo";
	Tim t2 = "Zeljeznicar";
	t1.ObradiUtakmicu(5, 2);
	t1.ObradiUtakmicu(1, 5);
	t1.ObradiUtakmicu(4, 4);
	t2.ObradiUtakmicu(4, 1);
	t2.ObradiUtakmicu(0, 0);
	t2.ObradiUtakmicu(2, 3);
	t1.IspisiPodatke();
	t2.IspisiPodatke();
	return 0;
}
