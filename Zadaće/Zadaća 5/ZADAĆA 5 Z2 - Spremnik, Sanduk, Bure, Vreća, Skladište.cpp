// TP 2021/2022: Zadaća 5, Zadatak 3
#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>


using namespace std;

class Spremnik {
protected:
  string ime;
  double tezina;

public:
  Spremnik(double tezinaSpremnika, string naziv)
      : tezina(tezinaSpremnika), ime(naziv) {}
  double DajTezinu() const { return tezina; }
  virtual double DajUkupnuTezinu() const = 0;
  virtual void Ispisi() const = 0;
  virtual ~Spremnik() = default;
  virtual Spremnik *DajKopiju() const = 0;
};

class Sanduk : public Spremnik {
  vector<double> tezine;

public:
  Sanduk(double tezina, string ime, vector<double> tezine)
      : Spremnik(tezina, ime), tezine(tezine) {}
  double DajUkupnuTezinu() const override {
    double tezinaSanduka = DajTezinu();
    for (int i = 0; i < tezine.size(); i++) {
      tezinaSanduka += tezine[i];
    }
    return tezinaSanduka; // ukupna tezina
  }

  void Ispisi() const override {
    cout << "Vrsta spremnika: Sanduk" << endl << "Sadrzaj: " << ime << endl;
    cout << "Tezine predmeta: ";
    for (int i = 0; i < tezine.size(); i++)
      cout << tezine[i] << " ";
    cout << " (kg)" << endl
         << "Vlastita tezina: " << DajTezinu() << " (kg)" << endl
         << "Ukupna tezina: " << DajUkupnuTezinu() << " (kg)" << endl;
  }

  Sanduk *DajKopiju() const override { return new Sanduk(*this); }
};

class Bure : public Spremnik {
  double specTezina, zapremina;

public:
  Bure(double tezina, string naziv, double specTezina, double zapremina)
      : Spremnik(tezina, naziv), specTezina(specTezina), zapremina(zapremina) {}
  double DajUkupnuTezinu() const override {
    return DajTezinu() + (specTezina * zapremina) / 1000;
  }
  void Ispisi() const override {
    cout << "Vrsta spremnika: Bure" << endl
         << "Sadrzaj: " << ime << endl
         << "Vlastita tezina: " << DajTezinu() << " (kg)" << endl
         << "Specificna tezina tecnosti: " << specTezina << " (kg/m^3)" << endl
         << "Zapremina tecnosti: " << zapremina << " (l)" << endl
         << "Ukupna tezina: " << DajUkupnuTezinu() << " (kg)" << endl;
  }
  Bure *DajKopiju() const override { return new Bure(*this); }
};

class Vreca : public Spremnik {
  double tezinaPraha;

public:
  Vreca(double tezina, string ime, double tezinaPraha)
      : Spremnik(tezina, ime), tezinaPraha(tezinaPraha) {}
  double DajUkupnuTezinu() const override { return DajTezinu() + tezinaPraha; }
  Vreca *DajKopiju() const override { return new Vreca(*this); }
  void Ispisi() const override {
    cout << "Vrsta spremnika: Vreca" << endl
         << "Sadrzaj: " << ime << endl
         << "Vlastita tezina: " << DajTezinu() << " (kg)" << endl
         << "Tezina pohranjene materije: " << tezinaPraha << " (kg)" << endl
         << "Ukupna tezina: " << DajUkupnuTezinu() << " (kg)" << endl;
  }
};

