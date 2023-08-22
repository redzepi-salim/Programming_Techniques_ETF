//TP 2020/2021: Tutorijal 2, Zadatak 4

/*Prepravite prethodni program tako što će se umjesto impedansi Z̅k  sa tastature posebno unositi aktivni 
i reaktivni otpori    i   , i što će se na kraju ispisivati posebno aktivni i reaktivni otpor paralelne 
veze elemenata. Dijalog između programa i korisnika treba da izgleda poput sljedećeg: */

#include <iostream>
#include <complex>

int main ()
{
    int n;
    std::cout << "Unesite broj elemenata: \n";
    std::cin >> n;
    std::complex<double> z(0, 0);
    for(int i=0; i<n; i++) {
        double re, im;
        std::cout << "R" << i+1 << " = ";
        std::cin >> re;
        std::cout << "X" << i+1 << " = ";
        std::cin >> im;
        z += 1./std::complex<double>(re, im);
    }
    std::cout << "\nParalelna veza ovih elemenata ima R = " << std::real(1./z) << " i X = " << std::imag(1./z) << ".";
    return 0;
}
