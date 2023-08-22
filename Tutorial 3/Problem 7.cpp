//TP 2021/2022: LV 3, Zadatak 7

/*Napišite funkciju “PascalovTrougao” (ili “PascalovTrokut”, ovisno od Vaših jezičkih preferencija) 
koja kao parametar prima cijeli broj 𝑛. Ova funkcija treba kreirati strukturu “grbave matrice” sa 
𝑛 redova u kojoj prvi red ima jedan element, drugi red dva elementa, treći red tri elementa, itd. 
koju nakon kreiranja treba popuniti elementima Pascalovog trougla (trokuta) sa 𝑛 redova. Funkcija 
treba da kao rezultat vrati upravo tako kreiranu “grbavu matricu”. Funkciju testirajte u programu 
koji za unesenu vrijednost 𝑛 sa tastature ispisuje Pascalov trougao (trokut) sa 𝑛 redova. Prilikom 
ispisa, za svaki element treba zauzeti onoliko prostora koliko iznosi širina najšireg broja koji se 
javlja u trouglu (trokutu) uvećana za 1, uz ravnanje udesno (za određivanje ove širine, iskoristite 
istu funkciju “NajvecaSirina” koju ste pisali u prethodnom zadatku. Uglavnom, dijalog između programa 
i korisnika trebao bi izgledati poput sljedećeg; 
Pri tome, elemente Pascalovog trougla nije dozvoljeno računati preko binomnih koeficijenata, već treba 
koristiti činjenicu da je svaki element Pascalovog trougla jednak zbiru elemenata koji se nalaze tačno 
iznad njega, i njegovog susjeda sa lijeve strane.   Ukoliko se funkciji 𝑛 kao parametar proslijedi 0, 
funkcija treba da vrati praznu matricu. Ukoliko joj se proslijedi negativan broj, funkcija treba da baci 
izuzetak tipa “domain_error” uz prateći tekst “Broj redova ne smije biti negativan”. U glavnom programu 
ne trebate predvidjeti hvatanje ovog izuzetka, ali će biti testirano da li ga funkcija zaista baca. */

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <stdexcept>

std::vector<std::vector<int>> PascalovTrougao(int n) {
    if( n == 0) {
        std::vector<std::vector<int>> m;
        return m;
    }
    if(n < 0) throw std::domain_error("Broj redova ne smije biti negativan");
    std::vector<std::vector<int>> v(n);
    for(int i=0; i<v.size(); i++) {
        v.at(i).resize(i + 1);
        for(int j=0; j<=i; j++) {
            if(j == 0 || i == j) v.at(i).at(j) = 1;
            else v.at(i).at(j) = v.at(i-1).at(j-1) + v.at(i-1).at(j);
        }
    }
    return v;
}

int NajvecaSirina(std::vector<std::vector<int>> m) {
    int brojac = 0;
    if(m.size() == 0) return 0;
    std::vector<int> sirina;
    for(std::vector<int> v : m) {
        for(int x : v) {
            if(x < 0) brojac++;
            while(x != 0) {
                x = x/10;
                brojac++;
            }
            sirina.push_back(brojac);
            brojac = 0;
        }
    }
    int max = sirina.at(0);
    for(int i=0; i<sirina.size(); i++) {
        if(sirina.at(i) > max) max = sirina.at(i);
    }
    return max;
}

int main ()
{
    int n;
    std::cout << "Unesite broj redova: ";
    std::cin >> n;
    std::cout << std::endl;
    try {
        std::vector<std::vector<int>> m = PascalovTrougao(n);
        for(std::vector<int> v : m) {
            for(int x : v) {
                std::cout << std::setw(NajvecaSirina(m) + 1) << std::right << x;
            }
            std::cout << std::endl;
        }
    } catch(std::domain_error izuzetak) {
        std::cout << izuzetak.what() << std::endl;
    }
	return 0;
}
