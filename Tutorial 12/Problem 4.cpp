/*  TP 16/17 (Tutorijal 12, Zadatak 4)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)



Prepravite operator “<<” u klasi “Kompleksni” sa Predavanja 12_a tako da se ispis kompleksnih brojeva vrši 
u algebarskom formatu, tj. u obliku poput “2+3i” umjesto “(2,3)”. Obratite pažnju na razne specijalne 
slučajeve koji mogu nastupiti, tako da recimo treba ispisivati “2-3i”, “3+i”, “1-i”, “2i”, “-5i”, “i”, “3” 
itd. a ne “2+-3i”, “3+1i”, “1-1i” (ili, još gore, “1+-1i”), “0+2i”, “0-5i” (ili, još gore, “0+-5i”), “0+1i”
(ili “0+i”), “3+0i”, itd. Kao dodatni izazov (ovo se neće testirati na vježbi), probajte prepraviti operator 
“>>” da omogući unos kompleksnih brojeva sa tastature u istom formatu kao prilikom ispisa. Treba da se 
prihvataju sve smislene varijante unosa koje se mogu protumačiti kao kompleksan broj. Uspijete li ovo 
uraditi, obavezno se javite predmetnom nastavniku. 
*/
#include <iostream>
#include <complex>

typedef std::complex<int> Kompleksni;

std::ostream &operator <<(std::ostream &tok, Kompleksni x){
	if(x.real() != 0) tok << x.real();
	if(x.imag() == 1 && x.real() != 0) tok << "+" << "i";
	else if(x.imag() == 1 && x.real() == 0) tok << "i";
	else if(x.imag() == -1) tok << "-i";
	else if(x.imag() != 0) {
		if(x.imag() > 0 && x.real() != 0) tok << "+" << x.imag() << "i";
		else tok << x.imag() << "i";
	}
	if(x.real() == 0 && x.imag() == 0) tok << 0;
	return tok;
}
int main ()
{
	std::cout << Kompleksni (0, -1) << std::endl;
	return 0;
}
