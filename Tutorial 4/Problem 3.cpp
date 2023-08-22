//TP 2021/2022: LV 4, Zadatak 3

/*Napišite funkciju “IzdvojiKrajnjeRijeci” sa 3 parametra, čiji je prvi parametar vektor stringova 
(tj. vektor čiji su elementi tipa “string”) za koji se pretpostavlja da sadrži neki spisak riječi (svaka 
riječ je u posebnom stringu). Funkcija treba da pronađe prvu i posljednju riječ po abecednom poretku (ne
 praveći pri tome razliku između malih i velikih slova) i da ih smjesti redom u drugi i treći parametar 
 funkcije. U slučaju praznog vektora, u drugi i treći parametar treba smjestiti prazan string. Zatim 
 napišite funkciju “ZadrziDuplikate” čiji je jedini parametar ponovo vektor stringova za koji se 
 pretpostavlja da sadrži neki spisak riječi. Funkcija treba da modificira ovaj vektor stringova, tako što 
 će u njemu zadržati samo one stringove (riječi) koji su duplikati, tj. koji se u vektoru pojavljuju više 
 od jedanput, pri čemu svaki duplikat treba zadržati samo jedanput (tačnije, prilikom njegovog prvog 
 pojavljivanja). Recimo, ukoliko vektor sadrži redom riječi “xyzzy”, “qwert”, “uiop”, “asd”, “rrrfat”, 
 “asd”, “yxcvbb”, “qwert”, “asd” i “cvbnm”, nakon poziva ove funkcije isti vektor treba da sadrži samo 
 riječi “qwert” i “asd” (u tom poretku), jer su ovo jedine dvije riječi koje se pojavljuju više od jedanput 
 unutar vektora. Za realizaciju ove funkcije nije dozvoljeno koristiti funkciju “erase”. Napisane funkcije 
 iskoristite u testnom programu koji traži od korisnika da unese spisak riječi (broj riječi se prethodno
  unosi sa tastature), a zatim ispisuje na ekran prvu i poslednju riječ iz spiska po abecednom poretku, 
  kao i popis svih riječi koje se ponavljaju. Dijalog između korisnika i programa bi trebao izgledati poput 
  sljedećeg: */

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <cctype>

void IzdvojiKrajnjeRijeci(std::vector<std::string> v, std::string &s_min, std::string &s_max) {
    if(v.size() == 0) return;
    std::vector<std::string> s = v, &s_temp = v;
    for(int i=0; i<s.size(); i++) {
        for(char &x : s.at(i)) x = std::toupper(x);
    }
    s_max = s.at(0);
    s_min = s.at(0);
    for(auto x : s) {
        if(x > s_max) s_max = x;
        if(x < s_min) s_min = x;
    }
    int i_max, i_min;
    for(int i=0; i<s.size(); i++) {
        if(s.at(i) == s_max) i_max = i;
        if(s.at(i) == s_min) i_min = i;
    }
    for(int i=0; i<s_temp.size(); i++) {
        if(i == i_max) s_max = s_temp.at(i);
        if(i == i_min) s_min = s_temp.at(i);
    }
}

bool Duplikat(std::vector<std::string> v, std::string s, int i) {
    for(int j=i + 1; j<v.size(); j++) {
        if(s == v.at(j)) return true;
    }
    return false;
}

void ZadrziDuplikate(std::vector<std::string> &v) {
    std::vector<std::string> temp;
    for(int i=0; i<v.size(); i++) {
        if(Duplikat(v, v.at(i), i) && !Duplikat(temp, v.at(i), -1)) temp.push_back(v.at(i));
    }
    v = temp;
}

int main ()
{
    int n;
    std::cout << "Koliko zelite unijeti  rijeci: ";
    std::cin >> n;
    std::vector<std::string> s(n);
    std::cout << "Unesite rijeci: " << std::endl;
    std::cin.ignore(10000, '\n');
    for(int i=0; i<n; i++) {
        std::cin >> s.at(i);
    }
    std::string prva_rijec, zadnja_rijec;
    IzdvojiKrajnjeRijeci(s, prva_rijec, zadnja_rijec);
    ZadrziDuplikate(s);
    std::cout << "Prva rijec po abecednom poretku je: " << prva_rijec << std::endl;
    std::cout << "Posljednja rijec po abecednom poretku je: " << zadnja_rijec << std::endl;
    std::cout << "Rijeci koje se ponavljaju su: " ;
    for(auto x : s) std::cout << x << " ";
	return 0;
}
