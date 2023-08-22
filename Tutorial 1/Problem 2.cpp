//TP 2016/2017: Tutorijal 1, Zadatak 2

/*Napišite program koji traži da se sa tastature unesu tri realna broja 𝑎, 𝑏 i 𝑐, i koji 
ispisuje da li ta tri broja mogu biti stranice nekog trougla. Podsjetimo se da za stranice 
trougla mora vrijediti uvjet da su sve pozitivne i da je zbir dužina ma koje dvije stranice 
veći od dužine treće stranice. Ukoliko uneseni brojevi mogu predstavljati dužine stranica trougla, 
treba izračunati njegov obim, površinu i najmanji ugao, a zatim ispisati izračunate vrijednosti 
obima, površine i najmanjeg ugla, pri čemu ugao trea ispisati u stepenima, minutama i sekundama. 
Za računanje površine trougla koristite poznatu Heronovu formulu prema kojoj je P = √s(s-𝑎)(s-𝑏)(s-𝑐) 
gdje je s = (𝑎 + 𝑏 + 𝑐)/2, a za računanje ugla koristite kosinusnu teoremu prema kojoj je 𝑐  = 𝑎 + 𝑏 -   
2 𝑎 𝑏 cos γ (i analogno tome za preostale kombinacije stranica i uglova). Računajte da 1 radijan ima 
180/π stepeni, dok vrijednost π možete računati po formuli π = 4 ∙ arctg 1 (predmetni nastavnik ne 
želi da vidi da neko misli da je π = 3.14, to mu pokvari dan). Ukoliko uneseni brojevi ne mogu 
predstavljati dužine stranica trougla, treba ispisati odgovarajući komentar. Dijalozi koje formira 
program trebaju izgledati poput sljedećih (zanemarite eventualne probleme sa padežima i ostalom 
gramatikom): */

#include <iostream>
#include <cmath>
#include <math.h>
int main ()
{
    double a, b, c;
    std::cout << "Unesite tri broja: ";
    std::cin >> a >> b >> c;
    if(a<0 || b<0 || c<0 || a+b<=c || a+c<=b || b+c<=a) {
        std::cout << "Ne postoji trougao cije su duzine stranica " << a << ", " << b << " i " << c << "!" << std::endl; 
    }
    else {
        std::cout << "Obim trougla sa duzinama stranica " << a << ", " << b << " i " << c << " iznosi " << a+b+c << "." << std::endl;
        double s = (a + b + c) / 2;
        std::cout << "Njegova povrsina iznosi " << std::sqrt(s * (s-a) * (s-b) * (s-c)) << "." << std::endl;
        double alfa = std::acos((a*a + b*b - c*c) / (2*a*b)) * (180 / (4*std::atan(1)));
        double beta = std::acos((b*b + c*c - a*a) / (2*b*c)) * (180 / (4*std::atan(1)));
        double gama = std::acos((a*a + c*c - b*b) / (2*a*c)) * (180 / (4*std::atan(1)));
        if(alfa < beta && alfa < gama) {
            int stepeni = int(alfa);
            int minute = int((alfa - int(alfa)) * 60);
            int sekunde = ((alfa - int(alfa)) * 60 - minute) * 60;
            std::cout << "Njegov najmanji ugao ima " << stepeni << " stepeni, " << minute << " minuta i " << sekunde << " sekundi." << std::endl;
        }
        else if (beta < alfa && beta < gama) {
            int stepeni = int(beta);
            int minute = int((beta - int(beta)) * 60);
            int sekunde = ((beta - int(beta)) * 60 - minute) * 60;
            std::cout << "Njegov najmanji ugao ima " << stepeni << " stepeni, " << minute << " minuta i " << sekunde << " sekundi." << std::endl;
        }
        else {
            int stepeni = int(gama);
            int minute = int((gama - int(gama)) * 60);
            int sekunde = ((gama - int(gama)) * 60 - minute) * 60;
            std::cout << "Njegov najmanji ugao ima " << stepeni << " stepeni, " << minute << " minuta i " << sekunde << " sekundi." << std::endl;
        }
    }
	return 0;
}
