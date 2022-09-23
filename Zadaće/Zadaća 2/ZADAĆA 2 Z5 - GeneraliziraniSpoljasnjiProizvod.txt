// TP 2021/2022: Zadaća 2, Zadatak 5
#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename Tip1, typename Tip2>
int Velicina(Tip1 pocetak1, Tip2 kraj1) {
  int brojac = 0;
  while (pocetak1 != kraj1) {
    brojac++;
    pocetak1++;
  }
  return brojac;
}

template <typename Tip1, typename Tip2, typename funkcija>
auto GeneraliziraniSpoljasnjiProizvod(Tip1 pocetak1, Tip1 kraj1, Tip2 pocetak2,
                                      Tip2 kraj2, funkcija fja) {
  int brRedova = Velicina(pocetak1, kraj1);
  int brKolona = Velicina(pocetak2, kraj2);

  decltype(fja(*pocetak1, *pocetak2)) **mat = nullptr;
  try {
    mat = new decltype(fja(*pocetak1, *pocetak2)) *[brRedova] {};
    try {
      for (int i = 0; i < brRedova; i++)
        mat[i] = new decltype(fja(*pocetak1, *pocetak2))[brKolona];

      auto a = pocetak1;
      auto b = pocetak2;
      for (int i = 0; i < brRedova; i++) {
        b = pocetak2;
        for (int j = 0; j < brKolona; j++) {
          mat[i][j] = fja(*a, *b);
          b++;
        }
        a++;
      }
    } catch (...) {
      for (int i = 0; i < brRedova; i++) {
        delete[] mat[i];
      }
      delete[] mat;
      throw;
    }
  } catch (...) {
    throw range_error("Nema dovoljno memorije!");
  }
  return mat;
}

int main() {
  vector<double> vektor;
  deque<double> dek;
  int a, b;

  cout << "Duzina prve sekvence: ";
  cin >> a;
  cout << "Elementi prve sekvence: ";
  for (int i = 0; i < a; i++) {
    double temp;
    cin >> temp;
    vektor.push_back(temp);
  }

  cout << "Duzina druge sekvence: ";
  cin >> b;
  cout << "Elementi druge sekvence: ";
  for (int i = 0; i < b; i++) {
    double temp;
    cin >> temp;
    dek.push_back(temp);
  }

  auto rez = GeneraliziraniSpoljasnjiProizvod(
      vektor.begin(), vektor.end(), dek.begin(), dek.end(),
      [](double x, double y) { return x + 2 * y; });

  cout << "Generalizirani spoljasnji proizvod uz f(x,y)=x+2y:";
  for (int i = 0; i < a; i++) {
    cout << endl;
    for (int j = 0; j < b; j++) {
      cout << rez[i][j] << " ";
    }
  }

  for (int i = 0; i < a; i++) {
    delete[] rez[i];
  }

  delete[] rez;

  return 0;
}
