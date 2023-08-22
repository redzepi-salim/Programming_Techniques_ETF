/*  TP 2018/2019: LV 5, Zadatak 1	
	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.
			  
			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!


Napišite program koji od korisnika traži da sa tastature unese rečenicu, ne dužu od 1000 znakova, a koji 
će zatim ispisati unesenu rečenicu bez prve riječi te rečenice, pri čemu ispis započinje od prvog znaka 
druge riječi (u slučaju da rečenica ima samo jednu riječ, ili da je “prazna” bez riječi, ne ispisuje se 
ništa). Pod riječi se ovdje smatra svaki niz znakova koji nisu razmaci a koji je s obje strane omeđen 
razmacima, osim na početku ili kraju kada ne mora biti razmaka lijevo odnodno desno od riječi. Vodite 
računa da može biti više razmaka između dvije riječi, kao i razmaka na početku ili kraju rečenice.  
Unesena rečenica se smješta u klasični niz znakova (dakle, ne u promjenljivu tipa “string”). Za realizaciju 
zadatka koristiti isključivo pokazivačku aritmetiku. Nije dozvoljena upotreba funkcija iz biblioteka 
“cstring” niti “string”, kao ni upotreba indeksiranja (što uključuje i njegovu trivijalnu simulaciju koja 
podrazumijeva pisanje “*(a + n)” umjesto “a[n]”). Dijalog između korisnika i programa treba izgledati ovako: 
*/
#include <iostream>
int main ()
{
    char niz[1000];
    std::cout << "Unesite recenicu: ";
    std::cin.getline(niz, sizeof niz);
    char *s = niz, *pocetak = niz;
    bool razmak = true;
    int br_rijeci = 0;
    while(*s != '\0') {
        if(*s == ' ') razmak = true;
        else if(razmak) {
            br_rijeci++;
            razmak = false;
            if (br_rijeci == 2) {
                while(*pocetak++ = *s++);
                break;
            }
        }
        s++;
    }
    if(br_rijeci > 1) std::cout << "Recenica bez prve rijeci glasi: " << niz << std::endl;
    else std::cout << "Recenica bez prve rijeci glasi: " << std::endl;
	return 0;
}
