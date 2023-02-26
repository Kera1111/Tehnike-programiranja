// TP 2021/2022: LV 3, Zadatak 4
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
      novi.push_front(pom);
    }
/*ovo ne bi radilo da smo koristili vector umjesto deque jer nije push_front ukljucen
kod vectora*/
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
/*posto treba ispis da ide od zadnjih ka naprijed clanovima
-- 3.
-- 7.

da je bilo:
1. sa push_front unos vektora a i for od prvog ka zadnjem, a gore push_front
unos: 1 2 3 4 5
a: 5 4 3 2 1
b: 2 4
c: 1 3 5
2. sa push_front unos vektora a i for od prvog ka zadnjem, a gore push_back
a: 5 4 3 2 1
b: 4 2
c: 5 3 1
3. sa push_back unos vektora a i for od prvog ka zadnjem, a gore push_front
a: 1 2 3 4 5
b: 4 2
c: 5 3 1
4. sa push_back unos vektora a i for od prvog ka zadnjem a gore push_back
a: 1 2 3 4 5
b: 2 4
c: 1 3 5
5. sa push_front unos vektora a i for od zadnjeg ka prvom, a gore push_front
unos: 1 2 3 4 5
a: 5 4 3 2 1
b: 2 4
c: 1 3 5
6. sa push_front unos vektora a i for od zadnjeg ka prvom, a gore push_back
a: 5 4 3 2 1
b: 4 2
c: 5 3 1
7. sa push_back unos vektora a i for od zadnjeg ka prvom, a gore push_front
a: 1 2 3 4 5
b: 4 2
c: 5 3 1
8. sa push_back unos vektora a i for od zadnjeg ka prvom a gore push_back
a: 1 2 3 4 5
b: 2 4
c: 1 3 5
*/
  for (i = n; i > 0; i--) {
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