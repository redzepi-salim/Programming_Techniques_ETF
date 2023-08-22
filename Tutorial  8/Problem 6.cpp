
/*Definirajte generičku strukturu “Cvor” koja sadrži polje “element” neodređenog tipa koji će se kasnije 
specificirati i polje “veza” koje je tipa pokazivač na generičku strukturu “Cvor” sa istim tipom polja 
“element” kao što je i ona sama. Zatim napišite pet jednostavnih generičkih funkcija sa sljedećim 
prototipovima:   
template <typename TipElemenata>     
Cvor<TipElemenata> *KreirajPovezanuListu(TipElemenata zavrsni);    

template <typename TipElemenata>    
int BrojElemenata(Cvor<TipElemenata> *pocetak);    

template <typename TipElemenata>    
TipElemenata SumaElemenata(Cvor<TipElemenata> *pocetak);   

template <typename TipElemenata>    
int BrojVecihOd(Cvor<TipElemenata> *pocetak, TipElemenata prag);   

template <typename TipElemenata>    
void UnistiListu(Cvor<TipElemenata> *pocetak);   

Funkcija “KreirajPovezanuListu” čita podatke tipa “TipElemenata” sa tastature sve dok se ne unese podatak 
čija je vrijednost jednaka vrijednosti parametra “zavrsni”, uvezuje te elemente u povezanu listu čvorova 
tipa “Cvor” (sa elementima tipa “TipElemenata”) pri čemu se završni element ne uvezuje, te vraća kao 
rezultat pokazivač na prvi čvor tako kreirane liste (ili nul-pokazivač ako nije unesen niti jedan koristan 
element). Funkcija “BrojElemenata” prima kao parametar pokazivač na prvi čvor povezane liste čvorova, a 
vraća kao rezultat broj elemenata tako povezane liste (ili 0 ako se zada nul-pokazivač). Funkcija 
“SumaElemenata” također prima kao parametar pokazivač na prvi */

#include <iostream>
#include <new>
template <typename NekiTip>
struct Cvor{
    NekiTip element;
    Cvor *veza;
};
template <typename NekiTip>
Cvor<NekiTip> *KreirajPovezanuListu(NekiTip zavrsni){
    Cvor<NekiTip> *pocetak = nullptr, *prethodni;
    for(;;){
        NekiTip n;
        std::cin >> n;
        if(n == zavrsni) break;
        Cvor<NekiTip> *novi = new Cvor<NekiTip>{n, nullptr};
        if(!pocetak) pocetak = novi;
        else prethodni->veza = novi;
        prethodni = novi;
    }
    return pocetak;
} 
template <typename NekiTip>
int BrojElemenata(Cvor<NekiTip> *pocetak){
    int brojac = 0;
    if(!pocetak) return 0;
    else for(Cvor<NekiTip> *p=pocetak; p!=nullptr; p=p->veza) brojac++;
    return brojac;
}
template <typename NekiTip>
NekiTip SumaElemenata(Cvor<NekiTip> *pocetak){
    NekiTip suma = NekiTip();
    for(Cvor<NekiTip> *p=pocetak; p!=nullptr; p=p->veza) suma += p->element;
    return suma;
} 
template <typename NekiTip>
int BrojVecihOd(Cvor<NekiTip> *pocetak, NekiTip prag){
    if(!pocetak) return 0;
    int brojac = 0;
    for(Cvor<NekiTip> *p=pocetak; p!=nullptr; p=p->veza) if(p->element > prag) brojac++;
    return brojac;
}
template <typename NekiTip>
void UnistiListu(Cvor<NekiTip> *pocetak){
    while (pocetak != nullptr) {
        Cvor<NekiTip> *sljedeci = pocetak->veza;
        delete pocetak;
        pocetak = sljedeci;
    }
}
int main ()
{
    Cvor<double> *lista;
    std::cout << "Unesite slijed brojeva (0 za kraj): " ;
    lista = KreirajPovezanuListu<double>(0);
    std::cout << "U slijedu ima " << BrojVecihOd(lista, SumaElemenata(lista) / BrojElemenata(lista)) << " brojeva vecih od njihove aritmeticke sredine" << std::endl;
    UnistiListu(lista);
	return 0;
}
