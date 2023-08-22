/* TP 2018/2019: LV 5, Zadatak 7	
	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.
			  
			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!


Napišite generičku funkciju “SumaBloka”, koja slično kao funkcije iz biblioteke “algorithm” prima kao 
parametre dva pokazivača ili iteratora koji omeđuju neki blok (prvi pokazuje na početak bloka, a drugi 
tačno iza kraja bloka). Funkcija treba da kao rezultat vrati sumu svih elemenata u bloku, uz pretpostavku 
da su elementi bloka takvi da se mogu sabirati. U slučaju da je blok prazan, treba baciti izuzetak tipa 
“range_error” uz prateći tekst “Blok je prazan”. Testirajte funkciju na jednom deku realnih brojeva čiji 
se elementi unose sa tastature.    Napomena 1: Funkciju koja radi tačno ovako kako je opisano nemoguće 
je napisati bez C++11 inovacija. Slična funkcija, pod imenom “accumulate”, postoji u biblioteci “numeric”, 
ali ona zahtijeva i jedan dodatni parametar koji služi da se prevaziđu problemi koji se nisu mogli 
riješiti do uvođenja standarda C++11.   Napomena 2: Vjerovatno će Vam trebati operator “decltype”. Međutim, 
vodite računa da ovaj operator vraća tip reference ukoliko mu je parametar l-vrijednost, tako da će 
konstrukcija poput “decltype(*p)” vratiti tip reference, jer je izraz “*p”, koji je zadan kao parametar 
operatora “decltype”, l-vrijednost. Tip reference u ovom slučaju neće biti pogodan, tako da je potrebno 
nekako prevazići ovaj problem. Univerzalan (ali nažalost prilično rogobatan) način za rješavanje ovog 
problema je upotreba metafunkcije “remove_reference”. Međutim, u ovom konkretnom primjeru moguće je i 
znatno jednostavnije rješenje. Naime, mada će “decltype(*p)” vratiti tip reference, “decltype(*p + *p)” 
neće vratiti tip reference, jer izraz “*p + *p” nije l-vrijednost. Pored toga, izraz “*p + *p” je 
garantirano legalan, jer smo pošli od pretpostavke da su elementi bloka takvi da se mogu sabirati (što ne 
bi moralo biti bez ove pretpostavke).  
*/
#include <iostream>
#include <stdexcept>
#include <deque>

template <typename NekiTip>
auto SumaBloka(NekiTip p1, NekiTip p2) {
    if(p1 == p2) throw std::range_error("Blok je prazan");
    auto suma = *p1; p1++;
    while(p1 != p2) {
        suma += *p1;
        p1++;
    }
    return suma;
}
int main ()
{
    int n;
    std::cout << "Unesite broj elemenata deka: ";
    std::cin >> n;
    std::deque<double> d(n);
    std::cout << "Unesite elemente deka: ";
    for(double &x : d) std::cin >> x;
    try {
        std::cout << SumaBloka(d.begin(), d.end());
    } catch(std::range_error izuzetak) {
        std::cout << izuzetak.what();
    }
	return 0;
}
