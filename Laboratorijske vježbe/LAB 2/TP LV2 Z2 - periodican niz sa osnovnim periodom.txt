// TP 2020/2021: Tutorijal 2, Zadatak 2
#include <iostream>
#include <vector>
using namespace std;

bool TestPerioda(vector<double> vektor, int p) {

  int i;
  if (vektor.size() - p <= 0 || vektor.size() == 1)
    return false;

  for (i = 0; i < vektor.size() - p; i++) {
    if (vektor[i] != vektor[i + p])
      return false;
  }

  return true;
}

int OdrediOsnovniPeriod(vector<double> vektor) {

  int i;
  for (i = 1; i < vektor.size(); i++) {
    bool period(false);
    if (vektor[i] == vektor[0]) {
      period = TestPerioda(vektor, i);
      if (period)
        return i;
    }
  }

  return 0;
}

int main() {
  vector<double> vektor;
  double n;
  cout << "Unesite slijed brojeva (0 za kraj): ";
  cin >> n;
  while (n != 0) {
    vektor.push_back(n);
    cin >> n;
  }
  if (OdrediOsnovniPeriod(vektor)) {
    cout << "Slijed je periodican sa osnovnim periodom "
         << OdrediOsnovniPeriod(vektor) << "." << endl;
  } else {
    cout << "Slijed nije periodican!" << endl;
  }

  return 0;
}
