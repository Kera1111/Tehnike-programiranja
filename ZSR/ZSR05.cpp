/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 9 */
#include <iostream>
#include <vector>
#include <string>
std::string Satrovaci(std::string s)
{
  std::string str;
  std::string samoglasnici = "AEIOUaeiou";
  for (int i = 0; i < s.length(); i++) {
    str += s[i];
    for (char c : samoglasnici)
      if (s[i] == c) {str += 'p'; str += c;}
  }
  return str;
}
int main()
{
  std::cout << Satrovaci("dobar dan");
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 10 */
#include <iostream>
#include <vector>
template<typename tip>
void DvaNajmanja(tip *niz, int n, tip &min1, tip &min2)
{
  int broj_istih = 0;
  for (int i = 1; i < n; i++)
    if (niz[i] == niz[0])broj_istih++;
  if (broj_istih == n - 1)throw std::logic_error("Svi isti");
  min1 = niz[0];
  for (int i = 0; i < n; i++)
    if (niz[i] < min1)min1 = niz[i];
  std::vector<tip>temp;
  for (int i = 0; i < n; i++)
    if (niz[i] != min1)temp.push_back(niz[i]);
  broj_istih = 0;
  for (int i = 1; i < temp.size(); i++)
    if (temp[i] == temp[0])broj_istih++;
  if (broj_istih == temp.size() - 1)
    throw std::logic_error("Nema drugog najmanjeg");
  min2 = temp[0];
  for (int i = 0; i < temp.size(); i++)
    if (temp[i] < min2)min2 = temp[i];
}
int main()
{
  int niz[5] {1, 2, 2, 2, 2}, min1, min2;
  try {
    DvaNajmanja(niz, 5, min1, min2);
    std::cout << min1 << " " << min2;
  }
  catch (const std::logic_error &e) {
    std::cout << "Izuzetak: " << e.what();
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 11 */
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
std::vector<int>Djelioci(int n) {
  std::vector<int>vek;
  for (int i = 1; i <= n; i++)
    if (n % i == 0)vek.push_back(i);
  return vek;
}
void Mod13(std::vector<int>&vek) {
  for (int &i : vek)
    i = (i * i + 1) % 13;
}
void NajveciNajmanji(std::vector<int>vek, int &min, int &max) {
  int najmanji = vek[0], najveci = vek[0];
  for (int i = 0; i < vek.size(); i++) {
    if (vek[i] > najveci) {najveci = vek[i]; max = i;}
    if (vek[i] < najmanji) {najmanji = vek[i]; min = i;}
  }
}
bool PotpunKvadrat(std::vector<int>vek) {
  for (int i : vek) {
    long double sr = sqrt(i);
    if (sr * sr == i)return true;
  }
  return false;
}
template<typename tip>
void Ispisi(tip poc, tip kraj) {
  while (poc != kraj)
    std::cout << *poc++ << " ";
}
int main()
{
  int n;
  std::cin >> n;
  std::vector<int>vek = Djelioci(n);
  Mod13(vek);
  int min, max;
  NajveciNajmanji(vek, min, max);
  for (int i = 0; i < vek.size(); i++)
    if (i == min || i == max)vek[i] = 0;
  Ispisi(vek.begin(), vek.end());
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 12 */
#include <iostream>
#include <vector>
#include <cmath>
std::vector<int>PotpunKvadrat(int n) {
  std::vector<int>vek;
  for (int i = 1; i < n; i++) {
    long double sr = sqrt(i);
    if (sr * sr == i)vek.push_back(i);
  }
  return vek;
}
void Mod19(std::vector<int>&vek) {
  for (int &i : vek)
    i = (4 * i + 7) % 19;
}
void NajveciNajmanji(std::vector<int>vek, int &min, int &max) {
  min = max = vek[0];
  for (int i = 0; i < vek.size(); i++) {
    if (vek[i] > max)max = vek[i];
    if (vek[i] < min)min = vek[i];
  }
}
bool ImaLiParnih(std::vector<int>vek) {
  for (int i : vek)
    if (i % 2 == 0)return true;
  return false;
}
template<typename tip>
void Ispisi(tip poc, tip kraj) {
  while (poc != kraj)
    std::cout << *poc++ << " ";
}
int main()
{
  int n;
  std::cin >> n;
  std::vector<int>vek = PotpunKvadrat(n);
  Mod19(vek);
  int min, max;
  NajveciNajmanji(vek, min, max);
  std::cout << min << " " << max << std::endl;
  Ispisi(vek.begin(), vek.end());
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 13 */
#include <iostream>
#include <vector>
#include <cmath>
std::vector<int>StepeniDva(int n) {
  std::vector<int>vek;
  int st = 1;
  while (st < n) {
    vek.push_back(st); st *= 2;
  }
  return vek;
}
void Mod17(std::vector<int>&vek) {
  for (int &i : vek)
    i = (3 * i * i + 2) % 17;
}
void NajveciNajmanji(std::vector<int>vek, int &min, int &max) {
  min = max = vek[0];
  for (int i = 0; i < vek.size(); i++) {
    if (vek[i] > max)max = vek[i];
    if (vek[i] < min)min = vek[i];
  }
}
bool ImaLiTrocifrenih(std::vector<int>vek) {
  for (int i : vek)
  {
    int broj_cifara = 0;
    while (i) {
      i /= 10;
      broj_cifara++;
    }
    if (broj_cifara == 3)return true;
  }
  return false;
}
template<typename tip>
void Ispisi(tip poc, tip kraj) {
  while (poc != kraj)
    std::cout << *poc++ << " ";
}
int main()
{
  int n;
  std::cin >> n;
  std::vector<int>vek = StepeniDva(n);
  Mod17(vek);
  int min, max;
  NajveciNajmanji(vek, min, max);
  std::cout << max - min << std::endl;
  Ispisi(vek.begin(), vek.end());
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 14 */
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
std::vector<int>TrocifrenDjeljiv(int n) {
  std::vector<int>vek;
  for (int i = 1; i <= std::numeric_limits<int>::max(); i++)
  {
    int broj_cifara = 0, num = i;
    while (num) {
      broj_cifara++;
      num /= 10;
    }
    if (i % n == 0 && broj_cifara == 3)
      vek.push_back(i);
  }
  return vek;
}
void Mod23(std::vector<int>&vek) {
  for (int &i : vek)
    i = (6 * i * i + 5) % 23;
}
void NajveciNajmanji(std::vector<int>vek, int &min, int &max) {
  int najmanji = vek[0], najveci = vek[0];
  for (int i = 0; i < vek.size(); i++) {
    if (vek[i] > najveci) {najveci = vek[i]; max = i;}
    if (vek[i] < najmanji) {najmanji = vek[i]; min = i;}
  }
}
bool ImaLiStepenaDva(std::vector<int>vek) {
  for (int i : vek)
    if (ceil(log2(i)) == floor(log2(i)) && i > 0)return true;
  return false;
}
template<typename tip>
void Ispisi(tip poc, tip kraj) {
  while (poc != kraj)
    std::cout << *poc++ << " ";
}
int main()
{
  int n;
  std::cin >> n;
  std::vector<int>vek = TrocifrenDjeljiv(n);
  Mod23(vek);
  int min, max;
  NajveciNajmanji(vek, min, max);
  std::cout << max << " " << min << std::endl;
  Ispisi(vek.begin(), vek.end());
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 15 */
#include <iostream>
template<typename tip>
int BrojTrocifrenih(tip poc, tip kraj) {
  int broj_trocifrenih = 0;
  while (poc != kraj) {
    int num = *poc++;
    int broj_cifara = 0;
    while (num) {
      num /= 10;
      broj_cifara++;
    }
    if (broj_cifara == 3)broj_trocifrenih++;
  }
  return broj_trocifrenih;
}
int main()
{
  int niz[] {1, 2, 3, 100, 123};
  std::cout << BrojTrocifrenih(niz, niz + 5);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 16 */
#include <iostream>
template<typename tip>
int BrojParnih(tip poc, tip kraj) {
  int broj_parnih = 0;
  while (poc != kraj)
    if (*poc++ % 2 == 0)broj_parnih++;
  return broj_parnih;
}
int main()
{
  int niz[] {1, 2, 3, 100, 123};
  std::cout << BrojParnih(niz, niz);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 17 */
#include <iostream>
#include <vector>
template<typename tip1, typename tip2>
tip1 Podblok(tip1 poc1, tip1 kraj1, tip2 poc2, tip2 kraj2) {
  int n = std::distance(poc2, kraj2);
  int broj_istih = 0;
  tip1 pocetak, p = poc2;
  while (poc1 != kraj1) {
    if (*poc1 == *poc2) {
      if (broj_istih == 0) pocetak = poc1;
      broj_istih++;
      poc2++;
      poc1++;
      if (broj_istih == n)break;
    }
    else {
      broj_istih = 0;
      poc1++;
      poc2 = p;
    }

  }
  return pocetak;
}
int main()
{
  std::vector<int> n{1, 7, 3, 5, 2, 6}, m{3, 5, 2};
  std::vector<int>::iterator pocetak =
    Podblok(n.begin(), n.end(), m.begin(), m.end());
  while (pocetak != n.end())
    std::cout << *pocetak++ << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 18 */
#include <iostream>
#include <cmath>
double Izvod(double f(double), double x, double h = 0.00001) {
  return (f(x + h) - f(x)) / h;
}
int main() {
  std::cout << Izvod([](double x) {return sin(x);}, 0) << std::endl;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 19 */
#include <iostream>
#include <cmath>
double Simpson(double f(double), int a, int b, int n) {
  int suma_jedan = 0, suma_dva = 0;
  double h = (b - a) / double(n);
  for (int k = 1; k <= n - 1; k++)
    suma_jedan += (f(a + k * h));
  for (int k = 2; k <= n - 2; k++)
    suma_dva += (f(a + k * h));
  double rez = f(a) + 4 * suma_jedan + 2 * suma_dva + f(b);
  return rez;
}
int main()
{
  std::cout << Simpson([](double x) {return sin(x);}, 0, 4 * atan(1), 10) << std::endl;
  std::cout << Simpson([](double x) {return x * x * x;}, 0, 10, 10) << std::endl;
  std::cout << Simpson([](double x) {return 1 / x;}, 1, 2, 10) << std::endl;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 20 */
#include <iostream>
#include <vector>
template<typename tip>
bool JednakiBlokovi(tip p1, tip p2, tip p3) {
  while (p1 != p2)
    if (*p1++ != *p3++)return false;
  return true;
}
int main()
{
  std::vector<int>a{1, 2, 3, 4, 5}, b{3, 4, 5};
  std::cout << JednakiBlokovi(a.begin() + 2, a.end(), b.begin());
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 21 */
#include <iostream>
#include <vector>
template<typename tip, typename F>
tip Nadji(tip p1, tip p2, F f) {
  while (p1 != p2)
    if (f(*++p1))return p1;
  return p1;
}
int main()
{
  std::vector<int>a{1, 2, 3, 4, 5};
  std::vector<int>::iterator it = Nadji(a.begin(), a.end(), [](int x) {return x > 2;});
  while (it != a.end())
    std::cout << *it++ << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 22 */
#include <iostream>
#include <vector>
template<typename tip, typename F>
int Prebroji(tip p1, tip p2, F f) {
  int broj = 0;
  while (p1 != p2)
    if (f(*p1++))broj++;
  return broj;
}
int main()
{
  std::vector<int>a{1, 2, 3, 4, 5};
  std::cout << Prebroji(a.begin(), a.end(), [](int x) {return x > 2;});
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 23 */
#include <iostream>
#include <vector>
template<typename tip, typename F, typename t>
void Zamijeni(tip p1, tip p2, tip p3, F f, t v) {
  while (p1 != p2) {
    *p3 = *p1;
    if (f(*p3))*p3 = v;
    p1++; p3++;
  }
}
int main()
{
  std::vector<int>a{1, 2, 3, 4, 5}, b{1, 2, 3, 4, 5};
  Zamijeni(a.begin(), a.end(), b.begin(), [](int x) {return x > 2;}, 0);
  for (int i : b)std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 24 */
#include <iostream>
#include <vector>
template<typename tip>
bool RazlicitiBlokovi(tip p1, tip p2, tip p3) {
  while (p1 != p2)
    if (*p1++ == *p3++)return false;
  return true;
}
int main()
{
  std::vector<int>a{1, 2, 6, 7, 8}, b{3, 4, 5};
  std::cout << RazlicitiBlokovi(a.begin() + 2, a.end(), b.begin());
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 26 */
#include <iostream>
#include <deque>
template<typename tip>
bool Simetrican(tip poc, tip kraj)
{
  int vel = kraj - poc;
  tip zadnji = kraj - 1;
  int i = 0;
  while (i < vel / 2) {
    if (*poc++ != *zadnji--)return false;
    i++;
  }
  return true;
}
int main()
{
  std::deque<int>a{/*3, 5, 1, 8,2, 8, 1, 5, 3*/};
  int b[10] {/*3, 5, 1, 8,2, 8, 1, 5, 3*/};
  int x;
  for (int i = 0; i < 10; i++)
  {
    std::cin >> x;
    a.push_back(x);
    b[i] = x;
  }
  std::cout << Simetrican(a.begin(), a.end());
  std::cout << Simetrican(b, b + 10);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 27 */
#include <iostream>
#include <vector>
template<typename tip, typename F>
auto SumaGeneric(tip p1, tip p2, F f) {
  using tip_objekta = typename std::decay<decltype(*p1)>::type;
  tip_objekta suma = 0;
  while (p1 != p2) {
    if (f(*p1))suma += *p1;
    p1++;
  }
  return suma;
}
int main()
{
  std::vector<int>a{1, 2, 3, 4, 5};
  std::cout << SumaGeneric(a.begin(), a.end(), [](int x) {return x > 2;});
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 30 */
#include <iostream>
#include <vector>
#include <cmath>
template<typename tip, typename F>
tip NajmanjiGeneric(tip p1, tip p2, F f) {
  tip min = p1;
  while (p1 != p2) {
    if (f(*p1) < f(*min))
      min = p1;
    p1++;
  }
  return min;
}
int main()
{
  std::vector<double>a{3, 2, 1, 4, 5};
  std::vector<double>::iterator it = NajmanjiGeneric(a.begin(), a.end(),
  [](double x) {return x - sin(x) / x + cos(x);});
  while (it != a.end())std::cout << *it++ << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 32 */
#include <iostream>
#include <deque>
#include <cmath>
#include <string>
template<typename tip, typename F>
tip najveci_element(tip p1, tip p2, F f) {
  tip max = p1;
  while (p1 != p2) {
    if (f(*p1, *max))max = p1;
    p1++;
  }
  return max;
}
int main()
{
  std::deque<std::string>a;
  for (int i = 0; i < 10; i++) {
    std::string s;
    std::getline(std::cin, s);
    a.push_back(s);
  }
  std::deque<std::string>::iterator it = najveci_element(a.begin(), a.end(),
  [](std::string x, std::string y) {return x.size() > y.size();});
  std::cout << *it;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 33 */
#include <iostream>
template<typename T, typename F>
T funkcija(T x, F f, int n) {
  for (int i = 0; i < n; i++)
    x = f(x);
  return x;
}
int main()
{
  std::cout << funkcija(1, [](double x) {return 3 * x * x + 5;}, 3);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 34 */
#include <iostream>
#include <vector>
template<typename T, typename F>
std::vector<T> funkcija(T x, F f, int n) {
  std::vector<T>vek;
  for (int i = 0; i < n; i++) {
    x = f(x);
    vek.push_back(x);
  }
  return vek;
}
int main()
{
  for (int i : funkcija(1, [](int x) {return x * 2;}, 3))
  std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 36 */
#include <iostream>
#include <vector>
int StringFunkcija(std::string &str, char f(char)) {
  int broj_promijenjenih = 0;
  for (char &c : str) {
    if (f(c) == c)
    {
      c = '+';
      broj_promijenjenih++;
    }
  }
  return broj_promijenjenih;
}
int main()
{
  std::string str = "abcdef";
  std::cout << StringFunkcija(str, [](char c) {
    if (c == 'a' || c == 'b' || c == 'c')
      return 'a';
    else return 'e';
  }) << " " << str;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 37 */
#include <iostream>
#include <deque>
#include <string>
#include <algorithm>
#include <iterator>
int main()
{
  std::deque<std::string>dek;
  std::deque<std::string>novi;
  for (int i = 0; i < 10; i++) {
    std::string str;
    std::getline(std::cin, str);
    dek.push_back(str);
  } 
  copy_if(dek.begin(), dek.end(),std::back_inserter(novi),
           [](std::string s) {
    std::string samoglasnici = "AEIOUaeiou";
    int broj_samoglasnika = 0;
    for (int i = 0; i < s.length(); i++)
      for (char c : samoglasnici)
        if (s[i] == c)broj_samoglasnika++;
    return broj_samoglasnika <= 5;
  });
  for (std::string s : novi)std::cout << s << std::endl;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 38 */
#include <iostream>
#include <vector>
#include <algorithm>
int main()
{
  std::vector<double>vek;
  for (int i = 1; i <= 100; i++)
    vek.push_back(i * i);
  std::for_each(vek.begin(), vek.end(), [](double & i) {i = int(i) % 42;});
  std::sort(vek.begin(), vek.end());
  double broj;
  std::cout << "broj: ";
  std::cin >> broj;
  if (std::binary_search(vek.begin(), vek.end(), broj))std::cout << "ima ga";
  else std::cout << "nema ga";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 39 */
#include <iostream>
#include <string>
bool f(char c) {
  return (c >= 'a' && c <= 'z');
}
std::string StringZnak(std::string &str, char znak, bool f(char)) {
  for (char &c : str)
    if (f(c))c = znak;
  return str;
}
int main()
{
  std::string s1, s2;
  char znak;
  std::getline(std::cin, s1);
  std::getline(std::cin, s2);
  std::cin >> znak;
  StringZnak(s1, znak, [](char c) {return (c >= 'a' && c <= 'z');} );
  StringZnak(s2, znak, f);
  std::cout << s1 << " " << s2;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 40 */
#include <iostream>
#include <complex>
#include <algorithm>
int main()
{
  std::complex<int> niz[3] {{5, 4}, {3, 4}, {1, 2}};
  std::sort(niz, niz + 3, [](std::complex<int>c1, std::complex<int>c2) {
    return c1.imag() < c2.imag() || c1.imag() <= c2.imag() && c1.real() < c2.real();
  });
  for (std::complex<int>i : niz)
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 41 */
#include <iostream>
#include <complex>
#include <algorithm>
int main()
{
  std::complex<int> niz[3] {{5, 4}, {3, 4}, {1, 2}};
  std::sort(niz, niz + 3, [](std::complex<int>c1, std::complex<int>c2) {
    return abs(c1) < abs(c2) || abs(c1) == abs(c2) && c1.real() < c2.real();
  });
  for (std::complex<int>i : niz)
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 42 */
#include <iostream>
#include <complex>
#include <algorithm>
int main()
{
  std::complex<int> niz[3] {{5, 4}, {3, 4}, {1, 2}};
  std::sort(niz, niz + 3, [](std::complex<int>c1, std::complex<int>c2) {
    if (c1.real() != c2.real())
      return c1.real() < c2.real();
    else return c1.imag() < c2.imag();
  });
  for (std::complex<int>i : niz)
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 43 */
#include <iostream>
#include <complex>
#include <algorithm>
int main()
{
  std::complex<int> niz[3] {{5, 4}, {3, 4}, {1, 2}};
  std::sort(niz, niz + 3, [](std::complex<int>c1, std::complex<int>c2) {
    if (arg(c1) != arg(c2))
      return arg(c1) < arg(c2);
    else return abs(c1) < abs(c2);
  });
  for (std::complex<int>i : niz)
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 44 */
#include <iostream>
#include <deque>
#include <algorithm>
int main()
{
  std::deque<int> dek{179, 372, 911, 4, 5, 6, 7, 8, 9};
  std::sort(dek.begin(), dek.end(), [](int a, int b) {
    int a_obrnut = 0;
    while (a) {
      int c = a % 10;
      a_obrnut += c;
      a /= 10;
    }
    int b_obrnut = 0;
    while (b) {
      int c = b % 10;
      b_obrnut += c;
      b /= 10;
    }
    return a_obrnut < b_obrnut;
  });
  for (int i : dek)
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 45 */
#include <iostream>
#include <deque>
#include <algorithm>
int main()
{
  std::deque<int> dek{10, 12, 24, 4, 5, 6, 7, 8, 512};
  std::sort(dek.begin(), dek.end(), [](int a, int b) {
    int a_djelioci = 0, b_djelioci = 0;
    for (int i = 1; i <= a; i++)
      if (a % i == 0)a_djelioci++;
    for (int i = 1; i <= b; i++)
      if (b % i == 0)b_djelioci++;
    return a_djelioci > b_djelioci;
  });
  for (int i : dek)
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 46 */
#include <iostream>
#include <deque>
#include <algorithm>
#include <iomanip>
int main()
{
  std::deque<int> dek{7835, 6735, 9188, 1234, 5678,
                      4321, 7654, 9876, 1234, 5678};
  std::sort(dek.begin(), dek.end(), [](int a, int b) {
    int a_raspon = 0, b_raspon = 0;
    int min_a = a % 10, max_a = a % 10, n = a;
    while (n) {
      int c = n % 10;
      if (c > max_a)max_a = c;
      if (c < min_a)min_a = c;
      n /= 10;
    }
    a_raspon = max_a - min_a;
    int min_b = b % 10, max_b = b % 10, m = b;
    while (m) {
      int c = m % 10;
      if (c > max_b)max_b = c;
      if (c < min_b)min_b = c;
      m /= 10;
    }
    b_raspon = max_b - min_b;
    if (a_raspon != b_raspon)
      return a_raspon > b_raspon;
    else return a < b;
  });
  for (int i : dek)std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 47 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
int main()
{
  int niz[5] {45, 56, 1, 2, 3};
  std::sort(niz, niz + 5, [](int a, int b) {
    int broj_cifara_a = 0, broj_cifara_b = 0, n = a;
    while (n) {
      n /= 10;
      broj_cifara_a++;
    }
    n = b;
    while (n) {
      n /= 10;
      broj_cifara_b++;
    }
    if (broj_cifara_a != broj_cifara_b)
      return broj_cifara_a < broj_cifara_b;
    else return a > b;
  });
  for (int i : niz)std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR5 - ZADATAK 48 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
int main()
{
  std::vector<std::string> vek{"abc", "deff"};
  std::sort(vek.begin(), vek.end(), [](std::string a, std::string b) {
    if (a.length() != b.length())
      return a.length() > b.length();
    else {
      for (char &c : a)c = toupper(c);
      for (char &c : b)c = toupper(c);
      return a < b;
    }
  });
  for (std::string s : vek)std::cout << s << " ";
  return 0;
}
/*-----------------------------------------------*/


























