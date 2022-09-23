// TP 2021/2022: LV 3, Zadatak 1
#include <cmath>
#include <iostream>
#include <vector>


using namespace std;

vector<int> IzdvojiElemente(vector<int> v, bool p) {
  vector<int> novi;
  int suma, pom;
  for (int x : v) {
    /* provjerimo kroz citav vektor clan po clan
    da li je suma cifara parna ili ne */
    suma = 0;
    pom = x; // kao temp varijabla jer cemo dijelit x sa 10
    // suma cifara
    while (x != 0) {        // npr. 15
      suma += fabs(x % 10); // 5+1=6
      x /= 10;              // 15,1,0
    }
    /* ako je vektor za parne onda ubacujemo u njega clanove
    kod kojih je suma djeljiva sa 2, u suprotnom ubacujemo u vektor sa neparnim
    */
    if ((p && !(suma % 2)) || (!p && suma % 2)) {
      novi.push_back(pom);
    }
  }
  return novi;
}

int main() {

  int n;
  cout << "Koliko zelite unijeti elemenata: ";
  cin >> n;

  if (n <= 0) {
    cout << "Broj elemenata mora biti veci od 0!";
    return 0;
  }

  int element, i;
  vector<int> a;
  cout << "Unesite elemente: ";
  for (i = 0; i < n; i++) {
    cin >> element;
    a.push_back(element);
  }
  vector<int> b(IzdvojiElemente(a, 1));
  vector<int> c(IzdvojiElemente(a, 0));

  for (int x : b) {//ispisujemo citav vektor b
    cout << x << " ";
  }
  cout << endl;
  for (int x : c) {//ispisujemo citav vektor c
    cout << x << " ";
  }

  return 0;
}