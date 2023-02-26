/* 
    TP 16/17 (LV 9, Zadatak 4)
	
	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <stdexcept>

class Sat {

    int h, m, s;
    static const int D = 86400;

    public:
    
    static bool DaLiJeIspravno(int sati, int min, int sek){
        if(sati<0 || sati>23 || min<0 || min>59 || sek<0 || sek>59) return false;
        else return true;
    }
    
    void Postavi(int sati, int min, int sek){
        try{
        bool Ispravan = DaLiJeIspravno(sati, min, sek);
        if(Ispravan){
            h = sati;
            m = min; 
            s = sek;
        }else{
            throw std::domain_error("Neispravno vrijeme");
        }
    }catch(...){
        throw;
    }
    }
    
    void PostaviNormalizirano(int sati, int min, int sek){
        while(sek<0){
            sek+=60;
            min--;
        }
        while(min<0){
            min+=60;
            sati--;
        }
        while(sati<0){
            sati+=24;
        }
        while(sek>59){
            min++;
            sek-=60;
        }
        while(min>59){
            sati++;
            min-=60;
        }
        while(sati>23){
            sati-=24;
        }
        h=sati; m=min; s=sek;
    }
    
    Sat &Sljedeci(){s++; PostaviNormalizirano(h, m, s); return *this;};
    
    Sat &Prethodni(){s--; PostaviNormalizirano(h, m, s); return *this;};
    
    Sat &PomjeriZa(int sek){
        s+=sek;
        PostaviNormalizirano(h, m, s);
        return *this;
    }
    
    void Ispisi() const{
        std::cout.fill('0');std::cout.width(2);std::cout<<h<<":";
        std::cout.fill('0');std::cout.width(2);std::cout<<m<<":";
        std::cout.fill('0');std::cout.width(2);std::cout<<s;
    }

    int DajSate() const { return h; };
    
    int DajMinute() const { return m; };
    
    int DajSekunde() const { return s; };
    
    friend int BrojSekundiIzmedju(const Sat &v1, const Sat &v2);
    
    static int Razmak(Sat &v1, Sat &v2){
        return v1.s+60*v1.m+3600*v1.h-v2.s-60*v2.m-3600*v2.h;
    }
};

int BrojSekundiIzmedju(const Sat &v1, const Sat &v2){
    return v1.s+60*v1.m+3600*v1.h-v2.s-60*v2.m-3600*v2.h;
}

int main ()
{
	return 0;
}