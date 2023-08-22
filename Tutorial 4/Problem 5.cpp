//TP 2021/2022: LV 4, Zadatak 5

/*Napišite generičku funkciju “Presjek” koja prima dva parametra “v1” i “v2”. Ovi parametri su vektori 
proizvoljnog ali istog tipa elemenata. Funkcija treba da kao rezultat vrati novi vektor koji se sastoji 
od elemenata koji se javljaju i u vektoru “v1” i u vektoru “v2” (drugim riječima, treba formirati presjek 
skupova čiji su elementi pohranjeni u vektorima “v1” i “v2”). Pored toga, u vektoru koji je vraćen kao 
rezultat iz funkcije svi elementi treba da budu različiti (odnosno, elemente koji se ponavljaju ne treba 
prepisivati više puta). Elementi pohranjeni u rezultatu treba da budu u istom redoslijedu kao što je 
redoslijed njihovog prvog pojavljivanja u vektoru “v1”. Na primjer, ukoliko vektor “v1” sadrži redom 
brojeve 3, 7, 2, 6, 3, 4, 8, 1, 6 i 5, a vektor “v2” redom brojeve 4, 9, 5, 9, 7, 0, 4 i 6, rezultirajući 
vektor treba redom sadržavati brojeve 7, 6, 4 i 5. Napisanu funkciju testirajte u testnom programu prvo 
na dva vektora realnih brojeva, a zatim na dva vektora čiji su elementi stringovi (elementi se unose sa 
tastature). Dijalog između programa i korisnika teba izgledati poput sljedećeg:*/

#include <iostream>
#include <cmath>
#include <vector>

template <typename NekiTip>
std::vector<NekiTip> Presjek(std::vector<NekiTip> v1, std::vector<NekiTip> v2) {
    std::vector<NekiTip> v;
    for(int i=0; i<v1.size(); i++) {
        for(int j=0; j<v2.size(); j++) {
            if(v1.at(i) == v2.at(j)) {
                bool ima_u_v = false;
                for(int k=0; k<v.size(); k++) if(v.at(k) == v1.at(i)) {
                    ima_u_v = true;
                    break;
                }
                if(!ima_u_v) v.push_back(v1.at(i));
            }
        }
    }
    return v;
}

int main ()
{
    std::cout << "Test za realne brojeve..." << std::endl;
    int n, m;
    std::cout << "Unesite broj elemenata prvog vektora: ";
    std::cin >> n;
    std::vector<double> v1(n);
    std::cout << "Unesite elemente prvog vektora: ";
    for(int i=0; i<n; i++) std::cin >> v1.at(i);
    std::cout << "Unesite broj elemenata drugog vektora: ";
    std::cin >> m;
    std::vector<double> v2(m);
    std::cout << "Unesite elemente drugog vektora: ";
    for(int i=0; i<m; i++) std::cin >> v2.at(i);
    std::cout << "Zajednicki elementi su: ";
    std::vector<double> v = Presjek(v1, v2);
    for(int i=0; i<v.size(); i++) std::cout << v.at(i) << " ";

    std::cout << "Test za stringove..." << std::endl;
    std::cout << "Unesite broj elemenata prvog vektora: ";
    std::cin >> n;
    std::vector<std::string> s1(n);
    std::cin.ignore(10000, '\n');
    std::cout << "Unesite elemente prvog vektora (ENTER nakon svakog unosa): " << std::endl;
    for(int i=0; i<n; i++) std::getline(std::cin, s1.at(i));
    std::cout << "Unesite broj elemenata drugog vektora: ";
    std::cin >> m;
    std::vector<std::string> s2(m);
    std::cin.ignore(10000, '\n');
    std::cout << "Unesite elemente drugog vektora (ENTER nakon svakog unosa): " << std::endl;
    for(int i=0; i<m; i++) std::getline(std::cin, s2.at(i));
    std::vector<std::string> s = Presjek(s1, s2);
    std::cout << "Zajednicki elementi su: " << std::endl;
    for(int i=0; i<s.size(); i++) std::cout << s.at(i) << std::endl;
	return 0;
}
