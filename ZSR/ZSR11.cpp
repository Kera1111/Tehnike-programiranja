/*-----------------------------------------------*/
/* ZSR11 - ZADATAK 2 */
#include <iostream>
#include <algorithm>
class Temperature {
  double* niz;
  const int max_br_elemenata;
  int br_elemenata;
public:
  explicit Temperature(int max): max_br_elemenata(max), br_elemenata(0), niz(new double[max]) {}
  ~Temperature() {delete[] niz;}
  Temperature(const Temperature &t);
  Temperature &operator=(Temperature &&t);
  void Dodaj(double t);
  void ObrisiSve();
  double DajProsjecnu() const;
  double DajMaksimalnu() const;
  double DajMinimalnu() const;
  void Ispisi();
};
Temperature::Temperature(const Temperature &t): max_br_elemenata(t.max_br_elemenata)
  , br_elemenata(t.br_elemenata), niz(new double[t.br_elemenata]) {
  std::copy(t.niz, t.niz + t.br_elemenata, niz);
}
Temperature &Temperature::operator=(Temperature &&t) {
  if (&t != this) {
    delete[] niz; niz = t.niz; t.niz = nullptr;
    br_elemenata = t.br_elemenata;
  }
  return *this;
}
void Temperature::Dodaj(double t) {
  if (br_elemenata + 1 > max_br_elemenata)throw std::domain_error("Nema mjesta više");
  niz[br_elemenata++] = t;
}
void Temperature::ObrisiSve() {
  niz = nullptr;
  br_elemenata = 0;
}
double Temperature::DajMaksimalnu()const {
  double max = niz[0];
  for (int i = 1; i < br_elemenata; i++)
    if (niz[i] > max)max = niz[i];
  return max;
}
double Temperature::DajMinimalnu()const {
  double min = niz[0];
  for (int i = 1; i < br_elemenata; i++)
    if (niz[i] < min)min = niz[i];
  return min;
}
double Temperature::DajProsjecnu()const {
  double suma = 0;
  for (int i = 1; i < br_elemenata; i++)
    suma += niz[i];
  return suma / br_elemenata;
}
void Temperature::Ispisi() {
  for (int i = 0; i < br_elemenata; i++)
    std::cout << niz[i] << " ";
}
int main() {
  Temperature t(4);
  t.Dodaj(1); t.Dodaj(2); t.Dodaj(3);
  std::cout << t.DajMaksimalnu() << " " << t.DajMinimalnu() << " " << t.DajProsjecnu() << "\n";
  t.ObrisiSve();
  t.Ispisi();
  return 0;
}
/*-----------------------------------------------*/
/* ZSR11 - ZADATAK 5 */
/*-----------------------------------------------*/
/* ZSR11 - ZADATAK 11 */
#include <iostream>
#include <string>
class Zahtjev {
  std::string ime, prezime, tekst;
  int index, dan, mjesec, godina;
public:
  Zahtjev(std::string ime, std::string prezime, std::string tekst, int index, int dan, int mjesec, int godina)
    : ime(ime), prezime(prezime), tekst(tekst), index(index) {
    int broj_dana[] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (godina % 4 == 0 && godina % 100 != 0 || godina % 400 == 0)broj_dana[1]++;
    if (godina < 1 || mjesec < 1 || mjesec > 12 || dan < 1 || dan > broj_dana[mjesec - 1])
      throw std::domain_error("Neispravan datum");
    this->dan = dan; this->mjesec = mjesec; this->godina = godina;
  }
  void Ispisi()const {
    std::cout << ime << " " << prezime << " " << tekst << " "
              << index << " " << dan << "/" << mjesec << "/" << godina << std::endl;
  }
};
class Zahtjevi {
  Zahtjev** niz{};
  const int max_br_zahtjeva;
  int br_zahtjeva;
  int brojac_ispisa = 0;
public:
  Zahtjevi(int max): max_br_zahtjeva(max), br_zahtjeva(0), niz(new Zahtjev * [max] {}) {}
  ~Zahtjevi() {}
  Zahtjevi(const Zahtjevi &z);
  Zahtjevi &operator=(Zahtjevi &&z);
  Dodaj(std::string ime, std::string prezime, std::string tekst,
        int index, int dan, int mjesec, int godina);
  void IspisiObrisi();
  bool Test()const {if (br_zahtjeva)return true; return false;}
};
Zahtjevi::Zahtjevi(const Zahtjevi &z): max_br_zahtjeva(z.max_br_zahtjeva), br_zahtjeva(z.br_zahtjeva),
  niz(new Zahtjev * [z.br_zahtjeva] {}) {
  try {
    for (int i = 0; i < br_zahtjeva; i++)
      niz[i] = new Zahtjev(*z.niz[i]);
  } catch (...) {
    for (int i = 0; i < br_zahtjeva; i++)delete[] niz[i]; delete[] niz;
    throw;
  }
}
Zahtjevi &Zahtjevi::operator=(Zahtjevi &&z) {
  delete[] niz; niz = z.niz; z.niz = nullptr;
  br_zahtjeva = z.br_zahtjeva;
}
Zahtjevi::Dodaj(std::string ime, std::string prezime, std::string tekst,
                int index, int dan, int mjesec, int godina) {
  if (br_zahtjeva + 1 > max_br_zahtjeva)throw std::domain_error("Nema mjesta vise");
  niz[br_zahtjeva++] = new Zahtjev(ime, prezime, tekst, index, dan, mjesec, godina);
}
void Zahtjevi::IspisiObrisi() {
  niz[brojac_ispisa]->Ispisi();
  niz[brojac_ispisa] = nullptr;
  brojac_ispisa++;
  br_zahtjeva--;
}

