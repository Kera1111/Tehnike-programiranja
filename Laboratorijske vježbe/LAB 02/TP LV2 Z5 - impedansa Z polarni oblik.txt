// TP 2020/2021: Tutorijal 2, Zadatak 5
#include <complex>
#include <iostream>

using namespace std;
int main() {
  int n, i;
  cout << "Unesite broj elemenata:" << endl;
  cin >> n;
  double fi, Zt;
  complex<double> Zk, SumaNazivnika, Z;

  for (i = 1; i <= n; i++) {
    cout << "Z" << i << " = ";
    cin >> Zt;
    cout << "fi" << i << " = ";
    cin >> fi;
    Zk = polar(Zt, ((fi * 4 * atan(1)) / (180)));
    SumaNazivnika = SumaNazivnika + (1. / Zk);
    cout << endl;
  }
  Z = 1. / SumaNazivnika;

  cout << "Paralelna veza ovih elemenata ima Z = " << abs(Z)
       << " i fi = " << arg(Z) * 180 / (4 * atan(1)) << "." << endl;

  return 0;
}
