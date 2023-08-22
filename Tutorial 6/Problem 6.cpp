/*  TP 2018/2019: LV 6, Zadatak 6
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak



Ponovite prethodni zadatak, ali uz korištenje kontinualne umjesto fragmentirane alokacije. 
*/
#include <iostream>
#include <new>
#include <vector>
#include <deque>
#include <type_traits>

template <typename NekiTip1>
auto KreirajDinamickuKopiju2D(NekiTip1 v) -> typename std::remove_reference<decltype(v[0][0])>::type**
{
	try {
		int brojac = 0;
		auto a = new typename std::remove_reference<decltype(v[0][0])>::type*[v.size()];
		try {
			for(int i=0; i<v.size(); i++) {
				brojac += v[i].size();
			}
			a[0] = new typename std::remove_reference<decltype(v[0][0])>::type[brojac];
			for(int i=1; i<v.size(); i++) {
				a[i] = a[i-1] + v[i-1].size();
			}
			for(int i=0; i<v.size(); i++) {
				for(int j=0; j<v[i].size(); j++) {
					a[i][j] = v[i][j];
				}
			}
			return a;
		} catch (...) {
			delete[] a;
			throw std::bad_alloc();
		}
	} catch (...) {
		throw std::bad_alloc();
	}
}
int main ()
{
    try {
		int n;
		std::cout << "Unesite broj redova kvadratne matrice: " ;
		std::cin >> n;
		std::vector<std::deque<int>> v(n, std::deque<int> (n));
		std::cout << "Unesite elemente matrice: " ;
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				std::cin >> v[i][j];
			}
		}
		int **a = nullptr;
		a = KreirajDinamickuKopiju2D(v);
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				std::cout << a[i][j] << " " ;
			}
			std::cout << std::endl;
		}
		delete[] a[0];
		delete[] a;
	} catch (std::bad_alloc) {
		std::cout << "Nedovoljno memorije" << std::endl;
	}
	return 0;
}
