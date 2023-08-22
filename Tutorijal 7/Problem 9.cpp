/*  TP 16/17 (LV 7, Zadatak 9)
	Vrsit ce se provjera na prepisivanje tutorijala.



Napišite funkcije “plus2” i “plus3” koje implementiraju respektivno funkcije 𝑓 i 𝑔 definirane na sljedeći 
način. 𝑓 je funkcija takva da izraz 𝑓(𝑥)(𝑦) treba da kao rezultat da vrijednost 𝑥 + 𝑦. 𝑔 je funkcija takva 
da izraz 𝑔(𝑥)(𝑦)(𝑧) treba da kao rezultat da vrijednost 𝑥 + 𝑦 + 𝑧. Ovdje su 𝑥, 𝑦 i 𝑧 realni brojevi. 
Napišite i kratki testni program u kojem ćete testirati napisane funkcije. 
*/
#include <iostream>
#include <functional>

std::function<double(double)> plus2(double x) {
    return [x](double y){ return x + y; };
}

std::function<std::function<double(double)>(double)> plus3(double x) {
    return [x](double y) { return [x, y](double z){return x + y + z; }; };
}

int main ()
{
	double x, y, z;
	std::cout << "Unesite realne brojeve: " ;
	std::cin >> x >> y >> z;
	std::cout << "f = " << plus2(x)(y) << ", g = " << plus3(x)(y)(z) << std::endl;
	return 0;
}
