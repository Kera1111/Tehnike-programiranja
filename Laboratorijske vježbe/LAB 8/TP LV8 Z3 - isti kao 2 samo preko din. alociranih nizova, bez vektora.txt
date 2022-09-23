// TP 2021/2022: LV 8, Zadatak 3
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

//kod ovog se mora ici preko oslobodi memoriju za brisanje

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

void UnesiUcenike(Ucenik **&pokucenici, const int &broj_ucenika);

void ObradiUcenike(Ucenik **&pokucenici, const int &broj_ucenika);

void IspisiIzvjestaj(const Ucenik *const *const &pokucenici, const int &broj_ucenika);

void OslobodiMemoriju(Ucenik **&pokucenici, const int &broj_ucenika);

int main() {
  
  int broj_ucenika;
  std::cout << "Koliko ima ucenika: ";
  std::cin >> broj_ucenika;
  Ucenik **pokucenici{nullptr}; // staviti pokazivac na pokazivac na strukturu
  try {
      pokucenici = new Ucenik* [broj_ucenika];
      for(int i=0; i<broj_ucenika; i++){
          pokucenici[i] = nullptr;
      }
    UnesiUcenike(pokucenici, broj_ucenika);
    ObradiUcenike(pokucenici, broj_ucenika);
    IspisiIzvjestaj(pokucenici, broj_ucenika);
    OslobodiMemoriju(pokucenici, broj_ucenika);
  } catch (...) {
      OslobodiMemoriju(pokucenici, broj_ucenika);
    std::cout << "Problemi sa memorijom...\n";
  }
  return 0;
}

void UnesiUcenike(Ucenik **&pokucenici, const int &broj_ucenika){
  void UnesiJednogUcenika(Ucenik* pokucenik);
  for (int i = 0; i < broj_ucenika; i++) {
    std::cout << "Unesite podatke za " << i + 1 << ". ucenika:\n";
    pokucenici[i] = new Ucenik;
    UnesiJednogUcenika(pokucenici[i]);
  }
}

void UnesiJednogUcenika(Ucenik* pokucenik) {
  void UnesiDatum(Datum & datum);
  void UnesiOcjene(int ocjene[], int broj_predmeta);
  std::cout << "  Ime: ";
  std::cin >> pokucenik->ime;
  std::cout << "  Prezime: ";
  std::cin >> pokucenik->prezime;
  std::cout << "  Datum rodjenja (D/M/G): ";
  UnesiDatum(pokucenik->datum_rodjenja);
  UnesiOcjene(pokucenik->ocjene, BrojPredmeta);
}

void UnesiDatum(Datum &datum) {
  char znak;
  std::cin >> datum.dan >> znak >> datum.mjesec >> znak >> datum.godina;
}

void UnesiOcjene(int ocjene[], int broj_predmeta) {
  void UnesiOcjenu(int &ocjena);
  for (int i = 0; i < broj_predmeta; i++) {
    std::cout << "  Ocjena iz " << i + 1 << ". predmeta: ";
    UnesiOcjenu(ocjene[i]);
  }
}

void UnesiOcjenu(int &ocjena) { std::cin >> ocjena; }

void ObradiUcenike(Ucenik **&pokucenici, const int &broj_ucenika){
  void ObradiJednogUcenika(Ucenik* pokucenik);
  for (int i=0; i<broj_ucenika; i++)
    ObradiJednogUcenika(pokucenici[i]);
  std::sort(pokucenici, pokucenici + broj_ucenika,
            [](const Ucenik* u1, const Ucenik* u2) {
              return u1->prosjek > u2->prosjek;
            });
}

void ObradiJednogUcenika(Ucenik* pokucenik) {
  double suma_ocjena = 0;
  pokucenik->prosjek = 1;
  pokucenik->prolaz = false;
  for (int ocjena : pokucenik->ocjene) {
    if (ocjena == 1)
      return;
    suma_ocjena += ocjena;
  }
  pokucenik->prolaz = true;
  pokucenik->prosjek = suma_ocjena / BrojPredmeta;
}

void IspisiIzvjestaj(const Ucenik *const *const &pokucenici, const int &broj_ucenika){
  void IspisiJednogUcenika(const Ucenik* pokucenik);
  std::cout << std::endl;
  for (int i=0; i<broj_ucenika; i++)
    IspisiJednogUcenika(pokucenici[i]);
}

void IspisiJednogUcenika(const Ucenik* pokucenik) {
  void IspisiDatum(const Datum &datum);
  std::cout << "Ucenik " << pokucenik->ime << " " << pokucenik->prezime << " rodjen ";
  IspisiDatum(pokucenik->datum_rodjenja);
  if (pokucenik->prolaz)
    std::cout << " ima prosjek " << std::setprecision(3) << pokucenik->prosjek;
  else
    std::cout << " mora ponavljati razred";
  std::cout << std::endl;
}

void IspisiDatum(const Datum &datum) {
  std::cout << datum.dan << "/" << datum.mjesec << "/" << datum.godina;
}

void OslobodiMemoriju(Ucenik **&pokucenici, const int &broj_ucenika){
    if(pokucenici==nullptr){
        return;
    }
    for(int i=0; i<broj_ucenika; i++){
        delete pokucenici[i]; 
    }
    delete[] pokucenici;
}