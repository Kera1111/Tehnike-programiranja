/* 
    TP 16/17 (LV 10, Zadatak 5)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cmath>
#include <iomanip>

const double PI = 4*atan(1);

class Ugao {
        int h,m,s;
        void Plin(double &x){
            while(x>=2*PI) x-=2*PI;
            while(x<0) x+=2*PI;
        }
        void pretv(double &radijan, int stepen, int minuta, int sekunda){
            radijan = (stepen*3600 + minuta*60 + sekunda) * (PI/(180*3600));
        }
        void pretv2(double radijan, int &stepen, int &minuta, int &sekunda){
            int temp = radijan * (180 * 3600)/ PI;
            sekunda = temp % 60;
            temp /= 60; minuta = temp % 60;
            temp /= 60; stepen = temp; 
        }
    public:
        Ugao(double radijani=0){
            Plin(radijani);
            pretv2(radijani, h, m, s);
        }
        Ugao(int stepeni, int minute, int sekunde){
            double radijani;
            pretv(radijani,stepeni,minute,sekunde);
            Plin(radijani);
            pretv2(radijani,h,m,s);
        }
        void Postavi(double x){ pretv(x,h,m,s); }
        void Postavi(int stepeni, int minute, int sekunde){
            double radijani;
            pretv(radijani,stepeni,minute,sekunde);
            Plin(radijani);
            pretv2(radijani,h,m,s);
        }
        double DajRadijane() const { return (h*3600 + m*60 + s) * (PI/(180*3600)); }
        void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde){
            h = stepeni;
            m = minute;
            s = sekunde;
        }
        int DajStepene() const {return h;}
        int DajMinute() const {return m;}
        int DajSekunde() const {return s;}
        void Ispisi() const {
            double radijani;
            radijani = (h*3600 + m*60 + s) * (PI/(180*3600));
            std::cout<<std::fixed<<std::setw(6)<<std::setprecision(5)<<radijani;
        }
        void IspisiKlasicno() const {
            std::cout<<h<<"deg "<<m<<"min "<<s<<"sec";
        }
        Ugao &SaberiSa(const Ugao &u){
            h += u.h;
            m += u.m;
            s += u.s;
            double radijani;
            pretv(radijani,h,m,s);
            Plin(radijani);
            pretv2(radijani,h,m,s);
            return *this;
        }
        Ugao &PomnoziSa(double x){
            double radijani;
            pretv(radijani,h,m,s);
            radijani*=x;
            Plin(radijani);
            pretv2(radijani,h,m,s);
            return *this;
        }
        friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
        friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);
};

Ugao ZbirUglova(const Ugao &u1, const Ugao &u2){
    return {u1.h+u2.h, u1.m+u2.m,u1.s+u2.s};
}

Ugao ProduktUglaSaBrojem(const Ugao &u, double x){
    double radijani;
    radijani = (u.h*3600+u.m*60+u.s)*(PI/(180*3600));
    radijani *= x;
    int temp = radijani*(180*3600)/PI;
    int stepen, minuta, sekunda;
    
	sekunda = temp % 60;
	temp /= 60; minuta = temp % 60;
	temp /= 60; stepen = temp;

    Ugao z = 0;
    z.Postavi(stepen, minuta, sekunda);
    return z;
}

int main ()
{
    Ugao u = 60;
    u = ZbirUglova(u,3);
    u.Ispisi();
    std::cout<<std::endl;
    u.IspisiKlasicno();
    std::cout<<std::endl;
    
    u.PomnoziSa(2);
    u.Ispisi();
    std::cout<<std::endl;
    
    u.SaberiSa(4);
	u.IspisiKlasicno();
    std::cout<<std::endl;

    u = ProduktUglaSaBrojem(u,5);
    u.IspisiKlasicno();
    std::cout<<std::endl;

    return 0;
}