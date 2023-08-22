/* TP 2018/2019: LV 6, Zadatak 2	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak



Napišite generičku funkciju “KreirajIzvrnutiNiz” sa dva parametra koji predstavljaju pokazivače ili 
iteratore koji omeđuju neki blok elemenata (prvi parametar pokazuje na početak, a drugi tačno iza 
kraja bloka). Funkcija prvo treba da dinamički kreira niz čiji su elementi istog tipa kao i elementi 
razmatranog bloka i koji sadrži isti broj elemenata kao i razmatrani. U slučaju da alokacija ne uspije, 
funkcija treba baciti izuzetak tipa “bad_alloc”, što je uobičajeno ponašanje u slučajevima kada alokacija 
ne uspijeva. Funkcija zatim treba prepisati sve elemente bloka u kreirani niz u obrnutom poretku (tj. prvi 
element bloka treba da postane posljednji element niza itd.) i vratiti pokazivač na prvi element tako 
kreiranog niza kao rezultat. Nad pokazivačima odnosno iteratorima koji se prosljeđuju kao parametri 
funkcije nije dozvoljeno koristiti niti jednu drugu operaciju osim dodjele (“=”), dereferenciranja (“*”), 
poređenja na jednakost i različitost (“==” i “!=”), te pomjeranja unaprijed (“++”). Razlog za ova 
ograničenja je da se funkcija učini univerzalnijom tako da može raditi i sa kontejnerima čiji iteratori 
nisu jednako moćni kao i pokazivači te podržavaju isključivo navedene operacije (kasnije ćemo vidjeti da 
ima i takvih kontejnera). Također, nije dozvoljeno ni koristiti funkcije iz biblioteke “algorithm”, s 
obzirom da je cilj zadatka upravo da se one simuliraju i to uz posve ograničeni skup dozvoljenih operacija. 
Napišite i mali testni program u kojem ćete demonstrirati kako se upotrebljava napisana funkcija na 
vektoru realnih brojeva čiji se elementi unose sa tastature. Dijalog između programa i korisnika treba da 
izgleda poput sljedećeg: 
*/
#include <iostream>
#include <new>
#include <stdexcept>
#include <type_traits>
#include <vector>

template <typename NekiTip>
auto KreirajIzvrnutiNiz(NekiTip p1, NekiTip p2) -> typename std::remove_reference<decltype(*p1)>::type* {
    typename std::remove_reference<decltype(*p1)>::type *pok = nullptr;
    int brojac = 0;
    NekiTip pom = p1;
    while(pom != p2) {
        brojac++;
        pom++;
    }
    try {
        pok = new typename std::remove_reference<decltype(*p1)>::type [brojac];
    } catch(...) { 
        delete[] pok;
        throw std::bad_alloc(); 
    }
    int j=1;
    pom = p1;
    while(p1 != p2) {
        pok[brojac - j] = *p1;
        j++; p1++;
    }
    return pok;
}

int main ()
{
    try {
        int n;
        std::cout << "Koliko zelite elemenata: ";
        std::cin >> n;
        std::vector<double> v(n);
        std::cout << "Unesite elemente: ";
        for(double &x : v) std::cin >> x;
        double *pok = KreirajIzvrnutiNiz(v.begin(), v.end());
        std::cout << "Kreirani niz: ";
        for(int i=0; i<n; i++) std::cout << pok[i] << " ";
        delete[] pok;
    } catch(std::bad_alloc) {
        std::cout << "Nedovoljno memorije!" ;
    }
	return 0;
}
