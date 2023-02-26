// TP 2020/2021: Tutorijal 2, Zadatak 3
#include <complex>
#include <iostream>

using namespace std;
int main() {
  int n, i;
  cout << "Unesite broj elemenata: " << endl;
  cin >> n;
  complex<double> Zk, SumaNazivnika, Z;

  for (i = 1; i <= n; i++) {
    cout << "Z_" << i << " = ";
    cin >> Zk;
    SumaNazivnika = SumaNazivnika + (1. / Zk);
  }
  Z = 1. / SumaNazivnika;

  cout << endl
       << "Paralelna veza ovih elemenata ima impedansu Z_ = " << Z << "."
       << endl;

  return 0;
}
