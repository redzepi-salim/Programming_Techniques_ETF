/*  TP 2018/2019: LV 6, Zadatak 4
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak



Ponovite prethodni zadatak, ali uz korištenje kontinualne umjesto fragmentirane alokacije. 
*/
#include <iostream>
#include <stdexcept>
#include <new>

int **KreirajTrougao(int n) {
    if(n<=0) throw std::domain_error("Broj redova mora biti pozitivan");
    int **a = nullptr;
    try {
        a = new int*[n]{};
        try {
            a[0] = new int[n*n];
            int m = 1;
            for(int i=1; i<n; i++) {
                a[i] = a[i - 1] + m;
                m += 2;
            }
            m = 1;
            for(int i=0; i<n; i++) {
                int b=0;
                for(int j=0; j<m; j++) {
                    if(i == j) a[i][j] = 1;
                    else if(i > j) {
                        a[i][j] = i + 1 - b;
                        b++;
                    }
                    else {
                        b--;
                        a[i][j] = i + 1 - b;
                    }
                }
                m += 2;
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
    int n;
	std::cout << "Koliko zelite redova: " ;
	std::cin >> n;
	int **a = nullptr;
	try {
		a = KreirajTrougao(n);
		int m=1;
		for(int i=0; i<n; i++) {
			for(int j=0; j<m; j++) {
				std::cout << a[i][j] << " ";
			}
			std::cout << std::endl;
			m += 2;
		}
		delete[] a[0];
        delete[] a;
	} catch (std::domain_error izuzetak) {
		std::cout << "Izuzetak: " << izuzetak.what() << std::endl;
	} catch (std::bad_alloc) {
		std::cout << "Izuzetak: Nedovoljno memorije!" << std::endl;
	}
	return 0;
}
