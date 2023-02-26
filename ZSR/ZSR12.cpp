/*-----------------------------------------------*/
/* ZSR12 - ZADATAK 4 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
class VektorNd {
  double* niz;
  int br_koordinata;
public:
  explicit VektorNd(int dimenzija, double value = 0): br_koordinata(dimenzija),
    niz(new double[dimenzija] {}) {
    for (int i = 0; i < br_koordinata; i++)
      niz[i] = value;
  }
  VektorNd(int dimenzija, double* arr): br_koordinata(dimenzija),
    niz(new double[dimenzija]) {
    for (int i = 0; i < dimenzija; i++)
      niz[i] = arr[i];
  }
  ~VektorNd() {delete[] niz;}
  VektorNd(const VektorNd &v);
  VektorNd &operator=(VektorNd &&v);
  int Velicina()const {return br_koordinata;}
  double DajKoordinatu(int i)const {
    if (i < 1 || i > br_koordinata)throw std::domain_error("Neispravna koordinata");
    return niz[i - 1];
  }
  void Postavi(int i, double n) {
    if (i < 1 || i > br_koordinata)throw std::domain_error("Neispravna koordinata");
    niz[i - 1] = n;
  }
  double Duzina()const {
    double suma = 0;
    for (int i = 0; i < br_koordinata; i++)
      suma += niz[i];
    return sqrt(suma);
  }
  friend double DuzinaVektora (const VektorNd &v) {return v.Duzina();}
  int Rang()const {int broj = 0; for (int i = 0; i < br_koordinata; i++)if (niz[i])broj++; return broj;}
  void PromijeniDimenziju(int n);
  friend std::ostream &operator<<(std::ostream &tok, const VektorNd &v);
  friend VektorNd operator+(const VektorNd &a, const VektorNd &b);
  friend VektorNd operator-(const VektorNd &a, const VektorNd &b);
  friend double operator*(const VektorNd &a, const VektorNd &b);
  friend VektorNd operator*(const VektorNd &a, double n);
  friend VektorNd operator*(double n, const VektorNd &a);
  VektorNd &operator+=(const VektorNd &a);
  VektorNd &operator-=(const VektorNd &a);
  VektorNd &operator*=(const VektorNd &a);
  friend VektorNd &operator++(VektorNd &a);
  friend VektorNd operator++(VektorNd &a, int);
  friend bool operator!(VektorNd a);
  friend bool operator==(const VektorNd &a, const VektorNd &b);
  friend bool operator!=(const VektorNd &a, const VektorNd &b);
  friend double Ugao(const VektorNd &a, const VektorNd &b);
};
VektorNd::VektorNd(const VektorNd &v): br_koordinata(v.br_koordinata),
  niz(new double[v.br_koordinata] {}) {
  std::copy(v.niz, v.niz + v.br_koordinata, niz);
}
VektorNd &VektorNd::operator=(VektorNd &&v) {
  if (&v != this) {
    delete[] niz; niz = v.niz; v.niz = nullptr;
    br_koordinata = v.br_koordinata;
  }
  return *this;
}
void VektorNd::PromijeniDimenziju(int n) {
  double* arr = new double[n] {};
  for (int i = 0; i < br_koordinata; i++)
    arr[i] = niz[i];
  delete[] niz; niz = new double[n] {};
  for (int i = 0; i < n; i++)
    niz[i] = arr[i];
  br_koordinata = n;
}
std::ostream &operator<<(std::ostream &tok, const VektorNd &v) {
  tok << "{";
  for (int i = 0; i < v.br_koordinata; i++) {
    tok << v.niz[i];
    if (i != v.br_koordinata - 1)tok << ",";
  }
  tok << "}";
  return tok;
}
VektorNd operator+(const VektorNd &a, const VektorNd &b) {
  if (a.Velicina() != b.Velicina())throw std::domain_error("Nisu iste velicine");
  VektorNd c(a); c += b; return c;
}
VektorNd operator-(const VektorNd &a, const VektorNd &b) {
  if (a.Velicina() != b.Velicina())throw std::domain_error("Nisu iste velicine");
  VektorNd c(a); c -= b; return c;
}
double operator*(const VektorNd &a, const VektorNd &b) {
  if (a.Velicina() != b.Velicina())
    throw std::domain_error("Nisu iste dimenzije");
  double skalarni_produkt = 0;
  for (int i = 0; i < a.Velicina(); i++)
    skalarni_produkt += (a.niz[i] * b.niz[i]);
  return skalarni_produkt;
}
VektorNd operator*(const VektorNd &a, double n) {
  VektorNd c(a.br_koordinata);
  for (int i = 0; i < a.br_koordinata; i++)
    c.niz[i] = a.niz[i] * n;
  return c;
}
VektorNd operator*(double n, const VektorNd &a) {
  VektorNd c(a.br_koordinata);
  for (int i = 0; i < a.br_koordinata; i++)
    c.niz[i] = a.niz[i] * n;
  return c;
}
VektorNd &VektorNd::operator+=(const VektorNd &a) {
  for (int i = 0; i < a.Velicina(); i++)
    niz[i] += a.niz[i];
  return niz;
}
VektorNd &VektorNd::operator-=(const VektorNd &a) {
  for (int i = 0; i < a.Velicina(); i++)
    niz[i] -= a.niz[i];
}
VektorNd &VektorNd::operator*=(const VektorNd &a) {
  for (int i = 0; i < a.Velicina(); i++)
    niz[i] *= a.niz[i];
}
VektorNd &operator++(VektorNd &a) {
  for (int i = 0; i < a.br_koordinata; i++)
    a.niz[i]++;
  return a;
}
VektorNd operator++(VektorNd &a, int) {
  VektorNd pomocni(a);
  ++a;
  return pomocni;
}
bool operator!(VektorNd a) {
  for (int i = 0; i < a.br_koordinata; i++)
    if (a.niz[i] != 0)return false;
  return true;
}
bool operator==(const VektorNd &a, const VektorNd &b) {
  if (a.Velicina() != b.Velicina())return false;
  for (int i = 0; i < a.br_koordinata; i++)
    if (a.niz[i] != b.niz[i])return false;
  return true;
}
bool operator!=(const VektorNd &a, const VektorNd &b) {
  return !(a == b);
}
double Ugao(const VektorNd &a, const VektorNd &b) {
  double skalarni_proizvod = a * b;
  double modul_a = 0, modul_b;
  for (int i = 0; i < a.br_koordinata; i++)
    modul_a += a.niz[i];
  for (int i = 0; i < b.br_koordinata; i++)
    modul_b += b.niz[i];
  modul_a = sqrt(modul_a); modul_b = sqrt(modul_b);
  double ugao = acos(skalarni_proizvod / (modul_a * modul_b));
  return ugao * 180 / (atan(1) * 4);
}
int main() {
  VektorNd v(3, 0.3);
  VektorNd x(3);
  x.Postavi(1, 1); x.Postavi(2, 2); x.Postavi(3, 3);
  x += v; VektorNd y(x * 3); ++y;
  std::cout << Ugao(x, v) << " " << y << " " << (x == y) << " " << !y;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR12 - ZADATAK 6 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
class Polinom {
  std::vector<double>vek;
  void TestIndexa(int i)const {
    if (i < 0 || i > vek.size() - 1)throw std::domain_error("Pogresan index");
  }
public:
  explicit Polinom(int stepen): vek(stepen + 1) {}
  double operator[](int i)const;
  double &operator[](int i);
  double operator()(double x);
  friend Polinom operator+(const Polinom &a, const Polinom &b);
  Polinom &operator+=(const Polinom &a);
  friend Polinom operator-(const Polinom &a, const Polinom &b);
  Polinom &operator-=(const Polinom &a);
  friend Polinom operator*(const Polinom &a, const Polinom &b);
  Polinom &operator*=(const Polinom &a);
  friend Polinom operator/(const Polinom &a, const Polinom &b);
  Polinom &operator/=(const Polinom &a);
  friend Polinom operator%(const Polinom &a, const Polinom &b);
  Polinom &operator%=(const Polinom &a);
  friend bool operator==(const Polinom &a, const Polinom &b);
  friend bool operator!=(const Polinom &a, const Polinom &b);
  friend Polinom operator-(Polinom a);
  friend std::ostream &operator<<(std::ostream &tok, const Polinom &a);
};
double Polinom::operator[](int i)const {TestIndexa(i); return vek[i];}
double &Polinom::operator[](int i) {TestIndexa(i); return vek[i];}
double Polinom::operator()(double x) {
  double suma = 0, p = 1;
  for (int i = 0; i < vek.size(); i++, p *= x)
    suma += vek[i] * p;
  return suma;
}
Polinom operator+(const Polinom &a, const Polinom &b) {
  Polinom c(a.vek.size() - 1);
  c.vek = a.vek; c += b; return c;
}
Polinom &Polinom::operator+=(const Polinom &a) {
  if (a.vek.size() > vek.size())vek.resize(a.vek.size());
  for (int i = 0; i < a.vek.size(); i++)
    vek[i] += a.vek[i];
  return vek;
}
Polinom operator-(const Polinom &a, const Polinom &b) {
  Polinom c(a.vek.size()); c = a; c -= b; return c;
}
Polinom &Polinom::operator-=(const Polinom &a) {
  if (a.vek.size() > vek.size())vek.resize(a.vek.size());
  for (int i = 0; i < a.vek.size(); i++)
    vek[i] -= a.vek[i];
}
Polinom operator*(const Polinom &a, const Polinom &b) {
  Polinom c(a.vek.size()); c = a; c *= b; return c;
}
Polinom &Polinom::operator*=(const Polinom &a) {
  if (a.vek.size() > vek.size())vek.resize(a.vek.size());
  for (int i = 0; i < a.vek.size(); i++)
    vek[i] *= a.vek[i];
}
Polinom operator/(const Polinom &a, const Polinom &b) {
  Polinom c(a.vek.size()); c = a; c /= b; return c;
}
Polinom &Polinom::operator/=(const Polinom &a) {
  if (a.vek.size() > vek.size())vek.resize(a.vek.size());
  for (int i = 0; i < a.vek.size(); i++)
    vek[i] /= a.vek[i];
}
Polinom operator%(const Polinom &a, const Polinom &b) {
  Polinom c(a.vek.size()); c = a; c %= b; return c;
}
Polinom &Polinom::operator%=(const Polinom &a) {
  if (a.vek.size() > vek.size())vek.resize(a.vek.size());
  for (int i = 0; i < a.vek.size(); i++) {
    if (int(vek[i]) == 0 || int(a.vek[i]) == 0 || int(vek[i]) == 0 && int(a.vek[i]) == 0)vek[i] = 0;
    else vek[i] = int(vek[i]) % int(a.vek[i]);
  }
}
bool operator==(const Polinom &a, const Polinom &b) {
  if (a.vek.size() != b.vek.size())return false;
  for (int i = 0; i < a.vek.size(); i++)
    if (b.vek[i] != a.vek[i])return false;
  return true;
}
bool operator!=(const Polinom &a, const Polinom &b) {
  return !(a == b);
}
Polinom operator-(Polinom a) {
  for (int i = 0; i < a.vek.size(); i++)
    a.vek[i] *= (-1);
  return a;
}
std::ostream &operator<<(std::ostream &tok, const Polinom &a) {
  for (int i = 0; i < a.vek.size(); i++) {
    if (i > 0 && a.vek[i] > 0 )tok << " + ";
    if (a.vek[i] < 0)tok << " - ";
    if (a.vek[i] != 0 && fabs(a.vek[i]) != 1)tok << fabs(a.vek[i]);
    if (i > 0 && a.vek[i] != 0) {
      if (fabs(a.vek[i]) != 1)tok << " ";
      tok << "x^" << i;
    }
  }
  return tok;
}
int main() {
  Polinom p(3), x(2), y(0);
  p[0] = 4; p[1] = 5; p[2] = 6; p[3] = 8;
  x[0] = 3; x[1] = 7; x[2] = 1; y[0] = 1;
  std::cout << p << "\n";
  std::cout << -p;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR12 - ZADATAK 7 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
class Polinom {
  double* niz;
  int stepen;
  void TestIndexa(int i)const {
    if (i < 0 || i > stepen)throw std::domain_error("Pogresan index");
  }
public:
  explicit Polinom(int stepen): stepen(stepen), niz(new double[stepen + 1]) {}
  ~Polinom() {delete[] niz;}
  Polinom (const Polinom &p);
  Polinom &operator=(Polinom &&p);
  double operator[](int i)const;
  double &operator[](int i);
  double operator()(double x);
  friend Polinom operator+(const Polinom &a, const Polinom &b);
  Polinom &operator+=(const Polinom &a);
  friend Polinom operator-(const Polinom &a, const Polinom &b);
  Polinom &operator-=(const Polinom &a);
  friend Polinom operator*(const Polinom &a, const Polinom &b);
  Polinom &operator*=(const Polinom &a);
  friend Polinom operator/(const Polinom &a, const Polinom &b);
  Polinom &operator/=(const Polinom &a);
  friend Polinom operator%(const Polinom &a, const Polinom &b);
  Polinom &operator%=(const Polinom &a);
  friend bool operator==(const Polinom &a, const Polinom &b);
  friend bool operator!=(const Polinom &a, const Polinom &b);
  friend Polinom &operator++(Polinom &a);
  friend Polinom operator++(Polinom &a, int);
  friend std::ostream &operator<<(std::ostream &tok, const Polinom &a);
};
Polinom::Polinom(const Polinom &p): stepen(p.stepen),
  niz(new double[p.stepen + 1]) {
  std::copy(p.niz, p.niz + p.stepen + 1, niz);
}
Polinom &Polinom::operator=(Polinom &&p) {
  if (&p != this) {
    delete[] niz; niz = p.niz; p.niz = nullptr;
    stepen = p.stepen;
  }
  return *this;
}
double Polinom::operator[](int i)const {TestIndexa(i); return niz[i];}
double &Polinom::operator[](int i) {TestIndexa(i); return niz[i];}
double Polinom::operator()(double x) {
  double suma = 0, p = 1;
  for (int i = 0; i < stepen + 1; i++, p *= x)
    suma += niz[i] * p;
  return suma;
}
Polinom operator+(const Polinom &a, const Polinom &b) {
  Polinom c(a); c += b; return c;
}
Polinom &Polinom::operator+=(const Polinom &a) {
  if (a.stepen + 1 > stepen + 1)niz = new double[a.stepen + 1];
  for (int i = 0; i < a.stepen + 1; i++)
    niz[i] += a.niz[i];
  return niz;
}
Polinom operator-(const Polinom &a, const Polinom &b) {
  Polinom c(a); c -= b; return c;
}
Polinom &Polinom::operator-=(const Polinom &a) {
  if (a.stepen + 1 > stepen + 1)niz = new double[a.stepen + 1];
  for (int i = 0; i < a.stepen + 1; i++)
    niz[i] -= a.niz[i];
}
Polinom operator*(const Polinom &a, const Polinom &b) {
  Polinom c(a); c *= b; return c;
}
Polinom &Polinom::operator*=(const Polinom &a) {
  if (a.stepen + 1 > stepen + 1)niz = new double[a.stepen + 1];
  for (int i = 0; i < a.stepen + 1; i++)
    niz[i] *= a.niz[i];
}
Polinom operator/(const Polinom &a, const Polinom &b) {
  Polinom c(a); c /= b; return c;
}
Polinom &Polinom::operator/=(const Polinom &a) {
  if (a.stepen + 1 > stepen + 1)niz = new double[a.stepen + 1];
  for (int i = 0; i < a.stepen + 1; i++)
    niz[i] /= a.niz[i];
}
Polinom operator%(const Polinom &a, const Polinom &b) {
  Polinom c(a); c %= b; return c;
}
Polinom &Polinom::operator%=(const Polinom &a) {
  if (a.stepen + 1 > stepen + 1)niz = new double[a.stepen + 1];
  for (int i = 0; i < a.stepen + 1; i++) {
    if (int(niz[i]) == 0 || int(a.niz[i]) == 0 || int(niz[i]) == 0 && int(a.niz[i]) == 0)niz[i] = 0;
    else niz[i] = int(niz[i]) % int(a.niz[i]);
  }
}
bool operator==(const Polinom &a, const Polinom &b) {
  if (a.stepen + 1 != b.stepen + 1)return false;
  for (int i = 0; i < a.stepen + 1; i++)
    if (b.niz[i] != a.niz[i])return false;
  return true;
}
bool operator!=(const Polinom &a, const Polinom &b) {
  return !(a == b);
}
Polinom &operator++(Polinom &a) {
  double *arr = new double[a.stepen + 1] {};
  for (int i = 0; i < a.stepen + 1; i++)
    arr[i] = a.niz[i];
  a.niz = new double[a.stepen + 2] {};
  for (int i = 0; i < a.stepen + 1; i++)
    a.niz[i] = arr[i];
  a.niz[a.stepen + 1] = 0;
  a.stepen++;
  delete[] arr;
  return a;
}
Polinom operator++(Polinom &a, int) {
  Polinom pomocni(a);
  ++a;
  return pomocni;
}
std::ostream &operator<<(std::ostream &tok, const Polinom &a) {
  for (int i = 0; i < a.stepen + 1; i++) {
    if (i > 0 && a.niz[i] > 0)tok << " + ";
    if (i > 0 && a.niz[i] < 0)tok << " - ";
    if (a.niz[i] != 0 && fabs(a.niz[i]) != 1)tok << fabs(a.niz[i]);
    if (i > 0 && a.niz[i] != 0) {
      if (fabs(a.niz[i]) != 1)tok << " ";
      tok << "x^" << i;
    }
  }
  return tok;
}
int main() {
  Polinom p(3);
  p[0] = 3; p[1] = 4; p[2] = 1; p[3] = 8;
  std::cout << p++ << "\n" << p;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR12 - ZADATAK 8 */
