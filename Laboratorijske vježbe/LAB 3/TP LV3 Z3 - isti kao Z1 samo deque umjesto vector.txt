// TP 2021/2022: LV 3, Zadatak 3
#include <cmath>
#include <iostream>
#include <deque>

using namespace std;

deque<int> IzdvojiElemente(deque<int> v, bool p) {
  deque<int> novi;
  int suma, pom;
  for (int x : v) {
    suma = 0;
    pom = x;
    while (x != 0) {
      suma += fabs(x % 10);
      x /= 10;
    }
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
  deque<int> a;
  cout << "Unesite elemente: ";
  for (i = 0; i < n; i++) {
    cin >> element;
    a.push_back(element);
  }
  deque<int> b(IzdvojiElemente(a, 1));
  deque<int> c(IzdvojiElemente(a, 0));
  
  if (b.size() > 0) {
    for (i = 0; i < b.size() - 1; i++) {
      cout << b[i] << ",";
    }
    if (i == b.size() - 1)
      cout << b[i];
  }
  cout << endl;
  if (c.size() > 0) {
    for (i = 0; i < c.size() - 1; i++) {
      cout << c[i] << ",";
    }
    if (i == c.size() - 1)
      cout << c[i];
  }
  return 0;
}