int main() {
  Zahtjevi z(3);
  z.Dodaj("abc", "ABC", "dodaj 1", 11111, 1, 1, 2020);
  z.Dodaj("def", "DEF", "dodaj 2", 22222, 2, 2, 2021);
  z.Dodaj("ghi", "GHI", "dodaj 3", 33333, 3, 3, 2022);
  z.IspisiObrisi();
  z.IspisiObrisi();
  std::cout << z.Test();
  return 0;
}
/*-----------------------------------------------*/
/* ZSR11 - ZADATAK 20 */
#include <iostream>
#include <algorithm>
#include <cmath>
struct Tjeme {
  double x, y;
};
class Poligon {
  double *x, *y;
  int br_tjemena;
public:
  explicit Poligon(int broj);
  ~Poligon();
  Poligon(const Poligon &p);
  Poligon &operator=(Poligon &&p);
  int DajBrojTjemena()const;
  int PostaviKoordinate(int index, double x, double y);
  Tjeme operator[](int i);
  double DajPovrsinu()const;
  bool Test()const;
};
Poligon::Poligon(int broj) {
  if (broj < 3)throw std::domain_error("Pogresan broj tjemena");
  br_tjemena = broj; x = new double[broj] {}; y = new double[broj] {};
}
Poligon::~Poligon() {
  delete x; delete y;
}
Poligon::Poligon(const Poligon &p): br_tjemena(p.br_tjemena),
  x(new double[p.br_tjemena]), y(new double[p.br_tjemena]) {
  std::copy(p.x, p.x + p.br_tjemena, x);
  std::copy(p.y, p.y + p.br_tjemena, y);
}
Poligon &Poligon::operator=(Poligon &&p) {
  delete x; delete y; x = p.x; y = p.y; p.x = nullptr; p.y = nullptr; br_tjemena = p.br_tjemena;
}
int Poligon::DajBrojTjemena()const {return br_tjemena;}
int Poligon::PostaviKoordinate(int index, double x, double y) {
  if (index < 1 || index > br_tjemena)throw std::domain_error("Pogresan index");
  this->x[index - 1] = x; this->y[index - 1] = y;
}
Tjeme Poligon::operator[](int i) {
  Tjeme t;
  t.x = Poligon::x[i - 1]; t.y = Poligon::y[i - 1];
  return t;
}
double Poligon::DajPovrsinu()const {
  double suma = 0;
  for (int i = 0; i < br_tjemena - 2; i++)
    suma += (x[i] * y[i + 1] - x[i + 1] * y[i]);
  double rez = 0.5 * fabs(x[br_tjemena - 1] * y[0] - x[0] * y[br_tjemena - 1] + suma);
  return rez;
}
bool Poligon::Test()const {
  for (int i = 0; i < br_tjemena; i++)
    for (int j = i + 1; j < br_tjemena; j++)
      if (x[i] == x[j] && y[i] == y[j])return true;
  return false;
}
int main() {
  Poligon p(3);
  p.PostaviKoordinate(1, 1, 2);
  p.PostaviKoordinate(2, 3, 4);
  p.PostaviKoordinate(3, 5, 6);
  std::cout << p[1].x << " " << p[1].y << " ";
  Poligon x(p);
  std::cout << p.DajPovrsinu() << " " << x.DajPovrsinu();
  return 0;
}
/*-----------------------------------------------*/
/* ZSR11 - ZADATAK 30 */
#include <iostream>
#include <vector>
#include <algorithm>
template<typename tip>
class Skup {
  std::vector<tip>vek{};
public:
  Skup() {vek.clear();}
  Skup(std::initializer_list<tip> s) {
    auto it = s.begin();
    while (it != s.end()) {
      int found = 0;
      for (int j = 0; j < vek.size(); j++)
        if (*it == vek[j])found++;
      if (found == 0)vek.push_back(*it);
      it++;
    }
    std::sort(vek.begin(), vek.end());
  }
  int Velicina()const {return vek.size();}
  void Dodaj(tip n) {
    int found = 0;
    for (int j = 0; j < vek.size(); j++)
      if (n == vek[j])found++;
    if (found == 0)vek.push_back(n);
    std::sort(vek.begin(), vek.end());
  }
  void Izbrisi(tip n) {
    for (int j = 0; j < vek.size(); j++)
      if (n == vek[j])vek.erase(vek.begin() + j);
  }
  bool ImaLiga(tip n) {for (auto i : vek)if (i == n)return true; return false;}
  void Ispisi()const {for (auto i : vek)std::cout << i << " ";}
};

int main() {
  Skup<int>s({8, 7, 1, 2, 2, 3, 2, 4, 4, 6, 5});
  s.Izbrisi(3);
  s.Ispisi();
  return 0;
}
/*-----------------------------------------------*/