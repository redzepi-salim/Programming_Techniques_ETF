
/*Napišite generičke funkcije “Unija” i “Presjek” koje kao parametre primaju dva skupa (tj. objekta tipa 
“set”) proizvoljnog ali istog tipa elemenata, i koje kao rezultat daju novi skup koji predstavlja njihovu 
uniju, odnosno presjek. Napisane funkcije demonstrirajte u testnom programu koji nalazi uniju i presjek 
dva fiksna skupa čiji su elementi stringovi. */

#include <iostream>
#include <cmath>
#include <set>

template <typename Tip>
std::set<Tip> Unija(std::set<Tip> s1, std::set<Tip> s2) {
    std::set<Tip> s;
    for(Tip x : s1) s.insert(x);
    for(Tip x : s2) s.insert(x);
    return s;
}

template <typename Tip>
std::set<Tip> Presjek(std::set<Tip> s1, std::set<Tip> s2) {
    std::set<Tip> s;
    for(Tip x : s1) {
        for(Tip y : s2) {
            if(x == y) s.insert(x);
        }
    }
    return s;
}

int main ()
{
    int n, m;
	std::cout << "Koliko ima elemenata: " ;
	std::cin >> n >> m;
	std::set<std::string> s1, s2;
	std::cout << "Unesite elemente prvog skupa: " ;
    for(int i=0; i<n; i++){
		std::string temp;
		std::getline(std::cin, temp);
		s1.insert(temp);
	}
	std::cin.ignore(10000, '\n');
	std::cout << "Unesite elemente drugog skupa: " ;
	for(int i=0; i<m; i++){
		std::string temp;
		std::getline(std::cin, temp);
		s2.insert(temp);
	}
	std::set<std::string> unija = Unija(s1, s2), presjek = Presjek(s1, s2);
	std::cout << "Unija skupova: " ;
	for(std::string x : unija) std::cout << x << " " ;
	std::cout << std::endl << "Presjek skupova: " ;
	for(std::string x : presjek) std::cout << x << " " ;
	return 0;
}
