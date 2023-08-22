//TP 2020/2021: Tutorijal 2, Zadatak 3

/*Kompleksni brojevi svoju najveću primjenu nalaze upravo u elektrotehnici (i u kvantnoj fizici). 
Recimo, u teoriji električnih kola uvodi se pojam impedanse, koja je kompleksan broj Z̅ definiran kao 
Z̅ = R + X 𝑖, gdje je R tzv. aktivni otpor, a X tzv. reaktivni otpor (ili reaktansa), koji može biti i 
negativan. Ukoliko imamo paralelni spoj 𝑛 elemenata čije su impedanse Z̅ , Z̅ , …, Z̅ , ukupna impedansa 
paralelne veze Z̅ računa se kao Z̅ = 1/(1/ Z̅  + 1/Z̅  + … + 1/Z̅ ). Drugim riječima, situacija je slična 
paralelnom spajanju otpornika, osim što se ovdje radi sa kompleksnim impedansama. Napišite program u 
kojem se korisnika traži da se unese broj elemenata 𝑛, a zatim 𝑛 impedansi Z̅  za sve 𝑘 od 1 do 𝑛. 
Impedanse se unose kao kompleksni brojevi, tačnije kao parovi realnih i imaginarnih dijelova unutar 
zagrada, razdvojeni zarezom. Nakon toga, treba da izračuna i ispiše impedansu paralelne veze svih 𝑛 
elemenata, ponovo kao kompleksan broj. Dijalog između programa i korisnika treba da izgleda poput 
sljedećeg: */

#include <iostream>
#include <complex>

int main ()
{
    int n;
    std::cout << "Unesite broj elemenata: \n";
    std::cin >> n;
    std::complex<double> z(0, 0);
    for(int i=0; i<n; i++) {
        std::complex<double> pom;
        std::cout << "Z_" << i+1 << " = ";
        std::cin >> pom;
        z += 1./pom;
    }
    std::cout << "\nParalelna veza ovih elemenata ima impedansu Z_ = " << 1./z << ".";
    return 0;
}