#include <iostream>
#include <utility>
#include <cmath>
class Perpleksni {
  std::pair<double, double>broj;
public:
  Perpleksni(double x = 0, double y = 0) {
    broj.first = x; broj.second = y;
  }
  Perpleksni DajRealni() {return broj.first;}
  Perpleksni DajHiperbolni() {return broj.second;}
  friend Perpleksni operator+(const Perpleksni &a, const Perpleksni &b);
  friend Perpleksni operator-(const Perpleksni &a, const Perpleksni &b);
  friend Perpleksni operator*(const Perpleksni &a, const Perpleksni &b);
  friend Perpleksni operator/(const Perpleksni &a, const Perpleksni &b);
  friend bool operator==(const Perpleksni &a, const Perpleksni &b);
  friend bool operator!=(const Perpleksni &a, const Perpleksni &b);
  friend Perpleksni &operator++(Perpleksni &a);
  friend Perpleksni operator++(Perpleksni &a, int);
  friend Perpleksni operator-(Perpleksni a);
  friend std::ostream &operator<<(std::ostream &tok, const Perpleksni &a);
  friend std::istream &operator>>(std::istream &tok, Perpleksni &a);
  friend double DajRealni(const Perpleksni &a) {return a.broj.first;}
  friend double DajHiperbolni(const Perpleksni &a) {return a.broj.second;}
  friend double DajApsolutnu(const Perpleksni &a);
  friend Perpleksni DajKonjugaciju(const Perpleksni &a);
  Perpleksni &operator+=(const Perpleksni &a);
  Perpleksni &operator-=(const Perpleksni &a);
  Perpleksni &operator*=(const Perpleksni &a);
  Perpleksni &operator/=(const Perpleksni &a);
};
Perpleksni operator+(const Perpleksni &a, const Perpleksni &b) {
  Perpleksni c(a.broj.first, a.broj.second); c += b; return c;
}
Perpleksni operator-(const Perpleksni &a, const Perpleksni &b) {
  Perpleksni c(a.broj.first, a.broj.second); c -= b; return c;
}
Perpleksni operator*(const Perpleksni &a, const Perpleksni &b) {
  Perpleksni c(a.broj.first, a.broj.second); c *= b; return c;
}
Perpleksni operator/(const Perpleksni &a, const Perpleksni &b) {
  Perpleksni c(a.broj.first, a.broj.second); c /= b; return c;
}
bool operator==(const Perpleksni &a, const Perpleksni &b) {
  if (a.broj.first == b.broj.first && a.broj.second == b.broj.second)return true; return false;
}
bool operator!=(const Perpleksni &a, const Perpleksni &b) {return !(a == b);}
Perpleksni &operator++(Perpleksni &a) {
  a.broj.first++;
  return a;
}
Perpleksni operator++(Perpleksni &a, int) {
  Perpleksni pomocni(a.broj.first, a.broj.second);
  ++a;
  return pomocni;
}
Perpleksni operator-(Perpleksni a) {
  Perpleksni b(-a.broj.first, -a.broj.second); return b;
}
std::ostream &operator<<(std::ostream &tok, const Perpleksni &a) {
  tok << "(" << a.broj.first << "|" << a.broj.second << ") ";
  return tok;
}
std::istream &operator>>(std::istream &tok, Perpleksni &a) {
  char znak;
  tok >> std::ws;
  if (tok.peek() != '(') {
    tok >> a.broj.first;
    a.broj.second = 0;
  } else {
    tok >> znak >> a.broj.first >> znak;
    if (znak != '|') tok.setstate(std::ios::failbit);
    tok >> a.broj.second >> znak;
    if (znak != ')')tok.setstate(std::ios::failbit);
  }
  return tok;
}
double DajApsolutnu(const Perpleksni &a) {
  if (a.broj.first * a.broj.first >= a.broj.second * a.broj.second)
    return sqrt(a.broj.first * a.broj.first - a.broj.second * a.broj.second);
  else - sqrt(a.broj.first * a.broj.first - a.broj.second * a.broj.second);
}
Perpleksni DajKonjugaciju(const Perpleksni &a) {
  Perpleksni b(a.broj.first, a.broj.second); return -b.broj.second;
}
Perpleksni &Perpleksni::operator+=(const Perpleksni &a) {
  broj.first += a.broj.first; broj.second += a.broj.second;
}
Perpleksni &Perpleksni::operator-=(const Perpleksni &a) {
  broj.first -= a.broj.first; broj.second -= a.broj.second;
}
Perpleksni &Perpleksni::operator*=(const Perpleksni &a) {
  broj.first = broj.first * a.broj.first + broj.second * a.broj.second;
  broj.second = broj.first * a.broj.second + a.broj.second * broj.second;
}
Perpleksni &Perpleksni::operator/=(const Perpleksni &a) {
  broj.first = (broj.first * a.broj.first - broj.second * a.broj.second) /
               (a.broj.first * a.broj.first - a.broj.second * a.broj.second);
  broj.second = (broj.first * a.broj.second - a.broj.second * broj.second) /
                (a.broj.first * a.broj.first - a.broj.second * a.broj.second);
}
int main() {
  Perpleksni p(1, 2), x;
  std::cin >> x;
  p *= x; x += p; p -= x; x /= p;
  x.DajHiperbolni() = 9;
  std::cout << DajApsolutnu(x) << " " << DajKonjugaciju(p) << " " << -x << "\n";
  std::cout << p++ << " " << p;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR12 - ZADATAK 9 */
#include <iostream>
#include <cmath>
class Dualni {
  double x, y;
public:
  Dualni(double vidljivi = 0, double skriveni = 0): x(vidljivi), y(skriveni) {}
  double &DajVidljivi() {return x;}
  double &DajSkriveni() {return y;}
  friend Dualni operator+(const Dualni &a, const Dualni &b) {
    Dualni c(a.x, a.y); c += b; return c;
  }
  friend Dualni operator-(const Dualni &a, const Dualni &b) {
    Dualni c(a.x, a.y); c -= b; return c;
  }
  friend Dualni operator/(const Dualni &a, const Dualni &b) {
    Dualni c(a.x, a.y); c /= b; return c;
  }
  friend Dualni operator*(const Dualni &a, const Dualni &b) {
    Dualni c(a.x, a.y); c *= b; return c;
  }
  Dualni &operator+=(const Dualni &a) {
    x += a.x; y += a.y;
    return *this;
  }
  Dualni &operator-=(const Dualni &a) {
    x -= a.x; y -= a.y; return *this;
  }
  Dualni &operator*=(const Dualni &a) {
    x -= a.x; y = x * a.y + a.x * y; return *this;
  }
  Dualni &operator/=(const Dualni &a) {
    x /= a.x; y = (a.x * y - x * a.y) / (a.x * a.x - a.y * a.y); return *this;
  }
  friend bool operator==(const Dualni &a, const Dualni &b) {
    if (a.x == b.x && a.y == b.y)return true; return false;
  }
  friend bool operator!=(const Dualni &a, const Dualni &b) {
    return !(a == b);
  }
  friend bool operator<(const Dualni &a, const Dualni &b) {
    if (a.x < b.y || a.x == b.x && a.y < b.y)return true; return false;
  }
  friend bool operator<=(const Dualni &a, const Dualni &b) {
    if (a == b || a < b)return true; return false;
  }
  friend bool operator>(const Dualni &a, const Dualni &b) {
    return !(a < b);
  }
  friend bool operator>=(const Dualni &a, const Dualni &b) {
    return !(a <= b);
  }
  friend Dualni &operator++(Dualni &a) {
    a.x++;
    return a;
  }
  friend Dualni operator++(Dualni a, int) {
    Dualni pomocni(a.x, a.y);
    ++a; return pomocni;
  }
  friend Dualni &operator-(Dualni &a) {
    a.x *= -1; a.y *= (-1); return a;
  }
  friend std::ostream &operator<<(std::ostream &tok, const Dualni &a) {
    tok << "<" << a.x << "'" << a.y << "> ";
    return tok;
  }
  friend std::istream &operator>>(std::istream &tok, Dualni &a) {
    tok >> std::ws;
    char znak;
    if (tok.peek() != '<')tok.setstate(std::ios::failbit);
    else {
      tok >> znak >> a.x >> znak;
      if (znak != '\'')tok.setstate(std::ios::failbit);
      tok >> a.y >> znak;
      if (znak != '>')tok.setstate(std::ios::failbit);
    }
    return tok;
  }
  friend double DajVidljivi(const Dualni &a) {return a.x;}
  friend double DajSkriveni(const Dualni &a) {return a.y;}
  friend double DajApsolutnu(const Dualni &a) {
    return fabs(a.x);
  }
  friend Dualni DajKonjugaciju(Dualni a) {
    a.y *= (-1); return a;
  }
};
int main() {
  Dualni a(1, 1), b;
  -a; a++;
  std::cin >> b;
  b += a; a *= b; a -= b; b /= a;
  std::cout << (a == b); if (b <= a)std::cout << b++;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR12 - ZADATAK 11 */
// a)
#include <iostream>
#include <cmath>
class Tacka {
  double x, y, ro, theta;
public:
  Tacka() {x = 0; y = 0;}
  Tacka(double x, double y): x(x), y(y) {}
  void Postavi(double x, double y) {
    this->x = x; this->y = y;
  }
  void PostaviPolarno(double ro, double theta) {
    x = ro * cos(theta); y = ro * sin(theta);
    this->ro = ro; this->theta = theta;
  }
  double DajX() const {return x;}
  double DajY() const {return y;}
  double DajRo() const {return ro;}
  double DajTheta() const {return theta;}
  void PostaviX(double x) {this->x = x;}
  void PostaviY(double y) {this->y = y;}
  void Transliraj(double delta_x, double delta_y) {this->x += delta_x; this->y += delta_y;}
  void Rotiraj(double alpha, const Tacka &centar = Tacka()) {
    this->x = this->x + (centar.x - this->x) * cos(alpha) - (this->y - centar.y) * sin(alpha);
    this->y = centar.y + (this->x - centar.x) * sin(alpha) + (this->y - centar.y) * cos(alpha);
  }
  friend bool operator==(const Tacka &a, const Tacka &b) {
    if (a.x == b.x && a.y == b.y)return true; return false;
  }
  friend bool operator!=(const Tacka &a, const Tacka &b) {
    return !(a == b);
  }
  friend bool operator!(const Tacka&a) {
    if (a.x == 0 && a.y == 0)return true; return false;
  }
  friend double operator-(const Tacka &a, const Tacka &b) {
    return sqrt(a.x * a.x - b.x * b.x + a.y * a.y - b.y * b.y);
  }
};
int main() {
  Tacka a(1, 2), b;
  b.PostaviPolarno(0.2, 1.4);
  b.PostaviX(2); a.PostaviY(3);
  std::cout << b.DajTheta() << " " << b.DajRo() << " "
            << a.DajX() << " " << a.DajY() << " " << a - b << " " << !b;
  return 0;
}
// b)
#include <iostream>
#include <cmath>
class Tacka {
  double ro, theta;
public:
  Tacka() {ro = 0; theta = 0;}
  Tacka(double x, double y): ro(cos(theta) / x), theta(sin(theta) / y) {}
  void Postavi(double x, double y) {
    ro = cos(theta) / x; theta = sin(theta) / y;
  }
  void PostaviPolarno(double ro, double theta) {
    this->ro = ro; this->theta = theta;
  }
  double DajX() const {return ro * cos(theta);}
  double DajY() const {return ro * sin(theta);}
  double DajRo() const {return ro;}
  double DajTheta() const {return theta;}
  void PostaviX(double x) {this->ro = cos(theta) / x;}
  void PostaviY(double y) {this->theta = sin(theta) / y;}
  void Transliraj(double delta_x, double delta_y) {
    double x = cos(theta) / ro; x += delta_x;
    double y = sin(theta) / ro; y += delta_y;
    this->ro = cos(theta) / x; this->theta = sin(theta) / y;
  }
  void Rotiraj(double alpha, const Tacka &centar = Tacka()) {
    double x = cos(theta) / ro;
    double y = sin(theta) / ro;
    double cx = cos(centar.theta) / centar.ro;
    double cy = sin(centar.theta) / centar.ro;
    x = x + (cx - x) * cos(alpha) - (y - cy) * sin(alpha);
    y = cy + (x - cx) * sin(alpha) + (y - cy) * cos(alpha);
    this->ro = cos(theta) / x; this->theta = sin(theta) / y;
  }
  friend bool operator==(const Tacka &a, const Tacka &b) {
    double x1 = cos(a.theta) / a.ro;
    double y1 = sin(a.theta) / a.ro;
    double x2 = cos(b.theta) / b.ro;
    double y2 = sin(b.theta) / b.ro;
    if (x1 == x2 && y1 == y2)return true; return false;
  }
  friend bool operator!=(const Tacka &a, const Tacka &b) {
    return !(a == b);
  }
  friend bool operator!(const Tacka&a) {
    double x = cos(a.theta) / a.ro;
    double y = sin(a.theta) / a.ro;
    if (x == 0 && y == 0)return true; return false;
  }
  friend double operator-(const Tacka &a, const Tacka &b) {
    double x1 = cos(a.theta) / a.ro;
    double y1 = sin(a.theta) / a.ro;
    double x2 = cos(b.theta) / b.ro;
    double y2 = sin(b.theta) / b.ro;
    return sqrt(x1 * x1 - x2 * x2 + y1 * y1 - y2 * y2);
  }
};
int main() {
  Tacka a(1, 2), b;
  b.PostaviPolarno(0.2, 1.4);
  b.PostaviX(2); a.PostaviY(3);
  std::cout << b.DajTheta() << " " << b.DajRo() << " "
            << a.DajX() << " " << a.DajY() << " " << a - b << " " << !b;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR12 - ZADATAK 12 */
#include <iostream>
#include <cmath>
#include <algorithm>
const double e = 0.0001;
class Ugao {
  int d, m, s, z;
public:
  Ugao(int d = 0, int m = 0, int s = 0) {Postavi(d, m, s);}
  void Postavi(int d, int m, int s);
  void Ocitaj(int d, int m, int s);
  void I() {std::cout << d << " " << m << " " << s;}
  double DajStepene()const {return d + m / 60. + s / 3600.;}
  friend Ugao operator-(const Ugao &u);
  friend Ugao operator+( Ugao a, Ugao b) {
    Ugao c(a.d, a.m, a.s); c += b; return c;
  }
  Ugao &operator+=(Ugao &a) {
    Postavi(d + a.d, m + a.m, s + a.s); return *this;
  }
  friend Ugao operator-(Ugao a, Ugao b) {
    Ugao c(a.d, a.m, a.s); c -= b; return c;
  }
  Ugao &operator-=(Ugao &a) {
    Postavi(d - a.d, m - a.m, s - a.s);
    return *this;
  }
  friend Ugao operator*(Ugao a, Ugao b) {
    Ugao c(a.d, a.m, a.s); c *= b; return c;
  }
  Ugao &operator*=(Ugao &a) {
    Postavi(d * a.d, m * a.m, s * a.s); return *this;
  }
  friend Ugao &operator++(Ugao &a) {
    a.s++;
    return a;
  }
  friend Ugao operator++(Ugao &a, int) {
    Ugao pomocni(a.d, a.m, a.s);
    ++a; return pomocni;
  }
  friend bool operator==(const Ugao &a, const Ugao &b) {
    if (fabs(a.DajStepene() - b.DajStepene()) < e)return true; return false;
  }
  friend bool operator!=(const Ugao &a, const Ugao &b) {
    return !(a == b);
  }
  friend bool operator<(const Ugao &a, const Ugao &b) {
    if (fabs(a.DajStepene() - b.DajStepene()) > e)return true; return false;
  }
  friend bool operator>(const Ugao &a, const Ugao &b) {
    if (fabs(a.DajStepene()) - b.DajStepene() < e)return true; return false;
  }
  friend bool operator<=(const Ugao &a, const Ugao &b) {
    if (a == b || a < b)return true; return false;
  }
  friend bool operator>=(const Ugao &a, const Ugao &b) {
    if (a == b || a > b)return true; return false;
  }
  friend std::istream &operator>>(std::istream &tok,  Ugao &u);
  friend std::ostream &operator<<(std::ostream &tok, const Ugao &u);
};
class Uglovi {
  Ugao** niz;
  int br_uglova;
  const int max_br_uglova;
public:
  explicit Uglovi(int max_br_uglova): max_br_uglova(max_br_uglova), br_uglova(0),
    niz(new Ugao * [max_br_uglova]) {}
  ~Uglovi() {delete[]niz;}
  Uglovi(const Uglovi &u): max_br_uglova(u.max_br_uglova), br_uglova(u.br_uglova),
    niz(new Ugao * [u.br_uglova]) {
    try {
      for (int i = 0; i < br_uglova; i++)
        niz[i] = new Ugao(*u.niz[i]);
    } catch (...) {
      for (int i = 0; i < br_uglova; i++)delete niz[i]; delete[] niz; throw;
    }
  }
  Uglovi &operator=(Uglovi &u) {
    if (&u != this) {
      delete[] niz; niz = u.niz; u.niz = nullptr;
      br_uglova = u.br_uglova;
    }
    return *this;
  }
  void Dodaj(int d, int m, int s) {
    if (br_uglova == max_br_uglova)throw std::domain_error("Popunjeno");
    niz[br_uglova] = new Ugao(d, m, s);
    br_uglova++;
  }
  void ObrisiSve() {
    niz = nullptr; br_uglova = 0;
  }
  void Ispisi() {
    for (int i = 0; i < br_uglova; i++)
      std::cout << *niz[i] << std::endl;
  }
  Ugao DajNajmanji()const {
    Ugao* min = niz[0];
    for (int i = 1; i < br_uglova; i++)
      if (niz[i] < min)min = niz[i]; return *min;
  }
  Ugao DajNajveci()const {
    Ugao* max = niz[0];
    for (int i = 1; i < br_uglova; i++)
      if (niz[i] < max)max = niz[i]; return *max;
  }
  int BrojUglova()const {return br_uglova;}
  int BrojOstrih()const {
    int broj = 0;
    for (int i = 0; i < br_uglova; i++)
      if (niz[i]->DajStepene() < 90)broj++; return broj;
  }
  Ugao* operator[]( int i) {
    if (i < 0 || i > br_uglova - 1)throw std::range_error("izvan opsega");
    return niz[i];
  }
};
void Ugao::Postavi(int d, int m, int s) {
  if (d < 0 || m < 0 || s < 0)throw std::domain_error("Negativan parametar");
  this->d = d; this->m = m; this->s = s;
  int povecaj_m = this->s / 60;
  if (this->s > 59)this->s %= 60;
  this->m += povecaj_m;
  int povecaj_d = this->m / 60;
  if (this->m > 59)this->m %= 60;
  this->d += povecaj_d;
  if (this->d > 360) {
    povecaj_d = this->d / 360;
    this->d = this->d - povecaj_d * 360;
  }
}
void Ugao::Ocitaj(int d, int m, int s) {
  d = this->d; m = this->m; s = this->s;
}
Ugao operator-(const Ugao &u) {
  Ugao a(u.d, u.m, u.s);
  a.s = 60 - a.s;
  a.m = 59 - a.m;
  a.d = 359 - a.d;
  return a;
}
std::ostream &operator<<(std::ostream &tok, const Ugao &u) {
  tok << u.d << "d " << u.m << "m " << u.s << "s";
  return tok;
}
std::istream &operator>>(std::istream &tok, Ugao &u) {
  tok >> std::ws;
  char znak; int d, m, s;
  tok >> d >> znak;
  if (znak != 'd')tok.setstate(std::ios::failbit);
  tok >> m >> znak;
  if (znak != 'm')tok.setstate(std::ios::failbit);
  tok >> s >> znak;
  if (znak != 's')tok.setstate(std::ios::failbit);
  u.Postavi(d, m, s);
  return tok;
}
int main() {
  Uglovi u(3);
  u.Dodaj(1, 2, 3); u.Dodaj(4, 5, 6);
  Ugao a(7, 8, 9);
  *u[1] = a;
  u.Ispisi();
  return 0;
}
/*-----------------------------------------------*/
/* ZSR12 - ZADATAK 13 */
#include <iostream>
#include <cmath>
#include <algorithm>
const double PI = 4 * atan(1);
const double e = 0.00001;
class Ugao {
  double radijani;
public:
  Ugao(double rad = 0) {
    Postavi(rad);
  }
  Ugao(int d, int m, int s) {
    Postavi(d, m, s);
  }
  Postavi(double rad) {
    if (rad < 0)radijani = 180 - rad;
    else if (rad > 2 * PI)
      radijani = rad - int(rad / 2 * PI) * 2 * PI;
    else radijani = rad;
  }
  Postavi(int d, int m, int s) {
    if (d < 0 || m < 0 || s < 0)throw std::range_error("Negativan parametar");
    double dd = d + m / 60. + s / 3600.;
    if (dd < 0)dd = 180 - dd;
    if (dd > 360)dd = dd - int(dd / 360) * 360;
    radijani = dd * 180 / PI;
  }
  friend operator-(Ugao u) {
    return 2 * PI - u.radijani;
  }
  friend Ugao &operator++(Ugao &u) {
    double d = u.radijani * PI / 180;
    d++; u.radijani = d * 180 / PI; return u;
  }
  friend Ugao operator++(Ugao &u, int) {
    Ugao pomocni(u.radijani);
    ++u; return pomocni;
  }
  friend Ugao operator+(const Ugao &a, const Ugao &b) {
    Ugao c(a.radijani);
    c += b;
    return c;
  }
  Ugao &operator+=(const Ugao &a) {
    radijani += a.radijani; return *this;
  }
  friend Ugao operator-(const Ugao &a, const Ugao &b) {
    Ugao c(a.radijani); c -= b; return c;
  }
  Ugao &operator-=(const Ugao &a) {
    radijani -= a.radijani; return *this;
  }
  friend Ugao operator*(const Ugao &a, const Ugao &b) {
    Ugao c(a.radijani); c *= b; return c;
  }
  Ugao &operator*=(const Ugao &a) {
    radijani *= a.radijani; return *this;
  }
  friend Ugao operator*(const Ugao a, double broj) {
    return a.radijani * broj;
  }
  friend bool operator<(const Ugao &a, const Ugao &b) {
    return b.radijani - a.radijani > e;
  }
  friend std::ostream &operator<<(std::ostream &tok, const Ugao &a) {
    tok << a.radijani*PI / 180 << "d " << (a.radijani * PI / 180) / 60 << "m " << (a.radijani * PI / 180) / 60 << "s";
    return tok;
  }
  friend std::istream &operator>>(std::istream &tok, Ugao &a) {
    tok >> std::ws;
    char znak; int d, m, s;
    tok >> d >> znak; if (znak != 'd')tok.setstate(std::ios::failbit);
    tok >> m >> znak; if (znak != 'm')tok.setstate(std::ios::failbit);
    tok >> s >> znak; if (znak != 's')tok.setstate(std::ios::failbit);
    return tok;
  }
  double DajRadijane()const {return radijani;}
  double DajStepen() const {return (radijani * PI) / 180;}
  double DajMinute() const {return ((radijani * PI) / 180) / 60;}
  double DajSekunde() const {return ((radijani * PI) / 180) / 3600;}
};
int main() {
  return 0;
}
/*-----------------------------------------------*/
/* ZSR12 - ZADATAK 14 */
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <iomanip>
static const int size_1 = 31;
static const int size_2 = 11;
class Let {
  char odrediste[size_1], oznaka[size_2];
  int br_izlazne_kapije, polazak_h, polazak_m, trajanje_m, kasnjenje_m;
public:
  Let(char naziv[31], char sign[11],
      int broj, int start_h, int start_m, int last, int late): kasnjenje_m(0) {
    if (broj < 0 || start_h < 0 || start_m > 59 || last < 0 || late < 0 || strlen(naziv) > 30 || strlen(sign) > 10)throw std::range_error("Pogresni parametri");
    strcpy(odrediste, naziv);
    strcpy(oznaka, sign);
    br_izlazne_kapije = broj; polazak_h = start_h; polazak_m = start_m; trajanje_m = last; kasnjenje_m = late;
  }
  void PostaviKasnjenje(int kasnjenje) {kasnjenje_m = kasnjenje;}
  bool DaLiKasni() {if (kasnjenje_m)return true; return false;}
  int TrajanjeLeta()const {return trajanje_m;}
  Let OcekivanoPolijetanje()const {
    int m = polazak_m + kasnjenje_m, h;
    int povecaj_h = m / 60;
    if (m > 59)m %= 60;
    Let b("", "", 0, polazak_h + povecaj_h, m, 0, 0); return b;
  }
  Let OcekivanoSlijetanje()const {
    int m = polazak_m + trajanje_m + kasnjenje_m, h;
    int povecaj_h = m / 60;
    if (m > 59)m %= 60;
    Let b("", "", 0, polazak_h + povecaj_h, m, 0, 0); return b;
  }
  friend std::ostream &operator<<(std::ostream &tok, const Let &l) {
    if (l.kasnjenje_m == 0) {
      tok << std::setw(10) << l.oznaka << std::setw(30) << l.odrediste << std::setw(10) << l.polazak_h << ":" << l.polazak_m << std::setw(10) <<
          l.OcekivanoSlijetanje().polazak_h << ":" << l.OcekivanoSlijetanje().polazak_m <<
          std::setw(8) << l.br_izlazne_kapije;
    }
    else {
      Let bez_kasnjenja("", "", 0, l.polazak_h, l.polazak_m, l.trajanje_m, 0);
      tok << std::setw(10) << l.oznaka << std::setw(30) << l.odrediste << std::setw(10) << l.OcekivanoPolijetanje().polazak_h
          << ":" << l.OcekivanoPolijetanje().polazak_m << std::setw(10) << " (Planirano " << l.polazak_h << ":" << l.polazak_m <<
          ", Kasni " << l.kasnjenje_m << " min)"
          << std::setw(10) << l.OcekivanoSlijetanje().polazak_h
          << ":" << l.OcekivanoSlijetanje().polazak_m << std::setw(10) << " (Planirano " << bez_kasnjenja.OcekivanoSlijetanje().polazak_h << ":"
          << bez_kasnjenja.OcekivanoSlijetanje().polazak_m << ", Kasni " << l.kasnjenje_m << " min)" <<
          std::setw(8) << l.br_izlazne_kapije;
    }
    return tok;
  }
  Let operator+( int broj) {
    Let a("", "", 0, 0, 0, 0, 0); a += broj; return a;
  }
  Let &operator+=(int broj) {
    int m = polazak_m + broj;
    int povecaj_h = m / 60;
    if (m > 59)m %= 60;
    polazak_h += povecaj_h; polazak_m = m; return *this;
  }
  friend bool operator!(const Let &l) {if (l.kasnjenje_m)return true; return false;}
  friend Let &operator++(Let &a) {
    a.polazak_h++; return a;
  }
  friend Let operator++(Let &a, int) {
    Let pomocni(a.odrediste, a.oznaka, a.br_izlazne_kapije, a.polazak_h, a.polazak_m, a.trajanje_m, a.kasnjenje_m);
    ++a; return pomocni;
  }
  friend bool operator<(const Let &a, const Let &b) {
    if (a.polazak_h * 60 + a.polazak_m + a.kasnjenje_m < b.polazak_h * 60 + b.polazak_m + b.kasnjenje_m)return true; return false;
  }
  friend bool operator>(const Let &a, const Let &b) {
    if (a.polazak_h * 60 + a.polazak_m + a.kasnjenje_m > b.polazak_h * 60 + b.polazak_m + b.kasnjenje_m)return true; return false;
  }
};
class Letovi {
  int br_letova;
  const int max_br_letova;
  Let** niz;
public:
  explicit Letovi(int max): max_br_letova(max), br_letova(0), niz(new Let * [max]) {}
  ~Letovi() {for (int i = 0; i < br_letova; i++)delete[] niz[i]; delete[] niz;}
  Letovi(const Letovi &l): max_br_letova(l.max_br_letova), br_letova(l.br_letova), niz(new Let * [l.br_letova]) {
    try {
      for (int i = 0; i < br_letova; i++)
        niz[i] = new Let(*l.niz[i]);
    } catch (...) {
      for (int i = 0; i < br_letova; i++)delete niz[i]; delete[] niz;
    }
  }
  Letovi &operator=( Letovi &l) {
    if (br_letova != l.br_letova)throw std::logic_error("Razlicite dimenzije");
    if (&l != this) {
      delete[] niz; niz = l.niz; l.niz = nullptr;
    }
    return *this;
  }
  void Dodaj(Let* let) {
    if (br_letova == max_br_letova)throw std::logic_error("Popunjeno");
    niz[br_letova++] = new Let(*let);
  }
  int DajBrojLetova()const {return br_letova;}
  int DajBrojLetovaKojiKasne() const {
    int broj = 0;
    for (int i = 0; i < br_letova; i++)
      if (!*niz[i])broj++; return broj;
  }
  Let Prvi()const {return *niz[0];}
  Let Posljednji()const {return *niz[br_letova - 1];}
  void Ispisi() const {
    std::cout << std::setw(10) << "Let" << std::setw(10) <<
              "Odrediste" << std::setw(10) << "Polazak" << std::setw(10) << "Dolazak: " << std::setw(10) << "Kapija" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::sort(niz, niz + br_letova, [](Let * a, Let * b) {
      return *a < *b;
    });
    for (int i = 0; i < br_letova; i++)
      std::cout << *niz[i] << std::endl;
  }
};
int main() {
  Let a("New York", "JFK 327", 5, 12, 50, 7 * 60 - 20,  0);
  a += 10;
  Let b("Istanbul", "IST 932", 4, 13, 30, 2 * 60,  20);
  Letovi niz(3);
  niz.Dodaj(&a); niz.Dodaj(&b);
  niz.Ispisi();
  return 0;
}
/*-----------------------------------------------*/
/* ZSR12 - ZADATAK 15 */
#include <iostream>
#include <algorithm>
#include <cstring>
class Polazak {
  char odrediste[21];
  int broj_voza, broj_perona;
  bool vrsta_voza;
  int polazak_h, polazak_m, kasnjenje_m;
public:
  Polazak(char naziv[21], int voz, int peron, bool vrsta, int start_h, int start_m, int late): kasnjenje_m(0) {
    if (strlen(naziv) > 20 || voz < 0 || peron < 0 || start_h < 0 || start_m > 59)throw std::range_error("Pogresni parametri");
    strcpy(odrediste, naziv); broj_voza = voz; broj_perona = peron; vrsta_voza = vrsta;
    polazak_h = start_h; polazak_m = start_m; kasnjenje_m = late;
  }
  void PostaviKasnjenje(int late) {kasnjenje_m = late;}
  bool DaLiKasni()const {if (kasnjenje_m)return true; return false;}
  Polazak OcekivaniPolazak() {
    int m = polazak_m + kasnjenje_m;
    int povecaj_h = m / 60;
    if (m > 59)m %= 60;
    polazak_h += povecaj_h; polazak_m = m; char *c;
    Polazak ocekivani(c, 0, 0, 0, polazak_h, polazak_h, 0); return ocekivani;
  }
  friend std::ostream &operator<<(std::ostream &tok, const Polazak &p) {
    if (p.kasnjenje_m == 0) {
      if (p.vrsta_voza)tok << "Brzi "; else tok << "Lokalni ";
      tok << "voz broj " << p.broj_voza << ", odrediste " << p.odrediste << ", polazi sa perona " << p.broj_perona <<
          " u " << p.polazak_h << ":" << p.polazak_m << ". Putnicima i voznom osoblju zelimo ugodno putovanje.";
    } else {
      if (p.vrsta_voza)tok << "Brzi "; else tok << "Lokalni ";
      tok << "voz broj " << p.broj_voza << ", odrediste " << p.odrediste << ", sa predvidjenim vremenom polaska u " <<
          p.polazak_h << ":" << p.polazak_m << ", kasni oko "
          << p.kasnjenje_m << " minuta. Izvinjavamo se putnicima zbog eventualnih neugodnosti";
    }
  }
  friend bool operator<(const Polazak &a, const Polazak &b) {
    if (a.polazak_h * 60 + a.polazak_m + a.kasnjenje_m < b.polazak_h * 60 + b.polazak_m + b.kasnjenje_m)return true; return false;
  }
  friend bool operator>(const Polazak &a, const Polazak &b) {
    if (a.polazak_h * 60 + a.polazak_m + a.kasnjenje_m > b.polazak_h * 60 + b.polazak_m + b.kasnjenje_m)return true; return false;
  }
};
class RedVoznje {
  int br_registriranih;
  const int max_br_registriranih;
  Polazak **niz;
public:
  explicit RedVoznje(int max): max_br_registriranih(max), br_registriranih(0), niz(new Polazak * [max] {}) {}
  RedVoznje (const RedVoznje &r) = delete;
  RedVoznje (RedVoznje &&r) = delete;
  RedVoznje &operator=(const RedVoznje &r) = delete;
  RedVoznje &operator=(RedVoznje &&r) = delete;
  ~RedVoznje() {for (int i = 0; i < br_registriranih; i++)delete niz[i]; delete[] niz;}
  void Dodaj(Polazak *p) {
    if (br_registriranih == max_br_registriranih)throw std::domain_error("Popunjeno");
    niz[br_registriranih++] = new Polazak(*p);
  }
  void Ispisi()const {
    std::sort(niz, niz + br_registriranih, [](Polazak * a, Polazak * b) {
      return *a < *b;
    });
    for (int i = 0; i < br_registriranih; i++)
      std::cout << *niz[i] << std::endl;
  }
};
int main() {
  char aa[] = "abc", bb[] = "def";
  Polazak a(aa, 1, 5, true, 12, 30, 0), b(bb, 2, 7, false, 7, 30, 20);
  RedVoznje red(2); red.Dodaj(&a); red.Dodaj(&b);
  red.Ispisi();
  return 0;
}
/*-----------------------------------------------*/
/* ZSR12 - ZADATAK 16 */
#include <iostream>
#include <algorithm>
#include <cstring>
class Pregled {
  std::string ime, prezime;
  int dan, mjesec, vrijeme_h, vrijeme_m;
public:
  Pregled(std::string name, std::string surname, int d, int mj, int h, int m) {
    int broj_dana[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mj < 0 || mj > 12 || d < 0 || d > broj_dana[mj - 1] || h < 0 || m > 59)throw std::domain_error("Pogresni parametri");
    ime = name; prezime = surname; dan = d; mjesec = mj; vrijeme_h = h; vrijeme_m = m;
  }
  std::string Ime()const {return ime;}
  std::string Prezime()const {return prezime;}
  int Dan()const {return dan;}
  int Mjesec()const {return mjesec;}
  int Sati()const {return vrijeme_h;}
  int Minute()const {return vrijeme_m;}
  friend std::ostream &operator<<(std::ostream &tok, const Pregled &p) {
    std::cout << p.ime << " " << p.prezime << " " << p.dan << "/" << p.mjesec << " " << p.vrijeme_h << ":" << p.vrijeme_m << std::endl; return tok;
  }
  friend bool operator<(const Pregled &a, const Pregled &b) {
    if (a.mjesec != b.mjesec) {
      return a.mjesec < b.mjesec;
    }
    if (a.dan != b.dan) {
      return a.dan < b.dan;
    }
    return a.vrijeme_h * 60 + a.vrijeme_m < b.vrijeme_h * 60 + b.vrijeme_m;
  }
  friend Pregled &operator++(Pregled &p) {
    p.dan++; return p;
  }
  friend Pregled operator++(Pregled &p, int) {
    Pregled pomocni(p.ime, p.prezime, p.dan, p.mjesec, p.vrijeme_h, p.vrijeme_m);
    ++p; return pomocni;
  }
  friend Pregled &operator--(Pregled &p) {
    p.dan--; return p;
  }
  friend Pregled operator--(Pregled &p, int) {
    Pregled pomocni(p.ime, p.prezime, p.dan, p.mjesec, p.vrijeme_h, p.vrijeme_m);
    --p; return pomocni;
  }
  friend Pregled operator+(const Pregled &p, int n) {
    if (n < 0)throw std::domain_error("Negativan");
    Pregled b(p.ime, p.prezime, p.dan, p.mjesec, p.vrijeme_h, p.vrijeme_m);
    b += n; return b;
  }
  Pregled &operator+=( int n) {
    if (n < 0)throw std::domain_error("Negativan");
    for (int i = 0; i < n; i++)
      ++*this; return *this;
  }
};
class Pregledi {
  int br_pregleda;
  const int max_br_pregleda;
  Pregled **niz;
public:
  explicit Pregledi(int max): max_br_pregleda(max), br_pregleda(0), niz(new Pregled * [max] {}) {}
  ~Pregledi() {for (int i = 0; i < br_pregleda; i++)delete niz[i]; delete[] niz;}
  Pregledi(const Pregledi &p): max_br_pregleda(p.max_br_pregleda), br_pregleda(p.br_pregleda), niz(new Pregled * [p.max_br_pregleda] {}) {
    try {
      for (int i = 0; i < br_pregleda; i++)niz[i] = new Pregled(*p.niz[i]);
    } catch (...) {
      for (int i = 0; i < br_pregleda; i++)delete[] niz; delete[] niz;
    }
  }
  Pregledi &operator=(Pregledi &p) {
    if (&p != this) {
      delete[] niz; niz = p.niz; p.niz = nullptr; br_pregleda = p.br_pregleda;
    }
    return *this;
  }
  void Dodaj(std::string name, std::string surname, int d, int mj, int h, int m) {
    if (br_pregleda == max_br_pregleda)throw std::logic_error("Popunjeno");
    niz[br_pregleda++] = new Pregled(name, surname, d, mj, h, m);
  }
  void Sortiraj() {
    std::sort(niz, niz + br_pregleda, [](Pregled * a, Pregled * b) {
      return *a < *b;
    });
  }
  void UkoloniNajraniji() {
    if (br_pregleda == 0)throw std::logic_error("prazna");
    Pregled *min = niz[0];
    for (int i = 1; i < br_pregleda; i++)
      if (*niz[i] < *min)min = niz[i];
    for (int i = 0; i < br_pregleda; i++)
      if (niz[i] == min) {
        for (int j = i + 1; j < br_pregleda; j++)
          niz[j - 1] = niz[j];
        i--;
        br_pregleda--;
      }
  }
  void IspisiSveSaDatuma(int d, int m) {
    int broj = 0;
    for (int i = 0; i < br_pregleda; i++)
      if (niz[i]->Dan() != d && niz[i]->Mjesec() != m)broj++;
    if (broj == br_pregleda)throw std::logic_error("nema pregleda na tom datumu");
    for (int i = 0; i < br_pregleda; i++)
      if (niz[i]->Dan() == d && niz[i]->Mjesec() == m)
        std::cout << *niz[i] << std::endl;
  }
  friend std::ostream &operator<<(std::ostream &tok, const Pregledi &p) {
    if (p.br_pregleda == 0)throw std::logic_error("prazna");
    for (int i = 0; i < p.br_pregleda; i++)
      std::cout << *p.niz[i] << std::endl; return tok;
  }
  friend bool operator!(const Pregledi &p) {if (p.br_pregleda == 0)return true; return false;}
  Pregled* &operator[](int i) {
    return niz[i];
  }
};
int main() {
  Pregled a("ab", "cd", 1, 5, 7, 30);
  //std::cout<<a<<std::endl;
  a += 5; Pregled b = a;
  Pregledi p(3);
  p.Dodaj("ab", "cd", 1, 5, 7, 30);
  *p[0] = b;
  std::cout << *p[0];
  return 0;
}
/*-----------------------------------------------*/
/* ZSR12 - ZADATAK 17 */
#include <iostream>
#include <algorithm>
#include <cstring>
struct Osoba {
  char ime[21], prezime[21], odjeljenje[11];
  int broj_telefona;
  Osoba(char name[21], char surname[21], char razred[11], int number) {
    if (strlen(name) > 20 || strlen(surname) > 20 || strlen(razred) > 10)throw std::domain_error("Predugacki podaci");
    strcpy(ime, name); strcpy(prezime, surname); strcpy(odjeljenje, razred); broj_telefona = number;
  }
  friend std::ostream &operator<<(std::ostream &tok, const Osoba &o) {
    tok << o.ime << " " << o.prezime << " " << o.odjeljenje << " " << o.broj_telefona; return tok;
  }
};
class Imenik {
  int br_osoba;
  const int max_br_osoba;
  Osoba **niz;
public:
  Imenik(int max): max_br_osoba(max), br_osoba(0), niz(new Osoba * [max] {}) {}
  ~Imenik() {for (int i = 0; i < br_osoba; i++)delete niz[i]; delete[] niz;}
  Imenik(const Imenik &p): max_br_osoba(p.max_br_osoba), br_osoba(p.br_osoba),
    niz(new Osoba * [p.max_br_osoba] {}) {
    try {
      for (int i = 0; i < br_osoba; i++) niz[i] = new Osoba(*p.niz[i]);
    } catch (...) {
      for (int i = 0; i < br_osoba; i++)delete niz[i]; delete[] niz;
    }
  }
  Imenik &operator=(Imenik &p) {
    if (&p != this) {
      delete[] niz; niz = p.niz; p.niz = nullptr; br_osoba = p.br_osoba;
    } return *this;
  }
  void Dodaj(char name[21], char surname[21], char razred[11], int number) {
    if (br_osoba == max_br_osoba)throw std::domain_error("Popunjeno");
    niz[br_osoba++] = new Osoba(name, surname, razred, number);
  }
  void IspisiImePrezime(char *name, char *surname) {
    for (int i = 0; i < br_osoba; i++)
      if (strcpy(niz[i]->ime, name) && strcpy(niz[i]->prezime, surname) == 0)std::cout << *niz[i] << std::endl;
  }
  void IspisiBroj(int broj) {
    for (int i = 0; i < br_osoba; i++)
      if (niz[i]->broj_telefona == broj)std::cout << *niz[i] << std::endl;
  }
  void IspisiIme(char *name) {
    for (int i = 0; i < br_osoba; i++)
      if (strcmp(niz[i]->ime, name) == 0)std::cout << *niz[i] << std::endl;
  }
  void IspisiOdjeljenje(char *razred) {
    for (int i = 0; i < br_osoba; i++)
      if (strcmp(niz[i]->odjeljenje, razred) == 0)std::cout << *niz[i] << std::endl;
  }
  void Ispisi() {
    for (int i = 0; i < br_osoba; i++)
      std::cout << *niz[i] << std::endl;
  }
  void Sortiraj() {
    std::sort(niz, niz + br_osoba, [](Osoba * a, Osoba * b) {
      if (strcmp(a->prezime, b->prezime) != 0)return a->prezime > b->prezime;
      return a->ime > b->ime;
    });
  }
  int &operator[](char *name) {
    for (int i = 0; i < br_osoba; i++)
      if (strcmp(niz[i]->ime, name) == 0)return niz[i]->broj_telefona;
  }
  int operator[](const char *name)const {
    for (int i = 0; i < br_osoba; i++)
      if (strcmp(niz[i]->ime, name) == 0)return niz[i]->broj_telefona;
  }
};
int main() {
  Imenik i(2);
  i.Dodaj("b", "bb", "bbb", 2);
  i.Dodaj("a", "bb", "aaa", 1);
  i.Sortiraj();
  const char c[2] = "b"; char cc[2] = "a";
  std::cout << i[c];
  i[cc] = 5;
  i.Ispisi();
  return 0;
}
/*-----------------------------------------------*/
/* ZSR12 - ZADATAK 18 */
#include <iostream>
#include <string>
#include <algorithm>
class Rjecnik {
  std::string **niz;
  int br_rijeci;
  const int max_br_rijeci;
public:
  explicit Rjecnik(int max): max_br_rijeci(max), br_rijeci(0), niz(new std::string * [max] {}) {}
  ~Rjecnik() {for (int i = 0; i < br_rijeci; i++)delete niz[i]; delete[] niz;}
  Rjecnik(const Rjecnik &r): max_br_rijeci(r.max_br_rijeci), br_rijeci(r.br_rijeci), niz(new std::string * [r.max_br_rijeci] {}) {
    try {
      for (int i = 0; i < br_rijeci; i++)niz[i] = new std::string(*r.niz[i]);
    } catch (...) {
      for (int i = 0; i < br_rijeci; i++)delete niz[i]; delete[] niz;
    }
  }
  Rjecnik &operator=(Rjecnik &r) {
    if (&r != this) {
      delete[] niz; niz = r.niz; r.niz = nullptr; br_rijeci = r.br_rijeci;
    } return *this;
  }
  void Dodaj(std::string rijec) {
    for (char c : rijec)if (c == ' ')throw std::logic_error("ne moze recenica");
    if (br_rijeci == max_br_rijeci)throw std::logic_error("popunjeno");
    niz[br_rijeci++] = new std::string(rijec);
  }
  int DajBrojRijeci()const {return br_rijeci;}
  void ObrisiSve() {
    niz = nullptr; br_rijeci = 0;
  }
  int DajBrojRijeciSlovo(char c) {
    int broj = 0;
    for (int i = 0; i < br_rijeci; i++) {
      if (br_rijeci == 0)throw std::domain_error("nema rijeci");
      std::string s = *niz[i];
      if (s[0] == c)broj++;
    } return broj;
  }
  void Ispisi() {
    std::sort(niz, niz + br_rijeci, [](std::string * a, std::string * b) {
      return *a < *b;
    });
    for (int i = 0; i < br_rijeci; i++)
      std::cout << *niz[i] << std::endl;
  }
  friend Rjecnik operator+(const Rjecnik &x, std::string y) {
    Rjecnik z(x); z += y; return z;
  }
  Rjecnik &operator+=(std::string y) {
    for (int i = 0; i < br_rijeci; i++)
      *niz[i] += y; return *this;
  }
  friend Rjecnik &operator++(Rjecnik &r) {
    for (int i = 0; i < r.br_rijeci; i++)
      *r.niz[i] += '*'; return r;
  }
  friend Rjecnik &operator++(Rjecnik &r, int) {
    Rjecnik pomocni(r); ++r; return pomocni;
  }
  friend bool operator==(const Rjecnik &a, const Rjecnik &b) {
    if (a.br_rijeci != b.br_rijeci)return false;
    for (int i = 0; i < a.br_rijeci; i++)
      if (*a.niz[i] != *b.niz[i])return false;
    return true;
  }
  friend bool operator!=(const Rjecnik &a, const Rjecnik &b) {
    return !(a == b);
  }
};
int main() {
  Rjecnik r(3);
  r.Dodaj("def");
  r.Dodaj("abc") ;
  //r.ObrisiSve();
  std::string s = "---";
  r += s; r++;
  r.Ispisi();
  Rjecnik a(r);
  std::cout << r.DajBrojRijeciSlovo('a') << (r != a);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR12 - ZADATAK 19 */
#include <iostream>
#include <string>
#include <algorithm>
class Knjiga {
  int evidencijski_broj, godina, clanski_broj, koliko;
  std::string naslov, pisac, zanr;
public:
  Knjiga(int eviden_num, int year, int clan_num, int how_much, std::string name, std::string writer, std::string type):
    evidencijski_broj(eviden_num), godina(year), clanski_broj(clan_num), koliko(how_much), naslov(name), pisac(writer), zanr(type) {}
  int DajEvidencijskiBroj()const {return evidencijski_broj;}
  int DajGodinu()const {return godina;}
  int DajClanskiBroj()const {return clanski_broj;}
  int DajKoliko()const {return koliko;}
  std::string DajNaslov()const {return naslov;}
  std::string DajPisca()const {return pisac;}
  std::string DajZanr()const {return zanr;}
  void ProglasiZaduzenom(int clan_num) {
    clanski_broj = clan_num; koliko = 0;
  }
  void Razduzi() {clanski_broj = 0;}
  friend bool operator!(const Knjiga &k) {if (k.clanski_broj)return true; return false;}
  friend Knjiga &operator++(Knjiga &k) {
    if (!k)k.koliko++;
    return k;
  }
  friend Knjiga &operator++(Knjiga &k, int) {
    Knjiga pomocna(k.evidencijski_broj, k.godina, k.clanski_broj, k.koliko, k.naslov, k.pisac, k.zanr); ++k; return pomocna;
  }
  friend bool operator==(const Knjiga &a, const Knjiga &b) {
    if (a.naslov == b.naslov && a.pisac == b.pisac && a.zanr == b.zanr && a.godina == b.godina)return true; return false;
  }
  friend bool operator!=(const Knjiga &a, const Knjiga &b) {
    return !(a == b);
  }
  friend std::ostream &operator<<(std::ostream &tok, const Knjiga &k) {
    tok << k.evidencijski_broj << " " << k.naslov << " " << k.pisac << " " << k.zanr << " " << k.godina << "koliko " << k.koliko; return tok;
  }
};
class Biblioteka {
  int br_knjiga;
  const int max_br_knjiga;
  Knjiga **niz;
public:
  explicit Biblioteka(int max): br_knjiga(0), max_br_knjiga(max), niz(new Knjiga * [max] {}) {}
  void Dodaj(Knjiga *k) {niz[br_knjiga++] = new Knjiga(*k);}
  void Zaduzi(int eviden_num, int clan_num) {
    int broj = 0;
    for (int i = 0; i < br_knjiga; i++)
      if (niz[i]->DajEvidencijskiBroj() != eviden_num)broj++;
    if (broj == br_knjiga)throw std::logic_error("Nema te knjige");
    for (int i = 0; i < br_knjiga; i++)
      if (niz[i]->DajEvidencijskiBroj() == eviden_num)
        niz[i]->ProglasiZaduzenom(clan_num);
  }
  void Razduzi(int eviden_num, int clan_num) {
    int broj = 0;
    for (int i = 0; i < br_knjiga; i++)
      if (niz[i]->DajEvidencijskiBroj() != eviden_num)broj++;
    if (broj == br_knjiga)throw std::logic_error("Nema te knjige");
    for (int i = 0; i < br_knjiga; i++)
      if (niz[i]->DajEvidencijskiBroj() == eviden_num)
        niz[i]->Razduzi();
  }
  bool JeLiZaduzena(int eviden_num) {
    int broj = 0;
    for (int i = 0; i < br_knjiga; i++)
      if (niz[i]->DajEvidencijskiBroj() != eviden_num)broj++;
    if (broj == br_knjiga)throw std::logic_error("Nema te knjige");
    for (int i = 0; i < br_knjiga; i++)
      if (!*niz[i])return true;
    return false;
  }
  int DajClanskiBrojOdZaduzene(int eviden_num) {
    int broj = 0;
    for (int i = 0; i < br_knjiga; i++)
      if (niz[i]->DajEvidencijskiBroj() != eviden_num)broj++;
    if (broj == br_knjiga)throw std::logic_error("Nema te knjige");
    for (int i = 0; i < br_knjiga; i++)
      if (niz[i]->DajEvidencijskiBroj() == eviden_num)
        return niz[i]->DajClanskiBroj();
    return 0;
  }
  void IspisiSlobodne() {
    for (int i = 0; i < br_knjiga; i++)
      if (!!*niz[i])std::cout << *niz[i] << std::endl;
  }
  void IspisiZaduzene() {
    for (int i = 0; i < br_knjiga; i++)
      if (!*niz[i])std::cout << *niz[i] << std::endl;
  }
  void IspisiZaduzeneZaNDana(int n) {
    for (int i = 0; i < br_knjiga; i++)
      if (niz[i]->DajKoliko() == n)std::cout << *niz[i] << std::endl;
  }
  void Sortiraj() {
    std::sort(niz, niz + br_knjiga, [](Knjiga * a, Knjiga * b) {
      if (a->DajNaslov() == b->DajNaslov())
        return a->DajKoliko() > b->DajKoliko();
      return a->DajNaslov() < b->DajNaslov();
    });
  }
  Knjiga* &operator[](int eviden_num) {
    for (int i = 0; i < br_knjiga; i++)
      if (niz[i]->DajEvidencijskiBroj() == eviden_num)return niz[i];
  }
  friend Biblioteka &operator++(Biblioteka &b) {
    for (int i = 0; i < b.br_knjiga; i++)
      ++*b.niz[i];
    return b;
  }
};
int main() {
  Knjiga a(1, 2022, 0, 2, "abc", "aaa", "zzz");
  Knjiga b(2, 2022, 543, 3, "abc", "bbb", "ppp");
  Knjiga c(3, 2022, 78, 5, "abc", "bbb", "ppp");
  Biblioteka lib(3);
  lib.Dodaj(&a); lib.Dodaj(&b); lib.Dodaj(&c);
  lib.Sortiraj();
  ++lib;
  lib.IspisiZaduzeneZaNDana(2);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR12 - ZADATAK 22 */
#include <iostream>
class Vrijeme {
  int h, m, s;
public:
  Vrijeme(int hh, int mm, int ss) {
    Postavi(hh, mm, ss);
  }
  Vrijeme(): h(0), m(0), s(0) {}
  void Postavi(int hh, int mm, int ss) {
    int povecaj_m = ss / 60;
    if (ss > 59)ss %= 60;
    s = ss;
    mm += povecaj_m;
    int povecaj_h = mm / 60;
    if (mm > 59)mm %= 60;
    m = mm;
    hh += povecaj_h;
    if (hh > 24) {
      int smanji_h = hh / 24;
      hh = hh - smanji_h * 24;
    }
    h = hh;
  }
  int DajH()const {return h;}
  int DajM()const {return m;}
  int DajS()const {return s;}
  void Ocitaj(int &hh, int &mm, int &ss) {
    hh = h; mm = m; ss = s;
  }
  friend Vrijeme operator+(const Vrijeme &a, const Vrijeme &b) {
    Vrijeme c(a.h, a.m, a.s); c += b; return c;
  }
  Vrijeme &operator+=(const Vrijeme &a) {
    Postavi(h + a.h, m + a.m, s + a.s); return *this;
  }
  friend Vrijeme operator-(const Vrijeme &a, const Vrijeme &b) {
    Vrijeme c(a.h, a.m, a.s); c -= b; return c;
  }
  Vrijeme &operator-=(const Vrijeme &a) {
    Postavi(h - a.h, m - a.m, s - a.s); return *this;
  }
  friend Vrijeme operator*(const Vrijeme &a, const Vrijeme &b) {
    Vrijeme c(a.h, a.m, a.s); c *= b; return c;
  }
  Vrijeme &operator*=(const Vrijeme &a) {
    Postavi(h * a.h, m * a.m, s * a.s); return *this;
  }
  friend Vrijeme operator-(const Vrijeme &a) {
    Vrijeme b; b.s = 60 - a.s; b.m = 59 - a.m; b.h = 23 - a.h; return b;
  }
  friend Vrijeme &operator++(Vrijeme &a) {
    a.s++; return a;
  }
  friend Vrijeme operator++(Vrijeme &a, int) {
    Vrijeme pomocno(a.h, a.m, a.s); ++a; return pomocno;
  }
  friend bool operator==(const Vrijeme &a, const Vrijeme &b) {
    return (a.h == b.h && a.m == b.m && a.s == b.s);
  }
  friend bool operator!=(const Vrijeme &a, const Vrijeme &b) {
    return !(a == b);
  }
  friend bool operator<(const Vrijeme &a, const Vrijeme &b) {
    return (a.h * 3600 + a.m * 60 + a.s < b.h * 3600 + b.m * 60 + b.s);
  }
  friend bool operator<=(const Vrijeme &a, const Vrijeme &b) {
    return (a < b || a == b);
  }
  friend bool operator>(const Vrijeme &a, const Vrijeme &b) {
    return (a.h * 3600 + a.m * 60 + a.s > b.h * 3600 + b.m * 60 + b.s);
  }
  friend bool operator>=(const Vrijeme &a, const Vrijeme &b) {
    return (a > b || a == b);
  }
  friend std::ostream &operator<<(std::ostream &tok, const Vrijeme &a) {
    tok << a.h << "h " << a.m << "m " << a.s << "s"; return tok;
  }
};
class Podsjetnik {
  int br_vremena;
  const int max_br_vremena;
  Vrijeme **niz;
public:
  Podsjetnik(int max): max_br_vremena(max), br_vremena(0), niz(new Vrijeme * [max] {}) {}
  ~Podsjetnik() {for (int i = 0; i < br_vremena; i++)delete niz[i]; delete[] niz;}
  Podsjetnik(const Podsjetnik &a): max_br_vremena(a.max_br_vremena), br_vremena(a.br_vremena),
    niz(new Vrijeme * [a.max_br_vremena] {}) {
    try {
      for (int i = 0; i < br_vremena; i++)niz[i] = new Vrijeme(*a.niz[i]);
    } catch (...) {
      for (int i = 0; i < br_vremena; i++)delete niz[i]; delete[] niz; throw;
    }
  }
  Podsjetnik &operator=(Podsjetnik &a) {
    if (&a != this) {
      delete[] niz; niz = a.niz; a.niz = nullptr; br_vremena = a.br_vremena;
    } return *this;
  }
  void Dodaj(int hh, int mm, int ss) {
    if (br_vremena == max_br_vremena)throw std::domain_error("Popunjeno");
    niz[br_vremena++] = new Vrijeme(hh, mm, ss);
  }
  void ObrisiSve() {
    niz = nullptr; br_vremena = 0;
  }
  void Ispisi()const {
    for (int i = 0; i < br_vremena; i++)std::cout << *niz[i] << std::endl;
  }
  Vrijeme DajNajmanje()const {
    Vrijeme *min = niz[0];
    for (int i = 0; i < br_vremena; i++)
      if (*niz[i] < *min)min = niz[i];
    return *min;
  }
  Vrijeme DajNajvece()const {
    Vrijeme *max = niz[0];
    for (int i = 0; i < br_vremena; i++)
      if (*niz[i] < *max)max = niz[i];
    return *max;
  }
  int DajBrojVremena()const {return br_vremena;}
  int DajBrojVremenaPoslijePodne()const {
    int broj = 0;
    for (int i = 0; i < br_vremena; i++)
      if (niz[i]->DajH() == 12 && niz[i]->DajM() > 0 || niz[i]->DajH() > 12)broj++;
    return broj;
  }
  Vrijeme* &operator[](int i) {return niz[i];}
};
int main() {
  Podsjetnik p(2);
  p.Dodaj(1, 2, 3); p.Dodaj(3, 4, 5);
  p.Ispisi();
  Vrijeme v(54, 0, 0);
  std::cout << v;
  return 0;
}
/*-----------------------------------------------*/
