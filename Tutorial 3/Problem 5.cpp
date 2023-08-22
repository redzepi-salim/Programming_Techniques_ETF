//TP 2021/2022: LV 3, Zadatak 5

/*U prethodnom programu, izvršite izmjene u funkciji “IzdvojiElemente” tako da se i dalje koristi funkcija 
“push front”, ali da rezultat koji daje funkcija bude isti kakav je bio u Zadatku 3. (tako da i ispis koji 
će program proizvesti bude isti kao u Zadatku 3.). Pri tome, u funkciji nije dozvoljeno kreiranje ikakvih 
pomoćnih kontejnera (nizova, vektora, dekova, itd.). */

#include <iostream>
#include <cmath>
#include <deque>

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

std::deque<int> IzdvojiElemente(std::deque<int> v, bool parni) {
    std::deque<int> novo;
    if(parni) {
        for(int i=v.size()-1; i>=0; i--) {
            if(ParnaSuma(v.at(i))) novo.push_front(v.at(i));
        }
    }
    else {
        for(int i=v.size()-1; i>=0; i--) {
            if(!ParnaSuma(v.at(i))) novo.push_front(v.at(i));
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
    std::deque<int> v(n);
    std::cout << "Unesite elemente: ";
    for(int i=0; i<n; i++) {
        std::cin >> v.at(i);
    }
    std::deque<int> b = IzdvojiElemente(v, true), c = IzdvojiElemente(v, false);
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
