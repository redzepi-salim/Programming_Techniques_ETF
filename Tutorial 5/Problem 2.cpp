/*  TP 2018/2019: LV 5, Zadatak 2
	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.
			  
			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!


Napišite generičku funkciju “RazmijeniBlokove” koja prihvata iste parametre i obavlja isti zadatak kao 
funkcija “swap ranges” iz biblioteke “algorithm”. Funkcija treba koristiti potpunu dedukciju (tako da će 
da radi i sa pokazivačima i sa iteratorima) i treba je realizirati isključivo korištenjem pokazivačke 
aritmetike, bez korištenja indeksiranja i njegove trivijalne simulacije (tj. pisanja “*(p + i)” umjesto 
“p[i]”). Napišite i kratki testni program u kojem ćete testirati napisanu funkciju na jednom fiksnom paru 
nizova cijelih brojeva i na jednom fiksnom paru stringova (iste dužine). 
*/
#include <iostream>
#include <string>
#include <vector>

template <typename NekiTip1, typename NekiTip2, typename NekiTip3>
NekiTip3 RazmijeniBlokove(NekiTip1 p1, NekiTip2 p2, NekiTip3 p3) {
    while(p1 != p2){
        auto temp = *p1;
        *p1 = *p3;
        *p3 = temp;
        p1++;
        p3++;
    }
    return p3;
}

int main ()
{
    int niz1[] = {1, 2, 3, 4, 5}, niz2[] = {6, 7, 8, 9, 10};
    RazmijeniBlokove(std::begin(niz1), std::end(niz1), std::begin(niz2));
    std::cout << "Prvi niz: ";
    for(int x : niz1) std::cout << x << " ";
    std::cout << std::endl << "Drugi niz: ";
    for(int x : niz2) std::cout << x << " ";
    std::cout << std::endl;
    std::vector<std::string> v1{"Ja", "volim", "jagode"}, v2{"Ja", "volim", "jabuke"};
    RazmijeniBlokove(v1.begin(), v1.end(), v2.begin());
    for(std::string x : v1) std::cout << x << " ";
    std::cout << std::endl;
    for(std::string x : v2) std::cout << x << " ";
	return 0;
}
