//TP 2021/2022: LV 3, Zadatak 6

/*U linearnoj algebri, pod Kroneckerovim ili tenzorskim proizvodom  a ⊗ b  vektora a i b čiji su elementi 
ai  , 𝑖 = 1, 2, …, 𝑚 odnosno  bi , 𝑖 = 1, 2, …, 𝑛, podrazumijevamo matricu C formata 𝑚 × 𝑛 čiji se elementi 
računaju po formuli ci,j  = ai*bi , 𝑖 = 1, 2, …, 𝑚, 𝑗 = 1, 2, …, 𝑛  (koristeći kompaktniju notaciju iz 
linearne algebre, ukoliko su   i   predstavljeni kao vektor kolone, vrijedi a ⊗ b = ab^T  ). Napravite 
funkciju “KroneckerovProizvod” koja prima kao parametre dva vektora cijelih brojeva (tipa “int”), a vraća 
kao rezultat matricu organiziranu kao vektor vektôrā koja predstavlja Kroneckerov proizvod vektora koji 
su zadani kao parametri (pri tome, funkcija se treba konzistentno ponašati čak i ukoliko je neki od ulaznih 
vektora prazan). Napisanu funkciju iskoristite u glavnom programu u kojem će se sa tastature unijeti 
elementi dva vektora, a zatim kreirati i prikazati na ekranu njihov Kroneckerov proizvod. Pri tome, 
ispis na ekranu treba biti takav da se za svaki element matrice zauzme  prostor koji je za 1 veći nego 
što je širina najšireg broja u matrici, uz poravnavanje udesno (pod širinom broja podrazumijeva se broj 
njegovih cifara, eventualno uvećan za 1 ako je broj negativan, zbog prostora koji zauzima znak “−”). Za 
tu svrhu, u programu trebate napisati i još jednu funkciju nazvanu “NajvecaSirina” koja kao parametar 
prima matricu organiziranu kao vektor vektôrā cijelih brojeva, a vraća širinu najšireg broja u matrici. 
Funkcija treba ispravno da radi i ukoliko joj se ponudi grbava matrica, pa čak i prazna matrica (u 
posljednjem slučaju, funkcija treba vratiti 0 kao rezultat). Dijalog između korisnika i programa treba 
izgledati poput sljedećeg: */

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

std::vector<std::vector<int>> KroneckerovProizvod(std::vector<int> a, std::vector<int> b) {
    std::vector<std::vector<int>> v(a.size(), std::vector<int>(b.size()));
    for(int i=0; i<a.size(); i++) {
        for(int j=0; j<b.size(); j++) {
            v.at(i).at(j) = a.at(i) * b.at(j);
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
    int m;
    std::cout << "Unesite broj elemenata prvog vektora: ";
    std::cin >> m;
    std::cout << "Unesite elemente prvog vektora: ";
    std::vector<int> a(m);
    for(int i=0; i<a.size(); i++) {
        std::cin >> a.at(i);
    }
    int n;
    std::cout << "Unesite broj elemenata drugog vektora: ";
    std::cin >> n;
    std::cout << "Unesite elemente drugog vektora: ";
    std::vector<int> b(n);
    for(int i=0; i<b.size(); i++) {
        std::cin >> b.at(i);
    }
    std::vector<std::vector<int>> matrica = KroneckerovProizvod(a, b);
    std::cout << std::endl;
    for (int i=0; i<matrica.size(); i++) {
        for(int j=0; j<matrica.at(0).size(); j++) {
            std::cout << std::setw(NajvecaSirina(matrica) + 1) << std::right << matrica.at(i).at(j) ;
        }
        std::cout << std::endl;
    }
	return 0;
}
