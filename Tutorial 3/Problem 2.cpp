//TP 2021/2022: LV 3, Zadatak 2

/*Prepravite prethodni program tako da se brojevi ispisuju razdvojeni zarezom a ne razmakom, pri čemu 
iza posljednjeg broja u svakom redu ne treba da bude zarez. Na primjer, za iste ulazne podatke kao u 
prethodnom zadatku, dijalozi između korisnika i programa trebali bi izgledati ovako:*/

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
    for(int i=0; i<b.size(); i++) {
        if(i == b.size() - 1) std::cout << b.at(i) << std::endl;
        else std::cout << b.at(i) << ",";
    }
    for(int i=0; i<c.size(); i++) {
        if(i == c.size() - 1) std::cout << c.at(i);
        else std::cout << c.at(i) << ",";
    }
	return 0;
}
