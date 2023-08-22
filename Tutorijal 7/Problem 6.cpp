
/*Napišite generičku funkciju “SortirajListu” koja kao parametar prima neku listu (tj. objekat tipa “list”) 
čiji su elementi proizvoljnog tipa, ali koji se mogu upoređivati pomoću operatora “<”. Funkcija treba da 
kao rezultat vrati novu listu čiji su elementi isti kao u listi navedenoj kao parametar, ali sortirani u 
rastući poredak. Pri tome, sortiranje treba obaviti “ručno”, ne koristeći nikakve bibliotečke funkcije. 
Nije bitno da postupak sortiranja bude efikasan, bitno je samo da radi (sa znanjem koje trenutno imate, 
nećete moći napisati ikakav iole efikasniji postupak). Funkciju demonstrirajte u testnom programu koji će 
za listu cijelih brojeva unesenu sa tastature (broj elemenata se također zadaje putem tastature) kreirati
novu sortiranu listu i ispisati njen sadržaj na ekran. Dijalog između programa i korisnika treba izgledati 
poput sljedećeg: */

#include <iostream>
#include <cmath>
#include <list>

template <typename NekiTip>
std::list<NekiTip> SortirajListu(std::list<NekiTip> lista) {
    for(typename std::list<NekiTip>::iterator it1 = lista.begin(); it1 != lista.end(); it1++) {
        for(typename std::list<NekiTip>::iterator it2=it1; it2 != lista.end(); it2++) {
            if(*it1 > *it2) {
                NekiTip temp = *it1;
                *it1 = *it2;
                *it2 = temp;
            }
        }
    }
    return lista;
}

int main ()
{
    int n;
	std::cout << "Koliko ima elemenata: " ;
	std::cin >> n;
	std::list<int> lista;
	std::cout << "Unesite elemente: " ;
	for(int i=0; i<n; i++){
		int x;
		std::cin >> x;
		lista.push_back(x);
	}
	std::list<int> temp = SortirajListu(lista);
	std::cout << "Sortirana lista: " ;
	for(int x : temp) std::cout << x << " " ;
	return 0;
}
