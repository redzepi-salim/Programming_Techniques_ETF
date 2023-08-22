/*  TP 16/17 (LV 7, Zadatak 8)
	Vrsit ce se provjera na prepisivanje tutorijala.



Napišite funkciju “IzvrniBezRazmaka” koja kao parametar prima neki string, a kao rezultat vraća taj 
string izvrnut naopačke, sa izbačenim razmacima (tj. ako je ulaz string “Evo pada kiša”, izlazni rezultat 
treba da bude string “ašikadapovE”). Pri tome, funkcija treba da ima samo tri naredbe, od kojih je prva 
deklariranje pomoćnog stringa, a treća naredba “return”, tako da sva “logika” funkcije treba biti izvedena 
u jednoj jedinoj (drugoj) naredbi. Uputa: poslužite se funkcijom “remove_copy”, zatim obrnutim iteratorima 
te umetačima (inserterima). Napišite i kratki testni program u kojem ćete testirati napisanu funkciju. 
*/
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>

std::string IzvrniBezRazmaka(std::string s) {
    std::string pomocni;
    std::remove_copy(s.rbegin(), s.rend(), std::back_inserter(pomocni), ' ');
    return pomocni;
}

int main ()
{
    std::string s;
	std::cout << "Unesite string: " ;
	std::getline(std::cin, s);
	std::string s1 = IzvrniBezRazmaka(s);
	std::cout << s1 << std::endl;
	return 0;
}
