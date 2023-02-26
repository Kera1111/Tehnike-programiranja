/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 3 */
#include <iostream>
bool DvijeIsteCifre(int n) {
  int l = -1, m = 0;
  while (n != 0) {
    m = n % 10;
    if (m == l)
      return true;
    n /= 10;
    l = m;
  }
  return false;
}

int main()
{
  std::cout << DvijeIsteCifre(355241);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 9 */
#include <iostream>
#include <vector>
bool ImaParnih(std::vector<int>a) {
  for (int i = 0; i < a.size(); i++)
    if (a[i] % 2 == 0)
      return true;
  return false;
}

int main()
{
  int n, x;
  std::vector<int>a;
  std::cin >> n;
  std::cin.ignore(1000, '\n');
  for (int i = 0; i < n; i++) {
    std::cin >> x;
    a.push_back(x);
  }
  std::cout << ImaParnih(a);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 10 */
#include <iostream>
#include <vector>
#include <cmath>
bool ImaPotpunihKvadrata(std::vector<int>a) {
  int najveci = a[0];
  for (int i = 0; i < a.size(); i++)
    if (a[i] > najveci)najveci = a[i];
  for (int i = 0; i < a.size(); i++)
    for (int j = 1; j < sqrt(najveci); j++)
      if (a[i] == j * j)
        return true;;

  return false;
}

int main()
{
  int n, x;
  std::vector<int>a;
  std::cin >> n;
  std::cin.ignore(1000, '\n');
  for (int i = 0; i < n; i++) {
    std::cin >> x;
    a.push_back(x);
  }
  std::cout << ImaPotpunihKvadrata(a);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 11 */
#include <iostream>
#include <vector>
#include <cmath>
void KreirajVektor(int *niz, int n) {
  std::vector<double>a;
  for (int i = n - 1; i >= 0; i--) {
    a.push_back(niz[i]);
  }
  for (int i : a)
    std::cout << i << " ";
}

int main()
{
  int n;
  double x;
  std::cin >> n;
  std::cin.ignore(1000, '\n');
  double niz[n];
  for (int i = 0; i < n; i++) {
    std::cin >> x;
    niz[i] = x;
  }
  KreirajVektor(niz, n);

  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 12 */
#include <iostream>
#include <vector>
bool ImaTrocifrenih(std::vector<int>a) {
  for (int i = 0; i < a.size(); i++) {
    int suma_cifara = 0;
    int n = a[i];
    while (n != 0) {
      int m = n % 10;
      suma_cifara += m;
      n /= 10;
    }
    if (suma_cifara == 3)
      return true;
  }
  return false;
}

int main()
{
  int n, x;
  std::vector<int>a;
  std::cin >> n;
  std::cin.ignore(1000, '\n');
  for (int i = 0; i < n; i++) {
    std::cin >> x;
    a.push_back(x);
  }
  std::cout << ImaTrocifrenih(a);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 13 */
#include <iostream>
#include <vector>
bool je_li_stepen_dva(int i) {
  if ( i <= 0 )
    return false;
  return !(i & (i - 1));
}
bool ImaStepenDva(std::vector<int>a) {
  for (int i = 0; i < a.size(); i++)
    if (je_li_stepen_dva(a[i]))
      return true;
  return false;
}

int main()
{
  int n, x;
  std::vector<int>a;
  std::cin >> n;
  std::cin.ignore(1000, '\n');
  for (int i = 0; i < n; i++) {
    std::cin >> x;
    a.push_back(x);
  }
  std::cout << ImaStepenDva(a);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 14 */
#include <iostream>
#include <vector>
std::vector<int>Djelioci(int n) {
  std::vector<int>a;
  for (int i = 1; i <= n; i++)
    if (n % i == 0)
      a.push_back(i);
  return a;
}

int main()
{
  int n;
  std::cin >> n;
  std::cin.ignore(1000, '\n');
  for (int i : Djelioci(n))
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 15 */
#include <iostream>
#include <vector>
bool je_li_stepen_dva(int i) {
  if (i <= 0) return false;
  return ! (i & (i - 1));
}
std::vector<int>VektorStepenDva(int n) {
  std::vector<int>a;
  for (int i = 1; i < n; i++)
    if (je_li_stepen_dva(i))
      a.push_back(i);
  return a;
}

int main()
{
  int n;
  std::vector<int>a;
  std::cin >> n;
  std::cin.ignore(1000, '\n');
  a = VektorStepenDva(n);
  for (int i : a)
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 16 */
#include <iostream>
#include <vector>
std::vector<int>PotpuniKvadrat(int n) {
  std::vector<int>a;
  for (int i = 1; i < n; i++)
    for (int j = 1; j < n; j++)
      if (i * i == j)
        a.push_back(i);
  return a;
}

int main()
{
  int n;
  std::cin >> n;
  std::cin.ignore(1000, '\n');
  for (int i : PotpuniKvadrat(n))
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 17 */
#include <iostream>
#include <vector>
std::vector<int>TrocifrenDjeljiv(int n) {
  std::vector<int>a;
  for (int i = 100; i < 1000; i++) {
    if (i % n == 0)
      a.push_back(i);
  }
  return a;
}

int main()
{
  int n;
  std::cin >> n;
  std::cin.ignore(1000, '\n');
  for (int i : TrocifrenDjeljiv(n))
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 18 */
#include <iostream>
#include <vector>
std::vector<int>ParniNeparni(int *niz, int n) {
  std::vector<int>a;
  for (int i = 0; i < n; i++) {
    if (niz[i] % 2 == 0)
      a.push_back(niz[i]);
  }
  for (int i = 0; i < n; i++) {
    if (niz[i] % 2 == 1)
      a.push_back(niz[i]);
  }
  return a;
}
int main()
{
  int n = 10;
  int niz[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (int i : ParniNeparni(niz, n))
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 19 */
#include <iostream>
#include <vector>
std::vector<int>CifreVektora(std::vector<int>a) {
  std::vector<int>b;
  for (int i = 0; i < a.size(); i++) {
    int broj_cifara = 0;
    while (a[i])
    {
      int m = a[i] % 10;
      a[i] /= 10;
      broj_cifara++;
    }
    b.push_back(broj_cifara);
  }
  return b;
}
int main()
{
  int n, x;
  std::vector<int>a;
  std::cin >> n;
  std::cin.ignore(1000, '\n');
  for (int i = 0; i < n; i++) {
    std::cin >> x;
    a.push_back(x);
  }
  for (int i : CifreVektora(a))
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 20 */
#include <iostream>
#include <vector>
std::vector<int>CifreVektora(std::vector<int>a) {
  std::vector<int>b;
  for (int i = 0; i < a.size(); i++) {
    int broj_cifara = 0;
    while (a[i])
    {
      int m = a[i] % 10;
      a[i] /= 10;
      suma_cifara += m;
    }
    b.push_back(suma_cifara);
  }
  return b;
}
int main()
{
  int n, x;
  std::vector<int>a;
  std::cin >> n;
  std::cin.ignore(1000, '\n');
  for (int i = 0; i < n; i++) {
    std::cin >> x;
    a.push_back(x);
  }
  for (int i : CifreVektora(a))
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 21 */
#include <iostream>
#include <vector>
std::vector<int>CifreVektora(std::vector<int>a) {
  std::vector<int>b, temp;
  for (int i = 0; i < a.size(); i++) {
    while (a[i]) {
      int m = a % 10;
      a[i] /= 10;
      temp.push_back(m);
    }
    int najmanji = temp[0];
    for (int j = 0; j < temp.size(); j++)
      if (temp[j] < najmanji)najmanji = temp[0];
    b.push_back(najmanji);
  }
  return b;
}
int main()
{
  int n, x;
  std::vector<int>a;
  std::cin >> n;
  std::cin.ignore(1000, '\n');
  for (int i = 0; i < n; i++) {
    std::cin >> x;
    a.push_back(x);
  }
  for (int i : CifreVektora(a))
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 22 */
#include <iostream>
#include <vector>
#include <cmath>
std::vector<int> ProstiFaktori(int n) {
  std::vector<int> a;
  for (int i = 2; i * i <= n; )
    if (n % i == 0) {
      a.push_back(i);
      n /= i;
    }
    else i++;
  a.push_back(n);
  return a;
}
int main()
{
  int n;
  std::cin >> n;
  std::cin.ignore(1000, '\n');
  for (int i : ProstiFaktori(n)) std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 23 */
#include <iostream>
#include <vector>
#include <cmath>
bool je_li_prost(int n) {
  if(n<=1)return false;
  for (int i = 2; i <= sqrt(n); i++)
    if ( n % i == 0)return false;
  return true;
}
std::vector<int>NisuProsti(std::vector<int>a) {
  std::vector<int>b;
  for (int i = 0; i < a.size(); i++)
    if (!je_li_prost(a[i]))
      b.push_back(a[i]);
  return b;
}
int main()
{
  int n, x;
  std::vector<int>a;
  std::cin >> n;
  std::cin.ignore(1000, '\n');
  for (int i = 0; i < n; i++) {
    std::cin >> x;
    a.push_back(x);
  }
  for (int i : NisuProsti(a))
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 24 */
#include <iostream>
#include <vector>
std::vector<int>LokalniMaksimum(std::vector<int>a) {
  std::vector<int>b;
  for (int i = 0; i < a.size(); i++) {
    bool rez = true;
    for (int j = i - 1; j >= 0; j--)
      if (a[i] < a[j])rez = false;
    if (rez)b.push_back(a[i]);
  }
  return b;
}
int main()
{
  std::vector<int>a{1, 3, 2, 4, 5, 7, 6, 10, 9, 8};
  for (int i : LokalniMaksimum(a))
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 25 */
#include <iostream>
#include <vector>
bool OscilatoranSlijed(std::vector<int>v) {
  int a, b, c;
  for (int i = 0; i < v.size() - 2; i++) {
    a = v[i]; b = v[i + 1]; c = v[i + 2];
    if (!(b > a && c < b || b < a && c > a))return false;
  }
  return true;
}
int main()
{
  std::vector<int>v{3, 1, 4, 2, 7, 3, 10, 6, 18, 9};
  std::cout << OscilatoranSlijed(v);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 26 */
#include <iostream>
#include <vector>
std::vector<bool> SumaPet(std::vector<int>v) {
  std::vector<bool>r(v.size());
  for (int i = 0; i < v.size(); i++) {
    int suma = 0;
    for (int j = 1; j < v[i]; j++) {
      int a = j, b = j + 1, c = j + 2, d = j + 3, e = j + 4;
      suma = a + b + c + d + e;
      if (suma == v[i])r[i] = true;
    }
  }
  return r;
}
int main()
{
  std::vector<int>v{1, 8, 14, 15, 20, 45};
  for (bool i : SumaPet(v))
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 27 */
#include <iostream>
#include <vector>
std::vector<bool> ProizvodPet(std::vector<int>v) {
  std::vector<bool>r(v.size());
  for (int i = 0; i < v.size(); i++) {
    int proizvod = 0;
    for (int j = 1; j < v[i]; j++) {
      int a = j, b = j + 1, c = j + 2, d = j + 3, e = j + 4;
      proizvod = a * b * c * d * e;
      if (proizvod == v[i])r[i] = true;
    }
  }
  return r;
}
int main()
{
  std::vector<int>v{1, 6, 110, 720};
  for (bool i : ProizvodPet(v))
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 28 */
#include <iostream>
#include <vector>
#include <cmath>
std::vector<bool> ProstiUVektoru(std::vector<int>v) {
  std::vector<bool>r(v.size());
  for (int i = 0; i < v.size(); i++) {
    bool rez = true;
    for (int j = 2; j <= sqrt(v[i]); j++)
      if (v[i] <= 1 || v[i] % j == 0)rez = false;
    if (rez)r[i] = true;
  }
  return r;
}
int main()
{
  std::vector<int>v{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<bool>r = ProstiUVektoru(v);
  int broj = 0;
  for (int i = 0; i < r.size(); i++)
    if (r[i])broj++;
  std::cout << broj;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 29 */
#include <iostream>
#include <vector>
#include <cmath>
std::vector<int> SumaCifaraParametar(std::vector<int>v, int n) {
  std::vector<int>a;
  for (int i = 0; i < v.size(); i++) {
    int suma_cifara = 0;
    int broj = v[i];
    while (broj) {
      int m = broj % 10;
      broj /= 10;
      suma_cifara += m;
    }
    if (suma_cifara > n)
      a.push_back(v[i]);
  }
  return a;
}
int main()
{
  std::vector<int>v{1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i : SumaCifaraParametar(v, 4))
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 30 */
#include <iostream>
#include <vector>
#include <cmath>
std::vector<int> SavrseniBrojevi(std::vector<int>v) {
  std::vector<int>a;
  for (int i = 0; i < v.size(); i++) {
    int suma_djelilaca = 0;
    for (int j = 1; j < v[i]; j++)
      if (v[i] % j == 0)suma_djelilaca += j;
    if (suma_djelilaca == v[i])
      a.push_back(v[i]);
  }
  return a;
}
int main()
{
  std::vector<int>v;
  int x = -1, n;
  while (x) {
    std::cin >> x;
    if (x)v.push_back(x);
  }
  for (int i : SavrseniBrojevi(v))
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 31 */
#include <iostream>
#include <vector>
int BrojPrijateljskihParova(std::vector<int>a) {
  std::vector<int>b;
  for (int i = 0; i < a.size(); i++) {
    int suma_djelioca = 0;
    for (int j = 1; j < a[i]; j++)
      if (a[i] % j == 0)
        suma_djelioca += j;
    b.push_back(suma_djelioca);
  }
  int broj = 0;
  for (int i = 0; i < a.size(); i++)
    std::cout << a[i] << " ";
  std::cout << std::endl;
  for (int j = 0; j < b.size(); j++)
    std::cout << b[j] << " ";
  std::cout << std::endl;
  for (int i = 0; i < a.size(); i++)
    for (int j = i + 1; j < b.size(); j++)
      if (a[i] == b[j]&&b[i]==a[j])
        broj++;
  return broj;
}

int main()
{
  std::vector<int>b{220, 1184, 284, 1210, 2620, 2924};
  std::cout << BrojPrijateljskihParova(b);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 32 */
#include <iostream>
#include <vector>
void IzbaciElementeVektora(std::vector<int>&a) {
  int n = a.size();
  for (int i = 0; i < n; i++) {
    int broj = a[i], broj_cifara = 0, broj_parnih = 0, broj_neparnih = 0;
    while (broj) {
      int m = broj % 10;
      broj /= 10;
      broj_cifara++;
      if (m % 2 == 0)broj_parnih++;
      else broj_neparnih++;
    }
    if (broj_parnih == broj_cifara || broj_neparnih == broj_cifara) {
      for (int j = i; j < n - 1; j++)
        a[j] = a[j + 1];
      n--;
      i--;
      a.resize(n);
    }
  }
}
int main()
{
  std::vector<int>a;
  int n, x;
  std::cin >> n;
  std::cin.ignore(1000, '\n');
  for (int i = 0; i < n; i++) {
    std::cin >> x;
    a.push_back(x);
  }
  IzbaciElementeVektora(a);
  for (int i : a)
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 33 */
#include <iostream>
#include <vector>
#include <cstdlib>
std::vector<int> NajmanjeCifreVektora(std::vector<int>&a) {
  std::vector<int>temp, b;
  for (int i = 0; i < a.size(); i++) {
    int broj = abs(a[i]);
    while (broj) {
      int m = broj % 10;
      broj /= 10;
      temp.push_back(m);
    }
    int najmanji = a[0];
    for (int i = 0; i < temp.size(); i++)
      if (temp[i] < najmanji)najmanji = temp[i];
    b[i] = najmanji;
    temp.clear();
  }
  return b;
}

int main()
{
  std::vector<int>a;
  int x;
  for (int i = 0; i < 10; i++) {
    std::cin >> x;
    a.push_back(x);
  }
  for (int i : NajmanjeCifreVektora(a))
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 34 */
#include <iostream>
#include <vector>
std::vector<int> FaktorijelVektora(std::vector<int>&a) {
  std::vector<int>b(a.size());
  for (int i = 0; i < a.size(); i++)
    if (a[i] >= 0) {
      int faktorijel = 1;
      for (int j = 1; j <= a[i]; j++)
        faktorijel *= j;
      b[i] = faktorijel;
    }
  return b;
}

int main()
{
  std::vector<int>a{6, 3, 2, -7, 1, 0, 4, 5};
  for (int i : FaktorijelVektora(a))
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 35 */
#include <iostream>
#include <vector>
#include <cmath>
#include <deque>
std::vector<int> IzmjeniCifreVektora(std::vector<int>&a) {
  std::vector<int>b;
  std::deque<int>temp;
  for (int i = 0; i < a.size(); i++) {
    bool neg = false;
    if (a[i] < 0)neg = true;
    int broj = abs(a[i]);
    while (broj) {
      int m = broj % 10;
      broj /= 10;
      if (m % 2 == 0)m += 1;
      else m -= 1;
      temp.push_front(m);
    }
    int num = 0;
    for (int m : temp) {
      num *= 10;
      num += m;
    }
    if (neg)num *= -1;
    b.push_back(num);
    temp.clear();
  }
  return b;
}

int main()
{
  std::vector<int>a{354};
  for (int i : IzmjeniCifreVektora(a))
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR2 - ZADATAK 37 */
#include <iostream>
#include <vector>
#include <cmath>
#include <deque>
int MedijanDeka(std::deque<int>&a) {
  int medijan = 0;
  for (int i = 0; i < a.size(); i++) {
    int broj_vecih = 0, broj_manjih = 0;
    for (int j = 0; j < a.size(); j++)
      if (a[j] != a[i]) {
        if (a[j] > a[i])broj_vecih++;
        else broj_manjih++;
      }
    if (broj_vecih == broj_manjih)medijan = a[i];
  }
  return medijan;
}

int main()
{
  std::deque<int>a{1, 3, 2, 5, 4, 7, 6};
  std::cout << MedijanDeka(a);
  /*Ako se unese paran broj elemenata deka, funkcija će vratiti broj 0
  kao medijan jer niti jedan elemenat deka neće imati jednak broj
  većih i manjih od sebe*/
  return 0;
}
/*-----------------------------------------------*/









