//TP 2020/2021: Tutorijal 2, Zadatak 1

/*Prosti brojevi su oni prirodni brojevi koji imaju tačno dva različita djelioca u skupu ℕ: jedinicu i 
samog sebe (prividno slična definicija po kojoj su prosti brojevi oni i samo oni koji su djeljivi samo sa 
jedinicom i sa samim sobom nije u potpunosti tačna, razmislite zašto). Napišite prvo funkciju “DaLiJeProst” 
sa jednim parametrom “n” koji predstavlja neki cijeli broj, a koja kao rezultat vraća logičku vrijednost 
“tačno” ili “netačno” u ovisnosti od toga da li je parametar prost broj ili ne. Zatim napišite funkciju 
“ProstiBrojeviUOpsegu”, također sa dva cjelobrojna parametra “a” i “b” koja kao rezultat vraća vektor koji 
se sastoji od svih prostih brojeva u intervalu od “a” do “b” uključivo (tj. svih prostih brojeva koji su 
veći ili jednaki od “a”, a manji ili jednaki od “b”). Napisanu funkciju iskoristite u glavnom programu koji 
traži da se sa tastature unesu dva cijela broja, a zatim za sve cijele brojeve u opsegu između ta dva 
unesena broja ispisuje koji su prosti brojevi u datom opsegu, ili informaciju da nema prostih brojeva u 
datom opsegu. Dijalozi između korisnika i programa trebali bi izgledati poput sljedećih (ovisno ima li 
ili nema prostih brojeva u zadanom opsegu): */

#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

bool DaLiJeProst(int n) {
    if (n < 2) return false;
    if(n < 4) return true;
    if(n > 2 && n%2 == 0) return false;
    if(n > 5 && (n%5 == 0 || n%10 == 5)) return false;
    for(int i=3; i<=std::sqrt(n); i += 2) {
        if(n%i == 0) return false;
    }
    return true;
}

std::vector<int> ProstiBrojeviUOpsegu(int a, int b) {
    std::vector<int> prosti;
    if (a < 0) a = 2;
    for(int i=a; i<=b; i++) {
        if(DaLiJeProst(i)) prosti.push_back(i);
        if(i == std::numeric_limits<int>::max()) break;
    }
    return prosti;
}

int main ()
{
    int a, b;
    std::cout << "Unesite pocetnu i krajnju vrijednost: ";
    std::cin >> a >> b;
    std::vector<int> prosti = ProstiBrojeviUOpsegu(a, b);
    if(prosti.size() != 0) {
        std::cout << "Prosti brojevi u rasponu od " << a << " do " << b << " su: ";
        for(int i=0; i<prosti.size(); i++) {
            if(i < prosti.size() - 1) std::cout << prosti.at(i) << ", ";
            else std::cout << prosti.at(i);
        }
        std::cout << std::endl;
    }
    else std::cout << "Nema prostih brojeva u rasponu od " << a << " do " << b << "!";
    return 0;
}
