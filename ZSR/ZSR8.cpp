/*-----------------------------------------------*/
/* ZSR8 - ZADATAK 6 */
#include <iostream>
#include <string>
#include <map>
std::string MonoalfabetskiSistem(std::string s, std::map<char, char>mapa) {
  std::string novi = s;
  for (int i = 0; i < s.size(); i++)
    for (std::pair<char, char> c : mapa)
      if (s[i] == c.first)novi[i] = c.second;
  return novi;
}
int main() {
  std::cout << MonoalfabetskiSistem("abc", { {'a', 'x'}, {'b', 'c'}, {'c', 'a'}});
  return 0;
}
/*-----------------------------------------------*/
/* ZSR8 - ZADATAK 10 */
#include <iostream>
#include <list>
#include <complex>
struct Kompleksni {
  double re, im;
  Kompleksni *sljedeci;
};
void ObrisiListu(Kompleksni *pocetak) {
  while (pocetak != nullptr) {
    Kompleksni *temp = pocetak;
    pocetak = pocetak->sljedeci;
    delete temp;
  }
}
Kompleksni* KreirajListu(std::list<std::complex<double>>l) {
  auto it = l.begin();
  Kompleksni *pocetak = nullptr, *prethodni;
  for (int i = 0; i < l.size(); i++) {
    Kompleksni *novi = new Kompleksni{(*it).real(), (*it).imag(), nullptr};
    if (!pocetak)pocetak = novi;
    else prethodni->sljedeci = novi;
    prethodni = novi;
    it++;
  }
  return pocetak;
}
int main() {
  std::list<std::complex<double>>l{{1, 2}, {3, 4}, {5, 6}};
  Kompleksni *pocetak = KreirajListu(l);
  for (Kompleksni *p = pocetak; p != nullptr; p = p->sljedeci)
    std::cout << "(" << p->re << "," << p->im << ") ";
  ObrisiListu(pocetak);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR8 - ZADATAK 11 */
#include <iostream>
#include <vector>
#include <utility>
struct Koordinata {
  double x, y;
  Koordinata *sljedeci;
};
void ObrisiListu(Koordinata *pocetak) {
  while (pocetak != nullptr) {
    Koordinata *temp = pocetak;
    pocetak = pocetak->sljedeci;
    delete temp;
  }
}
Koordinata* KreirajListu(std::vector<std::pair<double, double>> v) {
  Koordinata *pocetak = nullptr, *prethodni;
  for (int i = 0; i < v.size(); i++) {
    Koordinata *novi = new Koordinata{v[i].first, v[i].second, nullptr};
    if (!pocetak)pocetak = novi;
    else prethodni->sljedeci = novi;
    prethodni = novi;
  }
  return pocetak;
}
int main() {
  std::vector<std::pair<double, double>>l{{1, 2}, {3, 4}, {5, 6}};
  Koordinata *pocetak = KreirajListu(l);
  for (Koordinata *p = pocetak; p != nullptr; p = p->sljedeci)
    std::cout << "(" << p->x << "," << p->y << ") ";
  ObrisiListu(pocetak);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR8 - ZADATAK 12 */
#include <iostream>
#include <deque>
#include <cmath>
struct Cvor {
  unsigned int broj;
  Cvor *veza;
};
void ObrisiListu(Cvor *pocetak) {
  while (pocetak != nullptr) {
    Cvor *temp = pocetak;
    pocetak = pocetak->veza;
    delete temp;
  }
}
Cvor *KreirajListu(std::deque<int>d) {
  Cvor *pocetak = nullptr, *prethodni;
  for (int i = 0; i < d.size(); i++) {
    Cvor *novi = new Cvor{d[i], nullptr};
    if (!pocetak)pocetak = novi;
    else prethodni->veza = novi;
    prethodni = novi;
  }
  return pocetak;
}
bool JeLiProst(unsigned int n) {
  if (n <= 1)return false;
  for (unsigned int i = 2; i <= sqrt(n); i++)
    if (n % i == 0)return false;
  return true;
}
int BrojProstih(Cvor *pocetak) {
  int broj = 0;
  for (Cvor *p = pocetak; p != nullptr; p = p->veza)
    if (JeLiProst(p->broj))broj++;
  return broj;
}
int main() {
  Cvor *pocetak = KreirajListu({1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::cout << BrojProstih(pocetak);
  ObrisiListu(pocetak);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR8 - ZADATAK 13 */
#include <iostream>
#include <deque>
#include <cmath>
struct Cvor {
long broj;
Cvor *veza;
};
void ObrisiListu(Cvor *pocetak){
while(pocetak!=nullptr){
    Cvor* temp=pocetak;
    pocetak=pocetak->veza;
    delete temp;
}
}
Cvor* KreirajListu(std::deque<int>d){
Cvor* pocetak=nullptr, *prethodni;
for(int i=0;i<d.size();i++){
    Cvor* novi=new Cvor{d[i], nullptr};
    if(!pocetak)pocetak=novi;
    else prethodni->veza=novi;
    prethodni=novi;
}
return pocetak;
}
int BrojParnih(Cvor *pocetak){
    int broj=0;
  for(Cvor *p=pocetak; p!=nullptr; p=p->veza)
    if(p->broj%2==0)broj++;
return broj;
}
int main() {
   Cvor *pocetak=KreirajListu({1,2,3,4,5,6,7,8,9});
   std::cout<<BrojParnih(pocetak);
   ObrisiListu(pocetak);
  return 0;
}
/*-----------------------------------------------*/