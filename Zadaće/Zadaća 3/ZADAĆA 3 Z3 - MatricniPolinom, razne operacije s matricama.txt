// TP 2021/2022: Zadaća 3, Zadatak 3
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <new>
#include <stdexcept>
#include <vector>

template <typename TipElemenata> 
struct Matrica {
  char imeMatrice{};
  int brRedova{}, brKolona{};
  TipElemenata **elementi = nullptr;
};

template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> mat) {
  if (!mat.elementi) return;
  for (int i = 0; i < mat.brRedova; i++) delete[] mat.elementi[i];
  delete[] mat.elementi;
  mat.elementi = nullptr;
}

template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int brRedova, int brKolona, char ime = 0) {
  Matrica<TipElemenata> mat;
  try {
    mat.brRedova = brRedova;
    mat.brKolona = brKolona;
    mat.imeMatrice = ime;
    mat.elementi = new TipElemenata *[brRedova]{};
    for (int i = 0; i < brRedova; i++) mat.elementi[i] = nullptr;

    try {
      for (int i = 0; i < brRedova; i++)
        mat.elementi[i] = new TipElemenata[brKolona];
    } catch (...) {
      UnistiMatricu(mat);
      throw;
    }

  } catch (...) {
    UnistiMatricu(mat);
    throw;
  }
  for (int i = 0; i < mat.brRedova; i++) {
    for (int j = 0; j < mat.brKolona; j++) {
      mat.elementi[i][j] = {};
    }
  }
  return mat;
}

template <typename TipElemenata>
void UnesiMatricu(char imeMatrice, Matrica<TipElemenata> &mat) {
  mat.imeMatrice = imeMatrice;
  for (int i = 0; i < mat.brRedova; i++) {
    for (int j = 0; j < mat.brKolona; j++) {
      std::cout << mat.imeMatrice << "(" << i + 1 << "," << j + 1 << ") = ";
      std::cin >> mat.elementi[i][j];
    }
  }
}

template <typename TipElemenata>
void IspisiMatricu(const Matrica<TipElemenata> &mat, int sirina_ispisa,
                   int preciznost, bool treba_brisati) {
  for (int i = 0; i < mat.brRedova; i++) {
    for (int j = 0; j < mat.brKolona; j++) {
      std::cout << std::setw(sirina_ispisa) << std::setprecision(preciznost)
                << mat.elementi[i][j];
    }
    std::cout << std::endl;
  }
  if (treba_brisati) UnistiMatricu(mat);
}

template <typename TipElemenata>
void IspisiMatricu(const Matrica<TipElemenata> &mat, int sirina_ispisa,
                   int preciznost) {
  for (int i = 0; i < mat.brRedova; i++) {
    for (int j = 0; j < mat.brKolona; j++) {
      std::cout << std::setw(sirina_ispisa) << std::setprecision(preciznost)
                << mat.elementi[i][j];
    }
    std::cout << std::endl;
  }
}

template <typename TipElemenata>
void IspisiMatricu(const Matrica<TipElemenata> &mat, int sirina_ispisa) {
  for (int i = 0; i < mat.brRedova; i++) {
    for (int j = 0; j < mat.brKolona; j++) {
      std::cout << std::setw(sirina_ispisa) << mat.elementi[i][j];
    }
    std::cout << std::endl;
  }
}

