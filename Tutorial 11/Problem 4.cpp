/*  TP 16/17 (LV 11, Zadatak 4)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)



Napišite klasu “Liga” koja se oslanja na prethodno napisanu klasu “Tim”. Klasa treba da ima privatne atribute 
“broj_timova” i “max_br_timova” koji čuvaju redom broj timova odnosno maksimalni dozvoljeni broj timova u 
ligi (atribut “max_br_timova” treba da bude konstantni atribut), kao i privatni atribut “timovi” koji će 
služiti za pristup dinamički alociranom nizu od “max_br_timova” elemenata, pri čemu je svaki element niza 
pokazivač na objekat tipa “Tim”. Interfejs klase treba da izgleda ovako:   
explicit Liga(int velicina_lige);  
explicit Liga(std::initializer_list<Tim> lista_timova);  
~Liga();  Liga(const Liga &l);  
Liga(Liga &&l);  
Liga &operator =(const Liga &l);  
Liga &operator =(Liga &&l); 
void DodajNoviTim(const char ime_tima[]);  
void RegistrirajUtakmicu(const char tim1[], const char tim2[],     
int rezultat_1, int rezultat_2);  
void IspisiTabelu();   
Konstruktor treba da izvrši dinamičku alokaciju memorije za prihvatanje onoliko timova koliko je navedeno 
parametrom, dok destruktor treba da izvrši oslobađanje svih resursa koje je klasa “Liga” alocirala tokom 
svog rada. Sekvencijski konstruktor treba omogućiti konstrukciju objekata tipa “Liga” iz inicijalizacione 
liste čiji su elementi imena timova. Kopirajući konstruktor i kopirajući operator dodjele treba da se brinu 
za ispravno kopiranje i međusobno dodjeljivanje objekata tipa “Liga”. Pri tome, kako je kapacitet lige (tj. 
maksimalni dozvoljeni broj timova) nepromjenljiv, treba podržati samo međusobnu dodjelu između dva objekta 
tipa “Liga” istog kapaciteta, u suprotnom treba baciti izuzetak tipa “logic_error” uz prateći tekst “Nesaglasni 
kapaciteti liga”. Pomjerajući konstruktor i pomjerajući operator dodjele predviđeni su da djeluju kao 
optimizirane varijante kopirajućeg konstruktora i kopirajućeg operatora dodjele za slučaj kada se kopiraju 
privremeni objekata. Metoda “DodajNoviTim” kreira tim sa navedenim imenom (tj. dinamički kreira objekat 
tipa “Tim”) i upisuje ga na prvo slobodno mjesto u ligu (tj. upisuje pokazivač na njega na odgovarajuće 
mjesto u nizu pokazivača na objekte tipa “Tim”). Pri tome se, naravno, broj timova u ligi povećava za 
jedinicu. U slučaju da je ime tima predugačko, baca se izuzetak (isti kakav baca izuzetak klase “Tim” u tom 
slučaju). U slučaju da je dostignut maksimalni broj timova, treba baciti izuzetak tipa “range_error” uz 
prateći tekst “Liga popunjena”. Također, ukoliko se pokuša upisati tim čije ime već postoji, baca se 
izuzetak tipa “logic_error” uz prateći tekst “Tim vec postoji”.   Ključna metoda klase je metoda “RegistrirajUtakmicu”, 
čija prva dva parametra predstavljaju imena timova koji su odigrali utakmicu, dok su treći i četvrti 
parametar broj golova koji su dali prvi i drugi tim respektivno. Ova metoda treba da ažurira rezultate u 
tabeli za oba tima, odnosno da baci izuzetak tipa “logic_error” uz prateći tekst “Tim nije nadjen” ukoliko 
timovi sa navedenim imenima ne postoje u tabeli (tačnije, ukoliko makar jedan od timova nije nađen). Isto 
tako, u slučaju da se zada besmislen (negativan) broj golova, baca se isti izuzetak kao u metodi  
“ObradiUtakmicu” u klasi “Tim”. Pri tome, ukoliko dođe do bacanja izuzetka, stanje lige mora biti identično 
kao da ova metoda uopće nije bila pozvana, tj. ne smije se desiti da dođe do parcijalne izmjene 
evidentiranih podataka (jaka sigurnost na izuzetke). Konačno, metoda “IspisiTabelu” treba da ispiše tabelu 
lige sortiranu u opadajućem poretku po broju bodova. Ukoliko dva tima imaju isti broj poena, tada prvo 
dolazi tim sa većom gol razlikom, a ako je i gol razlika ista, onda prije dolazi tim koji je prije po 
abecedi. Sortiranje vršite pozivom funkcije “sort”, uz pogodno definiranu funkciju kriterija. Kako ova 
metoda nije planirana da bude inspektor, dozvoljeno je da njen poziv ostavi tabelu lige sortiranu, iako je 
ranije možda bila nesortirana. Ispis treba vršiti pozivom metode “IspisiPodatke” iz klase “Tim”, tako da bi 
prikazana tabela trebala da ima izgled poput sljedećeg: 
*/
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <initializer_list>
#include <iomanip>
#include <algorithm>

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

