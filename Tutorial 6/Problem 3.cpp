/* TP 2018/2019: LV 6, Zadatak 3
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak



Napišite funkciju “KreirajTrougao” (ili “KreirajTrokut”, ovisno od Vaših jezičkih preferencija) sa jednim 
cjelobrojnim parametrom 𝑛 koja vrši dinamičku alokaciju “grbave matrice” sa 𝑛 redova u kojoj prvi red 
sadrži samo element 1, drugi red elemente 2, 1 i 2, treći red elemente 3, 2, 1, 2 i 3, četvrti red elemente 
4, 3, 2, 1, 2, 3 i 4, itd. (elementi su tipa “int”). Kao rezultat, funkcija vraća dvostruki pokazivač preko 
kojeg se može pristupiti elementima tako kreirane grbave matrice. Ukoliko je 𝑛 negativan ili 0, funkcija 
treba baciti izuzetak tipa “domain_error”, uz prateći tekst “Broj redova mora biti pozitivan”. U slučaju 
da alokacija ne uspije, funkcija treba baciti izuzetak tipa “bad_alloc”, pazeći pri tome da ne dođe do 
curenja memorije ni u kakvim okolnostima. Za alociranje koristite postupak fragmentirane alokacije. 
Napisanu funkciju iskoristite u isječku programa koji traži da se sa tastature unese broj 𝑛, zatim kreira 
“grbavu matricu” traženih svojstava sa 𝑛 redova, te na kraju ispisuje njene elemente red po red (uz jedan 
razmak između elemenata istog reda) nakon čega oslobađa prostor koji je zauzela ta matrica. Predvidite i 
hvatanje svih izuzetaka koji bi funkcija eventualno mogla baciti. U slučaju bacanja izuzetka tipa 
“bad_alloc”, tekst koji se prikazuje na ekranu treba glasiti “Izuzetak: Nedovoljno memorije!”. Dijalozi 
između korisnika i programa trebaju izgledati poput sljedećih: 
*/
#include <iostream>
#include <new>
#include <stdexcept>

int **KreirajTrougao(int n) {
    if(n <= 0) throw std::domain_error("Broj redova mora biti pozitivan");
    int **a = nullptr;
    try {
        a = new int* [n]{nullptr};
        int brojac = 0;
        try {
            int m = 1;
            while(brojac < n) {
                a[brojac++] = new int [m];
                m += 2;
            }
            m = 1;
            for(int i=0; i<n; i++) {
                int b = 0;
                for(int j=0; j<m; j++) {
                    if (i == j) a[i][j] = 1;
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
        } catch (std::bad_alloc) {
            for(int i=0; i<n; i++) delete[] a[i];
            delete[] a;
            throw std::bad_alloc();
        }
    } catch(std::bad_alloc) { throw std::bad_alloc(); }
    return a;
}
int main ()
{
    int n;
    std::cout << "Koliko zelite redova: ";
    std::cin >> n;
    int m = 1;
    try {
        int **p = KreirajTrougao(n);
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                std::cout << p[i][j] << " ";
            }
            std::cout << std::endl;
            m += 2;
        }
        for(int i=0; i<n; i++) delete[] p[i];
        delete[] p;
    } catch(std::domain_error izuzetak) {
        std::cout << "Izuzetak: " << izuzetak.what();
    } catch(std::bad_alloc) {
        std::cout << "Izuzetak: Nedovoljno memorije!" ;
    }
	return 0;
}