template <typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &m1,
                                     const Matrica<TipElemenata> &m2) {
  try {
    if (m1.brKolona != m2.brRedova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
  } catch (std::domain_error &izuzetak) {
    std::cout << izuzetak.what();
  }
  Matrica<TipElemenata> produkt;
  try {
    produkt = StvoriMatricu<TipElemenata>(m1.brRedova, m2.brKolona);
    for (int i = 0; i < m1.brRedova; i++) {
      for (int j = 0; j < m2.brKolona; j++) {
        produkt.elementi[i][j] = {};
      }
    }
    for (int i = 0; i < m1.brRedova; i++) {
      int br = 0;
      for (int j = 0; j < m1.brKolona; j++) {
        for (int k = 0; k < m2.brKolona; k++) {
          j = 0;
          for (int h = 0; h < m2.brRedova; h++) {
            produkt.elementi[i][br] += m1.elementi[i][j] * m2.elementi[h][k];
            j++;
          }
          br++;
        }
      }
    }
    return produkt;
  } catch (...) {
    UnistiMatricu(produkt);
    throw;
  }
}

template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1,
                                  const Matrica<TipElemenata> &m2) {
  if (m1.brRedova != m2.brRedova || m1.brKolona != m2.brKolona) {
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
  }
  auto m3 = StvoriMatricu<TipElemenata>(m1.brRedova, m1.brKolona);
  for (int i = 0; i < m1.brRedova; i++) {
    for (int j = 0; j < m1.brKolona; j++) {
      m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
    }
  }
  return m3;
}

template <typename TipElemenata>
void PomnoziSaSkalarom(Matrica<TipElemenata> mat, double skalar){
    for (int i = 0; i < mat.brRedova; i++) {
        for (int j = 0; j < mat.brKolona; j++) {
            mat.elementi[i][j] *= skalar;
        }
    }
}

template <typename TipElemenata>
Matrica<TipElemenata> MatricniPolinom(Matrica<TipElemenata> a,
                                      std::vector<double> v) {
  if (a.brKolona != a.brRedova)
    throw std::domain_error("Matrica mora biti kvadratna");
  auto MatPolinom(StvoriMatricu<TipElemenata>(a.brKolona, a.brKolona));
  for (int i = 0; i < a.brRedova; i++) {
    for (int j = 0; j < a.brKolona; j++) {
      MatPolinom.elementi[i][j] = 0;
    }
  }
  for (int i = 0; i < v.size(); i++) {
    if (v[i] == 0) continue;
    try {
      auto JedinicnaMatrica(StvoriMatricu<TipElemenata>(a.brRedova, a.brKolona));
      for (int i = 0; i < a.brRedova; i++) {
        for (int j = 0; j < a.brKolona; j++) {
          if (i == j)
            JedinicnaMatrica.elementi[i][j] = 1;
          else
            JedinicnaMatrica.elementi[i][j] = 0;
        }
      }
      for (int j = 0; j < i; j++) {
        auto temp = JedinicnaMatrica;
        try {
          JedinicnaMatrica = ProduktMatrica(a, JedinicnaMatrica);
          UnistiMatricu(temp);
        } catch (...) {
          UnistiMatricu(JedinicnaMatrica);
          throw;
        }
      }

      PomnoziSaSkalarom(JedinicnaMatrica, v[i]);

      try {
        auto temp = MatPolinom;
        MatPolinom = ZbirMatrica(MatPolinom, JedinicnaMatrica);
        UnistiMatricu(JedinicnaMatrica);
        UnistiMatricu(temp);
      } catch (...) {
        UnistiMatricu(JedinicnaMatrica);
        throw;
      }
    } catch (...) {
      UnistiMatricu(MatPolinom);
      throw;
    }
  }
  return MatPolinom;
}

int main() {
  Matrica<double> a;
  std::vector<double> koeficijenti;
  int m, n;
  std::cout << "Unesite dimenziju kvadratne matrice: ";
  std::cin >> m;

  try {
    a = StvoriMatricu<double>(m, m);
    std::cout << "Unesite elemente matrice A: \n";
    UnesiMatricu('A', a);
    std::cout << "Unesite red polinoma: ";
    std::cin >> n;
    std::cout << "Unesite koeficijente polinoma: ";
    for (int i = 0; i <= n; i++) {
      double x;
      std::cin >> x;
      koeficijenti.push_back(x);
    }
    IspisiMatricu(MatricniPolinom(a, koeficijenti), 10, 6, true);
    UnistiMatricu(a);
  } catch (...) {
    UnistiMatricu(a);
  }
  return 0;
}
