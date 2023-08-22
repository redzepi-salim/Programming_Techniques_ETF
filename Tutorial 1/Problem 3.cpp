//TP 2016/2017: LV 1, Zadatak 3

/*Napišite program koji traži da se sa tastature unesu dva prirodna broja 𝑎 i 𝑏, ne veća od 9999 
i pri čemu je 𝑎 < 𝑏, a koji zatim za sve prirodne brojeve u opsegu od 𝑎 do 𝑏 uključivo ispisuje 
tablicu njihovih kvadrata, kvadratnih korijena i prirodnih logaritama. Tačan izgled tablice vidljiv 
je iz dijaloga koji će biti prikazan. Uglavnom, kolona za prikaz brojeva široka je 9 polja. Brojevi 
se ispisuju poravnati ulijevo, pri čemu je prvo polje uvijek razmak. Kolone za prikaz kvadrata i korijena 
široke su 10 polja, dok je kolona za prikaz logaritama široka 11 polja. Kvadrati, korijeni i logaritmi se 
ispisuju poravnati udesno, pri čemu je posljednje polje uvijek razmak. Pored toga, korijeni se ispisuju 
fiksno na tri decimale, a logaritmi fiksno na pet decimala. Slijedi primjer kako treba izgledati dijalog 
između korisnika i programa: */

#include <iomanip>
#include <iostream>
#include <cmath>
int main ()
{
    int a, b;
    std::cout << "Unesite pocetnu i krajnju vrijednost: ";
    std::cin >> a >> b;
    std::cout << std::endl << "+" << std::setfill('-') << std::setw(10) << "+" << std::setw(11) << "+" << std::setw(11) << "+" << std::setw(12) << "+" << std::endl;
    std::cout << "| Brojevi | Kvadrati | Korijeni | Logaritmi |" << std::endl;
    std::cout << "+" << std::setfill('-') << std::setw(10) << "+" << std::setw(11) << "+" << std::setw(11) << "+" << std::setw(12) << "+" << std::setfill(' ') << std::endl;
    for(int i=a; i<=b; i++) {
        std::cout << "| " << std::left << std::setw(8) << i << "|" << std::right << std::setw(9) << i*i << " |" << std::setw(9) << std::fixed << std::setprecision(3) << std::sqrt(i) << " |" << std::setw(10) << std::fixed << std::setprecision(5) << std::log(i) << " |" << std::endl;
    }
    std::cout << "+" << std::setfill('-') << std::setw(10) << "+" << std::setw(11) << "+" << std::setw(11) << "+" << std::setw(12) << "+" << std::endl;
	return 0;
}
