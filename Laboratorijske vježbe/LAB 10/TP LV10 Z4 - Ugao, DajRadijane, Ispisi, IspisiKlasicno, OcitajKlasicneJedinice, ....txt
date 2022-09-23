/* 
    TP 16/17 (LV 10, Zadatak 4)
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
        double radijani;
        void Plin(double &x){
            while(x>=2*PI) x-=2*PI;
            while(x<0) x+=2*PI;
        }
    public:
        Ugao(double radijani=0){
            Ugao::radijani = radijani;
            Plin(Ugao::radijani);
        }
        Ugao(int stepeni, int minute, int sekunde){
            radijani = (stepeni*3600 + minute*60 + sekunde)*(PI/(180*3600));
            Plin(radijani);
        }
        void Postavi(double x){ radijani = x; }
        void Postavi(int stepeni, int minute, int sekunde){
            radijani = (stepeni*3600 + minute*60 + sekunde)*(PI/(180*3600));
            Plin(radijani);
        }
        double DajRadijane() const { return radijani; }
        void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde){
            int temp = radijani*(180*3600)/PI;
            sekunde = temp%60;
            temp/=60; minute=temp%60;
            temp/=60; stepeni=temp;
        }
        int DajStepene() const {int a = radijani*(180*3600)/PI; return a/3600;}
        int DajMinute() const {int a = radijani*(180*3600)/PI; a/=60; return a%60;}
        int DajSekunde() const {int a = radijani*(180*3600)/PI; return a%60;}
        void Ispisi() const {
            std::cout<<std::fixed<<std::setw(6)<<std::setprecision(5)<<radijani;
        }
        void IspisiKlasicno() const {
            int stepeni, minute, sekunde;
            int temp = radijani*(180*3600)/PI;
            sekunde = temp%60;
            temp/=60; minute=temp%60;
            temp/=60; stepeni=temp;
            std::cout<<stepeni<<"deg "<<minute<<"min "<<sekunde<<"sec";
        }
        Ugao &SaberiSa(const Ugao &u){
            radijani += u.radijani;
            Plin(radijani);
            return *this;
        }
        Ugao &PomnoziSa(double x){
            radijani *= x;
            Plin(radijani);
            return *this;
        }
        friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
        friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);
};

Ugao ZbirUglova(const Ugao &u1, const Ugao &u2){
    return u1.radijani+u2.radijani;
}

Ugao ProduktUglaSaBrojem(const Ugao &u, double x){
    return u.radijani*x;
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