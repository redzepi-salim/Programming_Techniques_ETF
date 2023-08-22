//TP 2018/2019: Tutorijal 8, Zadatak 5

/*U modernom programiranju se, umjesto vlastito definiranih struktura, sve češće koristi standardni 
bibilotečki tip “tuple” (uređena 𝑛-torka). Zaista, s tim tipom može se raditi sve što i sa klasičnim 
vlastito definiranim strukturama (pa i još ponešto), uz jedinu bitnu razliku da polja unutar uređene 
n-torke nemaju imena, nego da im se pristupa po rednom broju. Tako, recimo, u primjeru iz Predavanja 8_a, 
umjesto da tip “Vektor3d” definiramo kao vlastito definiranu strukturu, možemo ga definirati kao uređenu 
trojku čija su sva tri polja tipa “double”. Da ne bismo stalno pisali nešto poput 2
“std::tuple<double, double, double>”, možemo uvesti “typedef” deklaraciju   
typedef std::tuple<double, double, double> Vektor3d;   
nakon čega možemo koristiti prosto “Vektor3d” kao ime tipa. Prepravite sve funkcije u programu iz primjera 
o kojem je riječ da rade sa ovako izmijenjenom definicijom tipa “Vektor3d”, uz ograničenje da glavni 
program (funkcija “main”) treba da ostane potpuno neizmijenjen. Pri tome, barem u jednoj od funkcija 
koju prepravljate upotrijebite i funkciju “tie”, tamo gdje mislite da bi njena upotreba mogla biti od 
najveće koristi (ovo je čisto da demonstrirate da razumijete mogućnost njene primjene). */

#include <iostream>
#include <tuple>

typedef std::tuple<double, double, double> Vektor3d;

void UnesiVektor(Vektor3d &v){
    std::cout << "X = " ; std::cin >> std::get<0>(v);
    std::cout << "Y = " ; std::cin >> std::get<1>(v);
    std::cout << "Z = " ; std::cin >> std::get<2>(v);
}
Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2){
    Vektor3d v3;
    std::get<0>(v3) = std::get<0>(v1) + std::get<0>(v2);
    std::get<1>(v3) = std::get<1>(v1) + std::get<1>(v2);
    std::get<2>(v3) = std::get<2>(v1) + std::get<2>(v2);
    return std::tie(std::get<0>(v3), std::get<1>(v3), std::get<2>(v3));
}
Vektor3d VektorskiProizvod(const Vektor3d &v1, const Vektor3d &v2){
    double x1, x2, y1, y2, z1, z2;
    std::tie(x1, y1, z1) = v1;
    std::tie(x2, y2, z2) = v2;
    Vektor3d v3 = std::make_tuple(y1 * z2 - z1 * y2, z1 * x2 - x1 * z2, x1 * y2 - y1 * x2);
    return v3;
}
void IspisiVektor(const Vektor3d &v){
    std::cout << "{" << std::get<0>(v) << "," << std::get<1>(v) << "," << std::get<2>(v) << "}" ;
}
int main ()
{
    Vektor3d a, b;
    std::cout << "Unesi prvi vektor: "  << std::endl;
    UnesiVektor(a);
    std::cout << "Unesi drugi vektor: " << std::endl;
    UnesiVektor(b);
    std::cout << "Suma ova dva vektora je: " ;
    IspisiVektor(ZbirVektora(a, b));
    std::cout << std::endl << "Njihov vektorski prozivod je: " ;
    IspisiVektor(VektorskiProizvod(a, b));
	return 0;
}
