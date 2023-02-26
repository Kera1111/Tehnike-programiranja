/* 
    TP 16/17 (LV 10, Zadatak 3)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cmath>

class Vektor3d {
  double koordinate[3];
  mutable int x = 0;//za DajBrojIspisa

public:
    Vektor3d(){koordinate[0]=koordinate[1]=koordinate[2]=0;}
    Vektor3d(double x1, double y1, double z1){koordinate[0]=x1; koordinate[1]=y1; koordinate[2]=z1;}
    Vektor3d(const Vektor3d &v1){for(int i=0; i<3; i++){koordinate[i]=v1.koordinate[i];} x=0; }

  void Postavi(double x, double y, double z) {
    koordinate[0] = x;
    koordinate[1] = y;
    koordinate[2] = z;
  }

  void PostaviX(double x) { koordinate[0] = x; }

  void PostaviY(double y) { koordinate[1] = y; }

  void PostaviZ(double z) { koordinate[2] = z; }

  void Ocitaj(double &x, double &y, double &z) const {
    x = DajX();
    y = DajY();
    z = DajZ();
  }

  double DajX() const { return koordinate[0]; }

  double DajY() const { return koordinate[1]; }

  double DajZ() const { return koordinate[2]; }

  int DajBrojIspisa() const { return x; } //vrati broj ponavljanja

  void PomnoziSaSkalarom(double s) { // treba referenca ako hocu da se mijenja
    koordinate[0] *= s;
    koordinate[1] *= s;
    koordinate[2] *= s;
  }

  void SaberiSa(const Vektor3d &v) { // isti razlog kao za prethodnu fju
    koordinate[0] += v.koordinate[0];
    koordinate[1] += v.koordinate[1];
    koordinate[2] += v.koordinate[2];
  }

  void Ispisi() const {
    std::cout << "{" << koordinate[0] << "," << koordinate[1] << ","
              << koordinate[2] << "}";
              x++; //da se poveca brojac za br ispisa
  }

  friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2) {
    Vektor3d v;
    v.koordinate[0] = v1.koordinate[0] + v2.koordinate[0];
    v.koordinate[1] = v1.koordinate[1] + v2.koordinate[1];
    v.koordinate[2] = v1.koordinate[2] + v2.koordinate[2];
    return v;
  }

  double DajDuzinu() const {
    return std::sqrt(koordinate[0] * koordinate[0] +
                     koordinate[1] * koordinate[1] +
                     koordinate[2] * koordinate[2]);
  }
};
int main() {
  Vektor3d v1, v2;
  v1.Postavi(4, 3, 0);
  v2.PostaviX(1);
  v2.PostaviY(2);
  v2.PostaviZ(3);
  v1.Ispisi();
  std::cout << std::endl;
  v2.Ispisi();
  double x, y, z;
  v2.Ocitaj(x, y, z);
  std::cout << std::endl << x << " " << y << " " << z;
  std::cout << std::endl << v2.DajX() << " " << v2.DajY() << " " << v2.DajZ();
  std::cout << std::endl << v1.DajDuzinu() << std::endl;

  const Vektor3d vConst(v1);
  std::cout << std::endl;
  vConst.Ispisi();
  vConst.Ocitaj(x, y, z);
  std::cout << std::endl << x << " " << y << " " << z << std::endl;
  std::cout << vConst.DajX() << " " << vConst.DajY() << " " << vConst.DajZ()
            << std::endl;
  std::cout << vConst.DajDuzinu();
  /*
Vektor3d v1, v2;
v1.Postavi(1,2,3);
v2.Postavi(4,-3,0);
v1.SaberiSa(v2).Ispisi();*/
  return 0;
}