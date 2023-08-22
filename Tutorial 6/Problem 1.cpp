/* TP 2018/2019: LV 6, Zadatak 1
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak



Napišite funkciju “GenerirajStepeneDvojke” sa jednim parametrom 𝑛, koja dinamički alocira niz od 𝑛 brojeva, 
ali čiji tačan tip nije specificiran nego se zadaje naknadno, npr. speficikacijom poput 
“GenerirajStepeneDvojke<unsigned long int>”. U slučaju da je 𝑛 ≤ 0, funkcija treba da baci izuzetak tipa 
“domain_error” uz prateći tekst “Broj elemenata mora biti pozitivan”. a u slučaju da alokacija ne uspije, 
funkcija treba da baci izuzetak tipa “runtime_error” uz prateći tekst “Alokacija nije uspjela”. Nakon 
alokacije, funkcija treba popuniti alocirani niz sa prvih 𝑛 stepena broja 2 (stepeni dvojke su redom 1, 
2, 4, 8, 16 itd.), pri čemu treba baciti izuzetak tipa “overflow_error” sa pratećim tekstom “Prekoracen 
dozvoljeni opseg” u slučaju da tom prilikom dođe do prekoračenja opsega tipa elemenata niza. Kao rezultat, 
funkcija treba da vrati  pokazivač na prvi element tako alociranog niza. Napisanu funkciju iskoristite u 
testnom programu u kojem se sa tastature unosi broj 𝑛, zatim poziva napisana funkcija za kreiranje traženog
niza, koji se potom ispisuje na ekran, i na kraju se vrši oslobađanje prostora koji je zauzeo niz. U 
testnom programu tip elemenata niza odaberite tako da program radi korektno za što je god moguće veće 𝑛, 
a da pri tome svi generirani stepeni dvojke budu prikazani potpuno egzaktno (odnosno bez ikakvog 
zaokruživanja). Također, u testnom programu treba predvidjeti hvatanje svih izuzetaka koji bi funkcija 
eventualno mogla baciti. Dijalozi između korisnika i programa trebali bi izgledati poput sljedećih: 	
*/
#include <iostream>
#include <stdexcept>
#include <limits>
#include <new>
#include <cmath>

template <typename NekiTip>
NekiTip *GenerirajStepeneDvojke(int n) {
    if(n <= 0) throw std::domain_error("Broj elemenata mora biti pozitivan");
    NekiTip temp1 = 1;
    for(int i=1; i<n; i++) temp1 *= 2;
    if(temp1 > std::numeric_limits<NekiTip>::max()) throw std::overflow_error("Prekoracen dozvoljeni opseg");
    NekiTip *a = nullptr;
    try {
        a = new NekiTip[n];
        for(int i=0; i<n; i++) {
            NekiTip temp = 1;
            for(int j=1; j<=i; j++) {
                temp *= 2;
                if(temp > std::numeric_limits<NekiTip>::max() || temp <= 0 || std::isinf(temp)) {
                    delete[] a;
                    throw std::overflow_error("Prekoracen dozvoljeni opseg");
                }
            }
            a[i] = temp;
        }
        return a;
    } catch(std::bad_alloc) {
        throw std::runtime_error("Alokacija nije uspjela");
    }
}

int main ()
{
    try {
        int n;
        std::cout << "Koliko zelite elemenata: ";
        std::cin >> n;
        unsigned long int *p = nullptr;
        p = GenerirajStepeneDvojke<unsigned long int>(n);
        for(int i=0; i<n; i++) {
            std::cout << p[i] << " ";
        }
        delete[] p;
    } catch(std::domain_error izuzetak) {
        std::cout << "Izuzetak: " << izuzetak.what();
    } catch(std::overflow_error izuzetak) {
        std::cout << "Izuzetak: " << izuzetak.what();
    } catch(std::runtime_error izuzetak) {
        std::cout << "Izuzetak: " << izuzetak.what();
    }
	return 0;
}
