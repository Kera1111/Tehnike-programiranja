/* 
    TP 16/17 (LV 9, Zadatak 1)
	
	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <math.h>

class Vektor3d {
    double x,y,z;
    public:
    void Postavi(double x, double y, double z){
        Vektor3d::x = x;
        Vektor3d::y = y;
        Vektor3d::z = z;
    }

    void PostaviX(double x){
        Vektor3d::x = x;
    }

    void PostaviY(double y){
        Vektor3d::y = y;
    }

    void PostaviZ(double z){
        Vektor3d::z = z;
    }

    void Ocitaj(double &x, double &y, double &z) const{
        x = Vektor3d::x;
        y = Vektor3d::y;
        z = Vektor3d::z;
    }

    double DajX() const{
        return x;
    }

    double DajY() const{
        return y;
    }

    double DajZ() const{
        return z;
    }

    Vektor3d PomnoziSaSkalarom(double s){
        x*=s; y*=s; z*=s;
        return *this;
    }

    Vektor3d SaberiSa(const Vektor3d &v){
        x+=v.x; y+=v.y; z+=v.z;
        return *this;
    }

    void Ispisi() const {
        std::cout<< "{" << x << "," << y << "," << z << "}";
    }

    friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2){
        Vektor3d v;
        v.x = v1.x + v2.x;
        v.y = v1.y + v2.y;
        v.z = v1.z + v2.z;
        return v;
    }

    double DajDuzinu() const{
        return std::sqrt(x*x+y*y+z*z);
    }
};
int main ()
{
    
Vektor3d v1, v2;
v1.Postavi(1,2,3);
v2.Postavi(4,-3,0);
v1.SaberiSa(v2).Ispisi();
	return 0;
}