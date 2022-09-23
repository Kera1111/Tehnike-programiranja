// TP 2021/2022: LV 1, Zadatak 4
#include <iomanip>
#include <iostream>
using namespace std;
int main() {

  double n;
  for (;;) {
    cout << "Unesite prirodan broj ili 0 za kraj: "; 
    cin >> n;
    if (cin && n==0) {
    cout << "Dovidjenja!";
    return 0;
    }else if (n < 0 || !cin || n!=int(n)) {
      cout << "Niste unijeli prirodan broj!" << endl;
      cin.clear();
      cin.ignore(100, '\n');
    }else{
        int i, suma = 0;
        for (i = 1; i < int(n); i++) {
        if (int(n) % i == 0)
            suma += i;
        }
        if (suma < n) {
        cout << "Broj " << n << " je manjkav!" << endl;
        } else if (suma == n) {
        cout << "Broj " << n << " je savrsen!" << endl;
        } else {
        cout << "Broj " << n << " je obilan!" << endl;
        }   
    }
}
  return 0;
}