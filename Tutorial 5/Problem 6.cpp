/* TP 2018/2019: LV 5, Zadatak 6
	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.
			  
			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!


Napišite program koji će tražiti da se sa tastature unese broj elemenata nekog vektora, a zatim i sami 
elementi tog vektora. Nakon toga, program treba da sortira elemente tog vektora u rastući poredak po sumi 
cifara (tj. brojevi sa većom sumom cifara treba da dođu iza elemenata sa manjom sumom cifara), i da ispiše 
tako sortirani niz. Ukoliko dva broja imaju istu sumu cifara, manji broj treba da dođe prije većeg broja. 
Konačno, nakon obavljenog sortiranja, program treba da korisnika pita za neki broj   i da ispiše na kojoj 
se poziciji taj broj nalazi u nizu nakon obavljenog sortiranja, ili činjenicu da se taj broj uopće ne 
nalazi u nizu, korištenjem binarne pretrage. Dijalog između programa i korisnika trebao bi izgledati poput 
sljedećeg: 
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int Suma(int x) {
    if(x == 0) return 0;
    return std::fabs(x % 10) + Suma(x / 10);
}

bool VecaSuma(int x, int y) {
    if(Suma(x) == Suma(y)) return x < y;
    return Suma(x) < Suma(y);
} 

int main ()
{
    int n;
    std::cout << "Unesite broj elemenata: ";
    std::cin >> n;
    std::vector<int> v(n);
    std::cout << "Unesite elemente: ";
    std::for_each(v.begin(), v.end(), [](int &x) { std::cin >> x; });
    std::sort(v.begin(), v.end(), VecaSuma);
    std::cout << "Niz sortiran po sumi cifara glasi: ";
    std::for_each(v.begin(), v.end(), [](int x) { std::cout << x << " "; });
    std::cout << "\nUnesite broj koji trazite: ";
    std::cin >> n;
    std::vector<int>::iterator it = std::find(v.begin(), v.end(), n);
    if(it != v.end()) std::cout << "Trazeni broj nalazi se na poziciji " << it - v.begin();
    else std::cout << "Trazeni broj ne nalazi se u nizu!";
	return 0;
}
