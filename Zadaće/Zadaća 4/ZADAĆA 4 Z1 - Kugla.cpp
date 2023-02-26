// TP 2021/2022: Zadaća 4, Zadatak 1
#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <vector>
#include <complex>

using namespace std;

const double PI = 4 * atan(1);
const double EPS = 0.00000000001; 

class Kugla {
  double X, Y, Z, R;
  public:
  
  explicit Kugla(double r = 0);
  Kugla(double x, double y, double z, double r = 0);
  explicit Kugla(const std::tuple<double, double, double> &centar,
                 double r = 0);
  double DajX() const;
  double DajY() const;
  double DajZ() const;
  std::tuple<double, double, double> DajCentar() const;
  double DajPoluprecnik() const;
  double DajPovrsinu() const;
  double DajZapreminu() const;
  Kugla &PostaviX(double x);
  Kugla &PostaviY(double y);
  Kugla &PostaviZ(double z);
  Kugla &PostaviCentar(double x, double y, double z);
  Kugla &PostaviCentar(const std::tuple<double, double, double> &centar);
  Kugla &PostaviPoluprecnik(double r);
  void Ispisi() const;
  void Transliraj(double delta_x, double delta_y, double delta_z);
  friend bool DaLiSuIdenticne(const Kugla &k1, const Kugla &k2);
  friend bool DaLiSuPodudarne(const Kugla &k1, const Kugla &k2);
  friend bool DaLiSuKoncentricne(const Kugla &k1, const Kugla &k2);
  friend bool DaLiSeDodirujuIzvana(const Kugla &k1, const Kugla &k2);
  friend bool DaLiSeDodirujuIznutra(const Kugla &k1, const Kugla &k2);
  friend bool DaLiSePreklapaju(const Kugla &k1, const Kugla &k2);
  friend bool DaLiSeSijeku(const Kugla &k1, const Kugla &k2);
  bool DaLiSadrzi(const Kugla &k) const;
  friend double RastojanjeCentara(const Kugla &k1, const Kugla &k2);
};

Kugla::Kugla(double r) {
  if (r < 0)
    throw domain_error("Ilegalan poluprecnik");
  R = r, X = 0, Y = 0;
  Z = 0;
}

Kugla::Kugla(double x, double y, double z, double r) {
  if (r < 0)
    throw domain_error("Ilegalan poluprecnik");
  R = r, X = x, Y = y;
  Z = z;
}

Kugla::Kugla(const std::tuple<double, double, double> &centar, double r) {
  X = get<0>(centar);
  Y = get<1>(centar);
  Z = get<2>(centar);
  R = r;
}

double Kugla::DajX() const { return X; }

double Kugla::DajY() const { return Y; }

double Kugla::DajZ() const { return Z; }

std::tuple<double, double, double> Kugla::DajCentar() const {
  return {X, Y, Z};
}

double Kugla::DajPoluprecnik() const { return R; }

double Kugla::DajPovrsinu() const { return 4 * R * R * PI; }

double Kugla::DajZapreminu() const { return (4 * R * R * R * PI) / 3.; }

Kugla &Kugla::PostaviX(double x) {
  X = x;
  return *this;
}

Kugla &Kugla::PostaviY(double y) {
  Y = y;
  return *this;
}

Kugla &Kugla::PostaviZ(double z) {
  Z = z;
  return *this;
}

Kugla &Kugla::PostaviCentar(double x, double y, double z) {
  this->X= x;
  this->Y = y;
  this->Z = z;
  return *this;
}

Kugla &Kugla::PostaviCentar(const std::tuple<double, double, double> &centar) {
  X = get<0>(centar);
  Y = get<1>(centar);
  Z = get<2>(centar);
  return *this;
}

Kugla &Kugla::PostaviPoluprecnik(double r) {
  R = 0;
  if (r < 0)
    throw domain_error("Ilegalan poluprecnik");
  R = r;
  return *this;
}

void Kugla::Ispisi() const {
  cout << "{(" << X << "," << Y << "," << Z << ")," << R << "}" << endl;
}

void Kugla::Transliraj(double delta_x, double delta_y, double delta_z) {
  X += delta_x;
  Y += delta_y;
  Z += delta_z;
}

bool DaLiSuIdenticne(const Kugla &k1, const Kugla &k2) {
    bool x = fabs(k2.X - k1.X) < EPS;
    bool y = fabs(k2.Y - k1.Y) < EPS;
    bool z = fabs(k2.Z - k1.Z) < EPS;
    bool r = fabs(k2.R - k1.R) < EPS;
    return x && y && z && r;
}

bool DaLiSuPodudarne(const Kugla &k1, const Kugla &k2) {
  return (fabs(k2.R - k1.R) < EPS * (fabs(k2.R) + fabs(k1.R)));
}

bool DaLiSuKoncentricne(const Kugla &k1, const Kugla &k2) {
  bool x = fabs(k2.X - k1.X) < EPS;
  bool y = fabs(k2.Y - k1.Y) < EPS;
  bool z = fabs(k2.Z - k1.Z) < EPS;
  return x && y && z;
}

