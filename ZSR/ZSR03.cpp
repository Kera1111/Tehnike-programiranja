/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 5 */
#include <iostream>
#include <vector>
#include <cmath>
#include <deque>
double Korijeni(std::vector<double>&a) {
  double korijen = 0;
  for (int i = a.size() - 1; i > 0; i--) {
    if (i == a.size() - 1)
      korijen = sqrt(sqrt(a[i]) + a[i - 1]);
    else
      korijen = sqrt(korijen + a[i - 1]);
  }
  return (korijen);
}
int main()
{
  std::vector<double>a{5, 6, 7, 8, 9};
  std::cout << Korijeni(a);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 6 */
#include <iostream>
#include <vector>
double SumaReda(std::vector<double> &a) {
  double result = a[a.size() - 1];
  for (int i = a.size() - 1; i >= 0; i--) {
    if (result == 0)
      throw std::domain_error("Dividing with 0");
    result = a[i] + 1 / result;
  }
  return result;
}
int main()
{
  std::vector<double>a{1, 2, 3, 4, 5};
  try {
    std::cout << SumaReda(a);
  }
  catch (std::domain_error e) {
    std::cout << e.what();
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 7 */
#include <iostream>
#include <vector>
double SumaRazlomaka(std::vector<double>&a) {
  double rez = 0, suma = 0;
  for (int i = 0; i < a.size(); i++) {
    suma += a[i];
    if (suma == 0)throw std::domain_error("Nula u nazivniku");
    rez += 1 / suma;
  }
  return rez;
}
int main()
{
  std::vector<double>a{1, 2, 3, 4, 10};
  try {
    std::cout << SumaRazlomaka(a);
  }
  catch (std::domain_error e) {
    std::cout << e.what();
  }

  return 0;
}/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 9 */
#include <iostream>
#include <vector>
std::vector<double> DvaVektora(std::vector<double>&a, std::vector<int>&b) {
  std::vector<double>c;
  for (int i = 0; i < b.size(); i++) {
    if (b[i] < 0 || b[i] >= a.size())
      throw std::range_error("Pogresan indeks");
    c.push_back(a[b[i]]);
  }
  return c;
}
int main()
{
  std::vector<double>a{1.2, 2.3, 3.4, 4.5};
  std::vector<int>b{1, 2, 3, 8};
  try {
    for (double i : DvaVektora(a, b))
      std::cout << i << " ";
  }
  catch (std::range_error e) {
    std::cout << e.what();
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 10 */
#include <iostream>
#include <vector>
std::vector<bool>vrati_vektor_logicki(std::vector<int>a)
{
  std::vector<bool>b(a.size(), false);
  for (int i = 0; i < a.size(); i++)
  {
    if (a[i] < 0)
      throw std::domain_error("Element manji od 1");
    for (int j = 1; j < 1000; j++)
      if (j * j * j == a[i])
        b[i] = true;
  }
  return b;
}

int main()
{
  std::vector<int>a{1, 8, 10, -5, 216, 20};
  try
  {
    std::vector<bool>b = vrati_vektor_logicki(a);
    for (bool i : b)
      std::cout << i << " ";
  }
  catch (std::domain_error e)
  {
    std::cout << "Izuzetak: " << e.what();
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 11 */
#include <iostream>
#include <vector>
std::vector<int> VektorLongLong(std::vector<long long int>a) {
  std::vector<int>c;
  for (int i = 0; i < a.size(); i++) {
    if (a[i] < 0)
      throw std::range_error("Negativan");
    int broj_cifara = 0;
    while (a[i]) {
      int m = a[i] % 10;
      a[i] /= 10;
      broj_cifara++;
    }
    c.push_back(broj_cifara);
  }
  return c;
}
int main()
{
  std::vector<long long int>a{121111111111, 222222223, 344444565756767};
  try {
    for (double i : VektorLongLong(a))
      std::cout << i << " ";
  }
  catch (std::range_error e) {
    std::cout << e.what();
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 14 */
#include <iostream>
#include <vector>
bool Stacionaran(std::vector<std::vector<double>>a) {
  double gore, dolje, lijevo, desno;
  int kolone = a[0].size();
  for (int i = 1; i < a.size(); i++)
    if (a[i].size() != kolone)
      throw std::range_error("Grbava matrica");
  // elementi na rubu ne mogu biti stacionarni
  for (int i = 1; i < a.size() - 1; i++)
    for (int j = 1; j < kolone - 1; j++)
    {
      gore = a[i][j + 1];
      dolje = a[i][j - 1];
      desno = a[i + 1][j];
      lijevo = a[i - 1][j];
      if (gore == dolje == desno == lijevo == a[i][j])return true;
    }
  return false;
}
int main()
{
  std::vector<std::vector<double>>a{{2, 1, 3}, {1, 1, 1}, {4, 1, 5}};
  try {
    if (Stacionaran(a))
      std::cout << "Ima stacionarnih";
    else std::cout << "Nema stacionarnih";
  }
  catch (std::range_error e) {
    std::cout << e.what();
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 15 */
#include <iostream>
#include <vector>

bool Tranzitivna(std::vector<std::vector<bool>>a) {
  int velicina = a[0].size();
  for (int i = 1; i < a.size(); i++)
    if (a.size() != velicina || a[i].size() != velicina)
      throw std::domain_error("Nije kvadratna matrica");
  for (int i = 0; i < velicina; i++)
    for (int j = 0; j < velicina; j++)
      if (a[i][j])
        for (int k = 0; k < velicina; k++)
          if (a[j][k])
            if (!a[i][k])return false;
  return true;
}

int main ()
{
  std::vector < std::vector < bool >>a
  {
    {1, 1, 0, 1, 0},
    {0, 1, 0, 0, 0},
    {1, 1, 0, 1, 1},
    {1, 1, 0, 1, 0},
    {1, 1, 0, 1, 0}
  };
  try {
    std::cout << Tranzitivna(a);
  }
  catch (std::domain_error e) {
    std::cout << e.what();
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 16 */
#include <iostream>
#include <vector>
#include <limits>
#include <complex>
std::complex<int> ZamijeniKolone(std::vector<std::vector<double>>&a) {
  int kolone = a[0].size();
  for (int i = 1; i < a.size(); i++)
    if (a[i].size() != kolone)
      throw std::range_error("Parametar nema formu matrice");
  double najveci = std::numeric_limits<double>::min();
  double najmanji = std::numeric_limits<double>::max();
  int najmanji_index = -1, najveci_index = -1;
  for (int i = 0; i < a.size(); i++) {
    double proizvod_kolona = 1;
    for (int j = 0; j < a.size(); j++)
      for (int k = 0; k < kolone; k++)
        if (i == k)proizvod_kolona *= a[j][k];
    if (proizvod_kolona < najmanji) {
      najmanji_index = i;
      najmanji = proizvod_kolona;
    }
    else {
      najveci_index = i;
      najveci = proizvod_kolona;
    }
  }
  std::complex<int>broj(najmanji_index, najveci_index);
  for (int j = 0; j < a.size(); j++)
    for (int k = 0; k < kolone; k++)
    {
      double temp = a[j][najveci_index];
      a[j][najveci_index] = a[j][najmanji_index];
      a[j][najmanji_index] = temp;
    }
  return broj;
}
int main()
{
  std::vector<std::vector<double>>a{
    {2, 1, 3},
    {1, 1, 1},
    {4, 1, 5}};
  try {
    std::cout << ZamijeniKolone(a) << std::endl;
    for (auto i : a) {
      for (auto j : i)
        std::cout << j << " ";
      std::cout << std::endl;
    }
  }
  catch (std::range_error e) {
    std::cout << e.what();
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 17 */
#include <iostream>
#include <vector>
#include <limits>
#include <complex>
std::complex<int> ZamijeniRedove(std::vector<std::vector<double>>&a) {
  int kolone = a[0].size();
  for (int i = 1; i < a.size(); i++)
    if (a[i].size() != kolone)
      throw std::range_error("Parametar nema formu matrice");
  double najveca_suma_reda = std::numeric_limits<double>::min();
  double najmanja_suma_reda = std::numeric_limits<double>::max();
  int najmanja_suma_reda_index = -1, najveca_suma_reda_index = -1;
  for (int i = 0; i < a.size(); i++) {
    double suma_reda = 0;
    for (int j = 0; j < a.size(); j++)
      for (int k = 0; k < kolone; k++)
        if (i == k)suma_reda += a[j][k];
    if (suma_reda < najmanja_suma_reda) {
      najmanja_suma_reda_index = i;
      najmanja_suma_reda = suma_reda;
    }
    else {
      najveca_suma_reda_index = i;
      najveca_suma_reda = suma_reda;
    }
  }
  std::complex<int>broj(najmanja_suma_reda_index, najveca_suma_reda_index);
  for (int j = 0; j < a.size(); j++)
    for (int k = 0; k < kolone; k++)
    {
      double temp = a[najveca_suma_reda_index][j];
      a[najveca_suma_reda_index][j] = a[najmanja_suma_reda_index][j];
      a[najmanja_suma_reda_index][j] = temp;
    }
  return broj;
}
int main()
{
  std::vector<std::vector<double>>a{
    {2, 1, 3},
    {1, 1, 1},
    {4, 1, 5}};
  try {
    std::cout << ZamijeniRedove(a) << std::endl;
    for (auto i : a) {
      for (auto j : i)
        std::cout << j << " ";
      std::cout << std::endl;
    }
  }
  catch (std::range_error e) {
    std::cout << e.what();
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 18 */
#include <iostream>
#include <deque>
bool Circularna(std::deque<std::deque<double>>&a) {
  int kolone = a[0].size();
  for (int i = 1; i < a.size(); i++)
    if (a[i].size() != kolone)
      return false;
  for (int i = 1; i < a.size(); i++)
    for (int j = 0; j < kolone; j++) {
      if (j == 0) {
        if (a[i][j] != a[i - 1][kolone - 1])return false;
      }
      else {
        if (a[i][j] != a[i - 1][j - 1]) return false;
      }
    }
  return true;
}
int main()
{
  std::deque<std::deque<double>>a{
    {1, 2, 3},
    {3, 1, 2},
    {2, 3, 1}
  };
  std::cout << Circularna(a) << std::endl;

  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 19 */
#include <iostream>
#include <vector>
bool Idempotentna(std::vector<std::vector<double>>&a) {
  int velicina = a[0].size();
  for (int i = 1; i < a.size(); i++)
    if (a.size() != velicina || a[i].size() != velicina)
      return false;
  for (int i = 0; i < velicina; i++)
    for (int j = 0; j < velicina; j++) {
      double proizvod = 0;
      for (int k = 0; k < velicina; k++)
        proizvod += a[i][k] * a[k][j];
      if (a[i][j] != proizvod)return false;
    }
  return true;
}
int main()
{
  std::vector<std::vector<double>>a{
    {3, -6},
    {1, -2},
  };
  std::cout << Idempotentna(a) << std::endl;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 20 */
#include <iostream>
#include <vector>
bool Ortogonalna(std::vector<std::vector<double>>&a) {
  int velicina = a[0].size();
  for (int i = 1; i < a.size(); i++)
    if (a.size() != velicina || a[i].size() != velicina)
      return false;
  double proizvod, dijagonala, nedijagonala;
  for (int i = 0; i < velicina; i++)
    for (int j = 0; j < velicina; j++) {
      proizvod = 0; dijagonala = 0; nedijagonala = 0;
      for (int k = 0; k < velicina; k++)
        proizvod += a[i][k] * a[k][j];
      if (i == j)dijagonala += proizvod;
      else nedijagonala += proizvod;
    }
  if (dijagonala != 1)return false;
  if (nedijagonala)return false;
  return true;
}
int main()
{
  std::vector<std::vector<double>>a{
    {1, 0},
    {0, -1},
  };
  std::cout << Ortogonalna(a) << std::endl;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 21 */
#include <iostream>
#include <vector>
bool MagicnaKvadratna(std::vector<std::vector<double>>&a) {
  int velicina = a[0].size();
  for (int i = 1; i < a.size(); i++)
    if (a.size() != velicina || a[i].size() != velicina)
      return false;
  double suma_dijagonale_1 = 0, suma_dijagonale_2 = 0;
  for (int i = 0; i < velicina; i++)
    for (int j = 0; j < velicina; j++)
    {
      suma_dijagonale_1 += a[i][i];
      suma_dijagonale_2 += a[i][velicina - i - 1];
    }
  if (suma_dijagonale_1 != suma_dijagonale_2)return false;
  double suma_redova = 0, suma_kolona = 0;
  for (int i = 0; i < velicina; i++)
    for (int j = 0; j < velicina; j++) {
      suma_redova += a[i][j];
      suma_kolona += a[j][i];
    }
  if (suma_redova != suma_kolona ||
      suma_redova != suma_dijagonale_1)return false;
  return true;
}
int main()
{
  std::vector<std::vector<double>>a
  { { 2, 7, 6 },
    { 9, 5, 1 },
    { 4, 3, 8 }};
  std::cout << MagicnaKvadratna(a) << std::endl;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 41 */
#include <iostream>
#include <string>
#include <cctype>
bool KorektnaRijec(std::string&s) {
  for (int i = 0; i < s.length(); i++) {
    int broj_uzastopnih_samoglasnika = 0;
    while (toupper(s[i]) != 'A' && toupper(s[i]) != 'E'
           && toupper(s[i]) != 'I' && toupper(s[i]) != 'O'
           && toupper(s[i]) != 'U') {
      broj_uzastopnih_samoglasnika++;
      i++;
      if (i == s.length())break;
    }
    if (broj_uzastopnih_samoglasnika > 2)
      return false;
  }
  return true;
}
int main()
{
  std::string s;
  std::getline(std::cin, s);
  std::cout << KorektnaRijec(s) << std::endl;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 42 */
#include <iostream>
#include <string>
std::string UkloniRazmake(std::string&s) {
  std::string str;
  int broj = 0;
  for (int i = 0; i < s.length(); i++) {
    std::string rijec;
    while (s[i] == ' ' && i < s.length())i++;
    while (s[i] != ' ' && i < s.length())rijec += s[i++];
    if (broj == 0)str += rijec;
    else str += (" " + rijec);
    broj++;
  }
  return str.substr(0, str.size() - 1);
}
int main()
{
  std::string s;
  std::getline(std::cin, s);
  std::cout << "\"" << UkloniRazmake(s) << "\"" << std::endl;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 44 */
#include <iostream>
#include <string>
int broj_rijeci(std::string s) {
  int broj = 0;
  for (int i = 0; i < s.length(); i++) {
    while (s[i] == ' ' && i < s.length())
      i++;
    if (i == s.length())break;
    broj++;
    while (s[i] != ' ' && i < s.length())
      i++;
  }
  return broj;
}
int main()
{
  std::string s;
  std::getline(std::cin, s);
  std::cout << broj_rijeci(s) << std::endl;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 46 */
#include <iostream>
#include <string>
std::string RazdvojiSaZnakom(std::string s, std::string znak) {
  std::string str;
  int broj = 0;
  for (int i = 0; i < s.length(); i++) {
    std::string rijec;
    while (s[i] == ' ' && i < s.length())
      i++;
    while (s[i] != ' ' && i < s.length())
      rijec += s[i++];
    if (broj == 0)str += rijec;
    else str += (znak + rijec);
    broj++;
  }
  return str;
}
int main()
{
  std::string s;
  std::getline(std::cin, s);
  std::cout << "\"" << RazdvojiSaZnakom(s, ",") << "\"" << std::endl;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 46 */
#include <iostream>
#include <string>
std::string Satrovacki(std::string s) {
  std::string str;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == 'A' || s[i] == 'E'
        || s[i] == 'I' || s[i] == 'O'
        || s[i] == 'U')
      str = str + s[i] + "P" + s[i];
    else
      str += s[i];
  }
  return str;
}
int main()
{
  std::string s;
  std::getline(std::cin, s);
  std::cout << "\"" << Satrovacki(s) << "\"" << std::endl;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 50 */
#include <iostream>
#include <string>
#include <vector>

std::vector<int> BrojeviUStringu(std::string s) {
  std::vector<int>vek;
  int broj = 0;
  for (int i = 0; i < s.length(); i++) {
    std::string rijec;
    while (s[i] == ' ' && i < s.length())i++;
    while (s[i] != ' ' && i < s.length())rijec += s[i++];
    int j = 0;
    while (rijec[j] >= '0' && rijec[j] <= '9')j++;
    std::string znakovi = ".,;!?";
    // provjera znaka nakon broja
    for (int i = 0; i < znakovi.size(); i++)
      if (rijec[j] == znakovi[i] || rijec[j] == '\0') {
        vek.push_back(std::stoi(rijec));
        break;
      }
  }
  return vek;
}
int main()
{
  std::string s;
  std::getline(std::cin, s);
  for (int i : BrojeviUStringu(s))
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 52 */
#include <iostream>
#include <string>
#include <vector>
std::string ZamijeniUStringu(std::string s, std::vector<double>vek) {
  std::string str;
  int j = 0;
  for (int i = 0; i < s.length(); i++) {
    while (s[i] != '%' && s[i] != 'f' && s[i] != 'd' && i < s.length()) {
      str += s[i];
      i++;
    }
    if (s[i] == '%' && (s[i + 1] == 'd' || s[i + 1] == 'f')) {
      if (s[i + 1] == 'd')
        str += (std::to_string(int(vek[j])));
      if (s[i + 1] == 'f') {
        str+= std::to_string(vek[j]);
        while(s.back() == '0') s.pop_back();
      }
      j++;
      if (j > vek.size())
        throw std::range_error("Vektor nema dovoljno elemenata");
      if (i == s.length())break;
    }
  }
  return str;
}
int main()
{
  try {
    std::cout << ZamijeniUStringu("abc%dxx%fyy %d", {12.25, 34.13, 25});
    std::cout << "\n" << "abc12xx34.13yy 25";
  }
  catch (std::range_error e) {
    std::cout << e.what();
  }

  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 56 */
#include <iostream>
#include <string>
#include <vector>
int PodstringIndex(std::string s1, std::string s2) {
  int broj=-1;
  int j=0;
  for(int i=0;i<s1.length();i++){
      while(s1[i]!=s2[0]&&i<s1.length())
          i++;
      if(s1[i]==s2[0]){
          broj=i;
          break;
      }
  }
  return broj;
}
int main()
{
  char s1[1000], s2[1000];
  std::cin.getline(s1, sizeof s1);
  std::cin.getline(s2, sizeof s2);
  std::cout<<PodstringIndex(s1,s2);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR3 - ZADATAK 57 */
#include <iostream>
#include <string>
#include <vector>
std::vector<std::string> NapraviVektorStringova(std::string s) {
  std::vector<std::string>vek;
  for(int i=0;i<s.length();i++){
      std::string rijec;
      while(s[i]==' '&&i<s.length())
      i++;
      if(i==s.length())break;
      while(s[i]!=' '&&i<s.length())
      rijec+=s[i++];
      vek.push_back(rijec);
  }
  return vek;
}
int main()
{
  std::string s;
  std::getline(std::cin, s);
  for(std::string i:NapraviVektorStringova(s))
  std::cout<<i<<std::endl;
  return 0;
}
/*-----------------------------------------------*/