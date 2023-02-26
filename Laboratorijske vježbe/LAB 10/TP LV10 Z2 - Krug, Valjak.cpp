/* 
    TP 16/17 (LV 10, Zadatak 2)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>

class Krug {
        double poluprecnik;
        const double PI = 4 * atan(1);
    public:
        explicit Krug(double x){
            if(x<=0) throw std::domain_error("Neispravan poluprecnik");
            poluprecnik = x;
        }
        void Postavi(double x){
            if(x<=0) throw std::domain_error("Neispravan poluprecnik");
            poluprecnik = x;
        }
        double DajPoluprecnik() const { return poluprecnik; }
        double DajObim() const { return 2*poluprecnik*PI; }
        double DajPovrsinu() const { return pow(poluprecnik,2)*PI; }
        void Skaliraj(double x){ 
            if(x<=0) throw std::domain_error("Neispravan faktor skaliranja");
            poluprecnik*=x;
        }
        void Ispisi() const{
            std::cout<<std::fixed<<std::setprecision(5)<<"R="<<DajPoluprecnik()<<" O="<<DajObim()<<" P="<<DajPovrsinu();
        }
};

class Valjak {
        double visina;
        Krug baza;
    public:
        explicit Valjak(double poluprecnik, double h):baza(poluprecnik){
            if(h<0) throw std::domain_error("Neispravna visina");
            visina = h;
        }
        void Postavi(double pp, double h){
            if(pp<0) throw std::domain_error("Neispravan poluprecnik");
            if(h<0) throw std::domain_error("Neispravna visina");
            baza.Postavi(pp);
            visina = h;
        }
        Krug DajBazu() const { return baza; }
        double DajPoluprecnikBaze() const { return baza.DajPoluprecnik(); }
        double DajVisinu() const { return visina; }
        double DajPovrsinu() const { return (2*baza.DajPovrsinu()+visina*baza.DajObim());}
        double DajZapreminu() const { return (baza.DajPovrsinu()*visina);}
        void Skaliraj(double x){
            if(x<=0) throw std::domain_error("Neispravan faktor skaliranja");
            baza.Skaliraj(x);
        }
        void Ispisi() const{
            std::cout<<std::setprecision(5)<<std::fixed<<"R="<<DajPoluprecnikBaze()<<" H="<<DajVisinu()<<" P="<<DajPovrsinu()<<" V="<<DajZapreminu();
        }
};

int main ()
{
    //konstruktori
    std::cout<<std::boolalpha<<std::is_convertible<int, Krug>::value <<std::endl;
    std::cout<<std::boolalpha<<std::is_default_constructible<Krug>::value<<std::endl;
    std::cout<<std::is_default_constructible<Krug>::value<<std::endl;

    std::cout<<std::boolalpha<<std::is_convertible<int, Valjak>::value <<std::endl;
    std::cout<<std::boolalpha<<std::is_default_constructible<Valjak>::value<<std::endl;
    std::cout<<std::is_default_constructible<Valjak>::value<<std::endl;


	return 0;
}