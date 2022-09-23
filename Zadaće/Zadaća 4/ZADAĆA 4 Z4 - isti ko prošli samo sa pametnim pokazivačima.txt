// TP 2021/2022: Zadaća 4, Zadatak 4
#include <algorithm>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
#include <vector>

using namespace std;

typedef pair<int, int> Vrijeme;

class Polazak {
  string odrediste, oznaka_voznje;
  int broj_voza, broj_perona, sat_polaska, minute_polaska, kasnjenje,
      trajanje_voznje;
  bool brzi_voz;
  static bool DaLiJeOKUnesenoVrijeme(int sati, int minute,
                                     int trajanje) {
    return (sati <= 24 && sati >= 0) && (minute <= 59 && minute >= 0) &&
           trajanje > 0;
  }

 public:
  Polazak(std::string odrediste, int broj_voza, int broj_perona, bool brzi_voz,
          int sat_polaska, int minute_polaska, int trajanje_voznje);
  void PostaviKasnjenje(int kasnjenje);
  bool DaLiKasni() const;
  int DajTrajanjeVoznje() const;
  std::pair<int, int> DajOcekivanoVrijemePolaska() const;
  std::pair<int, int> DajOcekivanoVrijemeDolaska() const;
  void Ispisi() const;
};

Polazak::Polazak(string odrediste, int broj_voza, int broj_perona,
                 bool brzi_voz, int sat_polaska, int minute_polaska,
                 int trajanje_voznje) {
  if (broj_voza >= 100000)  {throw domain_error("Broj voza moze imati maksimalno 5 cifara");}
  Polazak::broj_voza = broj_voza;
  if (broj_perona < 0 || broj_perona > 6){  throw domain_error("Broj perona mora biti cijeli broj u opsegu od 1 do 6");}
    if(!DaLiJeOKUnesenoVrijeme(sat_polaska, minute_polaska, trajanje_voznje)) { throw domain_error("Besmislene vrijednosti za sate i minute polaska i trajanje voznje");}
  Polazak::broj_perona = broj_perona;
  Polazak::odrediste = odrediste;
  Polazak::brzi_voz = brzi_voz;
  Polazak::sat_polaska = sat_polaska;
  Polazak::minute_polaska = minute_polaska;
  Polazak::trajanje_voznje = trajanje_voznje;
  Polazak::kasnjenje = 0;
}

void Polazak::PostaviKasnjenje(int kasnjenje) {
  if (kasnjenje < 0)
    throw domain_error("Parametri nisu valjani");
  Polazak::kasnjenje = kasnjenje;
}

bool Polazak::DaLiKasni() const { return kasnjenje != 0; }

int Polazak::DajTrajanjeVoznje() const { return trajanje_voznje; }

Vrijeme Polazak::DajOcekivanoVrijemePolaska() const {
  Vrijeme pol{};
  pol.first = sat_polaska;
  pol.second = minute_polaska;
  if (DaLiKasni()) {
    pol.second += kasnjenje;
    while (pol.second >= 60) {
      pol.first++;
      pol.second -= 60;
    }
    while (pol.first >= 24) {
      pol.first -= 24;
    }
  }
  return pol;
}

Vrijeme Polazak::DajOcekivanoVrijemeDolaska() const {
  Vrijeme dol{};
  dol.first = sat_polaska;
  dol.second = minute_polaska;
  int trajanjeVoznje = trajanje_voznje;
  while (trajanjeVoznje >= 60) {
    dol.first++;
    trajanjeVoznje -= 60;
  }
  dol.second += trajanjeVoznje;
  if (DaLiKasni()) {
    dol.second += kasnjenje;
  }
  while (dol.second >= 60) {
    dol.first++;
    dol.second -= 60;
  }
  while (dol.first >= 24) {
    dol.first -= 24;
  }
  return dol;
}

