//TP 2021/2022: LV 3, Zadatak 8

/*Napišite funkciju “IzdvojiRijec” sa dva parametra, od kojih je prvi tipa “string”, a drugi je cjelobrojan 
(tipa “int”). Prvi parametar predstavlja neku rečenicu, a drugi parametar redni broj riječi unutar te 
rečenice. Funkcija treba da izdvoji tu riječ iz rečenice, i da vrati kao rezultat tako izdvojenu riječ.
 Na primjer, ukoliko je kao prvi parametar zadan tekst “   Na   vrh brda      vrba   mrda” a kao drugi 
 parametar broj 4, funkcija treba kao rezultat da vrati string “vrba”. Ovdje pod pojmom riječ 
 podrazumijevamo bilo koji slijed uzastopnih znakova koji nisu razmaci, a ispred kojeg se eventualno 
 nalazi razmak (ili ništa), i iza kojeg eventualno slijedi razmak (ili ništa). Tako se, na primjer, u 
 tekstu “Kiša pada.Trava raste” slijed znakova “pada.Trava” tretira kao jedna riječ (druga po redu), jer 
 iza tačke nema razmaka (ovakav tretman vrijedi i u tekst procesorima poput Microsoft Word-a). Obratite 
 pažnju da riječi mogu biti razdvojene sa više uzastopnih razmaka, kao i da na početku i kraju teksta 
 može, ali i ne mora biti razmaka. Ukoliko je drugi parametar manji od 1 ili veći od broja riječi u 
 rečenici, funkcija treba baciti izuzetak tipa “range_error” uz prateći indeks “Pogresan redni broj rijeci”.  
  Napisanu funkciju demonstrirajte u testnom programu u kojem se za prirodan broj 𝑛 unesen sa tastature i 
  rečenicu unesenu sa tastature ispisuje 𝑛-ta riječ te rečenice (pozivom napisane funkcije). U testnom 
  programu obavezno predvidite hvatanje izuzetaka koji mogu biti bačeni iz funkcije. Dijalozi između 
  korisnika i programa trebaju izgledati poput sljedećeg: */

#include <iostream>
#include <string>
#include <stdexcept>

std::string IzdvojiRijec(std::string s, int n) {
    bool razmak = true;
    int br_rijeci = 0;
    std::string s1;
    for(char x : s) {
        if(x == ' ') {
            razmak = true;
            continue;
        }
        else if (razmak == true) {
            razmak = false;
            br_rijeci++;
        }
        if(br_rijeci == n && x != ' ') {
            s1.push_back(x);
        }
    }
    if(n < 1 || n > br_rijeci) throw std::range_error("IZUZETAK: Pogresan redni broj rijeci!");
    return s1;
}

int main ()
{
    int n;
    std::cout << "Unesite redni broj rijeci: " ;
    std::cin >> n;
    std::cin.ignore(10000, '\n');
    std::string s;
    std::cout << "Unesite recenicu: ";
    std::getline(std::cin, s);
    try {
        std::cout << "Rijec na poziciji " << n << " je " << IzdvojiRijec(s, n);
    } catch(std::range_error izuzetak) {
        std::cout << izuzetak.what() << std::endl;
    }
	return 0;
}
