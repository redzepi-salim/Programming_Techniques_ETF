/* TP 16/17 (Tutorijal 12, Zadatak 6)
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)



Prepravite generičku funkciju “Matrica” sa Predavanja 11_b tako da se umjesto funkcija članica “Unesi” i 
“Ispisi” te funkcije “ZbirMatrica” koriste odgovarajući operatori. Konkretno, dio “main” funkcije unutar 
try-bloka nakon prepravke trebao bi izgledati ovako:   
Matrica<double> a(m, n, 'A'), b(m, n, 'B');  
std::cout << "Unesi matricu A:\n";   
std::cin >> a;    
std::cout << "Unesi matricu B:\n";   
std::cin >> b;    
std::cout << "Zbir ove dvije matrice je:\n";   
std::cout << std::setw(7) << a + b;     
Ovdje je jedino “misteriozno” kako postići da operatorska funkcija za operator “<<” sazna koja je širina 
postavljena manipulatorom “setw”. Za tu svrhu, unutar operatorske funkcije nad objektom toka treba pozvati 
funkciju “width” bez parametara, i ona će kao rezultat dati trenutno postavljenu širinu ispisa (tj. onu koja 
je prethodno postavljena). Nakon obavljenih prepravki dodajte podršku za još neke operatore. Na prvom 
mjestu, dodajte podršku za operator “-” i “*”. Operator “*” treba da podrži kako množenje dvije matrice, 
tako i množenje matrice a brojem i obrnuto. Ukoliko matrice nisu saglasne za množenje, treba baciti izuzetak 
tipa “domain_error” uz prateći tekst “Matrice nisu saglasne za množenje”. Zatim, kako programerski bonton 
nalaže, dodajte podršku za operatore “+=” i “-=” i “*=”, koji će obezbijediti da izrazi oblika “A += B”, 
“A -= B” i “A *= B” uvijek imaju logički isto značenje kao i izrazi “A = A + B”, “A = A - B” i “A = A * B” 
kad god to ima smisla. Dalje, omogućite da se elementima matrice može pristupiti konstrukcijama poput 
“A[i][j]” i “A(i,j)”, pri čemu prva konstrukcija vrši pristup u C/C++ stilu, sa indeksacijom od nule i bez 
provjere ispravnosti indeksa), dok druga konstrukcija vrši pristup u matematičkom stilu, sa indeksacijom od 
jedinice i uz provjeru ispravnosti indeksa (u slučaju neispravnosti, baca se izuzetak tipa “range_error” uz 
prateći tekst “Neispravan indeks”. Konstrukcije poput “A[i][j]” i “A(i,j)” moraju se moći koristiti i sa 
lijeve strane znaka jednakosti, ali samo nad nekonstantnim objektima tipa “Matrica”. Konačno, treba podržati 
i automatsku konverziju objekata tipa “Matrica” u tip “string”, tako da se kao rezultat konverzije dobija 
string koji sadrži elemente matrice unutar vitičastih zagrada međusobno razdvojene zarezima (npr. 
“{{1,2,3},{4,5,6}}”). Obavezno napišite i testni program u kojem ćete demonstrirati implementirane operatore. 
*/
#include <iostream>
#include <stdexcept>
#include <new>
#include <string>
#include <iomanip>
#include <utility>
#include <cstring>
template <typename NekiTip1>
class Matrica
{

