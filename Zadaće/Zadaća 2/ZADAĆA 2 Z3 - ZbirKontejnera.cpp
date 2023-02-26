// TP 2021/2022: Zadaća 2, Zadatak 3
#include <algorithm>
#include <cmath>
#include <iostream>
#include <type_traits>
#include <vector>

using namespace std;

template <typename nekiTip>
int Velicina(nekiTip kontejner) { // nadji velicinu kontejnera
  unsigned int vel = 0;
  for_each(kontejner.begin(), kontejner.end(), [&vel](auto x) { vel++; });
  // povecavaj velicinu kako prolazis kroz kontejner
  return vel;
}

template <typename nekiDrugiTip, typename nekiTreciTip>
auto ZbirKontejnera(nekiDrugiTip kontejner1, nekiTreciTip kontejner2) {
  int vel1(Velicina(kontejner1));
  int vel2(Velicina(kontejner2));
  int i = 0;
  auto poz1 = kontejner1.begin();
  auto poz2 = kontejner2.begin();
  vector<decltype(*poz1 + *poz2)> konacni(max(vel1, vel2));
  typedef typename remove_reference<decltype(*poz1)>::type nekiTip1;
  typedef typename remove_reference<decltype(*poz2)>::type nekiTip2;

  while (1) { // prodji kroz prvi kontejner

    if (poz1 == kontejner1.end() && poz2 == kontejner2.end())
      return konacni;

    if (poz2 == kontejner2.end()) { // ako naletis na kraj drugog odmah onda ti
                                    // je konacni samo prvi kontejner pa njega
                                    // dodaj na samo na konacni s while
      while (poz1 != kontejner1.end()) {
        konacni[i] = *poz1++ + nekiTip2();
        i++;
      }
      return konacni;
    }

    if (poz1 ==
        kontejner1.end()) { // ako si zavrsio s dodavanjam prvog tj. vel2 je
                            // veca od vel1 e onda ti samo dodaj clanove
                            // drugog kontejnera ne moras prvi vise ni gledat
                            // (dodavanje izvrsi opet sa while petljom)
      while (poz2 != kontejner2.end()) {
        konacni[i] = *poz2++ + nekiTip1();
        i++;
      }
      return konacni;
    }
    konacni[i] =
        *poz1++ +
        *poz2++; // ako nisi naletio na onaj if onda ti obavi fino sabiranje tj
                 // na konacni dodaj vrijednosti od prvog i onda od drugog zato
                 // i ide *, a poz1++ poz2++ povecava se jer sljedeci put hocemo
                 // da dodamo clan sljedeci od prvog i drugog kontejnera
    i++;
  }

  return konacni;
}

int main() {
  int a, b;
  double temp;
  cout << "Duzina prvog kontejnera: ";
  cin >> a;
  cout << "Elementi prvog kontejnera: ";
  vector<double> vektor1(a);
  for (int i = 0; i < a; i++) {
    cin >> temp;
    vektor1.at(i) = temp;
  }

  cout << "Duzina drugog kontejnera: ";
  cin >> b;
  vector<double> vektor2(b);
  cout << "Elementi drugog kontejnera: ";

  for (int i = 0; i < b; i++) {
    cin >> temp;
    vektor2.at(i) = temp;
  }
  cout << "Zbir kontejnera: ";
  auto rezultat(ZbirKontejnera(vektor1, vektor2));
  for_each(rezultat.begin(), rezultat.end(), [](auto x) { cout << x << " "; });
  return 0;
}
