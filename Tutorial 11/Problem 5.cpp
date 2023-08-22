/*  TP 16/17 (LV 11, Zadatak 5)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)



Izmijenite klasu “Liga” razvijenu u prethodnom zadatku, tako što će se za evidenciju pokazivača na dinamički 
alocirane objekte tipa “Tim” umjesto dinamički alociranog niza pokazivača koristiti vektor čiji su elementi 
pametni pokazivači na objekte tipa “Tim”. Taj vektor će, naravno, biti privatni atribut klase (nazvaćemo ga 
isto “timovi”, jer to traži najmanju prepravku klase). Privatni atributi  “broj_timova” i “max_br_timova” 
više neće biti potrebni. Zaista, broj timova se može saznati testiranjem trenutne veličine vektora, dok 
maksimalan broj timova više nije potrebno zadavati, s obzirom da vektor može u toku rada po volji povećavati 
svoju veličinu (ograničeni smo isključivo količinom raspoložive memorije). Jedina izmjena u interfejsu klase 
biće u tome što konstruktoru više neće biti potreban parametar (zahvaljujući fleksibilnosti vektora, u ligu 
će se moći dodati onoliko timova koliko želimo, bez potrebe da unaprijed specificiramo njihov maksimalan 
broj). Što se tiče semantičkih aspekata (tj. šta metode klase “Liga” treba da rade), jedina razlika je u 
tome što metoda “DodajNoviTim” ne mora provjeravati da li je dostignut maksimalan broj timova, s obzirom 
da ograničenje na maksimalan broj timova više ne postoji (osim ograničenja uvjetovanih količinom raspoložive 
memorije). Svi ostali aspekti funkcioniranja klase “Liga” ostaju neizmijenjeni. Obratite pažnju kakve 
izmjene traže upravljački elementi klase (destruktor, kopirajući konstruktor, itd.). 
*/
#include <iostream>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <initializer_list>
#include <iomanip>
#include <vector>
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
    std::vector<std::shared_ptr<Tim>> timovi;
    public:
    explicit Liga() {}
    explicit Liga(std::initializer_list<Tim> lista_timova) {
        timovi.resize(lista_timova.size());
        int i = 0;
        for(auto it = lista_timova.begin(); it != lista_timova.end(); it++) {
            timovi[i] = std::make_shared<Tim>(*it);
            i++;
        }
    }
    ~Liga () {}
    Liga(const Liga &l) : timovi(l.timovi.size()) {
        for(int i=0; i<l.timovi.size(); i++) timovi.at(i) = std::make_shared<Tim>(*l.timovi.at(i));
    }
    Liga(Liga &&l) : timovi(std::move(l.timovi)) {}
    Liga &operator =(const Liga &l) {
        timovi.resize(l.timovi.size());
        for(int i=0; i<l.timovi.size(); i++) timovi.at(i) = std::make_shared<Tim>(*l.timovi.at(i));
        return *this;
    }
    Liga &operator =(Liga &&l) {
        timovi = std::move(l.timovi);
        return *this;   
    }
    void DodajNoviTim(const char ime_tima[]) {
        timovi.push_back(std::make_shared<Tim>(ime_tima));
    }
    void RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1, int rezultat_2) {
        bool postoji1 = false, postoji2 = false;
        int x, y;
        for(int i=0; i<timovi.size(); i++) {
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
        std::sort(timovi.begin(), timovi.end(), [](auto t1, auto t2) {
           if(t1->DajBrojPoena() == t2->DajBrojPoena()) {
               if(t1->DajGolRazliku() == t2->DajGolRazliku()) {
                   if(std::strcmp(t1->DajImeTima(), t2->DajImeTima()) < 0) return true;
                   else return false;
               }
               return t1->DajGolRazliku() > t2->DajGolRazliku();
           } 
           return t1->DajBrojPoena() > t2->DajBrojPoena();
        });
        for(int i=0; i<timovi.size(); i++) timovi[i]->IspisiPodatke();
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