class Liga {
    int broj_timova;
    const int max_br_timova;
    Tim **timovi;
    public:
    explicit Liga(int velicina_lige) : max_br_timova(velicina_lige), broj_timova(0), timovi(new Tim*[velicina_lige]{}) {}
    explicit Liga(std::initializer_list<Tim> lista_timova) : max_br_timova(lista_timova.size()), timovi(new Tim*[lista_timova.size()]{}) {
        int i = 0;
        for(auto it = lista_timova.begin(); it != lista_timova.end(); it++) {
            timovi[i] = new Tim(*it);
            i++;
        }
        broj_timova = lista_timova.size();
    }
    ~Liga () {
        for(int i=0; i<broj_timova; i++) delete timovi[i];
        delete[] timovi;
    }
    Liga(const Liga &l) : timovi(new Tim*[l.max_br_timova]{}), max_br_timova(l.max_br_timova), broj_timova(l.broj_timova) {
        try {
            for(int i=0; i<broj_timova; i++) timovi[i] = new Tim(*l.timovi[i]);
        } catch (...) {
            for(int i=0; i<broj_timova; i++) delete timovi[i];
            delete[] timovi; throw;
        }
    }
    Liga(Liga &&l) : timovi(l.timovi), max_br_timova(l.max_br_timova), broj_timova(l.broj_timova) {
        l.timovi = nullptr; l.broj_timova = 0;
    }
    Liga &operator =(const Liga &l) {
        if(max_br_timova != l.max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
        if(l.broj_timova > broj_timova) {
            try {
                for(int i = broj_timova; i < l.broj_timova; i++) {
                    timovi[i] = new Tim(*l.timovi[i]);
                }
            } catch(...) {
                for(int i = broj_timova; i < l.broj_timova; i++) {
                    delete timovi[i]; timovi[i] = nullptr;
                }
                throw;
            }
        }
        else {
            for(int i = l.broj_timova; i < broj_timova; i++) {
                delete timovi[i]; timovi[i] = nullptr;
            }
        }
        broj_timova = l.broj_timova;
        for(int i=0; i<broj_timova; i++) *timovi[i] = *l.timovi[i];
        return *this;
    }
    Liga &operator =(Liga &&l) {
        if(max_br_timova != l.max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
        std::swap(broj_timova, l.broj_timova);
        std::swap(timovi, l.timovi);
        return *this;   
    }
    void DodajNoviTim(const char ime_tima[]) {
        if(broj_timova + 1 > max_br_timova) throw std::range_error("Liga popunjena");
        try {
            timovi[broj_timova] = new Tim(ime_tima);
            broj_timova++;
        } catch(...) { throw; }
    }
    void RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1, int rezultat_2) {
        bool postoji1 = false, postoji2 = false;
        int x, y;
        for(int i=0; i<broj_timova; i++) {
            if(std::strcmp(timovi[i]->DajImeTima(), tim1) == 0) {
                postoji1 = true;
                x = i;
            }
            if(std::strcmp(timovi[i]->DajImeTima(), tim2) == 0) {
                postoji2 = true;
                y = i;
            }
        }
        if(postoji1 && postoji2) {
            timovi[x]->ObradiUtakmicu(rezultat_1, rezultat_2);
            timovi[y]->ObradiUtakmicu(rezultat_2, rezultat_1);
        }
        else throw std::logic_error("Tim nije nadjen");
    }
    void IspisiTabelu() {
        std::sort(timovi, timovi + broj_timova, [](Tim *t1, Tim *t2) {
           if(t1->DajBrojPoena() == t2->DajBrojPoena()) {
               if(t1->DajGolRazliku() == t2->DajGolRazliku()) {
                   if(std::strcmp(t1->DajImeTima(), t2->DajImeTima()) < 0) return true;
                   else return false;
               }
               return t1->DajGolRazliku() > t2->DajGolRazliku();
           } 
           return t1->DajBrojPoena() > t2->DajBrojPoena();
        });
        for(int i=0; i<broj_timova; i++) timovi[i]->IspisiPodatke();
    }
};

int main ()
{
    Liga l{"Zeljeznicar", "Zrinjski", "Sarajevo", "Jedinstvo", "Borac", "Celik"};
	do {
		l.IspisiTabelu();
		char t1[20], t2[20];
		try {
			std::cout << "Unesite ime prvog tima (ENTER za kraj): " ;
			std::cin.getline(t1, sizeof t1);
			std::cout << "Unesite ime drugog tima: " ;
			std::cin.getline(t2, sizeof t2);
			int rez1, rez2;
			std::cout << "Unesite broj postignutih golova za oba tima: " ;
			std::cin >> rez1 >> rez2;;
			l.RegistrirajUtakmicu(t1, t2, rez1, rez2);
		}
		catch (std::logic_error izuzetak) {
			std::cout << izuzetak.what() << std::endl;
		}
		catch (std::range_error izuzetak) {
			std::cout << izuzetak.what() << std::endl;
		}
		catch (std::bad_alloc) {
			std::cout << "Problemi sa memorijom" << std::endl;
		}
		std::cin.ignore(10000, '\n');
	} while(1);
	return 0;
}
