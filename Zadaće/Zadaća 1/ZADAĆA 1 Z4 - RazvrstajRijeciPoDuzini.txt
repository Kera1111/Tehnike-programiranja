// TP 2021/2022: Zadaća 1, Zadatak 4

#include <array>
#include <cctype>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
void pretvoriuVelika(string &recenica) {
  int i = 0;
  while (i<recenica.length()) {
    if (recenica.at(i) >= 'a' && recenica.at(i) <= 'z')
      recenica.at(i) -= 32;
    if (i == recenica.length()) break;
    i++;
    }
}

array<vector<string>, 100>
RazvrstajRijeciPoDuzini(string recenica) { // 100 jer 99 je granica za gresku pa
                                           // zaokruzena fina brojka 100 :)
  array<vector<string>, 100> niz;
  int i = 0, brSlovaiCifara;
  pretvoriuVelika(recenica);
  while (i < recenica.length()) {
    if ((recenica.at(i) >= 'a' && recenica.at(i) <= 'z') ||
        (recenica.at(i) >= 'A' && recenica.at(i) <= 'Z') ||
        (recenica.at(i) >= '0' && recenica.at(i) <= '9')) {
      int pocetakrijeci =
          i; // spasavam da bi kasnije i koristila za pocetak nove rijeci
      brSlovaiCifara = 0;
      while ((recenica.at(i) >= 'a' && recenica.at(i) <= 'z') ||
             (recenica.at(i) >= 'A' && recenica.at(i) <= 'Z') ||
             (recenica.at(i) >= '0' && recenica.at(i) <= '9')) {
        brSlovaiCifara++;
        i++;
        if (i == recenica.length())
          break; // ovo mi treba jer ce doc na kraj povecat i i onda out of
                 // range jer ode van dimenzija niza
      }
      if (brSlovaiCifara > 99) {
        throw range_error("Predugacka rijec!");
        return niz;
      }
      i = pocetakrijeci;

      int brojRijeciPoIstojDuzini = niz.at(brSlovaiCifara).size();
      // da bi dodali sljedecu rijec moramo prosiriti niz za jedno mjesto da bi
      // imala gdje da stane
      niz.at(brSlovaiCifara).resize(brojRijeciPoIstojDuzini + 1);
      while ((recenica.at(i) >= 'a' && recenica.at(i) <= 'z') ||
             (recenica.at(i) >= 'A' && recenica.at(i) <= 'Z') ||
             (recenica.at(i) >= '0' && recenica.at(i) <= '9')) {
        niz.at(brSlovaiCifara)
            .at(brojRijeciPoIstojDuzini)
            .push_back(recenica.at(i));
        i++;
        if (i == recenica.length())
          break; // ako je u pitanju kraj rijeci onda ce ga povecati a izaci ce
                 // greska jer nije u opsegu dimenzija niza vise
      }
    }
    i++;
  }
  return niz;
}


int main() {
  cout << "Unesite recenicu: ";
  string recenica;
  getline(cin, recenica);

  array<vector<string>, 100> niz;

  try {
    niz = RazvrstajRijeciPoDuzini(recenica);
  } catch (range_error greska) {
    cout <<endl<<"Greska: Recenica sadrzi predugacku rijec!"<<endl;
    return 0;
  }

  for (int i = 0; i < 100; i++) {
    // red po red za razlicite duzine
    if (niz.at(i).size() > 0) {
      cout << "Duzina " << i << ": ";
      for (int j = 0; j < niz.at(i).size(); j++) {
        // rijec po rijec iste duzine, vektor je pa koristim size
        for (int z = 0; z < niz.at(i).at(j).length(); z++) {
          // char po char za rijec a posto je to string koristim length a ne
          // size
          cout << niz.at(i).at(j).at(z);
        }
        cout << " "; // razmak izmedju rijeci
      }
      cout << endl; // novi red za svaku novu duzinu
    }
  }

  return 0;
}
