/*  TP 16/17 (LV 12, Zadatak 2)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)



Za skupovni tip “set” iz istoimene biblioteke definirajte operatore “+” i “*” koji će za dva skupa sa istim 
tipom elemenata dati kao rezultat respektivno njihovu uniju i presjek, kao i operator “<<” koji omogućava 
ispis elemenata skupa u vitičastim zagradama, koji su međusobno razdvojeni zarezima (kao pomoć, možete se 
poslužiti Zadatkom 7 s Laboratorijske vježbe 7). Također definirajte i odgovarajuće operatore “+=” i “*=” 
Nakon definiranja ovih operatora, mora postati moguće nešto poput sljedećeg:   
std::set<int> s1{3, 5, 1, 2, 8}, s2{7, 2, 8, 4};  
td::cout << s1 + s2 << std::endl;             // Ispis "{1,2,3,4,5,7,8}"  
std::cout << s1 * s2 << std::endl;             // Ispis "{2,8}"   
Također definirajte i operator “%” koji daje kao rezultat Dekartov proizvod skupova-operanada, pri čemu tip 
njihovih elemenata ne mora biti isti (operator “%=” ovdje nije moguće definirati, razmislite zašto). Kako 
su elementi Dekartovog proizvoda zapravo uređeni parovi, za njihovo formiranje koristite bibliotečki tip 
“pair”. Dalje, kako za objekte tipa “pair” nije inicijalno uvedena podrška za ispisivanje na ekran, 
uvedite i tu podršku (preklapanjem operatora “<<”) da omogućite njihov ispis na ekran kao uređenih parova u 
zagradama, sa prvom i drugom koordinatom razdvojenom zarezom. Kad sve ovo uradite, trebalo bi postati 
moguće nešto poput sljedećeg:   
std::set<char> s3{'A', 'B'};  
std::set<int> s4{1, 2, 3};  
std::cout << s1 % s2 << std::endl;    // Ispis "{(A,1),(A,2),(A,3),(B,1),(B,2),(B,3)}" 
*/
#include <iostream>
#include <set>
#include <utility>

template <typename Tip>
std::set<Tip> operator +(std::set<Tip> s1, std::set<Tip> s2) {
    std::set<Tip> s;
    for(auto x : s1) s.insert(x);
    for(auto x : s2) s.insert(x);
    return s;
}

template <typename Tip>
std::set<Tip> operator *(std::set<Tip> s1, std::set<Tip> s2) {
    std::set<Tip> s;
    for(auto x : s1) {
        if(s2.find(x) != s2.end()) s.insert(x);
    }
    return s;
}

template <typename Tip>
std::ostream &operator <<(std::ostream &tok, const std::set<Tip> &s) {
    tok << "{";
    for(auto it = s.begin(); it != s.end(); it++) {
        if(it == --s.end()) tok << *it;
        else tok << *it << ",";
    }
    tok << "}";
    return tok;
}

template <typename Tip>
std::set<Tip> &operator +=(std::set<Tip> &s1, std::set<Tip> s2) {
    for(auto x : s2) s1.insert(x);
    return s1;
}

template <typename Tip>
std::set<Tip> &operator *=(std::set<Tip> &s1, const std::set<Tip> &s2) {
    std::set<Tip> s;
    for(auto x : s1) {
        for(auto y : s2) if(x == y) s.insert(x);
    }
    s1 = s;
    return s1;
}

template <typename Tip1, typename Tip2>
std::set<std::pair<Tip1, Tip2>> operator %(const std::set<Tip1> &s1, const std::set<Tip2> &s2) {
    std::set<std::pair<Tip1, Tip2>> dekart;
    for(auto x : s1) {
        for(auto y : s2) dekart.insert(std::make_pair(x, y));
    }
    return dekart;
}

template <typename Tip1, typename Tip2>
std::ostream &operator <<(std::ostream &tok, const std::set<std::pair<Tip1, Tip2>> &dekart) {
    tok << "{";
    for(auto it = dekart.begin(); it != dekart.end(); it++) {
        if(it == --dekart.end()) tok << "(" << it->first << "," << it->second << ")";
        else tok << "(" << it->first << "," << it->second << "),";
    }
    tok << "}";
    return tok;
}

int main ()
{
	return 0;
}
