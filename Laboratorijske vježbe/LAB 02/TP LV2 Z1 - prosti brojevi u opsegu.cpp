// TP 2020/2021: Tutorijal 2, Zadatak 1
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// DEKLARISANJE FJA
bool DaLiJeProst(int n);
vector<int> ProstiBrojeviUOpsegu(int a, int b);

int main() {
  int x, y, i;
  // UNOS
  cout << "Unesite pocetnu i krajnju vrijednost: ";
  cin >> x >> y;

  vector<int> vektor = ProstiBrojeviUOpsegu(x, y);

  // ISPIS PROSTIH BROJEVA
  if (vektor.size() > 0) {
    cout << "Prosti brojevi u rasponu od " << x << " do " << y << " su: ";
    for (i = 0; i < vektor.size(); i++) {
      if (i == 0 && vektor[i] != 0) {
        // za prvi red mi ne treba ovaj zarez ko kod ostalih
        cout << vektor[i];
      } else if (vektor[i] != 0) {
        cout << ", " << vektor[i];
      }
    }
    cout << endl;
  } else {
    cout << endl
         << "Nema prostih brojeva u rasponu od " << x << " do " << y << "!";
  }
  return 0;
}

bool DaLiJeProst(int n) {
  int i;
  if (n < 2)
    return false;
  for (i = 2; i <= sqrt(n); i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

vector<int> ProstiBrojeviUOpsegu(int a, int b) {
  vector<int> konacni;
  int i;
  for (i = a; i < b; i++) {
    // javit ce se int overflow pa krahira ako bi islo do i<=b jer se
    // i++ i onda belaji nastaju, dok ovako razlaganjem na dva dijela
    // gdje u jednom ifu ispitamo za zadnji clan tj b ubacimo ga u
    // konacni vektor
    if (DaLiJeProst(i))
      konacni.push_back(i);
  }
  if (DaLiJeProst(b)) {
    konacni.push_back(b);
  }
  return konacni;
}