
/*Napišite funkciju “IteriranaFunkcija” koja kao parametar prima neku funkciju 𝑓 koja prima cijeli broj i 
vraća cijeli broj kao rezultat, te prirodan broj 𝑛. Ova funkcija kao rezultat treba vratiti novu funkciju 
(nazovimo je 𝑔) takvu da vrijedi da je 𝑔(𝑥) = 𝑓^(n)(𝑥) = 𝑓(𝑓(𝑓(... 𝑓(𝑥)...))), gdje se funkcija 𝑓 primjenjuje 
na argument 𝑛 puta uzastopno. Recimo, ukoliko je “f” neka funkcija koja prima i vraća cjelobrojnu vrijednost, 
tada isječak programa   
auto g = IteriranaFunkcija(f, 10);  
std::cout << g(5);   
odnosno   
std::cout << IteriranaFunkcija(f, 10)(5);   
treba da proizvede isti rezultat kao i naredba   
std::cout << f(f(f(f(f(f(f(f(f(f(5))))))))));   
Ukoliko je 𝑛 negativan ili 0, funkcija vraćena kao rezultat (koju smo nazvali 𝑔) treba da bude identička 
funkcija, tj. za nju treba da vrijedi 𝑔(𝑥) = 𝑥. Napišite i testni program u kojem ćete testirati ovu 
funkciju. */

#include <iostream>
#include <functional>

std::function<int(int)> IteriranaFunkcija(std::function<int(int)> f, int n) {
    if(n <= 0) return [](double x) { return x; };
    std::function<int(int)> g = [f](int x) { return f(f(x)); };
    if(n == 1) return [f](int x) { return f(x); };
    for(int i=2; i<n; i++) {
        g = [f, g](int x) { return g(f(x)); };
    } 
    return [g](int x) { return g(x); };
}

int main ()
{
    auto g = IteriranaFunkcija([](int x){ return x + 3; }, 5);
	std::cout << g(7) << std::endl;
	return 0;
}
