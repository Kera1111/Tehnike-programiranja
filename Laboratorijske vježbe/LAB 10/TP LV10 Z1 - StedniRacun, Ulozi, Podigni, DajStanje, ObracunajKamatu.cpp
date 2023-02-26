/* 
    TP 16/17 (LV 10, Zadatak 1)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <ios>
#include <iostream>
#include <stdexcept>
#include <type_traits>

class StedniRacun{
    double pare;
    public:
    StedniRacun(double z=0){
        if(z<0) throw std::logic_error("Nedozvoljeno pocetno stanje");
        pare = z;
    }
    void Ulozi(double z){
        double x = pare + z;
        if(x<0) throw std::logic_error("Transakcija odbijena");
        pare = x;
    }
    void Podigni(double z){
        if(z>pare) throw std::logic_error("Transakcija odbijena");
        pare -= z;
    }
    double DajStanje() const {return pare;}
    void ObracunajKamatu(double x){
        if(x<0) throw std::logic_error("Nedozvoljena kamatna stopa");
        double z;
        z = pare + pare*(x/100);
        pare = z;
    }
};

int main ()
{
    StedniRacun a=500, b=1000, c=1500;
    std::cout<<a.DajStanje()<<" "<<b.DajStanje()<<" "<<c.DajStanje()<<std::endl;
    a.Ulozi(100);
    std::cout<<a.DajStanje()<<std::endl;
    b.ObracunajKamatu(2);
    std::cout<<b.DajStanje()<<std::endl;
    c.Podigni(30);
    std::cout<<c.DajStanje()<<std::endl;

    //konstruktori
    std::cout<<std::boolalpha<<std::is_convertible<double, StedniRacun>::value <<std::endl;
    std::cout<<std::boolalpha<<std::is_default_constructible<StedniRacun>::value<<std::endl;
    std::cout<<std::is_default_constructible<StedniRacun>::value;
	return 0;
}