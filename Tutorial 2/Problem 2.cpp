//TP 2020/2021: Tutorijal 2, Zadatak 2

/*Za slijed brojeva  a1, a2, …, an   kažemo da ima period 𝑝 ukoliko je 1 ≤ 𝑝 < 𝑛 i ukoliko vrijedi da je
ai = ai+p  za sve vrijednosti 𝑖 za koje ova jednakost ima smisla (tj. za koju su oba indeksa 𝑖 i 𝑖 + 𝑝 legalni).
 Na primjer, slijed brojeva 1, 3, 1, 4, 2, 1, 3, 1, 4, 2, 1, 3 ima period 5, jer je    =      za sve 
 vrijednosti 𝑖 takve da su oba indeksa 𝑖 i 𝑖 + 5 unutar dozvoljenog opsega (tj. za 𝑖 od 1 do 7 uključivo). 
 Isti slijed također ima i period 10. Dalje, za slijed brojeva kažemo da je periodičan ukoliko postoji 
 makar jedan broj 𝑝 koji je period tog slijeda, pri čemu najmanji takav broj 𝑝 nazivamo osnovni period 
 slijeda. Ukoliko takav broj 𝑝 ne postoji, slijed nije periodičan. Na primjer, gore navedeni slijed brojeva 
 je periodičan s osnovnim periodom 5, dok slijed brojeva 4, 5, 1, 7, 1, 5 nije periodičan. Vaš zadatak je 
 da napišete dvije funkcije “TestPerioda” i “OdrediOsnovniPeriod”. Prva funkcija prima dva parametra, pri 
 čemu je prvi parametar vektor realnih brojeva, dok je drugi parametar cijeli broj 𝑝. Funkcija treba da 
 vrati kao rezultat logičku vrijednost “tačno” ili “netačno” ovisno od toga da li slijed brojeva pohranjen 
 u vektoru periodičan sa periodom 𝑝 ili ne. Druga funkcija prima samo jedan parametar koji je vektor 
 realnih brojeva, a ona kao rezultat vraća osnovni period slijeda pohranjenog u vektoru ukoliko je slijed 
 periodičan, ili nulu ukoliko slijed nije periodičan. To ćete najlakše izvesti tako što ćete iz druge 
 funkcije pozivati prvu funkciju kao pomoćnu, a kako to tačno izvesti, ostavlja Vam se za razmišljanje.
 Napisane funkcije iskoristite u glavnom programu u kojem ćete unositi elemente sa tastature u neki vektor 
 sve dok se sa tastature ne unese nula, koja označava kraj unosa (tu nulu ne treba smjestiti u vektor). 
 Nakon završetka unosa, program poziva funkciju “OdrediOsnovniPeriod” sa ciljem da utvrdi da li se elementi 
 periodično ponavljaju ili ne, nakon čega ispisuje odgovarajuči komentar na ekranu (informaciju o dužini 
 perioda, ili da elementi ne čine periodičan slijed). Napomenimo da nije unaprijed poznato koliko će 
 korisnik unijeti elemenata prije nego što unese nulu kao oznaku završetka unosa. Dijalozi između korisnika 
 i programa trebali bi izgledati poput sljedećih (ovisno da li je slijed periodičan ili ne): */

#include <iostream>
#include <vector>
#include <cmath>

bool TestPerioda (std::vector<double> v, int p)
{
    if(p<1 || p>=v.size()) return false;
    if(v.size()==1) return false;
    else {
        const double E=0.0001;
        for(int i=0; i<v.size(); i++) {
            if(p<(v.size()-i) && fabs(v.at(i)-v.at(i+p))>E) return false;
        }
        return true;
    }
}

int OdrediOsnovniPeriod (std::vector<double> v)
{
    for(int i=1; i<v.size(); i++) {
        if(TestPerioda(v, i)) return i;
    }
    return 0;
}

int main ()
{
    double n;
    std::vector<double> vektor;
    std::cout << "Unesite slijed brojeva (0 za kraj): " ;
    do {
        std::cin >> n;
        if(fabs(n) < 0.0001) break;
        vektor.push_back(n);
    } while (fabs(n) > 0.0001);
    if(!OdrediOsnovniPeriod(vektor)) std::cout << "Slijed nije periodican!" << std::endl;
    else std::cout << "Slijed je periodican sa osnovnim periodom " << OdrediOsnovniPeriod(vektor) << "." << std::endl;
    return 0;
}
