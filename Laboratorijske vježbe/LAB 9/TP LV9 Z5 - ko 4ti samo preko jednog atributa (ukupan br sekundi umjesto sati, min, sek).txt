/* 
    TP 16/17 (LV 9, Zadatak 5)
	
	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/

/*
Definirajte i implementirajte klasu “Sat” koja ima potpuno isti interfejs i potpuno isto ponašanje 
kao klasa iz prethodnog zadatka, samo čija se interna struktura umjesto tri atributa koja čuvaju 
trenutni broj sati, minuta i sekundi sastoji samo od jednog atributa, koji čuva ukupan broj sekundi
(npr. umjesto informacije “3 sata, 20 minuta, 15 sekundi” čuva se samo informacija koja kaže 
12015 sekundi). Mada će ovo možda tražiti izmjenu implementacije svih (ili skoro svih) metoda
klase (pri tipičnim izvedbama, metoda “Postavi” će se sasvim neznatno izmijeniti, metode “Sljedeci”, 
“Prethodni” i “PomjeriZa” kao i prijateljska funkcija “BrojSekundiIzmedju” odnosno statička metoda 
“Razmak” bitno će se pojednostaviti, metode “DajSate”, “DajMinute”, “DajSekunde” će se zakomplicirati,
dok će se metoda “Ispisi” možda zakomplicirati, a možda će i ostati potpuno ista, ako ste je 
pametno realizirali), pokažite da će testni program iz prethodnog zadatka bez ikakve prepravke 
raditi sa ovako modificiranom klasom. Savjet: da biste vršili što manje prepravki, probajte se 
prilikom rješavanja zadatka 4 u realizaciji funkcija članica što je god moguće više oslanjati na druge 
funkcije članice, a što manje na to šta su zaista atributi klase
*/

#include <iostream>
#include <stdexcept>

class Sat {

    int s=0; //sekunde
    static const int D = 86400; //ukupan br sek u danu 

    public:
    
    static bool DaLiJeIspravno(int sati, int min, int sek){
        if(sati<0 || sati>23 || min<0 || min>59 || sek<0 || sek>59) return false;
        else return true;
    }

    public:
    
    void Postavi(int sati, int min, int sek){
        try{
        bool Ispravan = DaLiJeIspravno(sati, min, sek);
        if(Ispravan){
            s = sati * 3600;
            s += min * 60; 
            s += sek;
        }else{
            throw std::domain_error("Neispravno vrijeme");
        }
    }catch(...){
        throw;
    }
    }
    
    void PostaviNormalizirano(int sati, int min, int sek){
        int sekunde=sati*3600+min*60+sek;
        int sekunde2=sekunde%86400;
        if(sekunde2<0) sekunde2+=86400;
        s=sekunde2;
    }
    
    Sat &Sljedeci(){PomjeriZa(1); return *this;};
    
    Sat &Prethodni(){PomjeriZa(-1);return *this;};
    
    Sat &PomjeriZa(int a){
        s+=a;
        PostaviNormalizirano(DajSate(), DajMinute(), DajSekunde());
        return *this;
    }
    
    void Ispisi() const{
        std::cout.fill('0');std::cout.width(2);std::cout<<DajSate()<<":";
        std::cout.fill('0');std::cout.width(2);std::cout<<DajMinute()<<":";
        std::cout.fill('0');std::cout.width(2);std::cout<<DajSekunde();
    }

    int DajSate() const { return s/3600; };
    
    int DajMinute() const { return (s%3600)/60; };
    
    int DajSekunde() const { return (s%3600)%60; };
    
    friend int BrojSekundiIzmedju(const Sat &v1, const Sat &v2);
    
    static int Razmak(Sat &v1, Sat &v2){
        return v1.s-v2.s;
    }
};

int BrojSekundiIzmedju(const Sat &v1, const Sat &v2){
    return v1.s-v2.s;
}

int main ()
{
	return 0;
}