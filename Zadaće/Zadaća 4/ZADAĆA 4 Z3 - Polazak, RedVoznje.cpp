// TP 2021/2022: Zadaća 4, Zadatak 3
#include <algorithm>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

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
  if (broj_voza >= 100000)
    throw domain_error("Broj voza moze imati maksimalno 5 cifara");
  Polazak::broj_voza = broj_voza;
  if (broj_perona < 0 || broj_perona > 6)
    throw domain_error("Broj perona mora biti cijeli broj u opsegu od 1 do 6");
    if(!DaLiJeOKUnesenoVrijeme(sat_polaska, minute_polaska, trajanje_voznje)) 
    throw domain_error("Besmislene vrijednosti za sate i minute polaska i trajanje voznje");
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
  Polazak **svi_polasci;
  int max_polazaka;
  int broj_polazaka;
    static bool KojiPolazakJePrije(const Polazak *p1, const Polazak *p2)
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
  explicit RedVoznje(int max_broj_polazaka);
  RedVoznje(std::initializer_list<Polazak> lista_polazaka);
  ~RedVoznje();
  RedVoznje(const RedVoznje &red_voznje);
  RedVoznje(RedVoznje &&red_voznje);
  RedVoznje &operator=(const RedVoznje &red_voznje);
  RedVoznje &operator=(RedVoznje &&red_voznje);
  void RegistrirajPolazak(std::string odrediste, int broj_voza, bool brzi_voz,
                          int broj_perona, int sat_polaska, int minute_polaska,
                          int trajanje_voznje);
  void RegistrirajPolazak(Polazak *polazak);
  int DajBrojPolazaka() const;
  int DajBrojPolazakaKojiKasne() const;
  int DajProsjecnoTrajanjeVoznji() const;
  Polazak &DajPrviPolazak() const;
  Polazak &DajPosljednjiPolazak() const;
  void IsprazniRedVoznje();
  void Ispisi(int sati, int minute) const;
};

RedVoznje::RedVoznje(int max_broj_polazaka) {
  if (max_broj_polazaka < 0)
    throw;
  svi_polasci = new Polazak *[max_broj_polazaka];
  max_polazaka = max_broj_polazaka;
  broj_polazaka = 0;
}

RedVoznje::RedVoznje(initializer_list<Polazak> lista_polazaka)
    : max_polazaka(lista_polazaka.size()),
      svi_polasci(new Polazak *[lista_polazaka.size()]),
      broj_polazaka(lista_polazaka.size()) {
  auto it = lista_polazaka.begin();
  for (int i = 0; i < lista_polazaka.size(); i++) {
    svi_polasci[i] = new Polazak(*it);
    it++;
  }
}

RedVoznje::~RedVoznje() {
  for (int i = 0; i < broj_polazaka; i++)
    delete svi_polasci[i];
  delete[] svi_polasci;
  broj_polazaka = 0;
}

RedVoznje::RedVoznje(const RedVoznje &red_voznje)
    : max_polazaka(red_voznje.max_polazaka),
      svi_polasci(new Polazak *[red_voznje.max_polazaka]),
      broj_polazaka(red_voznje.broj_polazaka) {
  for (int i = 0; i < broj_polazaka; i++)
    svi_polasci[i] = new Polazak(*red_voznje.svi_polasci[i]);
}

RedVoznje::RedVoznje(RedVoznje &&red_voznje)
    : svi_polasci(red_voznje.svi_polasci),
      max_polazaka(red_voznje.max_polazaka),
      broj_polazaka(red_voznje.broj_polazaka) {
  red_voznje.svi_polasci = nullptr;
  red_voznje.broj_polazaka = 0;
}

RedVoznje &RedVoznje::operator=(const RedVoznje &red_voznje) {
  if(&red_voznje==this) return *this;
  for(int i=0; i<broj_polazaka; i++) delete[] svi_polasci[i];
  delete[] svi_polasci;
  max_polazaka=red_voznje.max_polazaka;
  broj_polazaka=red_voznje.broj_polazaka;
  svi_polasci=new Polazak*[red_voznje.max_polazaka];
  for(int i=0; i<red_voznje.broj_polazaka; i++){
      svi_polasci[i] = new Polazak(*red_voznje.svi_polasci[i]);
  }
  return *this;
}

RedVoznje &RedVoznje::operator=(RedVoznje &&red_voznje) {
  if (&red_voznje != this) {
    for (int i = 0; i < broj_polazaka; i++)
      delete svi_polasci[i];
    delete[] svi_polasci;
    svi_polasci = red_voznje.svi_polasci;
    broj_polazaka = red_voznje.broj_polazaka;
    max_polazaka = red_voznje.max_polazaka;
    red_voznje.svi_polasci = nullptr;
    red_voznje.broj_polazaka = 0;
  }
  return *this;
}