class Skladiste {
  vector<shared_ptr<Spremnik>> vektor;

public:
  explicit Skladiste() {}
  Skladiste(const Skladiste &s);
  Skladiste(Skladiste &&s);
  Skladiste &operator=(const Skladiste &s);
  Skladiste &operator=(Skladiste &&s);
  Spremnik *DodajSanduk(double tezina, string ime, vector<double> tezine) {
    Sanduk *pomocni = new Sanduk(tezina, ime, tezine);
    vektor.push_back(shared_ptr<Spremnik>(pomocni));
    return pomocni;
  }
  Spremnik *DodajBure(double tezina, string ime, double specTezina,
                      double zapremina) {
    Bure *pomocni = new Bure(tezina, ime, specTezina, zapremina);
    vektor.push_back(shared_ptr<Spremnik>(pomocni));
    return pomocni;
  }
  Spremnik *DodajVrecu(double tezina, string ime, double tezinaPraha) {
    Vreca *pomocni = new Vreca(tezina, ime, tezinaPraha);
    vektor.push_back(shared_ptr<Spremnik>(pomocni));
    return pomocni;
  }
  Spremnik *DodajSpremnik(Spremnik *pok, bool jest) {
    if (jest) {
      Spremnik *pomocni = pok->DajKopiju();
      delete pok;
      vektor.push_back(shared_ptr<Spremnik>(pomocni));
      return pomocni;
    } else {
      Spremnik *pomocni = pok->DajKopiju();
      vektor.push_back(shared_ptr<Spremnik>(pomocni));
      return pomocni;
    }
  }
  Spremnik &DajNajtezi() {
    if (vektor.size() == 0)
      throw std::range_error("Skladiste je prazno");
    auto it = max_element(vektor.begin(), vektor.end(),
                          [](shared_ptr<Spremnik> s1, shared_ptr<Spremnik> s2) {
                            return (s1->DajTezinu() < s2->DajTezinu());
                          });
    return **it;
  }
  Spremnik &DajNajlaksi() {
    if (vektor.size() == 0)
      throw std::range_error("Skladiste je prazno");
    auto it = min_element(vektor.begin(), vektor.end(),
                          [](shared_ptr<Spremnik> s1, shared_ptr<Spremnik> s2) {
                            return (s1->DajTezinu() < s2->DajTezinu());
                          });
    return **it;
  }
  int BrojPreteskih(int broj) const {
    return count_if(vektor.begin(), vektor.end(),
                    [broj](shared_ptr<Spremnik> p1) {
                      if (p1->DajUkupnuTezinu() > broj)
                        return true;
                      return false;
                    });
  }
  void IzlistajSkladiste() const {
    auto kopija = vektor;
    sort(kopija.begin(), kopija.end(),
         [](shared_ptr<Spremnik> p1, shared_ptr<Spremnik> p2) {
           return p1->DajUkupnuTezinu() > p2->DajUkupnuTezinu();
         });
    for (auto x : kopija)
      x->Ispisi();
  }
  void UcitajIzDatoteke(string ime);
  void BrisiSpremnik(Spremnik *m) {
    for (int i = 0; i < vektor.size(); i++) {
      if (m == vektor[i].get()) {
        vektor.erase(vektor.begin() + i);
        break;
      }
    }
  }
};

Skladiste::Skladiste(const Skladiste &s) {
  for (auto x : s.vektor) {
    vektor.push_back(shared_ptr<Spremnik>(x->DajKopiju()));
  }
}

Skladiste::Skladiste(Skladiste &&s) {
  swap(vektor, s.vektor);
  s.vektor.resize(0);
}

Skladiste &Skladiste::operator=(const Skladiste &s) {
  for (auto x : vektor)
    x = nullptr;
  vektor.resize(0);
  for (auto x : s.vektor) {
    vektor.push_back(shared_ptr<Spremnik>(x->DajKopiju()));
  }
  return *this;
}

Skladiste &Skladiste::operator=(Skladiste &&s) {
  swap(vektor, s.vektor);
  return *this;
}

void Skladiste::UcitajIzDatoteke(string s) {
    vektor.clear();
  ifstream datoteka(s);
  if (!datoteka)
    throw logic_error("Trazena datoteka ne postoji");

  string naziv;
  char znak = ' ';
  double tezina;
  while (1) {
    datoteka>>znak;
    if (!datoteka)
      break;
    getline(datoteka, naziv);
    if (znak == 'S') {
      int brpred;
      vector<double> tezine;
      datoteka >> tezina >> brpred;
      for (int i = 0; i < brpred; i++) {
        double element;
        datoteka >> element;
        tezine.push_back(element);
      }
      if (!datoteka)
        break;
      DodajSanduk(tezina, naziv, tezine);
    } else if (znak == 'B') {
      double specTezina, zapremina;
      datoteka >> tezina>>specTezina >> zapremina;
      if (!datoteka)
        break;
      DodajBure(tezina, naziv, specTezina, zapremina);
    } else if (znak == 'V') {
      double tezinaPraha;
      datoteka >> tezina>>tezinaPraha;
      if (!datoteka)
        break;
      DodajVrecu(tezina, naziv, tezinaPraha);
    }
  }
  if (datoteka.bad())
      throw logic_error("Problemi pri citanju datoteke");
    else if (!datoteka.eof() && !datoteka)
      throw logic_error("Datoteka sadrzi besmislene podatke");
}
int main() {
// AT 3: Test ciscenja kolecije prije ucitavanja
    {
        std::ofstream izlaz("ROBA.TXT");
        izlaz << "S Tepsije\n10 9 2 3 1 2 2 4 3 1 3\n";
        izlaz << "V Brasno\n0.2 5\n";
        izlaz << "B Suncokretovo ulje\n5 1300 150";
        izlaz.flush();
        izlaz.close();

        Skladiste ETF;
        ETF.DodajSanduk(1, "A", {1, 2, 3});
        ETF.UcitajIzDatoteke("ROBA.TXT");
        ETF.IzlistajSkladiste();
    }/*
  Skladiste s;
  try {
    s.UcitajIzDatoteke("ROBA.TXT");
    s.IzlistajSkladiste();
  } catch (logic_error &e) {
    cout << e.what();
  }*/
  return 0;
}
