#include <array>
#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

#define EPS 0.0000000001

using namespace std;

typedef array<vector<vector<double>>, 2> trodimMatrica;
typedef vector<vector<double>> Matrica;
typedef vector<double> Vektor;

bool jelGrbavaMatrica(Matrica a) {

  int brkolonaa = 0;
  for (int i = 0; i < a.size(); i++) {
    if (i == 0)
      brkolonaa = a.at(i).size();
    else if (brkolonaa != a.at(i).size())
      return true;
  }
  return false;
}

Matrica MnozenjeMatrica(Matrica a, Matrica b) {
  Matrica c;

  int brkolonaa = 0, brkolonab = 0, brredovaa = a.size(), brredovab = b.size();

  if (a.size() == 0 && b.size() == 0) {
    return c;
  }

  if (jelGrbavaMatrica(a) || jelGrbavaMatrica(b)) {
    throw domain_error("Neispravna matrica!");
  }

  for (int i = 0; i < a.size(); i++) {
    if (i == 0)
      brkolonaa = a.at(i).size();
    else if (brkolonaa != a.at(i).size())
      throw domain_error("Neispravna matrica!");
  }

  for (int i = 0; i < b.size(); i++) {
    if (i == 0)
      brkolonab = b.at(i).size();
    else if (brkolonab != b.at(i).size())
      throw domain_error("Neispravna matrica!");
  }

  if (brkolonaa != brredovab)
    throw domain_error("Matrice nisu saglasne za mnozenje!");

  c.resize(brredovaa);
  for (int i = 0; i < brredovaa; i++) {
    c.at(i).resize(brkolonab);
  }

  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < b.at(i).size(); j++) {
      double suma = 0;
      for (int k = 0; k < b.size(); k++) {
        suma += a.at(i).at(k) * b.at(k).at(j);
      }
      c.at(i).at(j) = suma;
    }
  }
  return c;
}

bool jelMatricaKvadratnogOblika(Matrica a) {
  if (jelGrbavaMatrica(a))
    return false;

  int brkolonaa = 0;
  for (int i = 0; i < a.size(); i++) {
    brkolonaa = a.at(i).size();
    if (brkolonaa != a.size())
      return false;
  }

  return true;
}

trodimMatrica DoolittleLU(Matrica h) {
  array<vector<vector<double>>, 2> lu;

  if (jelGrbavaMatrica(h)) {
    throw domain_error("Neispravna matrica!");
  }

  if (!jelMatricaKvadratnogOblika(h)) {
    throw domain_error("Matrica mora biti kvadratna!");
  }

  Matrica l(h.size(), Vektor(h.size()));
  Matrica u(h.size(), Vektor(h.size()));

  for (int i = 0; i < h.size(); i++) {
    for (int j = i; j < h.size(); j++) {
      double S = 0;
      for (int k = 0; k < i; k++) {
        S += (l.at(i).at(k) * u.at(k).at(j));
      }
      u.at(i).at(j) = h.at(i).at(j) - S;

      if (i == j) {
        l.at(i).at(j) = 1;
      } else {
        double S = 0;
        for (int k = 0; k < i; k++)

        {
          S += l.at(j).at(k) * u.at(k).at(i);
        }
        l.at(j).at(i) = h.at(j).at(i) - S;
        l.at(j).at(i) /= (u.at(i).at(i));
      }
      if (fabs(u.at(i).at(i)) < EPS) {
        throw domain_error("Matrica je singularna!");
      }
    }
  }
  lu.at(0) = l;
  lu.at(1) = u;

  return lu;
}

bool ProvjeriFaktorizaciju(Matrica h, trodimMatrica lu) {
  if (h.size() == 0 && lu.at(1).size() == 0 && lu.at(0).size() == 0) {
    return true;
  }
  Matrica provjera = MnozenjeMatrica(lu.at(0), lu.at(1));
  if (h.size() != provjera.size())
    return false;
  for (int i = 0; i < provjera.size(); i++) {
    for (int j = 0; j < h.size(); j++) {
      if (fabs(provjera.at(i).at(j) - h.at(i).at(j)) > EPS)
        return false;
    }
  }
  return true;
}

int main() {
  int n = 0;
  cout << "Broj redova/kolona matrice: ";
  cin >> n;

  cout << "Elementi matrice: ";
  auto mat = Matrica(n, Vektor(n));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> mat.at(i).at(j);
    }
  }
  try {
    trodimMatrica konacna = DoolittleLU(mat);
    cout << "Matrica L:" << endl;
    for (int i = 0; i < konacna.at(0).size(); i++) {
      for (int j = 0; j < konacna.at(0).at(0).size(); j++) {
        cout << konacna.at(0).at(i).at(j) << "\t";
      }
      cout << endl;
    }
    cout << "Matrica U:" << endl;
    for (int i = 0; i < konacna.at(1).size(); i++) {
      for (int j = 0; j < konacna.at(1).at(0).size(); j++) {
        cout << konacna.at(1).at(i).at(j) << "\t";
      }
      cout << endl;
    }
  } catch (...) {
    cout << "LU faktorizacija ne postoji, jer je matrica singularna!";
  }
  return 0;
}