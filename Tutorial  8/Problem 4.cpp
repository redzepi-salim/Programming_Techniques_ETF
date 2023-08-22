//TP 2018/2019: Tutorijal 8, Zadatak 4

/*Napišite funkciju “ZamijeniPremaRjecniku” koja određene riječi u nekom stringu zamjenjuje nekim 
drugim riječima. Prvi parametar je tipa “string” i on predstavlja string u kojem se vrši zamjena. Drugi 
parametar je mapa (tj. objekat tipa “map”) kod koje su i ključno polje i pridružena vrijednost tipa 
“string”. Ova mapa se sastoji od uređenih parova, u kojima prvi element predstavlja riječ koja se 
zamjenjuje, a drugi element predstavlja zamjensku riječ koja se treba ubaciti umjesto riječi koja se 
zamjenjuje. Funkcija treba kao da rezultat vrati novi string koji se dobija nakon izvršenih zamjena. 
Na primjer, sljedeći testni primjer treba da ispiše “how yes no”:   
std::map<std::string, std::string> moj_rjecnik{{"jabuka", "apple"}, {"da", "yes"},    {"kako", "how"}, {"ne", "no"}, {"majmun", "monkey"}};  
std::cout << ZamijeniPremaRjecniku("kako da ne", moj_rjecnik);   
Radi jednostavnosti, pretpostavite da string koji se transformira sadrži samo mala slova i razmake (i 
ništa drugo). Isto tako, pretpostavite da riječi u parovima koje čine mapu koja predstavlja rječnik 
sadrže samo mala slova, bez razmaka. Ove pretpostavke ne morate provjeravati, već je samo uzmite kao takvu. 
Međutim, vodite računa da je moguće da riječi budu razdvojene sa više razmaka, kao i da se na početku 
odnosno kraju stringa mogu također nalaziti razmaci. Drugim riječima, string poput “   kako  da    ne ” 
uz pomoć istog “rječnika” kao i gore navedenom primjeru treba da se prevede u “   how  yes    no ”.   
Treba paziti da se uvijek se zamjenjuju samo cijele riječi, nikad njihovi dijelovi. Na primjer, ukoliko 
string koji se transformira glasi “davor martić ima sestre maju i juliju” i ukoliko se mapa koja definira 2
rječnik sastoji od parova (“mart”, “ožujak”), (“maj”, “svibanj”) i (“jul”, “srpanj”), rezultat 
transformacije treba da bude isti string bez ikakve promjene, odnosno rezultat ne treba da bude string 
“davor ožujakić ima sestre svibanju i srpanjiju”. Inače, nešto slično tome desilo se prije nekoliko godina 
prilikom pokušaja automatskog “prevođenja” transkripta jedne parlamentarne sjednice sa bosanskog na 
hrvatski jezik uz pomoć Word-ove “Find & Replace” komande, kada je poslanik Martić postao Ožujakić. 
Interesantno je što bez obzira što Word ima opciju “Whole words only” kojom bi se izbjegao taj problem, 
“prevodioci” su je držali isključenom, jer su smatrali da na taj način “rješavaju” problem promjene riječi 
po padežima, koje inače komanda “Find & Replace” ne može da “uhvati”.   Napišite i kratki testni program u 
kojem ćete demonstrirati napisanu funkciju. Način komunikacije između korisnika i programa izvedite prema 
vlastitoj volji (neće se testirati). */

#include <iostream>
#include <map>
#include <string>
#include <algorithm>

std::string ZamijeniPremaRjecniku(std::string s, std::map<std::string, std::string> mapa){
    std::string pomocni{};
    auto pok = s.begin();
    while (pok != s.end()) {
        if(*pok == ' ') pomocni.push_back(*pok);
        else {
            auto pocetak = pok;
            auto kraj = pok;
            while (kraj != s.end() && *kraj != ' ') kraj++;
            auto pok_rijec = mapa.find(s.substr(pocetak - s.begin(), kraj - pocetak));
            if(pok_rijec == mapa.end()) pomocni = pomocni + s.substr(pocetak - s.begin(), kraj - pocetak);
            else pomocni = pomocni + pok_rijec->second;
            if(kraj == s.end()) break;
            pok = kraj - 1;
        }
        pok++;
    }
    return pomocni;
}

int main ()
{
    std::map<std::string, std::string> moj_rjecnik{{"jabuka", "Apple"}, {"da", "yes"}, {"kako", "how"}, {"ne", "no"}, {"majmun", "monkey"}};
    std::cout << ZamijeniPremaRjecniku("kako da ne", moj_rjecnik) << std::endl;
	return 0;
}
