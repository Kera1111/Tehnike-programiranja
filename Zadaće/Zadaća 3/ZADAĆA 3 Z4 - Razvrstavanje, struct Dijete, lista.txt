//TP 2021/2022: Zadaća 3, Zadatak 4
#include <iostream>
#include <cmath>
#include <algorithm>
#include <list>
#include <string>
#include <stdexcept>
#include <vector>
#include <new>
#include <set>

void OcistiTok() {std::cin.ignore(10000,'\n');}

struct Dijete {
    std::string ime;
    Dijete *sljedeci = nullptr;
};

int BrojSlova(std::string s){
    int brojac = 0;
    for(char i : *&s){
        if((i>='A' && i<='Z') || (i>='a' && i<='z') || (i>='0' && i<='9')) brojac++;
    }
    return brojac;
}

std::vector<std::set<std::string>> Razvrstavanje(std::vector<std::string> &v, int brTimova){
    
    if(brTimova<1 || brTimova>v.size()) throw std::logic_error("Razvrstavanje nemoguce");

    std::vector<std::set<std::string>> imenaDjece(brTimova);
    int brDjece = v.size();

    Dijete *pocetak(nullptr), *prosloDijete(nullptr);

    for(int i=0; i<brDjece; i++){
        Dijete *novoDijete = new Dijete;
        novoDijete->ime = v[i];
        novoDijete->sljedeci = nullptr;
        if(!pocetak) pocetak = novoDijete;
        else prosloDijete->sljedeci = novoDijete;
        prosloDijete = novoDijete;
    } 

    Dijete *prvoDijete = pocetak->sljedeci;

    int pomak = BrojSlova(pocetak->ime);

    imenaDjece[0].insert(pocetak->ime);
    delete pocetak;
    prosloDijete->sljedeci = prvoDijete;

    std::vector<int> velTimova{};

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

    int index = 0;
    pomak--;

    auto poslije = prvoDijete->sljedeci;

    for(int i=0; i<brDjece-1; i++){
        
        for(int j=0; j<pomak-1; j++){
            prvoDijete = poslije;
            poslije = prvoDijete->sljedeci;
        }
        
        if(imenaDjece[index].size()>=velTimova[index]) index++;

        pomak = BrojSlova(poslije->ime);
        imenaDjece[index].insert(poslije->ime);
        prvoDijete->sljedeci = poslije->sljedeci;
        poslije->sljedeci = nullptr;
        delete poslije;
        if(i!=brDjece-2) poslije = prvoDijete->sljedeci;

    }
    return imenaDjece;
}

int main() {
  int n;
  std::cout << "Unesite broj djece: " << std::endl;
  std::cin >> n;

  std::cout << "Unesite imena djece: " << std::endl;
  std::vector<std::string> imenaDjece(n);
  OcistiTok();
  for (int i = 0; i < n; i++) {
    getline(std::cin, imenaDjece.at(i));
  }

  int brTimova = 0;
  std::cout << "Unesite broj timova: " << std::endl;
  std::cin >> brTimova;

  try {
    std::vector<std::set<std::string>> rezultat =
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