    int br_redova, br_kolona;
    NekiTip1 **elementi;
    char ime_matrice;
    static NekiTip1 **AlocirajMemoriju(int br_redova, int br_kolona);
    static void DealocirajMemoriju(NekiTip1 **elementi, int br_redova);
    void KopirajElemente(NekiTip1 **elementi);

public:
    Matrica (int br_redova, int br_kolona, char ime = 0);
    Matrica(const Matrica &mat);
    Matrica(Matrica &&mat);
    ~Matrica()
    {
        DealocirajMemoriju(elementi, br_redova);
    }
    Matrica &operator =(const Matrica &m);
    Matrica &operator =(Matrica &&m);
    NekiTip1* &operator [](int i)
    {
        return elementi[i];
    }
    NekiTip1* operator [](int i) const
    {
        return elementi[i];
    }
    NekiTip1 &operator ()(int i, int j)
    {
        if(i <= 0 || i > br_redova || j <= 0 || j > br_kolona) throw std::domain_error("Neispravan indeks");
        return elementi[i - 1][j - 1];
    }
    NekiTip1 operator()(int i, int j) const
    {
        if(i <= 0 || i > br_redova || j <= 0 || j < br_kolona) throw std::domain_error("Neispravan indeks");
        return elementi[i - 1][j - 1];
    }
    template <typename NekiTip>
    friend std::istream &operator >>(std::istream &tok, Matrica<NekiTip> &m)
    {
        for(int i=0; i<m.br_redova; i++) {
            for(int j=0; j<m.br_kolona; j++) {
                std::cout << m.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = " ;
                tok >> m.elementi[i][j];
            }
        }
        return tok;
    }
    template <typename NekiTip>
    friend std::ostream &operator <<(std::ostream &tok, const Matrica<NekiTip> &m)
    {
        int sirina = tok.width();
        for(int i=0; i<m.br_redova; i++) {
            for(int j=0; j<m.br_kolona; j++) {
                tok << std::setw(sirina) << m.elementi[i][j] ;
            }
            tok << std::endl;
        }
        return tok;
    }
    template <typename NekiTip2>
    friend Matrica<NekiTip2> ZbirMatrica(const Matrica<NekiTip2> &m1, const Matrica<NekiTip2> &m2)
    {
        if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije");
        Matrica<NekiTip2> m3(m1.br_redova, m1.br_kolona);
        for(int i=0; i<m1.br_redova; i++) {
            for(int j=0; j<m1.br_kolona; j++) m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
        }
        return m3;
    }
    template <typename NekiTip>
    friend Matrica<NekiTip> operator *(const Matrica<NekiTip> &m1, const Matrica<NekiTip> &m2)
    {
        if(m1.br_kolona != m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
        Matrica<NekiTip> m(m1.br_redova, m2.br_kolona);
        for(int i=0; m1.br_redova; i++) {
            for(int j=0; j<m2.br_kolona; j++) {
                m.elementi[i][j] = 0;
                for(int k=0; k<m1.br_redova; k++) m.elementi[i][j] = m.elementi[i][j] + m1.elementi[i][k] * m2.elementi[k][j];
            }
        }
        return m;
    }
    template <typename NekiTip>
    friend Matrica<NekiTip> operator +(const Matrica<NekiTip> &m1, const Matrica<NekiTip> &m2)
    {
        if(m1.br_kolona != m2.br_kolona && m1.br_redova != m2.br_redova) throw std::domain_error("Matrice nemaju jednake dimenzije");
        Matrica<NekiTip> m(m1.br_redova, m1.br_kolona);
        for(int i=0; i<m1.br_redova; i++) {
            for(int j=0; j<m1.br_kolona; j++) {
                m.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
            }
        }
        return m;
    }
    template <typename NekiTip>
    friend Matrica<NekiTip> operator -(const Matrica<NekiTip> &m1, const Matrica<NekiTip> &m2)
    {
        if(m1.br_kolona != m2.br_kolona && m1.br_redova != m2.br_redova) throw std::domain_error("Matrice nemaju jednake dimenzije");
        Matrica<NekiTip> m(m1.br_redova, m1.br_kolona);
        for(int i=0; i<m1.br_redova; i++) {
            for(int j=0; j<m2.br_redova; j++) m.elementi[i][j] = m1.elementi[i][j] - m2.elementi[i][j];
        }
        return m;
    }
    template <typename NekiTip>
    friend Matrica<NekiTip> &operator +=(Matrica<NekiTip> &m1, const Matrica<NekiTip> &m2)
    {
        if(m1.br_kolona != m2.br_kolona && m1.br_redova != m2.br_redova) throw std::domain_error("Matrice nemaju jednake dimenzije");
        m1 = m1 + m2;
        return m1;
    }
    template <typename NekiTip>
    friend Matrica<NekiTip> &operator -=(Matrica<NekiTip> &m1, const Matrica<NekiTip> &m2)
    {
        if(m1.br_kolona != m2.br_kolona && m1.br_redova != m2.br_redova) throw std::domain_error("Matrice nemaju jednake dimenzije");
        m1 = m1 - m2;
        return m1;
    }
    template <typename NekiTip>
    friend Matrica<NekiTip> &operator *=(Matrica<NekiTip> &m1, const Matrica<NekiTip> &m2)
    {
        if(m1.br_kolona != m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
        m1 = m1 * m2;
        return m1;
    }
    template <typename NekiTip>
    friend Matrica<NekiTip> operator *(int x, const Matrica<NekiTip> &m)
    {
        Matrica<NekiTip> temp(m.br_redova, m.br_kolona);
        for(int i=0; i<m.br_redova; i++) {
            for(int j=0; j<m.br_kolona; j++) temp.elementi[i][j] = x * m.elementi[i][j];
        }
        return temp;
    }
    template <typename NekiTip>
    friend Matrica<NekiTip> operator *(const Matrica<NekiTip> &m, int x)
    {
        Matrica<NekiTip> temp(m.br_redova, m.br_kolona);
        for(int i=0; i<m.br_redova; i++) {
            for(int j=0; j<m.br_kolona; j++) {
                temp.elementi[i][j] = x * m.elementi[i][j];
            }
        }
        return temp;
    }
    template <typename NekiTip>
    friend Matrica<NekiTip> &operator *=(Matrica<NekiTip> &m, int x)
    {
        for(int i=0; i<m.br_redova; i++) {
            for(int j=0; j<m.br_kolona; j++) {
                m.elementi[i][j] *= x;
            }
        }
        return m;
    }
    operator std::string() const
    {
        std::string s("{");
        for(int i=0; i<br_redova; i++) {
            s += "{";
            for(int j=0; j<br_kolona; j++) {
                s += std::to_string(int(elementi[i][j]));
                if(j != br_kolona - 1) s += ",";
            }
            if(i != br_redova - 1) s += "}";
            else s += "}";
        }
        s += "}";
        return s;
    }
};
template <typename NekiTip1>
NekiTip1 ** Matrica<NekiTip1>::AlocirajMemoriju(int br_redova, int br_kolona)
{
    NekiTip1 **elementi = new NekiTip1*[br_redova] {};
    try {
        for(int i=0; i<br_redova; i++) elementi[i] = new NekiTip1[br_kolona];
    } catch (...) {
        DealocirajMemoriju(elementi, br_redova);
        throw;
    }
    return elementi;
}
template <typename NekiTip1>
void Matrica<NekiTip1>::DealocirajMemoriju(NekiTip1 **elementi, int br_redova)
{
    for(int i=0; i<br_redova; i++) delete[] elementi[i];
    delete[] elementi;
}
template <typename NekiTip1>
void Matrica<NekiTip1>::KopirajElemente(NekiTip1 **elementi)
{
    for(int i=0; i<br_redova; i++) {
        for(int j=0; j<br_kolona; j++) {
            Matrica::elementi[i][j] = elementi[i][j];
        }
    }
}
template <typename NekiTip1>
Matrica<NekiTip1>::Matrica (int redovi, int kolone, char ime) : br_redova(redovi), br_kolona(kolone), ime_matrice(ime), elementi(AlocirajMemoriju(redovi, kolone)) {}

template <typename NekiTip1>
Matrica<NekiTip1>::Matrica (const Matrica &mat) : br_redova(br_redova), br_kolona(br_kolona), ime_matrice(mat.ime_matrice), elementi(AlocirajMemoriju(br_redova, br_kolona))
{
    KopirajElemente(mat.elementi);
}
template <typename NekiTip1>
Matrica<NekiTip1>::Matrica (Matrica &&mat) : br_redova(mat.br_redova), br_kolona(mat.br_kolona), elementi(mat.elementi), ime_matrice(mat.ime_matrice)
{
    mat.br_redova = 0;
    mat.elementi = nullptr;
}
template <typename NekiTip1>
Matrica<NekiTip1> &Matrica<NekiTip1>:: operator =(const Matrica &m)
{
    if(br_redova < m.br_redova || br_kolona < m.br_kolona) {
        NekiTip1 **novi_prostor = AlocirajMemoriju(m.br_redova, m.br_kolona);
        DealocirajMemoriju(elementi, br_redova);
        elementi = novi_prostor;
    } else if(br_redova > m.br_redova) {
        for(int i = m.br_redova; i<br_redova; i++) delete[] elementi[i];
    }
    br_redova = m.br_redova;
    br_kolona = m.br_kolona;
    ime_matrice = m.ime_matrice;
    KopirajElemente(m.elementi);
    return *this;
}
template <typename NekiTip1>
Matrica<NekiTip1> &Matrica<NekiTip1>:: operator =(Matrica &&m)
{
    std::swap(br_redova, m.br_redova);
    std::swap(br_kolona, m.br_kolona);
    std::swap(ime_matrice, m.ime_matrice);
    std::swap(elementi, m.elementi);
    return *this;
}
int main ()
{
    int m = 3, n = 3;
    Matrica<double> a(m, n, 'A'), b(m, n, 'B');
    std::cout << "Unesi matricu A:\n";
    std::cin >> a;
    std::cout << "Unesi matricu B:\n";
    std::cin >> b;
    std::cout << "Zbir ove dvije matrice je:\n";
    std::cout << std::setw(7) << a + b;
    return 0;
}
