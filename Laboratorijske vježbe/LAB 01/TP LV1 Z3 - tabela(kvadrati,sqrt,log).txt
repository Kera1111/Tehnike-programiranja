// TP 2021/2022: LV 1, Zadatak 3
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;
int main() {

  int broj1, broj2;
  cout << "Unesite pocetnu i krajnju vrijednost: ";
  cin >> broj1 >> broj2;
  cout << endl;
  int i;
  
  cout << "+---------+----------+----------+-----------+" << endl;
  cout << "| Brojevi | Kvadrati | Korijeni | Logaritmi |" << endl;
  cout << "+---------+----------+----------+-----------+" << endl;
  
  for (i = broj1; i <= broj2; i++) {
    cout << "| " << left << setw(8) << i ;
    cout << "| " << right << setw(8) << i * i << setprecision(3) << fixed;
    cout << " | " << right << setw(8) << sqrt(i) << setprecision(5) << fixed;
    cout << " | " << right << setw(9) << log(i) << " |" << endl;
  }
  cout << "+---------+----------+----------+-----------+" << endl;
  return 0;
}