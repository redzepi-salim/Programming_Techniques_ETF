/*  TP 16/17 (Tutorijal 12, Zadatak 3)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)



Neka je dat pobrojani tip   
enum Dani {Ponedjeljak, Utorak, Srijeda, Cetvrtak, Petak, Subota, Nedjelja};   
Poznato je da se, u odsustvu drugačijih uputa, promjenljive tipa “Dani” automatski konvertiraju u 
cjelobrojne vrijednosti. Recimo, ukoliko promjenljiva “d” tipa “Dani” ima vrijednost “Srijeda”, naredba 
poput “std::cout << d” će umjesto teksta “Srijeda” ispisati broj 2. Srećom, ovakvo ponašanje se može 
izmijeniti korištenjem preklapanja operatora. Napišite operatorsku funkciju za operator “<<” koji će 
omogućiti da se prilikom ispisa konstanti, promjenljivih i izraza tipa “Dani” umjesto brojčane vrijednosti 
dobijene konverzijom ispisuje tekst koji odgovara njihovom značenju. Testirajte napisanu funkciju u 
testnom programu koji sadrži petlju   
for(Dani d = Ponedjeljak; d <= Petak; d++) std::cout << d << std::endl;   
Takva petlja treba da zaista ispiše imena dana “Ponedjeljak”, “Utorak”, “Srijeda”, “Četvrtak” i “Petak”, a 
ne brojeve od 0 do 4. Za tu svrhu ćete također morati definirati i operator “++” koji podrazumijevano nije 
definiran za promjenljive pobrojanog tipa (uradite to na način kako je urađeno u Predavanju 12_a). 
Kada to uradite, probajte napraviti sličnu petlju koja bi trebala da ispiše sve dane u sedmici redom od 
ponedjeljka do nedjelje. U čemu je problem? Zbog čega petlja ne radi kako je očekivano? Šta se može učiniti 
po tom pitanju? Riješite ovaj problem, odnosno napravite petlju koja će korektno ispisati sve dane u sedmici. 
*/
#include <iostream>
#include <vector>
#include <string>
enum Dani {Ponedjeljak, Utorak, Srijeda, Cetvrtak, Petak, Subota, Nedjelja };
std::ostream &operator <<(std::ostream &tok, Dani d){
	std::vector<std::string> v{"Ponedjeljak", "Utorak", "Srijeda", "Cetvrtak", "Petak", "Subota", "Nedjelja"};
	tok << v.at(d);
	return tok;
}
Dani &operator ++(Dani &d){
	return d = Dani((int(d) + 1) % 7);
}
Dani operator ++(Dani &d, int){
	Dani temp(d);
	++d;
	return temp;
}
int main ()
{
	for(Dani d=Ponedjeljak; d<=Nedjelja; d++){
		std::cout << d << std::endl;
		if(d == Nedjelja) break;
	}
	return 0;
}