void Polazak::Ispisi() const {
  Vrijeme polazak, dolazak;
  dolazak = DajOcekivanoVrijemeDolaska();
  polazak = DajOcekivanoVrijemePolaska();
  if (brzi_voz) {
    cout << "Brzi voz ";
  } else
    cout << "Lokalni voz ";
  if (!DaLiKasni()) {
    cout << "broj " << broj_voza << ", odrediste " << odrediste
         << ", polazi sa perona " << broj_perona << " u ";
    if (sat_polaska < 10)
      cout << "0" << sat_polaska;
    else
      cout << sat_polaska;
    cout << ":";
    if (minute_polaska < 10)
      cout << "0" << minute_polaska;
    else
      cout << minute_polaska;
    cout << ", a na odrediste stize u ";
    if (dolazak.first < 10)
      cout << "0" << dolazak.first;
    else
      cout << dolazak.first;
    cout << ":";
    if (dolazak.second < 10)
      cout << "0" << dolazak.second;
    else
      cout << dolazak.second;
    cout << ". Putnicima i voznom osoblju zelimo ugodno putovanje." << endl;

  } else {
    cout << "broj " << broj_voza << ", odrediste " << odrediste
         << ", sa predvidjenim vremenom polaska u ";
    if (sat_polaska < 10)
      cout << "0" << sat_polaska;
    else
      cout << sat_polaska;
    cout << ":";
    if (minute_polaska < 10)
      cout << "0" << minute_polaska;
    else
      cout << minute_polaska;
    cout << ", kasni oko " << kasnjenje << " minuta, te ce poci oko ";
    if (polazak.first < 10)
      cout << "0" << polazak.first;
    else
      cout << polazak.first;
    cout << ":";
    if (polazak.second < 10)
      cout << "0" << polazak.second;
    else
      cout << polazak.second;
    cout << ". Ocekuje se da voz stigne na odrediste oko ";
    if (dolazak.first < 10)
      cout << "0" << dolazak.first;
    else
      cout << dolazak.first;
    cout << ":";
    if (dolazak.second < 10)
      cout << "0" << dolazak.second;
    else
      cout << dolazak.second;
    cout << ". Izvinjavamo se putnicima zbog eventualnih neugodnosti." << endl;
  }
}

class RedVoznje {
  //Polazak **sviPolasci;
  vector<shared_ptr<Polazak>> sviPolasci;
  //int max_polazaka;
  //int broj_polazaka;
    static bool KojiPolazakJePrije(shared_ptr<Polazak> p1, shared_ptr<Polazak> p2)
    {
        int h1 = p1->DajOcekivanoVrijemePolaska().first;
        int m1 = p1->DajOcekivanoVrijemePolaska().second;
        int h2 = p2->DajOcekivanoVrijemePolaska().first;
        int m2 = p2->DajOcekivanoVrijemePolaska().second;
        if(h2>h1) return true;
        else if(h2==h1){
            if(m2>m1) return true;
        }
        return false;
    }
    public:
  explicit RedVoznje(/*int max_broj_polazaka*/);
  RedVoznje(std::initializer_list<Polazak> lista_polazaka);
  //~RedVoznje();
  RedVoznje(const RedVoznje &red_voznje);
  RedVoznje(RedVoznje &&red_voznje);
  RedVoznje &operator=(const RedVoznje &red_voznje);
  RedVoznje &operator=(RedVoznje &&red_voznje);
  void RegistrirajPolazak(std::string odrediste, int broj_voza, bool brzi_voz,
                          int broj_perona, int sat_polaska, int minute_polaska,
                          int trajanje_voznje);
  void RegistrirajPolazak(/*Polazak *polazak*/shared_ptr<Polazak> polazak);
  int DajBrojPolazaka() const;
  int DajBrojPolazakaKojiKasne() const;
  int DajProsjecnoTrajanjeVoznji() const;
  Polazak &DajPrviPolazak() const;
  Polazak &DajPosljednjiPolazak() const;
  void IsprazniRedVoznje();
  void Ispisi(int sati, int minute) const;
};

RedVoznje::RedVoznje(/*int max_broj_polazaka*/) {
  sviPolasci.resize(0);
}

RedVoznje::RedVoznje(initializer_list<Polazak> lista_polazaka)
{
    sviPolasci.resize(lista_polazaka.size());
  auto it = lista_polazaka.begin();
  for (int i = 0; i < lista_polazaka.size(); i++) {
    sviPolasci[i] = make_shared<Polazak>(*it);
    it++;
  }
}
/*
RedVoznje::~RedVoznje() {
  for (int i = 0; i < broj_polazaka; i++)
    delete sviPolasci[i];
  delete[] sviPolasci;
  broj_polazaka = 0;
}
*/
RedVoznje::RedVoznje(const RedVoznje &red_voznje)
    : sviPolasci(red_voznje.sviPolasci.size()){
  for (int i = 0; i < sviPolasci.size(); i++)
    sviPolasci[i] = make_shared<Polazak>(*red_voznje.sviPolasci[i]);
}

