/*-----------------------------------------------*/
/* ZSR13 - ZADATAK 6 */
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
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
int main() {
  Likovi L(4);
  L.DodajKrug(1); L.DodajTrougao(7,8,9);
  L.DodajPravougaonik(1,6); L.DodajPravougaonik(3,4); // isti obim
  L.Sortiraj();
  std::cout<<L;
  std::cout<<"Broj krugova: "<<L.DajBrojKrugova();
  std::cout<<"\nNajveci lik: "<<L.DajNajveci()->DajNaziv();

  return 0;
}
/*-----------------------------------------------*/
/* ZSR13 - ZADATAK 7 */
#include <iostream>
#include <string>
#include <algorithm>
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
  friend bool operator!(const Knjiga &k) {if (k.clanski_broj)return true; return false;}
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
    k.DajKoliko();
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
  Knjiga a(1, 2022, 0, 2, "abc", "aaa", "zzz");
  Knjiga b(2, 2022, 543, 3, "abc", "bbb", "ppp");
  Udzbenik c(3, 2022, 78, 5, "abc", "bbb", "ppp","predmet");
  Biblioteka lib(3);
  lib.Dodaj(&a); lib.Dodaj(&b); lib.Dodaj(&c);
  lib.Sortiraj();
  ++lib;
  lib.IspisiZaduzeneZaNDana(2);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR13 - ZADATAK 8 */
#include <iostream>
#include <vector>
#include <algorithm>
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
  std::vector<KutijaApstraktna*>vek;
  int izbor=1;
  while(izbor){
    std::cout<<"0-Kraj, 1-Obicna, 2-SaPregradama: ";
    std::cin>>izbor;
    if(izbor==1){
      double tezina_kutije,tezina_sadrzaja;
      std::cout<<"Tezina kutije: "; std::cin>>tezina_kutije;
      std::cout<<"Tezina sadrzaja: "; std::cin>>tezina_sadrzaja;
      KutijaObicna k(tezina_kutije, tezina_sadrzaja);
      vek.push_back(&k);
    }
    else if(izbor==2){
      double tezina_kutije,broj_sadrzaja;
      std::vector<double>tezina_sadrzaja;
      std::cout<<"Tezina kutije: "; std::cin>>tezina_kutije;
      std::cout<<"Broj sadrzaja: "; std::cin>>broj_sadrzaja;
      for(int i=0;i<broj_sadrzaja;i++){
        double x; std::cin>>x;
        tezina_sadrzaja.push_back(x);
      }
      KutijaSaPregradama k(tezina_kutije, tezina_sadrzaja);
      vek.push_back(&k);
    }
    else break;
  }
  std::sort(vek.begin(),vek.end(),[](KutijaApstraktna *a, KutijaApstraktna *b){
            return a->DajUkupnuTezinu()<b->DajUkupnuTezinu();});
  for(KutijaApstraktna* i: vek)
    std::cout<<i->DajTezinu()<<std::endl;
   return 0;
}
/*-----------------------------------------------*/
/* ZSR13 - ZADATAK 9 */
#include <iostream>
#include <cmath>
#include <algorithm>
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
  Predmet **niz;
  int n,broj=0;
  std::cin>>n;
  niz=new Predmet*[n]{};
  for(int i=0;i<n;i++){
    char vrsta; double gustina;
    std::cin>>vrsta>>gustina;
    if(vrsta=='L'){
      double r; std::cin>>r;
      niz[broj++]=new Lopta(gustina, r);
    }
    else if(vrsta=='C'){
      double a,b,c; std::cin>>a>>b>>c;
      niz[broj++]=new Cigla(gustina,a,b,c);
    }
    else{
      std::cout<<"Pogresan unos! Ponovite!\n"; i--;
    }
  }
  std::sort(niz, niz+n,[](Predmet *a, Predmet *b){
    return a->DajMasu()<b->DajMasu();
  });
  for(int i=0;i<n;i++)
    std::cout<<niz[i]->DajZapreminu()<<" "<<niz[i]->DajMasu()<<std::endl;
    for(int i=0;i<n;i++)delete niz[i]; delete[] niz;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR13 - ZADATAK 10 */
#include <iostream>
#include <string>
#include <algorithm>
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
  Skladiste s(2);
  s.DodajSanduk("s",1,2,1);
  s.DodajBure("b",5,2);
  s.Ispisi();
  return 0;
}
/*-----------------------------------------------*/