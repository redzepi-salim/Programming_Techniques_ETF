//TP 2021/2022: LV 4, Zadatak 2

/*Napišite funkciju “IzvrniString” sa jednim parametrom tipa “string”. Funkcija treba da ispremješta 
elemente stringa tako da prvi znak postane posljednji, a posljednji prvi. Na primjer, ukoliko se u glavnom 
programu izvrši sekvenca naredbi   std::string 
s = "Ovo je neki tekst...";  
Izvrni(s);  std::cout << s;  
 ispis na ekranu treba da bude “...tsket iken ej ovO”. Funkcija treba da bude realizirana tako da vrši 
 premještanje “u mjestu”, odnosno da ne koristi nikakav pomoćni string osim stringa koji je prenesen kao 
 parametar (niti pomoćni niz, vektor ili nešto slično). Funkcija ne vraća nikakvu vrijednost nego samo 
 modificira string koji joj je poslan kao parametar. Napišite i kratki glavni program u kojoj ćete 
 demonstrirati napisanu funkciju na rečenici koja se unosi sa tastature.*/

#include <iostream>
#include <cmath>
#include <string>

void IzvrniString(std::string &s) {
    for(int i=0; i<s.size()/2; i++) {
        char temp = s.at(i);
        s.at(i) = s.at(s.size() - 1 - i);
        s.at(s.size() - 1 - i) = temp;
    }
}

int main ()
{
    std::string s;
    std::cout << "Unesi string: ";
    std::getline(std::cin, s);
    IzvrniString(s);
    std::cout << "Izvrnuti string je: " << s;
	return 0;
}
