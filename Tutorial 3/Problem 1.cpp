//TP 2021/2022: LV 3, Zadatak 1

/*Napišite funkciju “IzdvojiElemente” sa dva parametra, od kojih je prvi vektor cijelih brojeva 
(tipa “int”), a drugi logička vrijednost “tačno” ili “netačno”. Funkcija treba da kao rezultat vrati 
novi vektor koji se sastoji od onih elemenata čija je suma cifara parna odnosno neparna, ovisno od toga 
da li drugi parametar ima vrijednost “tačno” ili “netačno”. Elementi u novokreiranom vektoru trebaju biti 
u istom međusobnom poretku u kakvom su bili u izvornom vektoru. Za realizaciju funkcije obavezno koristite 
funkciju “push_back”. Napisanu funkciju iskoristite u testnom programu koji traži da se prvo unese prirodan 
broj 𝑛, a nakon toga elementi vektora “a”  koji ima 𝑛 cjelobrojnih elemenata. Program zatim treba da kreira 
dva nova vektora “b” i “c”, i da u vektor “b” prepiše sve brojeve iz vektora “a” sa parnom sumom cifara, a 
u vektor “c” sve brojeve iz vektora “a” sa neparnom sumom cifara. Konačno, program treba da u jednom redu 
ispiše brojeve sa parnom sumom cifara, a u drugom redu brojeve sa neparnim brojem cifara (moguće je da neki 
red ostane prazan, ukoliko nema niti jedan broj sa traženim svojstvom). Mogući dijalozi između programa i 
korisnika trebaju izgledati ovako: */

#include <iostream>
#include <cmath>
#include <vector>

bool ParnaSuma(int n) {
    int suma = 0;
    while(n!=0) {
        int x = n%10;
        n = n/10;
        suma += x;
    }
    if(suma % 2 == 0) return true;
    return false;
}

std::vector<int> IzdvojiElemente(std::vector<int> v, bool parni) {
    std::vector<int> novo;
    if(parni) {
        for(int i=0; i<v.size(); i++) {
            if(ParnaSuma(v.at(i))) novo.push_back(v.at(i));
        }
    }
    else {
        for(int i=0; i<v.size(); i++) {
            if(!ParnaSuma(v.at(i))) novo.push_back(v.at(i));
        }
    }
    return novo;
}

int main ()
{
    int n;
    std::cout << "Koliko zelite unijeti elemenata: ";
    std::cin >> n;
    if(n <= 0) {
        std::cout << "Broj elemenata mora biti veci od 0!";
        return 1;
    }
    std::vector<int> v(n);
    std::cout << "Unesite elemente: ";
    for(int i=0; i<n; i++) {
        std::cin >> v.at(i);
    }
    std::vector<int> b = IzdvojiElemente(v, true), c = IzdvojiElemente(v, false);
    for(int x : b) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    for(int x : c) {
        std::cout << x << " ";
    }
	return 0;
}
