/*
    TP 16/17 (LV 11, Zadatak 2)
        Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
        i pitanja slati na mail: hhasic2@etf.unsa.ba.

        Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <stdexcept>

class StedniRacun {
  mutable double Stanje; // da bi se moglo ubacivat u const fje
  static int kreiran;
  static int aktivan;

public:
  StedniRacun(double x = 0) {
    if (x < 0)
      throw std::logic_error("Nedozvoljeno pocetno stanje");
    StedniRacun::Stanje = x;
    kreiran++;
    aktivan++;
  }
  StedniRacun(const StedniRacun &x) {
    StedniRacun::Stanje = x.Stanje;
    kreiran++;
    aktivan++;
  }
  ~StedniRacun() { aktivan--; } // destruktor
  double DajStanje() const { return StedniRacun::Stanje; }
  double ObracunajKamatu(double x) const {
    if (x < 0)
      throw std::logic_error("Nedozvoljena kamatna stopa");
    StedniRacun::Stanje += (StedniRacun::Stanje / 100) * x;
    return StedniRacun::Stanje;
  }
  StedniRacun &Ulozi(double x = 0) {
    if (x < Stanje * -1)
      throw std::logic_error("Transakcija odbijena");
    else if (x < 0)
      this->Podigni(x * -1);
    else
      StedniRacun::Stanje += x;
    return *this;
  }
  StedniRacun &Podigni(double x = 0) {
    if (x > StedniRacun::Stanje)
      throw std::logic_error("Transakcija odbijena");
    if (x < 0)
      this->Ulozi(x * -1);
    else
      StedniRacun::Stanje -= x;
    return *this;
  }
  static int DajBrojKreiranih() { return kreiran; }
  static int DajBrojAktivnih() { return aktivan; }
};

int StedniRacun::aktivan = 0;
int StedniRacun::kreiran = 0;

int main() { return 0; }