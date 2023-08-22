/*  TP 2018/2019: LV 6, Zadatak 5
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak



Napišite generičku funkciju “KreirajDinamickuKopiju2D” koja kao svoj parametar prima neku dvodimenzionalnu 
strukturu nalik matrici, ali pri čemu broj elemenata u svakom redu ne mora nužno biti isti. Pretpostavlja 
se da je ta struktura predstavljena kao neki kontejnerski tip čiji su elementi ponovo nekog kontejnerskog 
tipa, ne nužno istog. Recimo, to može biti vektor vektōrâ, vektor dekōvâ, dek vektōrâ, dek dekōvâ, itd. 
Jedino ograničenje koje se postavlja na te kontejnerske tipove je da se mogu indeksirati i da podržavaju 
funkciju “size”. Elementi “unutrašnjeg” kontejnerskog tipa mogu također biti proizvoljnog tipa. Funkcija 
prvo treba da dinamički alocira prostor za dvodimenzionalnu strukturu identičnog oblika kao i parametar, 
zatim da u nju prepiše elemente dvodimenzionalne strukture predstavljene parametrom i, konačno, da kao 
rezultat vrati dvojni pokazivač preko kojeg se može izvršiti pristup elementima ove strukture. Za alociranje 
koristite metod fragmentirane alokacije. U slučaju da dođe do problema sa alokacijom memorije, funkcija 
treba baciti izuzetak (tipa “bad_alloc”). Pri tome, ni u kom slučaju ne smije doći do curenja memorije. 
Napisanu funkciju testirajte u testnom programu koji sa tastature unosi elemente matrice formata 𝑛 × 𝑛 
organizirane kao vektor dekōvâ cijelih brojeva (𝑛 se prethodno unosi sa tastature), a nakon toga poziva 
napisanu funkciju sa ciljem kreiranja odgovarajuće dinamičke matrice i, konačno, ispisuje elemente tako 
kreirane dinamičke matrice na ekran (svaki red matrice u posebnom redu, uz razmak između elemenata unutar 
jednog reda) i oslobađa zauzetu memoriju. U testnom programu predvidite i eventualno hvatanje bačenih 
izuzetaka. Dijalog između programa i korisnika treba izgledati poput sljedećeg (uz ispis teksta “Nedovoljno 
memorije” u slučaju bacanja izuzetka tipa “bad_alloc”): 
*/
#include <iostream>
#include <vector>
#include <deque>
#include <new>
#include <type_traits>

template <typename Tip>
auto KreirajDinamickuKopiju2D(Tip v) -> typename std::remove_reference<decltype(v[0][0])>::type** {
    try {
        auto a = new typename std::remove_reference<decltype(v[0][0])>::type* [v.size()]{nullptr};
        try {
            for(int i=0; i<v.size(); i++) {
                a[i] = new typename std::remove_reference<decltype(v[0][0])>::type [v[i].size()]{};
            }
            for(int i=0; i<v.size(); i++) {
                for(int j=0; j<v[i].size(); j++) {
                    a[i][j] = v[i][j];
                }
            }
            return a;
        } catch (std::bad_alloc) {
            for(int i=0; i<v.size(); i++) delete[] a[i];
            delete[] a;
            throw std::bad_alloc();
        }
    } catch(std::bad_alloc) { throw std::bad_alloc(); }
}

int main ()
{
    try {
        int n;
        std::cout << "Unesite broj redova kvadratne matrice: ";
        std::cin >> n;
        std::vector<std::deque<int>> v(n, std::deque<int>(n));
        std::cout << "Unesite elemente matrice: ";
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) std::cin >> v.at(i).at(j);
        }
        int **a = nullptr;
        a = KreirajDinamickuKopiju2D(v);
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) std::cout << a[i][j] << " ";
            std::cout << std::endl;
        }
        for(int i=0; i<n; i++) delete[] a[i];
        delete[] a;
    } catch(std::bad_alloc) {
        std::cout << "Nedovoljno memorije";
    }
	return 0;
}
