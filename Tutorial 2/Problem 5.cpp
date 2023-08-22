//TP 2020/2021: Tutorijal 2, Zadatak 5

/*Prepravite prethodni program tako što će se sve impedanse Z̅  umjesto preko aktivnog otpora i reaktivnog 
otpora zadavati preko tzv. prividnog otpora Z  i faznog pomaka  fi. Program na kraju treba prikazati 
prividni otpor i fazni pomak za čitavu paralelnu vezu. Fazni pomak treba zadavati i ispisivati u stepenima. 
Dijalog između programa i korisnika treba da izgleda poput sljedećeg: */

#include <iostream>
#include <complex>
#include <cmath>

int main ()
{
    int n;
    std::cout << "Unesite broj elemenata: \n";
    std::cin >> n;
    std::complex<double> z(0, 0);
    for(int i=0; i<n; i++) {
        double Z, fi;
        std::cout << "Z" << i+1 << " = ";
        std::cin >> Z;
        std::cout << "fi" << i+1 << " = ";
        std::cin >> fi;
        z += 1./std::polar(Z, fi*(4*std::atan(1))/180);
    }
    std::cout << "\nParalelna veza ovih elemenata ima Z = " << std::fabs(1./z) << " i fi = " << std::arg(1./z)*(180/(4*std::atan(1))) << ".";
    return 0;
}