void RedVoznje::RegistrirajPolazak(std::string odrediste, int broj_voza,
                                   bool brzi_voz, int broj_perona,
                                   int sat_polaska, int minute_polaska,
                                   int trajanje_voznje) {
  if (broj_polazaka == max_polazaka)
    throw range_error("Dostignut maksimalni broj polazaka");
  svi_polasci[broj_polazaka++] =
      new Polazak(odrediste, broj_voza, broj_perona, brzi_voz, sat_polaska,
                  minute_polaska, trajanje_voznje);
}

void RedVoznje::RegistrirajPolazak(Polazak *polazak) {
  if (broj_polazaka == max_polazaka)
    throw range_error("Dostignut maksimalni broj polazaka");
  svi_polasci[broj_polazaka] = polazak;
  broj_polazaka++;
}

int RedVoznje::DajBrojPolazaka() const { return broj_polazaka; }

int RedVoznje::DajBrojPolazakaKojiKasne() const {
  int brojac = 0;
  for (int i = 0; i < broj_polazaka; i++) {
    if ((*svi_polasci[i]).DaLiKasni())
      brojac++;
  }
  return brojac;
}

int RedVoznje::DajProsjecnoTrajanjeVoznji() const {
  double sumaKasnjenja = 0;
  for (int i = 0; i < broj_polazaka; i++) {
    sumaKasnjenja += svi_polasci[i]->DajTrajanjeVoznje();
  }
  return sumaKasnjenja / double(broj_polazaka);
}

Polazak &RedVoznje::DajPrviPolazak() const {
  if (broj_polazaka == 0)
    throw domain_error("Nema nijednog polaska");
  auto p = max_element(svi_polasci, svi_polasci + broj_polazaka,
                       [](Polazak *p1, Polazak *p2) -> bool { 
                        auto s1= p1->DajOcekivanoVrijemePolaska().first;
                        auto m1= p1->DajOcekivanoVrijemePolaska().second;
                        auto s2= p2->DajOcekivanoVrijemePolaska().first;
                        auto m2= p2->DajOcekivanoVrijemePolaska().second;
                        return (s2*60+m2)<(s1*60+m1);
                       });
    return **p;
}

Polazak &RedVoznje::DajPosljednjiPolazak() const {
     if (broj_polazaka == 0)
    throw domain_error("Nema nijednog polaska");
  auto p = min_element(svi_polasci, svi_polasci + broj_polazaka,
                       [](Polazak *p1, Polazak *p2) -> bool { 
                        auto s1= p1->DajOcekivanoVrijemePolaska().first;
                        auto m1= p1->DajOcekivanoVrijemePolaska().second;
                        auto s2= p2->DajOcekivanoVrijemePolaska().first;
                        auto m2= p2->DajOcekivanoVrijemePolaska().second;
                        return (s2*60+m2)<(s1*60+m1);
                       });
    return **p;
}

void RedVoznje::IsprazniRedVoznje() {
  for_each(svi_polasci, svi_polasci + broj_polazaka,
           [](Polazak *p) { delete p; });
  broj_polazaka = 0;
}

void RedVoznje::Ispisi(int sati, int minute) const {
    sort(svi_polasci, svi_polasci+broj_polazaka, KojiPolazakJePrije);
    for(int i=0; i<broj_polazaka; i++){
        if(svi_polasci[i]->DajOcekivanoVrijemePolaska().first>sati || (svi_polasci[i]->DajOcekivanoVrijemePolaska().first==sati && svi_polasci[i]->DajOcekivanoVrijemePolaska().second>=minute))
        (*svi_polasci[i]).Ispisi();
    }
}

int main() {
    RedVoznje v(5);
    v.RegistrirajPolazak("Mostar",123,true,2,12,45,230);
    v.RegistrirajPolazak("Sarajevo",124,true,4,12,45,230);
    v.RegistrirajPolazak("Mostar",123,false,2,15,45,230);
    v.RegistrirajPolazak("Bihac",125,true,3,12,45,230);
    v.RegistrirajPolazak("Mostar",126,false,5,17,45,530);
    Polazak* polazak = new Polazak("Banja Luka",127,true,2,12,45,330);
    v.RegistrirajPolazak(polazak);
    cout<<"Broj polazaka: "<<v.DajBrojPolazaka()<<endl;
    cout<<"Broj polazaka koji kasne: "<<v.DajBrojPolazakaKojiKasne()<<endl;
    cout<<"Prosjecno trajanje voznje: "<<v.DajProsjecnoTrajanjeVoznji()<<endl;
    Polazak prvi = v.DajPrviPolazak();
    Polazak posljednji = v.DajPosljednjiPolazak();
    cout<<"Prvi polazak dana: "; prvi.Ispisi(); cout<<endl;
    cout<<"Zadnji polazak dana: "; posljednji.Ispisi(); cout<<endl;
  return 0;
}
