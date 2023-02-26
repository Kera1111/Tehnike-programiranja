// TP 2020/2021: Tutorijal 2, Zadatak 4
#include <complex>
#include <iostream>

using namespace std;
int main() {
  int n, i;
  cout << "Unesite broj elemenata: " << endl;
  cin >> n;
  double Re, Im;
  complex<double> Zk, SumaNazivnika, Z;

  for (i = 1; i <= n; i++) {
    cout << "R" << i << " = ";
    cin >> Re;
    cout << "X" << i << " = ";
    cin >> Im;
    Zk = complex<double>(Re, Im);
    SumaNazivnika = SumaNazivnika + (1. / Zk);
    cout << endl;
  }
  Z = 1. / SumaNazivnika;

  cout << "Paralelna veza ovih elemenata ima R = " << real(Z)
       << " i X = " << imag(Z) << "." << endl;

  return 0;
}
