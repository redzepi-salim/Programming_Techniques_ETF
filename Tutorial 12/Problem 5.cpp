/*  TP 16/17 (Tutorijal 12, Zadatak 5)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)



Napravite program koji traži da se sa tastature unese slijed realnih brojeva u neki vektor (broj elemenata 
se također unosi sa tastature), a zatim zamjenjuje sve elemente vektora njihovim recipročnim vrijednostima 
i ispisuje elemente tako transformiranog vektora brojeva na ekran. Pri tome, transformaciju elemenata niza 
treba izvesti jednom jedinom naredbom, bez upotrebi petlji. Također, u programu nije dozvoljeno definirati 
nikakve pomoćne funkcije (dakle, “main” treba da bude jedina funkcija u programu), pa čak ni anonimne lambda 
funkcije. Za tu svrhu, poslužite se odgovarajućim funkcijama i funktorima iz biblioteka “algorithm” i 
“functional”.  Dijalog između korisnika i programa treba da izgleda poput sljedećeg: 

*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
int main ()
{
	int n;
	std::cout << "Koliko zelite elemenata: " ;
	std::cin >> n;
	std::vector<double> v(n);
	std::cout << "Unesite elemente: " ;
	for (int i = 0; i < n; i++) {
		std::cin >> v.at(i);
	}
	std::cout << "Transformirani elementi: " ;
	std::transform(v.begin(), v.end(), v.begin(), std::bind(std::divides<double>(), 1, std::placeholders::_1));
	for(int i=0; i<n; i++) std::cout << v.at(i) << " " ;
	return 0;
}
