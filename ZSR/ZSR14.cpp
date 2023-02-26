/*-----------------------------------------------*/
/* ZSR14 - ZADATAK 7 */
#include <iostream>
#include <fstream>
int main() {
  /*Kreiranje potrebne datoteke
  std::ofstream izlaz("brojevi.dat", std::ios::binary);
  double niz[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  izlaz.write(reinterpret_cast<char*>(niz), sizeof niz);
  izlaz.close();*/
  std::ifstream ulaz("brojevi.dat", std::ios::binary);
  ulaz.seekg(0, std::ios::end);
  int duzina_datoteke = ulaz.tellg();
  int broj_elemenata = duzina_datoteke / sizeof(double);
  for (int i = broj_elemenata - 1; i >= 0; i--) {
    double broj;
    ulaz.seekg(i * sizeof(double));
    ulaz.read(reinterpret_cast<char*>(&broj), sizeof broj);
    std::cout << broj << " ";
  }
  ulaz.close();
  return 0;
}
/*-----------------------------------------------*/
/* ZSR14 - ZADATAK 8 */
#include <iostream>
#include <fstream>
#include <cmath>
int main() {
  std::fstream file("korijeni.dat", std::ios::trunc | std::ios::in | std::ios::out | std::ios::binary);
  int a, b;
  std::cin >> a >> b;
  for (int i = a; i <= b; i++) {
    double broj = sqrt(i);
    file.write(reinterpret_cast<char*>(&broj), sizeof broj);
  }
  file.seekg(0, std::ios::end);
  int duzina_datoteke = file.tellg();
  int broj_elemenata = duzina_datoteke / sizeof(double);
  for (int i = 0; i < broj_elemenata; i++) {
    double broj;
    file.seekg(i * sizeof (double));
    file.read(reinterpret_cast<char*>(&broj), sizeof broj);
    broj++;
    file.seekp(i * sizeof (double));
    file.write(reinterpret_cast<char*>(&broj), sizeof broj);
  }
  // nakon izmjene
  file.seekg(0, std::ios::end);
  duzina_datoteke = file.tellg();
  broj_elemenata = duzina_datoteke / sizeof(double);
  for (int i = broj_elemenata - 1; i >= 0; i--) {
    double broj;
    file.seekg(i * sizeof (double));
    file.read(reinterpret_cast<char*>(&broj), sizeof broj);
    std::cout << broj << " ";
  }
  file.close();
  return 0;
}
/*-----------------------------------------------*/
/* ZSR14 - ZADATAK 9 */
#include <iostream>
#include <fstream>
#include <cmath>
void IzvrniDatoteku(std::string datoteka) {
  std::fstream file(datoteka, std::ios::in | std::ios::out | std::ios::binary);
  std::cout << "Izvnorna datoteka:" << std::endl;
  file.seekg(0, std::ios::end);
  int duzina_datoteke = file.tellg();
  int broj_elemenata = duzina_datoteke / sizeof(double);
  for (int i = 0; i < broj_elemenata; i++) {
    double broj;
    file.seekg(i * sizeof(double));
    file.read(reinterpret_cast<char*>(&broj), sizeof(broj));
    std::cout << broj << " ";
  }
  for (int i = 0; i < broj_elemenata / 2; i++) {
    double a, b;
    file.seekg(i * sizeof(double));
    file.read(reinterpret_cast<char*>(&a), sizeof a);
    file.seekg(-((i + 1)*sizeof(double)), std::ios::end);
    file.read(reinterpret_cast<char*>(&b), sizeof b);
    file.seekp(i * sizeof(double));
    file.write(reinterpret_cast<char*>(&b), sizeof b);
    file.seekp(-((i + 1)*sizeof(double)), std::ios::end);
    file.write(reinterpret_cast<char*>(&a), sizeof a);
  }
  std::cout << "\nNakon izvrtanja: " << std::endl;
  for (int i = 0; i < broj_elemenata; i++) {
    double broj;
    file.seekg(i * sizeof(double));
    file.read(reinterpret_cast<char*>(&broj), sizeof(broj));
    std::cout << broj << " ";
  }
  file.close();
}
int main() {
  IzvrniDatoteku("korijeni.dat");
  return 0;
}
/*-----------------------------------------------*/
/* ZSR14 - ZADATAK 16 */
#include <iostream>
#include <algorithm>
#include <fstream>
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
  void Snimi(std::string datoteka)const;
  void Obnovi(std::string datoteka);
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
void Temperature::Snimi(std::string datoteka)const {
  std::ofstream izlaz(datoteka, std::ios::binary);
  izlaz.write(reinterpret_cast<const char*>(this), sizeof * this);
  if (!izlaz.write(reinterpret_cast<char*>(niz), br_elemenata * sizeof niz[0]))
    throw std::logic_error("Nesto nije u redu sa upisom");
}
void Temperature::Obnovi(std::string datoteka) {
  std::ifstream ulaz(datoteka, std::ios::binary);
  if (!ulaz)throw std::logic_error("Datoteka ne postoji");
  delete[] niz;
  ulaz.read(reinterpret_cast<char*>(this), sizeof * this);
  niz = new double[max_br_elemenata] {};
  if (!ulaz.read(reinterpret_cast<char*>(niz), br_elemenata * sizeof niz[0])) {
    delete[] niz;
    throw std::logic_error("Nesto nije u redu sa citanjem");
  }
}
int main() {
  Temperature t(4), tt(3);
  t.Dodaj(1); t.Dodaj(2); t.Dodaj(3);
  tt.Dodaj(5); tt.Dodaj(6); tt.Dodaj(7);
  std::cout << t.DajMaksimalnu() << " " << t.DajMinimalnu() << " " << t.DajProsjecnu() << "\n";
  //t.ObrisiSve();
  t.Ispisi();
  t.Snimi("temperature.dat");
  tt.Obnovi("temperature.dat");
  return 0;
}
/*-----------------------------------------------*/
/* ZSR14 - ZADATAK 20 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
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
  int DajBrojKoordinata()const {return br_koordinata;}
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
  return *this;
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
  int n;
  std::cout << "n: "; std::cin >> n;
  VektorNd** niz = new VektorNd*[n] {};
  int broj_elemenata = 0;
  try {
    for (int i = 0; i < n; i++) {
      int broj;
      std::cout << "broj koordinata: "; std::cin >> broj;
      VektorNd temp(broj);
      for (int j = 0; j < broj; j++) {
        double x;
        std::cout << j + 1 << ". koordinata: "; std::cin >> x;
        temp.Postavi(j + 1, x);
      }
      niz[broj_elemenata++] = new VektorNd(temp);
    }
  } catch (...) {
    for (int i = 0; i < n; i++)delete niz[i]; delete[] niz;
  }
  std::sort(niz, niz + n, [](VektorNd * a, VektorNd * b) {return a->DajBrojKoordinata() < b->DajBrojKoordinata();});
  std::ofstream izlaz("vektori.txt");
  if (!izlaz)throw std::logic_error("Kreiranje datoteke nije uspjelo");
  else
    for (int i = 0; i < n; i++) {
      izlaz << *niz[i] << std::endl;
    }
  izlaz.close();
  return 0;
}
/*-----------------------------------------------*/
/* ZSR14 - ZADATAK 21 */
#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
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
  void IspisiNaIzlazniTok(std::string tok);
  void Snimi(std::string datoteka)const;
  void Obnovi(std::string datoteka);
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
void Uglovi::IspisiNaIzlazniTok(std::string tok) {
  std::ofstream izlaz(tok);
  for (int i = 0; i < br_uglova; i++)
    izlaz << *niz[i] << std::endl;
  izlaz.close();
}
void Uglovi::Snimi(std::string datoteka)const {
  std::ofstream izlaz(datoteka, std::ios::binary);
  izlaz.write(reinterpret_cast<const char*>(this), sizeof * this);
  for (int i = 0; i < br_uglova; i++)
    izlaz.write(reinterpret_cast<char*>(niz[i]), sizeof * niz[i]);
  if (!izlaz)throw std::logic_error("Problem sa upisom");
}
void Uglovi::Obnovi(std::string datoteka) {
  std::ifstream ulaz(datoteka, std::ios::binary);
  if (!ulaz)throw std::logic_error("Datoteka ne postoji");
  for (int i = 0; i < br_uglova; i++)delete niz[i]; delete[] niz;
  ulaz.read(reinterpret_cast<char*>(this), sizeof * this);
  niz = new Ugao*[max_br_uglova] {};
  try {
    for (int i = 0; i < br_uglova; i++) {
      niz[i] = new Ugao;
      ulaz.read(reinterpret_cast<char *>(niz[i]), sizeof * niz[i]);
    }
    if (!ulaz)throw std::logic_error("Problem sa citanjem");
  } catch (...) {
    for (int i = 0; i < br_uglova; i++)delete niz[i]; delete[] niz; throw;
  }
}
int main() {
  Uglovi u(3);
  u.Dodaj(1, 2, 3); u.Dodaj(4, 5, 6);
  Ugao a(7, 8, 9);
  *u[1] = a;
  u.IspisiNaIzlazniTok("uglovi.txt");
  u.Snimi("uglovi.dat");
  return 0;
}
/*-----------------------------------------------*/
/* ZSR14 - ZADATAK 22 */
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
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
  std::fstream file("rijeci.txt", std::ios::in | std::ios::out);
  int broj = 0;
  std::string rijec;
  while (std::getline(file, rijec))broj++;
  file.clear(); file.seekg(0);
  Rjecnik r(broj);
  while (std::getline(file, rijec)) {
    r.Dodaj(rijec);
  }
  std::string s = "!";
  r += s;
  r.Ispisi();
  return 0;
}
/*-----------------------------------------------*/
/* ZSR14 - ZADATAK 23 */
#include <iostream>
#include <fstream>
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
  void Snimi(std::string datoteka)const {
    std::ofstream izlaz(datoteka, std::ios::binary);
    izlaz.write(reinterpret_cast<const char*>(this), sizeof * this);
    for (int i = 0; i < br_vremena; i++)
      izlaz.write(reinterpret_cast<char*>(niz[i]), sizeof * niz[i]);
    if (!izlaz)throw std::logic_error("Problem sa upisom");
  }
  void Obnovi(std::string datoteka) {
    std::ifstream ulaz(datoteka, std::ios::binary);
    if (!ulaz)throw std::logic_error("Datoteka ne postoji");
    delete[] niz;
    ulaz.read(reinterpret_cast<char*>(this), sizeof * this);
    niz = new Vrijeme*[max_br_vremena] {};
    try {
      for (int i = 0; i < br_vremena; i++) {
        niz[i] = new Vrijeme;
        ulaz.read(reinterpret_cast<char*>(niz[i]), sizeof * niz[i]);
      }
      if (!ulaz)throw std::logic_error("Problem sa citanjem");
    } catch (...) {
      for (int i = 0; i < br_vremena; i++)delete niz[i]; delete[]niz; throw;
    }
  }
};
int main() {
  Podsjetnik p(2);
  p.Dodaj(1, 2, 3); p.Dodaj(3, 4, 5);
  p.Ispisi();
  Vrijeme v(54, 0, 0);
  std::cout << v;
  p.Snimi("podsjetnik.dat");
  return 0;
}
/*-----------------------------------------------*/
/* ZSR14 - ZADATAK 27 */
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <cstdlib>
const double PI=4*atan(1);
class ApstraktniLik{
  int brojac;
  std::string naziv;
public:
  ApstraktniLik(std::string name):brojac(1),naziv(name){}
  int DajBrojac()const{return brojac;}
  std::string DajNaziv()const{return naziv;}
  virtual double DajObim()const =0;
  friend std::ostream &operator<<(std::ostream &tok, const ApstraktniLik &a){
    tok<<"Lik: "<<a.naziv<<" Obim: "<<a.DajObim(); return tok;
  }
  friend bool operator<(const ApstraktniLik &a, const ApstraktniLik &b){
    return a.DajObim()<b.DajObim();
  }
  friend bool operator>(const ApstraktniLik &a, const ApstraktniLik &b){
    return a.DajObim()>b.DajObim();
  }
  friend ApstraktniLik &operator++(ApstraktniLik &a){
    a.brojac++; return a;
  }
};
class Krug:public ApstraktniLik{
  int r;
public:
  Krug(int poluprecnik):r(poluprecnik), ApstraktniLik("Krug"){}
  double DajObim()const override{return 2*r*PI;}
};
class Pravougaonik:public ApstraktniLik{
  int a,b;
public:
  Pravougaonik(int prva, int druga):a(prva),b(druga),ApstraktniLik("Pravougaonik"){}
  double DajObim()const override{return 2*(a+b);}
};
class Trougao:public ApstraktniLik {
  int a,b,c;
public:
  Trougao(int prva, int druga, int treca):a(prva),b(druga),c(treca),ApstraktniLik("Trougao"){}
  double DajObim()const override{return a+b+c;}
};
class Likovi{
  int br_likova;
  const int max_br_likova;
  ApstraktniLik **niz;
  template<typename tip>
  void TestPrijeDodavanja(tip l){
  if(br_likova==max_br_likova)throw std::domain_error("Popunjeno");
  for(int i=0;i<br_likova;i++)
    if(niz[i]->DajObim()==l.DajObim())++l;
  }
public:
  Likovi(int max):max_br_likova(max),br_likova(0),niz(new ApstraktniLik*[max]{}){}
  Likovi(const Likovi &l):max_br_likova(l.max_br_likova),br_likova(l.max_br_likova),
  niz(new ApstraktniLik*[l.max_br_likova]{}){}
  ~Likovi(){ for(int i=0;i<br_likova;i++)delete niz[i]; delete[] niz;}
  void DodajKrug(int r){
  TestPrijeDodavanja(Krug(r));
  niz[br_likova++]=new Krug(r);
  }
  void DodajPravougaonik(int a, int b){
  TestPrijeDodavanja(Pravougaonik(a,b));
  niz[br_likova++]=new Pravougaonik(a,b);
  }
  void DodajTrougao(int a, int b, int c){
  TestPrijeDodavanja(Trougao(a,b,c));
  niz[br_likova++]=new Trougao(a,b,c);
  }
  int DajBrojLikova()const{return br_likova;}
  ApstraktniLik* DajNajveci(){
  ApstraktniLik *max=niz[0];
  for(int i=0;i>br_likova;i++)
    if(niz[i]->DajObim()>max->DajObim())max=niz[i];
  return max;
  }
  int DajBrojKrugova()const{
  return std::count_if(niz, niz+br_likova,[](ApstraktniLik *a){
  return typeid(*a)==typeid(Krug);
  });
  }
  void Sortiraj(){
  std::sort(niz, niz+br_likova,[](ApstraktniLik *a, ApstraktniLik *b){
     return *a>*b;});
  }
  friend bool operator!(const Likovi &l){if(l.br_likova==0)return false; return true;}
  friend std::ostream &operator<<(std::ostream &tok, const Likovi &l){
  for(int i=0;i<l.br_likova;i++)
    tok<<*l.niz[i]<<std::endl; return tok;
  }
};
int CharToInt(int n){
return abs(n-'0');}
int main() {
  int broj;
  std::ifstream ulaz("likovi.txt");
  ulaz>>broj;
  Likovi L(broj);
  std::string rijec;
  while(std::getline(ulaz,rijec)){
    if(rijec[0]=='K'){
      std::string t;
      int i=1;
      while(rijec[i]>='0'&&rijec[i]<='9')
      t+=rijec[i++];
      int r=std::stoi(t);
      L.DodajKrug(r);
    }
    if(rijec[0]=='P'){
    std::string t;
      int i=1;
      while(rijec[i]>='0'&&rijec[i]<='9')
      t+=rijec[i++];
      int a=std::stoi(t);
      if(rijec[i]==',')i++;
      t.clear();
      while(rijec[i]>='0'&&rijec[i]<='9')
      t+=rijec[i++];
      int b=std::stoi(t);
      L.DodajPravougaonik(a,b);
    }
     if(rijec[0]=='T'){
      std::string t;
      int i=1;
      while(rijec[i]>='0'&&rijec[i]<='9')
      t+=rijec[i++];
      int a=std::stoi(t);
      if(rijec[i]==',')i++;
      t.clear();
      while(rijec[i]>='0'&&rijec[i]<='9')
      t+=rijec[i++];
      int b=std::stoi(t);
      if(rijec[i]==',')i++;
      t.clear();
      while(rijec[i]>='0'&&rijec[i]<='9')
      t+=rijec[i++];
      int c=std::stoi(t);
      L.DodajTrougao(a,b,c);
    }
  }
  ulaz.close();
  L.Sortiraj();
  std::cout<<L;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR14 - ZADATAK 28 */
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
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
  friend bool operator!(const Knjiga &k) {if (k.clanski_broj!=0)return true; return false;}
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
class Udzbenik:public Knjiga{
std::string predmet;
public:
  std::string &DajPredmet(){return predmet;}
  Udzbenik(int eviden_num, int year, int clan_num, int how_much,
           std::string name, std::string writer, std::string type, std::string subject):Knjiga(eviden_num,year,clan_num,how_much,
                             name, writer,type),predmet(subject){}
   friend std::ostream &operator<<(std::ostream &tok, const Udzbenik &k) {
    tok << k.DajEvidencijskiBroj() << " " <<k.predmet<<" "<< k.DajNaslov() << " " << k.DajPisca()
    << " " << k.DajZanr() << " " << k.DajGodinu() << "koliko " <<
    k.DajKoliko()<<k.predmet;
    return tok;
  }
};
class Biblioteka {
  int br_knjiga;
  const int max_br_knjiga;
  Knjiga **niz;
public:
  explicit Biblioteka(int max): br_knjiga(0), max_br_knjiga(max), niz(new Knjiga * [max] {}) {}
  void Dodaj(Knjiga *k) {niz[br_knjiga++] = new Knjiga(*k);}
  void Dodaj(Udzbenik *k) {niz[br_knjiga++] = new Udzbenik(*k);}
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
      if (niz[i]->DajKoliko() )std::cout << *niz[i] << std::endl;
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
  int broj=0;
  std::ifstream ulaz("knjige.txt");
  if(!ulaz)throw std::logic_error("Datoteka ne postoji");
  std::string eviden_num;
  while(std::getline(ulaz,eviden_num)){
  bool udzbenik=false;
  int godina, clan_num; std::string naslov,pisac,zanr,predmet;
  if(eviden_num[0]=='U')udzbenik=true;
  std::getline(ulaz,naslov);
  std::getline(ulaz,pisac);
  std::getline(ulaz,zanr);
  ulaz>>godina;
  ulaz.ignore(1000,'\n');
  if(udzbenik)std::getline(ulaz,predmet);
  broj++;
  }
  ulaz.clear(); ulaz.seekg(0);
  // Ucitavanje iz datoteke
  Biblioteka lib(broj);
  eviden_num.clear();
  while(std::getline(ulaz,eviden_num)){
  bool udzbenik=false;
  int godina, clan_num; std::string naslov,pisac,zanr,predmet;
  if(eviden_num[0]=='U')udzbenik=true;
  std::getline(ulaz,naslov);
  std::getline(ulaz,pisac);
  std::getline(ulaz,zanr);
  ulaz>>godina;
  ulaz.ignore(1000,'\n');
  int eviden;
  if(udzbenik){
        std::getline(ulaz,predmet);
         eviden=std::stoi(eviden_num.substr(1));
  }
  else{
    eviden=std::stoi(eviden_num);
  }
  std::ifstream zaduzenja("zaduzenja.txt");
  std::string trenutni_eviden_num;int trenutni_clan_num; char znak;
  while(std::getline(zaduzenja,trenutni_eviden_num)){
   zaduzenja>>znak;
   zaduzenja>>trenutni_clan_num;
   bool book=false;
   if(trenutni_eviden_num[0]=='U')book=true;
   int trenutni;
   if(book){
   trenutni=std::stoi(trenutni_eviden_num.substr(1));
   }else{
   trenutni=std::stoi(trenutni_eviden_num);}
    zaduzenja.ignore(1000,'\n');
    if(eviden==trenutni){
      if(udzbenik){
        Udzbenik k(eviden,godina,trenutni_clan_num,1,naslov,pisac,zanr,predmet);
        lib.Dodaj(&k);
      }
      else{
        Knjiga k(eviden,godina,trenutni_clan_num,1,naslov,pisac,zanr);
        lib.Dodaj(&k);
      }
    }
    else{
      if(udzbenik){
        Udzbenik k(eviden,godina,0,0,naslov,pisac,zanr,predmet);
        lib.Dodaj(&k);
      }
      else{
        Knjiga k(eviden,godina,0,0,naslov,pisac,zanr);
        lib.Dodaj(&k);
      }
    }
  }
  zaduzenja.close();
  }
  ulaz.close();
  lib.IspisiZaduzene();
  std::cout<<std::endl;
  lib.IspisiSlobodne();
  return 0;
}
/*-----------------------------------------------*/
/* ZSR14 - ZADATAK 29 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
class KutijaApstraktna{
  double tezina_kutije;
  public:
  KutijaApstraktna(double t):tezina_kutije(t){}
  double DajTezinu()const{return tezina_kutije;}
  virtual double DajUkupnuTezinu()const=0;
};
class KutijaObicna:public KutijaApstraktna{
  double tezina_sadrzaja;
  public:
  KutijaObicna(double t, double s):KutijaApstraktna(t),tezina_sadrzaja(s){}
  double DajUkupnuTezinu()const override{return DajTezinu()+tezina_sadrzaja;}
};
class KutijaSaPregradama:public KutijaApstraktna{
  std::vector<double>vek;
  public:
  KutijaSaPregradama(double t,std::vector<double>s):KutijaApstraktna(t),vek(s){}
  double DajUkupnuTezinu()const override{
    double suma=0;
    for(double i:vek)
      suma+=i;
    return suma+DajTezinu();
  }
};
int main() {
  KutijaApstraktna** niz;
  std::ifstream ulaz("kutije.txt");
  int broj=-1; // jer prvi red je broj elemenata
  std::string red;
  while(std::getline(ulaz,red))broj++;
  int broj_elemenata=0;
  niz=new KutijaApstraktna*[broj]{};
  ulaz.clear(); ulaz.seekg(0);
  while(std::getline(ulaz,red)){
    if(red[0]=='K'){
       std::string a,b; int i=1;
      while(red[i]>='0'&&red[i]<='9')
        a+=red[i++];
      if(red[i]==' ')i++;
        while(red[i]>='0'&&red[i]<='9')
        b+=red[i++];
        double tezina_kutije=std::stoi(a),tezina_sadrzaja=std::stoi(b);
      niz[broj_elemenata++]=new KutijaObicna(tezina_kutije, tezina_sadrzaja);
    }
    if(red[0]=='P'){
            std::string a,b; int i=1;
      while(red[i]>='0'&&red[i]<='9')
        a+=red[i++];
      if(red[i]==' ')i++;
        while(red[i]>='0'&&red[i]<='9')
        b+=red[i++];
       double tezina_kutije=std::stoi(a);
       int broj_sadrzaja=std::stoi(b);
      std::vector<double>tezina_sadrzaja;
      if(red[i]==' ')i++;
      for(int j=0;j<broj_sadrzaja;j++){
            a.clear();
        while(red[i]>='0'&&red[i]<='9')
        a+=red[i++];
        if(red[i]==' ')i++;
        double x=std::stoi(a);
        tezina_sadrzaja.push_back(x);
      }
      niz[broj_elemenata++]=new KutijaSaPregradama(tezina_kutije, tezina_sadrzaja);
    }
  }
  ulaz.close();
  std::sort(niz,niz+broj,[](KutijaApstraktna *a, KutijaApstraktna *b){
            return a->DajUkupnuTezinu()<b->DajUkupnuTezinu();});
   for(int i=0;i<broj;i++) std::cout<<niz[i]->DajTezinu()<<std::endl;
 for(int i=0;i<broj;i++)delete niz[i]; delete[] niz;
   return 0;
}
/*-----------------------------------------------*/
/* ZSR14 - ZADATAK 30 */
#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
const double PI=4*atan(1);
class Predmet{
  double gustina;
public:
  Predmet(double g):gustina(g){}
  virtual double DajZapreminu()const=0;
  double DajMasu()const{return gustina*DajZapreminu();}
};
class Lopta:public Predmet{
double r;
public:
  Lopta(double g, double poluprecnik):Predmet(g),r(poluprecnik){}
  double DajZapreminu()const override{return 4*PI*r*r*r/3;}
};
class Cigla:public Predmet{
  double a,b,c;
public:
  Cigla(double g, double a,double b,double c):Predmet(g),a(a),b(b),c(c){}
  double DajZapreminu()const override{return a*b*c;}
};
int main() {
  int broj=-1;
  std::string datoteka;
  std::cout<<"Unesite ime datoteke: "; std::cin>>datoteka;
  std::ifstream ulaz(datoteka);
  if(!ulaz)throw std::logic_error("Datoteka ne postoji");
  std::string red;
  while(std::getline(ulaz,red))broj++;
  Predmet **niz=new Predmet*[broj]{};
  int broj_elemenata=0;
  ulaz.clear(); ulaz.seekg(0);
  std::getline(ulaz,red); // prvi red sa brojem
  while(std::getline(ulaz,red)){
    if(red[0]=='L'){
      std::string t;
      int i=1;
      while(red[i]>='0'&&red[i]<='9')
        t+=red[i++];
      if(red[i]=='.'){
        i++;
        while(red[i]>='0'&&red[i]<='9')
        t+=red[i++];
      }
      double g=std::stod(t); t.clear();
        if(red[i]==' ')i++;
        while(red[i]>='0'&&red[i]<='9')
        t+=red[i++];
      if(red[i]=='.'){
        i++;
        while(red[i]>='0'&&red[i]<='9')
        t+=red[i++];
      }
      double r=std::stod(t);
      if(g<=0||r<=0)throw std::logic_error("Neispravan format datoteke");
      niz[broj_elemenata++]=new Lopta(g,r);
    }
    else if(red[0]=='C'){
      std::string t;
      int i=1;
      while(red[i]>='0'&&red[i]<='9')
        t+=red[i++];
      if(red[i]=='.'){
        i++;
        while(red[i]>='0'&&red[i]<='9')
        t+=red[i++];
      }
      double g=std::stod(t); t.clear();
        if(red[i]==' ')i++;
        while(red[i]>='0'&&red[i]<='9')
        t+=red[i++];
      if(red[i]=='.'){
        i++;
        while(red[i]>='0'&&red[i]<='9')
        t+=red[i++];
      }
      double a=std::stod(t); t.clear();
      if(red[i]==' ')i++;
        while(red[i]>='0'&&red[i]<='9')
        t+=red[i++];
      if(red[i]=='.'){
        i++;
        while(red[i]>='0'&&red[i]<='9')
        t+=red[i++];
      }
      double b=std::stod(t); t.clear();
      if(red[i]==' ')i++;
        while(red[i]>='0'&&red[i]<='9')
        t+=red[i++];
      if(red[i]=='.'){
        i++;
        while(red[i]>='0'&&red[i]<='9')
        t+=red[i++];
      }
      double c=std::stod(t);
      if(g<=0||a<=0||b<=0||c<=0)throw std::logic_error("Neispravan format datoteke");
      niz[broj_elemenata++]=new Cigla(g,a,b,c);
    }
    else
      throw std::logic_error("Neispravan format datoteke");
  }
  std::sort(niz, niz+broj,[](Predmet *a, Predmet *b){
    return a->DajMasu()<b->DajMasu();
  });
  for(int i=0;i<broj;i++)
    std::cout<<niz[i]->DajZapreminu()<<" "<<niz[i]->DajMasu()<<std::endl;
    for(int i=0;i<broj;i++)delete niz[i]; delete[] niz;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR14 - ZADATAK 31 */
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
class ApstraktniLik{
std::string vrsta,naziv;
double tezina;
public:
  ApstraktniLik(std::string tip, std::string name, double t):vrsta(tip),naziv(name),tezina(t){}
 double DajTezinu()const{return tezina;}
 virtual double DajUkupnuTezinu()const=0;
virtual ApstraktniLik* DajKopiju()const=0;
friend std::ostream &operator<<(std::ostream &tok,const ApstraktniLik &a){
 tok<<a.vrsta<<" "<<a.naziv<<" "<<a.DajTezinu()<<"kg."; return tok;
}
};
class Sanduk:public ApstraktniLik{
int broj_predmeta;
double tezina_predmeta;
public:
      Sanduk(std::string name, double t, int broj, double p):
       broj_predmeta(broj),tezina_predmeta(p),ApstraktniLik("Sanduk",name, t){}
      double DajUkupnuTezinu()const override{return DajTezinu()+broj_predmeta*tezina_predmeta;}
      ApstraktniLik* DajKopiju()const override{return new Sanduk(*this);
      }
};
class Bure:public ApstraktniLik{
  double tezina_tecnosti;
public:
  Bure(std::string name, double t, double p):tezina_tecnosti(p),ApstraktniLik("Bure",name,t){}
  double DajUkupnuTezinu()const override{return DajTezinu()+tezina_tecnosti;}
  ApstraktniLik* DajKopiju()const override{return new Bure(*this);}
};
class Skladiste{
int broj;
const int max_broj;
ApstraktniLik** niz;
public:
  explicit Skladiste(int max):max_broj(max),broj(0),niz(new ApstraktniLik*[max]{}){}
  ~Skladiste(){for(int i=0;i<broj;i++)delete niz[i]; delete[] niz;}
  Skladiste(const Skladiste &s):max_broj(s.max_broj),broj(s.broj),niz(new ApstraktniLik*[s.max_broj]{}){
    try{
      for(int i=0;i<broj;i++)
        niz[i]=s.niz[i]->DajKopiju();
    }catch(...){
      for(int i=0;i<broj;i++)delete niz[i]; delete[] niz; throw;
    }
  }
  Skladiste &operator=(Skladiste &s){
    if(&s!=this){
      delete[] niz; niz=s.niz; s.niz=nullptr; broj=s.broj;
    }return *this;
  }
  void DodajSanduk(std::string name, double t, int broj_predmeta, double p){
    if(broj==max_broj)throw std::logic_error("Popunjeno");
    niz[broj++]=new Sanduk(name, t,broj_predmeta,p);
  }
  void DodajBure(std::string name, double t, double p){
    if(broj==max_broj)throw std::logic_error("Popunjeno");
    niz[broj++]=new Bure(name, t,p);
  }
  ApstraktniLik* &DajNajtezi(){
    ApstraktniLik *max=niz[0];
    for(int i=1;i<broj;i++)
      if(niz[i]->DajUkupnuTezinu()>max->DajUkupnuTezinu())max=niz[i];
    return max;
  }
  ApstraktniLik* &DajNajlaksi(){
    ApstraktniLik *min=niz[0];
    for(int i=1;i<broj;i++)
      if(niz[i]->DajUkupnuTezinu()<min->DajUkupnuTezinu())min=niz[i];
    return min;
  }
  int DajBrojObjekata(int n)const{
int broj=0;
for(int i=0;i<broj;i++)
      if(niz[i]->DajUkupnuTezinu()>n)broj++;
  return broj;
}
void Ispisi(){
    std::sort(niz,niz+broj,[](ApstraktniLik *a, ApstraktniLik *b){
              return a->DajUkupnuTezinu()>b->DajUkupnuTezinu();});
  for(int i=0;i<broj;i++)
    std::cout<<*niz[i]<<std::endl;
}
};
int main() {
  std::ifstream ulaz("skladiste.txt");
  int broj=0; std::string red;
  while(std::getline(ulaz,red))broj++;
  Skladiste s(broj/2);
  ulaz.clear(); ulaz.seekg(0);
  while(std::getline(ulaz,red)){
    if(red[0]=='S'){
      std::string naziv;
      int i=2;
      while(i<red.length())
        naziv+=red[i++];
      double tezina_sanduka, tezina_predmeta; int broj_predmeta;
      ulaz>>tezina_sanduka>>broj_predmeta>>tezina_predmeta;
      ulaz.ignore(1000,'\n');
      s.DodajSanduk(naziv,tezina_sanduka,broj_predmeta,tezina_predmeta);
    }
    else if(red[0]=='B'){
            std::string naziv;
            int i=2;
      while(i<red.length())
        naziv+=red[i++];
      double tezina_bureta, tezina_tecnosti;
      ulaz>>tezina_bureta>>tezina_tecnosti;
      s.DodajBure(naziv, tezina_bureta,tezina_tecnosti);
    }
    else
      throw std::logic_error("Datoteka sadrzi besmislene podatke");
  }
 s.Ispisi();
  return 0;
}
/*-----------------------------------------------*/