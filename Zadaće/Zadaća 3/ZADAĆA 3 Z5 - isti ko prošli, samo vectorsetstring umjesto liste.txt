// TP 2021/2022: Zadaća 3, Zadatak 5
#include <algorithm>
#include <cmath>
#include <iostream>
#include <new>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

struct Dijete {
  std::string ime;
  Dijete *sljedeci = nullptr;
};

int BrojSlova(std::string s) {
  int brojac = 0;
  for (char i : *&s) {
    if ((i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z') ||
        (i >= '0' && i <= '9'))
      brojac++;
  }
  return brojac;
}

void OcistiTok() { std::cin.ignore(10000, '\n'); }

typedef std::vector<std::set<std::string>> vss;
typedef std::vector<std::string> vs;

vss Razvrstavanje(vs &v,int brTimova) {

    int brDjece = v.size();
  
    if (brTimova < 1 || brTimova > brDjece)
    throw std::logic_error("Razvrstavanje nemoguce");

  vss imenaDjece(brTimova);

  std::vector<int> velTimova{}; // formiramo vektor gdje spasavamo br djece po
                                // timu
  for (int i = 0; i < brTimova; i++) {
    if (brDjece % brTimova == 0)
      velTimova.push_back(brDjece / brTimova);
    else {
      int ostatak = brDjece % brTimova;
      if (i < ostatak)
        velTimova.push_back((brDjece / brTimova) + 1);
      else
        velTimova.push_back(brDjece / brTimova);
    }
  }

  Dijete *pocetak(nullptr), *prosloDijete(nullptr); // kreiranje rucno povezane liste

  for (int i = 0; i < brDjece; i++) {

    Dijete *novoDijete = new Dijete;
    novoDijete->ime = v.at(i);
    novoDijete->sljedeci = nullptr;

    if (!pocetak) // ako je u pitanju prvo dijete sto se unosi jer dotad pocetak
                  // pokazuje na nullptr
      pocetak = novoDijete;
    else
      prosloDijete->sljedeci = novoDijete;

    prosloDijete = novoDijete;

  }

  // razvrstavanje i brisanje sviju

    Dijete *prvo = pocetak->sljedeci;
    int pomak = BrojSlova(pocetak->ime);

    imenaDjece[0].insert(pocetak->ime);
    delete pocetak;
    prosloDijete->sljedeci = prvo;

    int index=0;
    pomak--;
    auto poslije = prvo->sljedeci;

  for (int i = 0; i <brDjece-1; i++) { // posto ih razvrstavam po timovima ide do brTimova
    for (int j = 0; j < pomak-1; j++) // sredjivanje jedan po jedan tim
    {
        prvo = poslije;
        poslije = prvo->sljedeci;
    }

    if(imenaDjece[index].size()>=velTimova[index]) index++;
    pomak = BrojSlova(poslije->ime);
    imenaDjece[index].insert(poslije->ime);
    prvo->sljedeci = poslije->sljedeci;
    poslije->sljedeci = nullptr;
    delete poslije;

    if(i!=brDjece-2) poslije = prvo->sljedeci;
  }
  return imenaDjece;
}

int main() {
  int n;
  std::cout << "Unesite broj djece: " << std::endl;
  std::cin >> n;

  std::cout << "Unesite imena djece: " << std::endl;
  vs imenaDjece(n);
  OcistiTok();
  for (int i = 0; i < n; i++) {
    getline(std::cin, imenaDjece.at(i));
  }

  int brTimova = 0;
  std::cout << "Unesite broj timova: " << std::endl;
  std::cin >> brTimova;

  try {
    vss rezultat =
        Razvrstavanje(imenaDjece, brTimova);
    for (int i = 0; i < rezultat.size(); i++) {
      std::set<std::string> trenutni = rezultat.at(i);
      std::cout << "Tim " << i + 1 << ": ";
      for (auto it = trenutni.begin(); it != trenutni.end(); it++) {
        if (it == --trenutni.end())
          std::cout << *it << std::endl;
        else
          std::cout << *it << ", ";
      }
    }
  } catch (std::logic_error &izuzetak) {
    std::cout << "Izuzetak: " << izuzetak.what() << std::endl;
    return 0;
  }
  return 0;
}
