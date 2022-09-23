// TP 2021/2022: LV 8, Zadatak 2
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

//zamjenila da je neki dvostruki pokazivac na ucenike tj isto ko dinamicke matrice
//imam dvostruki pokazivac na ucenika koji pokazuju na niz pokazivaca koji pokazuju na ucenike
//ukoliko ne pokazujes na nekog ucenika vise obrisi to

const int BrojPredmeta = 8;

struct Datum {
  int dan, mjesec, godina;
};

struct Ucenik {
  std::string ime, prezime;
  Datum datum_rodjenja;
  int ocjene[BrojPredmeta];
  double prosjek;
  bool prolaz;
};

// OVDJE SE MIJENJA 
/*
OVAKO JE BILO
void UnesiUcenike(std::vector<Ucenik> &ucenici) {
  void UnesiJednogUcenika(Ucenik & ucenik);
  for (int i = 0; i < ucenici.size(); i++) {
    std::cout << "Unesite podatke za " << i + 1 << ". ucenika:\n";
    UnesiJednogUcenika(ucenici[i]);
  }
}
*/
void UnesiUcenike(std::vector<std::shared_ptr<Ucenik>> &pametniucenici) {
  void UnesiJednogUcenika(std::shared_ptr<Ucenik> pametniucenik);
  for (int i = 0; i < pametniucenici.size(); i++) {
    std::cout << "Unesite podatke za " << i + 1 << ". ucenika:\n";
    pametniucenici[i] = std::make_shared<Ucenik>();
    UnesiJednogUcenika(pametniucenici[i]);
  }
}

void UnesiJednogUcenika(std::shared_ptr<Ucenik> pametniucenik) {
  void UnesiDatum(Datum & datum);
  void UnesiOcjene(int ocjene[], int broj_predmeta);
  std::cout << "Ime: ";
  std::cin >> pametniucenik->ime;
  std::cout << "Prezime: ";
  std::cin >> pametniucenik->prezime;
  std::cout << "Datum rodjenja (D/M/G): ";
  UnesiDatum(pametniucenik->datum_rodjenja);
  UnesiOcjene(pametniucenik->ocjene, BrojPredmeta);
}

void UnesiDatum(Datum &datum) {
  char znak;
  std::cin >> datum.dan >> znak >> datum.mjesec >> znak >> datum.godina;
}

void UnesiOcjene(int ocjene[], int broj_predmeta) {
  void UnesiOcjenu(int &ocjena);
  for (int i = 0; i < broj_predmeta; i++) {
    std::cout << "Ocjena iz " << i + 1 << ". predmeta: ";
    UnesiOcjenu(ocjene[i]);
  }
}

void UnesiOcjenu(int &ocjena) { std::cin >> ocjena; }

//OVDJE SE MIJENJA
/*
OVAKO JE BILO
void ObradiUcenike(std::vector<Ucenik> &ucenici) {
  void ObradiJednogUcenika(Ucenik & ucenik);
  for (Ucenik &ucenik : ucenici)
    ObradiJednogUcenika(ucenik);
  std::sort(ucenici.begin(), ucenici.end(),
            [](const Ucenik &u1, const Ucenik &u2) {
              return u1.prosjek > u2.prosjek;
            });
}
*/
void ObradiUcenike(std::vector<std::shared_ptr<Ucenik>> &pametniucenici) {
  void ObradiJednogUcenika(std::shared_ptr<Ucenik> pametniucenik);
  for (auto pametniucenik : pametniucenici)
    ObradiJednogUcenika(pametniucenik);
  std::sort(pametniucenici.begin(), pametniucenici.end(),
            [](std::shared_ptr<Ucenik> &pu1, std::shared_ptr<Ucenik> &pu2) {
              return pu1->prosjek > pu2->prosjek;
            });
}

//OVDJE SE MIJENJA
/*
OVAKO JE BILO
void ObradiJednogUcenika(Ucenik &ucenik) {
  double suma_ocjena = 0;
  ucenik.prosjek = 1;
  ucenik.prolaz = false;
  for (int ocjena : ucenik.ocjene) {
    if (ocjena == 1)
      return;
    suma_ocjena += ocjena;
  }
  ucenik.prolaz = true;
  ucenik.prosjek = suma_ocjena / BrojPredmeta;
}
*/
void ObradiJednogUcenika(std::shared_ptr<Ucenik> pametniucenik) {
  double suma_ocjena = 0;
  pametniucenik->prosjek = 1;
  pametniucenik->prolaz = false;
  for (int ocjena : pametniucenik->ocjene) {
    if (ocjena == 1)
      return;
    suma_ocjena += ocjena;
  }
  pametniucenik->prolaz = true;
  pametniucenik->prosjek = suma_ocjena / BrojPredmeta;
}

//OVDJE SE MIJENJA
/*
void IspisiIzvjestaj(const std::vector<Ucenik> &ucenici) {
  void IspisiJednogUcenika(const Ucenik &ucenik);
  std::cout << std::endl;
  for (const Ucenik &ucenik : ucenici)
    IspisiJednogUcenika(ucenik);
}
*/
void IspisiIzvjestaj(const std::vector<std::shared_ptr<Ucenik>> &pametniucenici) {
  void IspisiJednogUcenika(std::shared_ptr<Ucenik> pametniucenik);
  std::cout << std::endl;
  for (auto pametniucenik : pametniucenici)
    IspisiJednogUcenika(pametniucenik);
}

//OVDJE SE MIJENJA
/*
OVAKO JE BILO
void IspisiJednogUcenika(const Ucenik &ucenik) {
 void IspisiDatum(const Datum &datum);
 std::cout << "Učenik " << ucenik.ime << " " << ucenik.prezime << " rođen ";
 IspisiDatum(ucenik.datum_rodjenja);
 if(ucenik.prolaz) 
 std::cout << " ima prosjek " << std::setprecision(3) << ucenik.prosjek;
 else 
 std::cout << " mora ponavljati razred";
 std::cout << std::endl;
}
*/
void IspisiJednogUcenika(std::shared_ptr<Ucenik> pametniucenik) {
  void IspisiDatum(const Datum &datum);
  std::cout << "Ucenik " << pametniucenik->ime << " " << pametniucenik->prezime << " rodjen ";
  IspisiDatum(pametniucenik->datum_rodjenja);
  if (pametniucenik->prolaz)
    std::cout << " ima prosjek " << std::setprecision(3) << pametniucenik->prosjek;
  else
    std::cout << " mora ponavljati razred";
  std::cout << std::endl;
}

void IspisiDatum(const Datum &datum) {
  std::cout << datum.dan << "/" << datum.mjesec << "/" << datum.godina;
}

int main() {
  void UnesiUcenike(std::vector<std::shared_ptr<Ucenik>> & ucenici);
  void ObradiUcenike(std::vector<std::shared_ptr<Ucenik>> & ucenici);
  void IspisiIzvjestaj(const std::vector<std::shared_ptr<Ucenik>> &ucenici);
  int broj_ucenika;
  std::cout << "Koliko ima ucenika: ";
  std::cin >> broj_ucenika;
  try {
    std::vector<std::shared_ptr<Ucenik>> pametniucenici(broj_ucenika);
    UnesiUcenike(pametniucenici);
    ObradiUcenike(pametniucenici);
    IspisiIzvjestaj(pametniucenici);
  } catch (...) {
    std::cout << "Problemi sa memorijom...\n";
  }
  return 0;
}