RedVoznje::RedVoznje(RedVoznje &&red_voznje)
    : sviPolasci(move(red_voznje.sviPolasci)){}



RedVoznje &RedVoznje::operator=(const RedVoznje &red_voznje) {

    if(&red_voznje!=this){
  sviPolasci.resize(red_voznje.sviPolasci.size());
  for(int i=0; i<red_voznje.sviPolasci.size(); i++)
        sviPolasci[i] = make_shared<Polazak>(*red_voznje.sviPolasci[i]);
  }
  return *this;
}

RedVoznje &RedVoznje::operator=(RedVoznje &&red_voznje) {
  if (&red_voznje != this) {
      sviPolasci = move(red_voznje.sviPolasci);
  }
  return *this;
}

void RedVoznje::RegistrirajPolazak(std::string odrediste, int broj_voza,
                                   bool brzi_voz, int broj_perona,
                                   int sat_polaska, int minute_polaska,
                                   int trajanje_voznje) {
  shared_ptr<Polazak> polazak(make_shared<Polazak>(odrediste,broj_voza,broj_perona,brzi_voz,sat_polaska,minute_polaska,trajanje_voznje));
  sviPolasci.push_back(polazak);
}

void RedVoznje::RegistrirajPolazak(shared_ptr<Polazak> polazak) {
  sviPolasci.push_back(polazak);
}

int RedVoznje::DajBrojPolazaka() const { return sviPolasci.size(); }

int RedVoznje::DajBrojPolazakaKojiKasne() const {
  int brojac = 0;
  for (int i = 0; i < sviPolasci.size(); i++) {
    if (sviPolasci[i]->DaLiKasni())
      brojac++;
  }
  return brojac;
}

int RedVoznje::DajProsjecnoTrajanjeVoznji() const {
  double sumaKasnjenja = 0;
  for (int i = 0; i < sviPolasci.size(); i++) {
    sumaKasnjenja += sviPolasci[i]->DajTrajanjeVoznje();
  }
  return sumaKasnjenja / double(sviPolasci.size());
}

Polazak &RedVoznje::DajPrviPolazak() const {
  if (sviPolasci.size() == 0)  throw domain_error("Nema nijednog polaska");
  auto p = max_element(sviPolasci.begin(), sviPolasci.end(),
                       [](shared_ptr<Polazak> p1, shared_ptr<Polazak> p2) -> bool { 
                        auto s1= p1->DajOcekivanoVrijemePolaska().first;
                        auto m1= p1->DajOcekivanoVrijemePolaska().second;
                        auto s2= p2->DajOcekivanoVrijemePolaska().first;
                        auto m2= p2->DajOcekivanoVrijemePolaska().second;
                        return (s2*60+m2)<(s1*60+m1);
                       });
    return **p;
}

Polazak &RedVoznje::DajPosljednjiPolazak() const {
     if (sviPolasci.size() == 0) throw domain_error("Nema nijednog polaska");
  auto p = min_element(sviPolasci.begin(), sviPolasci.end(),
                       [](shared_ptr<Polazak> p1, shared_ptr<Polazak> p2) -> bool { 
                        auto s1= p1->DajOcekivanoVrijemePolaska().first;
                        auto m1= p1->DajOcekivanoVrijemePolaska().second;
                        auto s2= p2->DajOcekivanoVrijemePolaska().first;
                        auto m2= p2->DajOcekivanoVrijemePolaska().second;
                        return (s2*60+m2)<(s1*60+m1);
                       });
    return **p;
}

void RedVoznje::IsprazniRedVoznje() {
  sviPolasci.resize(0);
}

void RedVoznje::Ispisi(int sati, int minute) const {
    if(sviPolasci.size()!=0){
        vector<shared_ptr<Polazak>> pomocni;
        pomocni = sviPolasci;
        sort(pomocni.begin(), pomocni.end(), KojiPolazakJePrije);
        for(int i=0; i<sviPolasci.size(); i++){
        if(pomocni[i]->DajOcekivanoVrijemePolaska().first>sati || (pomocni[i]->DajOcekivanoVrijemePolaska().first==sati && pomocni[i]->DajOcekivanoVrijemePolaska().second>=minute))
        (*pomocni[i]).Ispisi();
    }
    }
    //sort(sviPolasci.begin(), sviPolasci.end(), KojiPolazakJePrije);
}

int main() {
    
  return 0;
}