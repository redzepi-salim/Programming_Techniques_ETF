//TP 2021/2022: LV 8, Zadatak 1


/* Definirajte strukturu “Vrijeme” koja sadrži tri polja “sati”, “minute” i “sekunde”, i koja predstavlja 
tekuće vrijeme u toku dana, izraženu u satima, minutama i sekundama. Zatim definirajte funkciju 
“IspisiVrijeme” koja ispisuje vrijeme proslijeđeno kao parametar u funkciju u obliku hh:mm:ss (tj. sati, 
minute i sekunde se ispisuju kao dvocifreni brojevi, eventualno sa vodećim nulama), kao i funkciju 
“SaberiVrijeme” koja prima dva vremena kao parametre, i vraća kao rezultat treće vrijeme koje nastaje 
sabiranjem vremena koja su proslijeđena kao parametri (npr. sabiranjem vremena 3 h 34 min 52 sek i 4 h 
42 min 20 sek treba da se dobije vrijeme 8 h 17 min 12 sek). Ukoliko se funkciji “IspisiVrijeme” pošalje 
struktura koja sadrži neispravno vrijeme (tj. ukoliko sati nisu u opsegu od 0 do 23 a minute i sekunde od 
0 do 59 uključivo), treba baciti izuzetak tipa “domain_error” uz prateći tekst “Neispravno vrijeme”. Isto
se treba desiti i ukoliko bilo koji od dva parametra funkcije “SaberiVrijeme” predstavlja neispravno 
vrijeme. Da biste ovo lakše izveli, napišite i pomoćnu funkciju “TestirajVrijeme” koja prima vrijeme kao 
parametar. Ukoliko je vrijeme legalno ova funkcija ne radi ništa, a ukoliko nije, baca gore navedeni 
izuzetak (ovu funkciju ćete pozivati iz funkcija “IspisiVrijeme” i “SaberiVrijeme”). Konačno, napravite 
mali testni program u kojem ćete testirati napisane funkcije. Dijalog između programa i korisnika treba 
izgledati poput sljedećeg: */

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>

struct Vrijeme {
    int sati, minute, sekunde;
};

void TestirajVrijeme(Vrijeme t) {
    if((t.sati<0 || t.sati>23) || (t.minute<0 || t.minute>59) || (t.sekunde<0 || t.sekunde>59)) throw std::domain_error("Neispravno vrijeme");
}

void IspisiVrijeme(Vrijeme t) {
    try {
        TestirajVrijeme(t);
        std::cout << std::setw(2) << std::setfill('0') << t.sati << ":" << std::setw(2) << std::setfill('0') << t.minute << ":" << std::setw(2) << std::setfill('0') << t.sekunde;
    } catch(...) { throw; }
}

Vrijeme SaberiVrijeme(Vrijeme t1, Vrijeme t2) {
    int suma = 0;
    Vrijeme t;
    try {
        TestirajVrijeme(t1);
        TestirajVrijeme(t2);
        suma += t1.sati*3600 + t1.minute*60 + t1.sekunde;
        suma += t2.sati*3600 + t2.minute*60 + t2.sekunde;
        if(suma >= 86400) suma -= 86400;
        t.sati = suma / 3600;
        t.minute = (suma % 3600) / 60;
        t.sekunde = suma % 60;
        TestirajVrijeme(t);
    } catch(...) { throw; }
    return t;
}

int main ()
{
    try {
        Vrijeme vrijeme1;
        std::cout << "Unesite prvo vrijeme (h m s): " ;
        std::cin >> vrijeme1.sati >> vrijeme1.minute >> vrijeme1.sekunde;
        TestirajVrijeme(vrijeme1);
        Vrijeme vrijeme2;
        std::cout << "Unesite drugo vrijeme (h m s): " ;
        std::cin >> vrijeme2.sati >> vrijeme2.minute >> vrijeme2.sekunde;
        TestirajVrijeme(vrijeme2);
        Vrijeme zbir = SaberiVrijeme(vrijeme1, vrijeme2);
        TestirajVrijeme(zbir);
        std::cout << "Prvo vrijeme: " ;
        IspisiVrijeme(vrijeme1);
        std::cout << "\nDrugo vrijeme: " ;
        IspisiVrijeme(vrijeme2);
        std::cout << "\nZbir vremena: " ;
        IspisiVrijeme(zbir);
    } catch (std::domain_error izuzetak) {
        std::cout << izuzetak.what() << std::endl;
    }
	return 0;
}