bool DaLiSeDodirujuIzvana(const Kugla &k1, const Kugla &k2) {
  return fabs(k1.R + k2.R - sqrt(pow(k2.X - k1.X, 2) + pow(k2.Y - k1.Y, 2) + pow(k2.Z - k1.Z, 2))) < EPS * (fabs(k1.R + k2.R) + fabs(sqrt(pow(k2.X - k1.X, 2) + pow(k2.Y - k1.Y, 2) +                         pow(k2.Z - k1.Z, 2))));
}

bool DaLiSeDodirujuIznutra(const Kugla &k1, const Kugla &k2) {
  return fabs(k1.R - k2.R - sqrt(pow(k2.X - k1.X, 2) + pow(k2.Y - k1.Y, 2) + pow(k2.Z - k1.Z, 2))) < EPS * (fabs(k1.R - k2.R) + fabs(sqrt(pow(k2.X - k1.X, 2) + pow(k2.Y - k1.Y, 2) +                         pow(k2.Z - k1.Z, 2))));
}

bool DaLiSePreklapaju(const Kugla &k1, const Kugla &k2) {
  return sqrt(pow(k2.X - k1.X, 2) + pow(k2.Y - k1.Y, 2) + pow(k2.Z - k1.Z, 2)) < k1.R + k2.R;
}

bool DaLiSeSijeku(const Kugla &k1, const Kugla &k2) {
  return sqrt(pow(k2.X - k1.X, 2) + pow(k2.Y - k1.Y, 2) + pow(k2.Z - k1.Z, 2)) < k1.R + k2.R &&  sqrt(pow(k2.X - k1.X, 2) + pow(k2.Y - k1.Y, 2) + pow(k2.Z - k1.Z, 2)) >  k1.R - k2.R;
}

bool Kugla::DaLiSadrzi(const Kugla &k) const {
  double s = sqrt(pow(k.X - X, 2) + pow(k.Y - Y, 2) + pow(k.Z - Z, 2));
  double r = R - k.R;
  if (r < s)
    return false;
  else
    return true;
}

double RastojanjeCentara(const Kugla &k1, const Kugla &k2) {
  return sqrt(pow(k2.X - k1.X, 2) + pow(k2.Y - k1.Y, 2) + pow(k2.Z - k1.Z, 2));
}


int main() {

  int n;
  cout << "Unesite broj kugla: ";
  cin >> n;

  vector<shared_ptr<Kugla>> v(n);
  for (int i = 0; i < n; i++) {
    try {
    probajOpet:
      double x = 0, y = 0, z = 0, r = 0;
      cout << "Unesite centar " << i + 1 << ". kugle: ";
      if(!(cin>>x>>y>>z)){
              cin.clear();
              cin.ignore(1000,'\n');
              cout<<"ne valja"<<endl;
              goto probajOpet;
          } 
      v.at(i)=make_shared<Kugla>(x,y,z);
      //v.at(i)->PostaviCentar(x, y, z);
      try {
        cout << "Unesite poluprecnik " << i + 1 << ". kugle: ";
          double temp;
          if(!(cin>>temp)){
              cin.clear();
              cin.ignore(1000,'\n');
              cout<<"Ilegalan poluprecnik"<<endl;
              goto probajOpet;
          } 
          v.at(i)->PostaviPoluprecnik(temp);
      } catch (domain_error &e) {
        cout << e.what() << endl;
        goto probajOpet;
      }

    } catch (range_error &izuzetak) {
      cout << izuzetak.what() << endl;

    }
  }

  int delta_x, delta_y, delta_z;
  cout << "Unesite parametre translacije (delta_x,delta_y,delta_z): ";
  cin >> delta_x >> delta_y >> delta_z;
  transform(v.begin(), v.end(), v.begin(), [&](shared_ptr<Kugla> iterator) {
    iterator->Transliraj(delta_x, delta_y, delta_z);
    return iterator;
  });
  cout << "Kugle nakon obavljenje transformacije imaju sljedece  vrijednosti:"
       << endl;

  sort(v.begin(), v.end(), [](shared_ptr<Kugla> it1, shared_ptr<Kugla> it2) {
    return it1->DajZapreminu() < it2->DajZapreminu();
  });

  for_each(v.begin(), v.end(),
           [](shared_ptr<Kugla> it) { return it->Ispisi(); });

  auto najvecaPovrsina(*max_element(
      v.begin(), v.end(), [](shared_ptr<Kugla> it1, shared_ptr<Kugla> it2) {
        return it1->DajPovrsinu() < it2->DajPovrsinu();
      }));
  cout << "Kugla sa najvecom povrsinom je: ";
  (*najvecaPovrsina).Ispisi();

  int brojac = 0, brojacIspisa=0; 

  vector<pair<shared_ptr<Kugla>, shared_ptr<Kugla>>> parVektora;
  for_each(v.begin(), v.end(), [v,&brojac, &brojacIspisa](shared_ptr<Kugla> k1) {
        brojacIspisa++;
    for_each(v.begin()+brojacIspisa, v.end(), [v,k1, &brojac, &brojacIspisa](shared_ptr<Kugla> k2) {
          if (k1!=k2 && DaLiSeSijeku(*k1, *k2) == true && !k1->DaLiSadrzi(*k2) && !k2->DaLiSadrzi(*k1) ) {
              cout << "Presjecaju se kugle: ";
              k1->Ispisi();
              k2->Ispisi();
              brojac++;
            }
          });
  });




  if (brojac == 0)
    cout << "Ne postoje kugle koje se presjecaju!";

  return 0;
}
