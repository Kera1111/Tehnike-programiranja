// TP 2021/2022: LV 3, Zadatak 5
#include <cmath>
#include <deque>
#include <iostream>

using namespace std;

deque<int> IzdvojiElemente(deque<int> v, bool p) {
  deque<int> novi;
  int suma, temp;
  for(int x=v.size()-1;x>=0;x--){
    suma = 0;
    temp = v.at(x);
    while (temp != 0) {
      suma += fabs(temp % 10);
      temp /= 10;
    }
    if ((p && !(suma % 2)) || (!p && suma % 2)) {
      novi.push_front(v.at(x));
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
  for (i = 0; i <n; i++) {
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

/*
ne radi rasponska ovdje zbg integer overflowa 
povecat ce se zadnji clan a kako ne postoji neki veci clan od MAX integera javlja se greska u ispisu
*/