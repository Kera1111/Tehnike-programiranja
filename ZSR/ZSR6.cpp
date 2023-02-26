/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 4 */
#include <iostream>
#include <limits>
#include <cmath>
bool JeLiProst(int n) {
  if (n <= 1)return false;
  for (int i = 2; i <= sqrt(n); i++)
    if (n % i == 0)return false;
  return true;
}
int *ProstiBrojeviAlokacija(int n) {
  if (n <= 0)throw std::domain_error("n manje ili jednako nuli");
  int *niz = new int[n] {};
  for (int i = 0, j = 0; i <= std::numeric_limits<int>::max(), j < n; i++)
    if (JeLiProst(i))niz[j++] = i;
  return niz;
}
int main()
{
  int *niz{};
  try {
    niz = ProstiBrojeviAlokacija(10);
    for (int i = 0; i < 10; i++)std::cout << niz[i] << " ";
    delete[] niz;
  }
  catch (...) {
    std::cout << "Alokacija nije uspjela";
  }
  return 0;
}

/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 5 */
#include <iostream>
#include <vector>
double *VektorAlokacija(std::vector<double>vek) {
  double *niz = new double[vek.size()] {};
  for (int i = 0; i < vek.size(); i++)
    niz[i] = 1 / vek[i];
  return niz;
}
int main()
{
  double *niz{};
  try {
    niz = VektorAlokacija({1, 2, 4, 8});
    for (int i = 0; i < 4; i++)std::cout << niz[i] << " ";
    delete[] niz;
  }
  catch (...) {
    std::cout << "Alokacija nije uspjela";
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 6 */
#include <iostream>
#include <cmath>
int *FibonacciNiz(int n) {
  int *niz = new int[n] {};
  niz[0] = 1; niz[1] = 1;
  for (int i = 2; i < n; i++)
    niz[i] = niz[i - 1] + niz[i - 2];
  return niz;
}
void Sredina(int *niz, int n, double &as, double &gs, double &hs) {
  double suma = 0, produkt = 1, suma_reciprocno = 0;
  for (int i = 0; i < n; i++) {
    suma += niz[i];
    produkt *= niz[i];
    suma_reciprocno += 1. / niz[i];
  }
  as = suma / n;
  gs = pow(produkt, 1. / n);
  hs = 1 / (suma_reciprocno / n);
}
int main()
{
  int *niz{};
  try {
    niz = FibonacciNiz(10);
    for (int i = 0; i < 10; i++)std::cout << niz[i] << " ";
    double as, gs, hs;
    Sredina(niz, 10, as, gs, hs);
    std::cout << std::endl << as << " " << gs << " " << hs;
    delete[] niz;
  }
  catch (...) {
    std::cout << "Alokacija nije uspjela";
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 7 */
#include <iostream>
#include <deque>
#include <string>
#include <algorithm>
#include <iterator>
double *ObrnutPoredak(double *niz, int n) {
  double *arr = new double[n] {};
  for (int i = n - 1, j = 0; i >= 0; i--, j++)
    arr[j] = niz[i];
  return arr;
}
int main()
{
  double niz[5] = {1, 2, 3, 4, 5};
  double *arr{};
  try {
    arr = ObrnutPoredak(niz, 5);
    for (int i = 0; i < 5; i++)std::cout << arr[i] << " ";
    delete[] arr;
  }
  catch (...) {
    std::cout << "Alokacija nije uspjela";
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 8 */
#include <iostream>
#include <vector>
template<typename tip>
void DodjeliAdresuGeneric(tip &mat, int n)
{
  using tip_objekta = typename std::decay<decltype(mat[0][0])>::type;
  mat = new tip_objekta*[n] {};
  try {
    for (int i = 0; i < n; i++)
      mat[i] = new tip_objekta[n];
  } catch (...) {
    for (int i = 0; i < n; i++)
      delete[] mat[i];
    delete[] mat;
    throw;
  }
}
int main()
{
  int **mat, n = 33;
  try {
    DodjeliAdresuGeneric(mat, n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        mat[i][j] = 1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++)std::cout << mat[i][j] << " ";
      std::cout << std::endl;
    }
    for (int i = 0; i < n; i++)delete[] mat[i];
    delete[] mat;
  } catch (...) {
    std::cout << "Alokacija nije uspjela";
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 9 */
#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
int main()
{
  std::vector<std::complex<double>>vek;
  for (;;) {
    std::complex<double>a;
    std::cin >> a;
    vek.push_back(a);
    if (a.real() == 0 && a.imag() == 0)break;
  }
  std::sort(vek.begin(), vek.end(), [](std::complex<double>a,
  std::complex<double>b) {
    return abs(a) < abs(b);
  });

  try {
    double *realni = new double[vek.size()] {};
    double *imaginarni = new double[vek.size()] {};
    for (int i = 0, j = 0; i < vek.size(); i++, j++) {
      realni[j] = vek[i].real();
      imaginarni[j] = vek[i].imag();
    }
    for (auto i : vek)std::cout << i << " ";
    std::cout << vek[0].real();
    delete[] realni; delete[] imaginarni;
  }
  catch (...) {
    std::cout << "Alokacija nije uspjela";
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 10 */
#include <iostream>
template<typename tip>
void MatricaMN(tip &mat, int m, int n) {
  using tip_objekta = typename std::decay<decltype(mat[0][0])>::type;
  mat = new tip_objekta*[m] {};
  try {
    for (int i = 0; i < n; i++)
      mat[i] = new tip_objekta[n] {};
  } catch (...) {
    for (int i = 0; i < n; i++)delete[] mat[i];
    delete[] mat;
    throw std::logic_error("Kreiranje nije uspjelo");
  }
}
int main()
{
  int **mat, m = 5, n = 3;
  try {
    MatricaMN(mat, m, n);
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 3; j++)std::cout << mat[i][j] << " ";
      std::cout << std::endl;
    }
    for (int i = 0; i < n; i++)delete[] mat[i];
    delete[] mat;
  } catch (const std::logic_error &e) {
    std::cout << e.what();
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 11 */
#include <vector>
#include <iostream>
template<typename tip>
tip **MatricaVektor(std::vector<std::vector<tip>>&mat) {
  for (int i = 1; i < mat.size(); i++)
    if (mat[i].size() != mat[0].size())
      throw std::logic_error("Nekorektna matrica");
  tip** dinamicka_mat = new tip*[mat.size()] {};
  try {
    for (int i = 0; i < mat.size(); i++)
      dinamicka_mat[i] = new tip[mat[i].size()] {};
  } catch (...) {
    for (int i = 0; i < mat.size(); i++)delete[] dinamicka_mat[i];
    delete[] dinamicka_mat;
    throw std::logic_error("Kreiranje nije uspjelo");
  }

  for (int i = 0; i < mat.size(); i++)
    for (int j = 0; j < mat[i].size(); j++)
      dinamicka_mat[i][j] = mat[i][j];
  return dinamicka_mat;
}
int main()
{
  std::vector<std::vector<int>>mat{{1, 2}, {3, 4}};
  try {
    int **dinamicka_mat = MatricaVektor(mat);
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++)
        std::cout << mat[i][j] << " ";
      std::cout << std::endl;
    }
    for (int i = 0; i < mat.size(); i++)delete[] dinamicka_mat[i];
    delete[] dinamicka_mat;
  } catch (const std::logic_error &e) {
    std::cout << e.what();
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 12 */
#include <vector>
#include <iostream>
template<typename tip>
tip **MatricaVektor(std::vector<std::vector<tip>>&mat) {
  int broj_elemenata = 0;
  for (auto i : mat)
    for (auto j : i)broj_elemenata++;

  tip** dinamicka_mat = new tip*[mat.size()] {};
  try {
    dinamicka_mat[0] = new tip[broj_elemenata] {};
    for (int i = 1; i < mat.size(); i++)
      dinamicka_mat[i] = dinamicka_mat[i - 1] + mat[i].size();
  } catch (...) {
    delete[] dinamicka_mat[0];
    delete[] dinamicka_mat;
    throw std::logic_error("Kreiranje nije uspjelo");
  }

  for (int i = 0; i < mat.size(); i++)
    for (int j = 0; j < mat[0].size(); j++)
      dinamicka_mat[i][j] = mat[i][j];
  return dinamicka_mat;
}
int main()
{
  std::vector<std::vector<int>>mat{{1, 2}, {3, 4, 5, 6}};
  int kolone[2] {2, 4};
  try {
    int **dinamicka_mat = MatricaVektor(mat);
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < kolone[i]; j++)
        std::cout << mat[i][j] << " ";
      std::cout << std::endl;
    }
    delete[] dinamicka_mat[0]; delete[] dinamicka_mat;
  } catch (const std::logic_error &e) {
    std::cout << e.what();
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 13 */
#include <vector>
#include <iostream>
template<typename tip, typename T>
void MatricaAlokacija(tip &a, int m, int n, T v, bool mod ) {
  using tip_objekta = typename std::decay<decltype(a[0][0])>::type;
  if (mod) {
    a = new tip_objekta*[m] {};
    try {
      a[0] = new tip_objekta[m * n] {};
      for (int i = 1; i < m; i++)a[i] = a[i - 1] + n;
    } catch (...) {
      delete[] a[0]; delete[] a;
      throw;
    }
  } else {
    a = new tip_objekta*[m] {};
    try {
      for (int i = 0; i < m; i++)a[i] = new tip_objekta[n];
    } catch (...) {
      for (int i = 0; i < m; i++)delete[]a[i]; delete[] a;
      throw;
    }
  }
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      a[i][j] = v;
}
int main()
{
  int **a;
  try {
    MatricaAlokacija(a, 3, 3, 0, 1);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++)
        std::cout << a[i][j] << " ";
      std::cout << std::endl;
    }
    delete[] a[0]; delete[]a;
  } catch (...) {
    std::cout << "Alokacija nije uspjela";
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 14 */
#include <iostream>
#include <vector>
template<typename tip>
tip** MatricaGeneric(std::vector<std::vector<tip>> mat) {
  tip** dinamicka_mat = new tip*[mat.size()] {};
  try {
    for (int i = 0; i < mat.size(); i++)
      dinamicka_mat[i] = new tip[mat[i].size()] {};
  } catch (...) {
    for (int i = 0; i < mat.size(); i++)delete[]dinamicka_mat[i];
    delete[] dinamicka_mat;
    throw;
  }
  for (int i = 0; i < mat.size(); i++)
    for (int j = 0; j < mat[i].size(); j++)
      dinamicka_mat[i][j] = mat[i][j];
  return dinamicka_mat;
}
int main()
{
  std::vector<std::vector<int>>vek;
  for (int i = 0; i < 3; i++) {
    std::vector<int>temp; int x;
    for (int j = 0; j < 3; j++) {
      std::cin >> x;
      temp.push_back(x);
    } vek.push_back(temp);
  }
  try {
    int **dinamicka_mat = MatricaGeneric(vek);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++)
        std::cout << dinamicka_mat[i][j] << " ";
      std::cout << std::endl;
    }
    for (int i = 0; i < 3; i++)delete[] dinamicka_mat[i];
    delete[] dinamicka_mat;
  } catch (...) {
    std::cout << "Alokacija nije uspjela";
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 15 */
#include <iostream>
#include <vector>
int** TablicaMnozenja(int n) {
  if (n <= 0)throw std::domain_error("Broj mora biti veci od 0");
  int **dinamicka_mat = new int*[n] {};
  try {
    dinamicka_mat[0] = new int[n * n] {};
    for (int i = 1; i < n; i++)dinamicka_mat[i] = dinamicka_mat[i - 1] + n;
  } catch (...) {
    delete[] dinamicka_mat[0]; delete[] dinamicka_mat;
  }
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)dinamicka_mat[i][j] = (i + 1) * (j + 1);
  return dinamicka_mat;
}
int main()
{
  int n;
  std::cin >> n;
  try {
    int **dinamicka_mat = TablicaMnozenja(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++)std::cout << dinamicka_mat[i][j] << " ";
      std::cout << std::endl;
    }
    delete[] dinamicka_mat[0]; delete[] dinamicka_mat;
  } catch (const std::domain_error &e) {
    std::cout << e.what();
  }
  catch (const std::bad_alloc) {
    std::cout << "Alokacija nije uspjela";
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 16 */
#include <iostream>
#include <vector>
#include <cstdlib>
int** TrougaonaMatrica(int n) {
  if (n <= 0)throw std::domain_error("Broj mora biti veci od 0");
  int **dinamicka_mat = new int*[n] {};
  try {
    for (int i = 0; i < n; i++)dinamicka_mat[i] = new int[2 * i + 1] {};
  } catch (...) {
    delete[] dinamicka_mat[0]; delete[] dinamicka_mat;
  }
  for (int i = 0; i < n; i++)
    for (int j = 0; j < 2 * i + 1; j++)dinamicka_mat[i][j] = abs(j - i) + 1;
  return dinamicka_mat;
}
int main()
{
  int n;
  std::cin >> n;
  try {
    int **dinamicka_mat = TrougaonaMatrica(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 2 * i + 1; j++)std::cout << dinamicka_mat[i][j] << " ";
      std::cout << std::endl;
    }
    delete[] dinamicka_mat[0]; delete[] dinamicka_mat;
  } catch (const std::domain_error &e) {
    std::cout << e.what();
  }
  catch (const std::bad_alloc) {
    std::cout << "Alokacija nije uspjela";
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 17 */
#include <iostream>
#include <vector>
#include <cstdlib>
template<typename tip>
void Kompaktifikacija(tip** &a, int m, int n) {
  tip** b = new tip*[m] {};
  try {
    b[0] = new tip[m * n] {};
    for (int i = 1; i < m; i++)b[i] = b[i - 1] + n;
  } catch (...) {
    delete[] b[0]; delete[] b;
    throw;
  }
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)b[i][j] = a[i][j];
  for (int i = 0; i < m; i++)delete[]a[i]; delete[] a;
  a = b;
}
int main()
{
  int **a, m = 3, n = 4;
  try {
    a = new int*[m] {};
    try {
      for (int i = 0; i < m; i++)a[i] = new int[n] {};
    } catch (...) {
      for (int i = 0; i < m; i++)delete[] a[i];
      delete[] a;
      std::cout << "Alokacija prve nije uspjela"; return 0;
    }
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++)a[i][j] = i + j;
  } catch (...) {
    std::cout << "Alokacije prve nije uspjela"; return 0;
  }
  try {
    Kompaktifikacija(a, m, n);
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++)std::cout << a[i][j] << " ";
      std::cout << std::endl;
    }
  } catch (...) {
    std::cout << "Alokacija druge nije uspjela";
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 18 */
#include <iostream>
int** GrbavaFragmentirana(int n) {
  if (n <= 0)throw std::domain_error("Pogresan parametar");
  int **mat = new int*[n] {};
  try {
    for (int i = 0; i < n; i++)
      mat[i] = new int[2 * i + 1] {};
    for (int i = 0; i < n; i++)
      for (int j = 0; j < 2 * i + 1; j++)mat[i][j] = abs(j - i) + 1;
  } catch (...) {
    for (int i = 0; i < n; i++)delete[] mat[i];
    delete[] mat;
    throw;
  }
  return mat;
}
int** GrbavaKontinualna(int n) {
  if (n <= 0)throw std::domain_error("Pogresan parametar");
  int **mat = new int*[n] {};
  int broj_elemenata = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < 2 * i + 1; j++)
      broj_elemenata++;
  try {
    mat[0] = new int[broj_elemenata] {};
    for (int i = 1; i < n; i++)
      mat[i] = mat[i - 1] + 2 * i - 1;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < 2 * i + 1; j++)mat[i][j] = abs(j - i) + 1;
  } catch (...) {
    delete[] mat[0]; delete[] mat;
    throw;
  }
  return mat;
}
int main()
{
  int n;
  std::cin >> n;
  try {
    int **mat = GrbavaFragmentirana(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 2 * i + 1; j++)std::cout << mat[i][j] << " ";
      std::cout << std::endl;
    }
    for (int i = 0; i < n; i++)delete[] mat[i];
    delete[] mat;
  } catch (const std::bad_alloc) {
    std::cout << "Alokacija nije uspjela";
  } catch (const std::domain_error &e) {
    std::cout << e.what();
  }
  try {
    int **mat = GrbavaKontinualna(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 2 * i + 1; j++)std::cout << mat[i][j] << " ";
      std::cout << std::endl;
    }
    delete[] mat[0]; delete[] mat;
  } catch (const std::bad_alloc) {
    std::cout << "Alokacija nije uspjela";
  } catch (const std::domain_error &e) {
    std::cout << e.what();
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 19 */
#include <iostream>
template<typename tip>
tip** GrbavaTip(int *niz, int n) {
  for (int i = 0; i < n; i++)
    if (niz[i] <= 0)throw std::domain_error("Negativan broj u nizu");
  tip** mat = new tip*[n] {};
  try {
    for (int i = 0; i < n; i++)
      mat[i] = new tip[niz[i]] {};
  } catch (...) {
    for (int i = 0; i < n; i++)delete[] mat[i];
    delete[] mat;
    throw;
  }
  return mat;
}

int main()
{
  int **mat, niz[3] {1, 2, 3};
  try {
    mat = GrbavaTip<int>(niz, 3);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < niz[i]; j++)
        std::cout << mat[i][j] << " ";
      std::cout << std::endl;
    }
    for (int i = 0; i < 3; i++)delete[] mat[i];
    delete[] mat;
  } catch (const std::domain_error &e) {
    std::cout << e.what();
  } catch (const std::bad_alloc) {
    std::cout << "Alokacija nije uspjela";
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 21 */
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
char **AlocirajChar(std::vector<std::string>vek) {
  char **a = new char*[vek.size()] {};
  try {
    for (int i = 0; i < vek.size(); i++)
      a[i] = new char[vek[i].size()];
    for (int i = 0; i < vek.size(); i++)
      strcpy(a[i], vek[i].c_str());
  } catch (...) {
    for (int i = 0; i < vek.size(); i++)delete[] a[i];
    delete[] a;
    throw std::bad_alloc();
  }
  return a;
}
int main() {
  try {
    char **a = AlocirajChar({"abc", "def"});
    for (int i = 0; i < 2; i++)
      std::cout << a[i] << " ";
    for (int i = 0; i < 2; i++)delete[] a[i];
    delete[] a;
  } catch (...) {
    std::cout << "Alokacija nije uspjela";
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 22 */
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
int** PascalovaMatrica(int n) {
  if (n <= 0)throw std::domain_error("Pogresan parametar");
  int **mat = new int*[n] {}, broj_elemenata = 0;
  int kolone[n], i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < i + 1; j++)
      broj_elemenata++;
    kolone[i] = j;
  }
  try {
    mat[0] = new int[broj_elemenata] {};
    for (int i = 1; i < n; i++)
      mat[i] = mat[i - 1] + kolone[i - 1];
  } catch (...) {
    delete[] mat[0]; delete[] mat;
    throw;
  }
  for (int i = 0; i < n; i++) {
    int a = 1;
    for (int j = 0; j < i + 1; j++)
    {
      if (j == 0)
        mat[i][j] = 1;
      else mat[i][j] = a;
      a = a * (i - j) / (j + 1);
    }
  }
  return mat;
}
int main() {
  int **mat, n;
  std::cin >> n;
  try {
    mat = PascalovaMatrica(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i + 1; j++)std::cout << mat[i][j] << " ";
      std::cout << std::endl;
    }
    delete[] mat[0]; delete[] mat;
  } catch (const std::domain_error &e) {
    std::cout << e.what();
  } catch (const std::bad_alloc) {
    std::cout << "Alokacija nije uspjela";
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 24 */
#include <iostream>
#include <vector>
#include <complex>
void UnistiTablu(std::complex<int>** &tabla) {
  delete[] tabla[0]; delete[] tabla;
}
template<typename tip>
void KreirajTabluSabiranja(tip** &tabla, std::vector<tip>v1, std::vector<tip>v2) {
  tabla = new tip*[v1.size()] {};
  try {
    tabla[0] = new tip[v1.size()*v2.size()] {};
    for (int i = 1; i < v1.size(); i++)
      tabla[i] = tabla[i - 1] + v2.size();
  } catch (...) {
    delete[] tabla[0]; delete[] tabla;
    throw std::logic_error("Kreiranje table nije uspjelo");
  }
  for (int i = 0; i < v1.size(); i++)
    for (int j = 0; j < v2.size(); j++)tabla[i][j] = v1[i] + v2[j];
}
int main() {
  std::vector<std::complex<int>>a, b;
  for (int i = 0; i < 2; i++) {
    std::complex<int>x;
    std::cin >> x;
    a.push_back(x);
  }
  for (int i = 0; i < 3; i++) {
    std::complex<int>x;
    std::cin >> x;
    b.push_back(x);
  }
  std::complex<int> **tabla;
  try {
    KreirajTabluSabiranja(tabla, a, b);
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 3; j++)std::cout << tabla[i][j] << " ";
      std::cout << std::endl;
    }
    UnistiTablu(tabla);
  } catch (...) {
    std::cout << "Alokacija nije uspjela";
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 25 */
#include <iostream>
#include <vector>
#include <deque>
template<typename T1, typename T2>
auto KnockerGeneric(T1 a, T2 b) {
  using tip_objekta = typename std::decay<decltype(a[0]*b[0])>::type;
  tip_objekta **mat = new tip_objekta*[a.size()] {};
  try {
    mat[0] = new tip_objekta[a.size()*b.size()] {};
    for (int i = 1; i < a.size(); i++)
      mat[i] = mat[i - 1] + b.size();
  } catch (...) {
    delete[] mat[0]; delete[] mat;
    throw std::logic_error("Alokacija nije uspjela");
  }
  for (int i = 0; i < a.size(); i++)
    for (int j = 0; j < b.size(); j++)
      mat[i][j] = a[i] * b[j];
  return mat;
}
int main() {
  int **mat;
  std::vector<int>a{1, 2, 3};
  std::deque<int>b{1, 2, 3, 4};
  try {
    mat = KnockerGeneric(a, b);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 4; j++)std::cout << mat[i][j] << " ";
      std::cout << std::endl;
    }
    delete[] mat[0]; delete[] mat;
  } catch (const std::logic_error &e) {
    std::cout << e.what();
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 26 */
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
void EvidencijaTP(std::string** &mat, int broj_pokazivaca, std::string novi) {
  std::string *ucenik = new std::string {};
  *ucenik = novi;
  bool ima_mjesta = false;
  for (int i = 0; i < broj_pokazivaca; i++)
    if (mat[i] == nullptr) {mat[i] = ucenik; ima_mjesta = true;}
  if (!ima_mjesta) {
    try {
      std::string **mat_nova = new std::string*[broj_pokazivaca + 10] {};
      for (int i = 0; i < broj_pokazivaca; i++)
        mat_nova[i] = mat[i];
      delete[] mat;
      mat_nova[broj_pokazivaca] = ucenik;
      mat = mat_nova;
    } catch (...) {
      for (int i = 0; i < broj_pokazivaca + 10; i++)delete mat_nova[i]; delete[] mat_nova;
      throw std::logic_error("Nema memorije");
    }
  }
}
int main() {
  std::string **mat = new std::string*[3] {};
  for (int i = 0; i < 3; i++)
    mat[i] = new std::string{};
  *mat[0] = "abc"; *mat[1] = "r"; *mat[2] = "def"; int n = 4; // nema slobodnih mjesta
  //*mat[0] = "abc"; mat[1] = nullptr; *mat[2] = "def"; int n=3; // ima jedno slobodno mjesto
  try {
    EvidencijaTP(mat, 3, "eee");
    for (int i = 0; i < n; i++)
      std::cout << *mat[i] << " ";
    for (int i = 0; i < n; i++)delete mat[i]; delete[] mat;
  } catch (const std::logic_error &e) {
    std::cout << e.what();
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 27 */
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
void EvidencijaObrisi(std::string** &mat, int broj_pokazivaca, std::string student) {
  int nema_ga = 0;
  for (int i = 0; i < broj_pokazivaca; i++)
    if (*mat[i] == student)nema_ga++;
  if (nema_ga == broj_pokazivaca)throw std::logic_error("Nema studenta");
  std::string *ucenik = new std::string {};
  *ucenik = student;
  for (int i = 0; i < broj_pokazivaca; i++)
    if (*mat[i] == *ucenik) {delete ucenik; mat[i] = nullptr;}
  int nula_pokazivaci = 0;
  for (int i = 0; i < broj_pokazivaca; i++)
    if (mat[i] == nullptr)nula_pokazivaci++;
  if (nula_pokazivaci > broj_pokazivaca / 2) {
    try {
      std::string **mat_novi = new std::string*[nula_pokazivaci] {};
      for (int i = 0; i < broj_pokazivaca; i++)
        mat_novi[i] = mat[i];
      delete[] mat;
      mat = mat_novi;
    } catch (...) {
      for (int i = 0; i < broj_pokazivaca; i++)delete mat[i]; delete[] mat;
      throw std::logic_error("Nema memorije");
    }
  }
}
int main() {
  std::string **mat = new std::string*[3] {};
  for (int i = 0; i < 3; i++)
    mat[i] = new std::string{};
  *mat[0] = "abc"; *mat[1] = "r"; *mat[2] = "def"; int n = 3;
  try {
    EvidencijaObrisi(mat, 3, "abc");
    for (int i = 0; i < n; i++)
        if (mat[i]) std::cout << *mat[i] << " "; else std::cout << "nullptr ";
    for (int i = 0; i < n; i++)delete mat[i]; delete[] mat;
  } catch (const std::logic_error &e) {
    std::cout << e.what();
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 30 */
int main() {
  std::string **mat = new std::string*[3] {};
  for (int i = 0; i < 3; i++)
    mat[i] = new std::string;
  *mat[0] = "abc"; mat[1] = nullptr; *mat[2] = "def";
  try {
    EvidencijaTP(mat, 3, "ghi");
    for (int i = 0; i < 3; i++)
      std::cout << *mat[i] << " ";
    for (int i = 0; i < 3; i++)delete[] mat[i]; delete[] mat;
  } catch (const std::logic_error &e) {
    std::cout << e.what();
  }

  return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
char ** Zvjezdice(int n, char** &b) {
  if (n <= 0)throw std::domain_error("Pogresan parametar");
  char **a = new char*[n] {};
  try {
    for (int i = 0; i < n; i++)
      a[i] = new char[i + 1] {};
  } catch (...) {
    for (int i = 0; i < n; i++)delete[] a; delete[] a;
    throw std::logic_error("Alokacija nije uspjela");
  }
  int j = 0, k = 0, niz[n];
  for (int i = 0; i < 4; i++) {
    j += (i + 1);
    niz[k++] = j;
  }
  b = new char*[n] {};
  try {
    b[0] = new char[j] {};
    for (int i = 1; i < n; i++)
      b[i] = b[i - 1] + niz[i - 1];
  } catch (...) {
    delete[] b[0]; delete[] b;
    throw std::logic_error("Alokacija nije uspjela");
  }
  for (int i = 0; i < n; i++)
    for (int j = 0; j < i + 1; j++)
      a[i][j] = '*';
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n - i; j++)
      b[i][j] = '*';
  return a;
}

int main() {
  char **a, **b; int n = 4;
  try {
    a = Zvjezdice(n, b);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i + 1; j++)
        std::cout << a[i][j];
      std::cout << std::endl;
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n - i; j++)
        std::cout << b[i][j];
      std::cout << std::endl;
    }
    for (int i = 0; i < n; i++)delete[] a[i]; delete[] a;
    delete[] b[0]; delete[] b;
  } catch (const std::domain_error &e) {
    std::cout << e.what();
  } catch (const std::logic_error &e) {
    std::cout << e.what();
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR6 - ZADATAK 32 */
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
int ** Zvjezdice(int n, int** &a) {
  if (n <= 0)throw std::domain_error("Pogresan parametar");
  a = new int*[n] {};
  try {
    for (int i = 0; i < n; i++)
      a[i] = new int[i + 1] {};
  } catch (...) {
    for (int i = 0; i < n; i++)delete[] a; delete[] a;
    throw std::logic_error("Alokacija nije uspjela");
  }
  int j = 0, k = 0, niz[n];
  for (int i = 0; i < 4; i++) {
    j += (i + 1);
    niz[k++] = j;
  }
  int** b = new int*[n] {};
  try {
    b[0] = new int[j] {};
    for (int i = 1; i < n; i++)
      b[i] = b[i - 1] + niz[i - 1];
  } catch (...) {
    delete[] b[0]; delete[] b;
    throw std::logic_error("Alokacija nije uspjela");
  }
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n - i; j++)
      a[i][j] = j + 1;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < i + 1; j++)
      b[i][j] = j + 1;
  return b;
}

int main() {
  int **a, **b, n = 4;
  try {
    b = Zvjezdice(n, a);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n - i; j++)
        std::cout << a[i][j];
      std::cout << std::endl;
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i + 1; j++)
        std::cout << b[i][j];
      std::cout << std::endl;
    }
    for (int i = 0; i < n; i++)delete[] a[i]; delete[] a;
    delete[] b[0]; delete[] b;
  } catch (const std::domain_error &e) {
    std::cout << e.what();
  } catch (const std::logic_error &e) {
    std::cout << e.what();
  }
  return 0;
}
/*-----------------------------------------------*/











