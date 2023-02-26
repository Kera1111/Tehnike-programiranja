/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 5 */
#include <iostream>
void SumeCifara(int n, int &s_par, int &s_nepar) {
  s_par = 0; s_nepar = 0;
  while (n) {
    int cifra = n % 10;
    if (cifra % 2)
      s_nepar += cifra;
    else s_par += cifra;
    n /= 10;
  }
}
int main() {
  int a, b;
  SumeCifara(7232649, a, b);
  std::cout << a << " " << b;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 6 */
#include <iostream>
void VeceManje(int n, int &vece, int &manje) {
  vece = 0; manje = 0;
  while (n) {
    int cifra = n % 10;
    if (cifra > 5)
      vece += cifra;
    else manje += cifra;
    n /= 10;
  }
}
int main() {
  int a, b;
  VeceManje(123678, a, b);
  std::cout << a << " " << b;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 12 */
#include <iostream>
#include <cmath>
void Sredina(int n, double &as, double &gs, double &hs) {
  int broj_cifara = 0, suma = 0;
  double produkt = 1, suma_reciprocno = 0;
  while (n) {
    int cifra = n % 10;
    broj_cifara++;
    suma += cifra;
    produkt *= cifra;
    suma_reciprocno += 1. / cifra;
    n /= 10;
  }
  as = double(suma) / broj_cifara;
  gs = pow(produkt, 1. / broj_cifara);
  hs = 1 / (suma_reciprocno / broj_cifara);
}
int main() {
  double a, b, c;
  Sredina(123, a, b, c);
  std::cout << a << " " << b << " " << c;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 13 */
#include <iostream>
void RazdvojiCifre(int n, int &par, int &nepar) {
  par = 0; nepar = 0;
  int broj_neparnih = 0;
  while (n) {
    int cifra = n % 10;
    if (cifra % 2) {
      nepar *= 10;
      nepar += cifra;
    }
    else {
      par *= 10;
      par += cifra;
    }
    n /= 10;
  }
  // zaokreni brojeve
  int num = nepar; nepar = 0;
  while (num) {
    int cifra = num % 10;
    nepar *= 10;
    nepar += cifra;
    num /= 10;
  }
  num = par; par = 0;
  while (num) {
    int cifra = num % 10;
    par *= 10;
    par += cifra;
    num /= 10;
  }
}

int main() {
  int a, b;
  RazdvojiCifre(32564719, a, b);
  std::cout << a << " " << b;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 14 */
#include <iostream>
#include <vector>
void RazdvojiCifre(std::vector<int>vek, int &par, int &nepar) {
  par = 0; nepar = 0;
  for (int i = 0; i < vek.size(); i++)
    if (vek[i] % 2)nepar++;
    else par++;
}

int main() {
  int a, b;
  RazdvojiCifre({1, 2, 3, 4, 5}, a, b);
  std::cout << a << " " << b;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 15 */
#include <iostream>
#include <vector>
bool PozNeg(double *niz, int n, int &poz, int &neg) {
  bool rez = false;
  poz = 0; neg = 0;
  for (int i = 0; i < n; i++) {
    if (niz[i] == 0)rez = true;
    if (niz[i] < 0)neg++;
    else poz++;
  }
  return rez;
}

int main() {
  int a, b;
  double niz[5] { -1, -2, 1, 2, 3};
  std::cout << PozNeg(niz, 5, a, b) << " " << a << " " << b;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 18 */
#include <iostream>
#include <vector>
bool Cjelobrojni(double *niz, int n, int &cijeli, int &dec) {
  bool rez = false;
  cijeli = 0; dec = 0;
  for (int i = 0; i < n; i++) {
    if (niz[i] < 0)rez = true;
    if (niz[i] == int(niz[i]))cijeli++;
    else dec++;
  }
  return rez;
}
int main() {
  int a, b;
  double niz[5] {1.23, 5, 6, 4.5, -2};
  std::cout << Cjelobrojni(niz, 5, a, b) << " " << a << " " << b;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 19 */
#include <iostream>
#include <vector>
void DodajSuprotne(std::vector<int>&vek) {
  for (int &i : vek)
    i *= (-1);
}
int main() {
  int n, x;
  std::vector<int>vek;
  std::cin >> n;
  for (int i = 0; i < n; i++)
  {
    std::cin >> x;
    vek.push_back(x);
  }
  DodajSuprotne(vek);
  for (int i : vek)
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 20 */
#include <iostream>
#include <vector>
#include <limits>
void MinimaxMaximin(std::vector<std::vector<double>>mat, double &minimax, double &maximin) {
  int kolone = mat[0].size();
  for (int i = 1; i < mat.size(); i++)
    if (mat[i].size() != kolone)throw std::domain_error("Parametar nema formu matrice");
  minimax = std::numeric_limits<double>::max();
  maximin = std::numeric_limits<double>::min();
  for (int i = 0; i < mat.size(); i++) {
    double najveci_u_redu = mat[i][0];
    double najmanji_u_redu = mat[i][0];
    for (int j = 0; j < kolone; j++) {
      if (mat[i][j] > najveci_u_redu)najveci_u_redu = mat[i][j];
      if (mat[i][j] < najmanji_u_redu)najmanji_u_redu = mat[i][j];
    }
    if (najveci_u_redu < minimax)minimax = najveci_u_redu;
    if (najmanji_u_redu > maximin)maximin = najmanji_u_redu;
  }
}
int main() {
  double a, b;
  MinimaxMaximin({{1, 2, 3}, {4, 5, 6}}, a, b);
  std::cout << a << " " << b;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 21 */
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
std::deque<double> ObrniIDek(std::vector<std::vector<double>>&mat) {
  int kolone = mat[0].size();
  for (int i = 1; i < mat.size(); i++)
    if (mat[i].size() != kolone)throw std::domain_error("Parametar nema formu matrice");
  std::deque<double>dek;
  for (auto &i : mat)
    std::reverse(i.begin(), i.end());
  for (int i = 0; i < kolone; i++) {
    double suma_kolone = 0;
    for (int j = 0; j < mat.size(); j++)
      for (int k = 0; k < kolone; k++)
        if (i == k)suma_kolone += mat[j][k];
    dek.push_back(suma_kolone);
  }
  return dek;
}
int main() {
  std::vector<std::vector<double>>mat{{1, 2, 3}, {4, 5, 6}};
  for (double i : ObrniIDek(mat))
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 22 */
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
std::deque<double> ObrniIDek(std::vector<std::vector<double>>&mat) {
  for (int i = 1; i < mat.size(); i++)
    if (mat[i].size() != mat[i - 1].size() + 1)throw std::domain_error("Parametar nema formu trougaone matrice");
  std::deque<double>dek;
  for (auto &i : mat)
    std::reverse(i.begin(), i.end());
  for (int i = 0; i < mat.size(); i++) {
    double proizvod_kolone = 1;
    for (int j = 0; j < mat.size(); j++)
      for (int k = 0; k < mat[j].size(); k++)
        if (i == k)proizvod_kolone *= mat[j][k];
    dek.push_back(proizvod_kolone);
  }
  return dek;
}
int main() {
  std::vector<std::vector<double>>mat{{1}, {2, 3}, {4, 5, 6}};
  for (double i : ObrniIDek(mat))
    std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 23 */
#include <iostream>
#include <vector>
bool PozNeg(double *niz, int n, int &poz, int &neg) {
  bool rez = false;
  poz = 0; neg = 0;
  for (int i = 0; i < n; i++) {
    if (niz[i] < 0)rez = true;
    if (niz[i] % 2)neg++;
    else poz++;
  }
  return rez;
}

int main() {
  int a, b;
  double niz[5] { -1, -2, 1, 2, 3};
  std::cout << PozNeg(niz, 5, a, b) << " " << a << " " << b;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 26 */
#include <iostream>
#include <vector>
bool JednocifreniDvocifreni(int *niz, int n, int &jedan, int &dva) {
  bool rez = false;
  jedan = 0; dva = 0;
  for (int i = 0; i < n; i++) {
    if (niz[i] < 0)rez = true;
    int num = niz[i];
    int broj_cifara = 0;
    while (num) {
      broj_cifara++;
      num /= 10;
    }
    if (niz[i] == 0)broj_cifara++;
    if (broj_cifara == 1)jedan++;
    if (broj_cifara == 2)dva++;
  }
  return rez;
}

int main() {
  int a, b;
  int niz[5] {1, 23, 456, 789, 0};
  std::cout << JednocifreniDvocifreni(niz, 5, a, b) << " " << a << " " << b;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 28 */
#include <iostream>
#include <vector>
#include <deque>
void OdstraniParneCifre(int &n) {
  std::deque<int>temp;
  while (n) {
    int cifra = n % 10;
    if (cifra % 2)
      temp.push_front(cifra);
    n /= 10;
  }
  n = 0;
  for (int i = 0; i < temp.size(); i++) {
    n *= 10;
    n += temp[i];
  }
}

int main() {
  int n = 32564718;
  OdstraniParneCifre(n);
  std::cout << n;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 29 */
#include <iostream>
#include <string>
void AnalizaStringa(std::string s, int &velika, int &mala, int &ostala) {
  velika = 0; mala = 0; ostala = 0;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] >= 'A' && s[i] <= 'Z')velika++;
    else if (s[i] >= 'a' && s[i] <= 'z')mala++;
    else ostala++;
  }
}
int main() {
  int a, b, c;
  AnalizaStringa("Ovo JE!striNG.,", a, b, c);
  std::cout << a << " " << b << " " << c;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 30 */
#include <iostream>
#include <string>
void AnalizaStringa(std::string s, int &velika, int &cifre, int &ostala) {
  velika = 0; cifre = 0; ostala = 0;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] >= 'A' && s[i] <= 'Z' || s[i] >= 'a' && s[i] <= 'z')velika++;
    else if (s[i] >= '0' && s[i] <= '9')cifre++;
    else ostala++;
  }
}
int main() {
  int a, b, c;
  AnalizaStringa("Ovo 1JE!striNG.,5", a, b, c);
  std::cout << a << " " << b << " " << c;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 33 */
#include <iostream>
#include <string>
void PovecajString(std::string &s) {
  for (int i = 0; i < s.length(); i++)
    s[i]++;
}
int main() {
  std::string s("PROBA");
  PovecajString(s);
  std::cout << s;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 34 */
#include <iostream>
#include <string>
void UmanjiString(std::string &s) {
  for (int i = 0; i < s.length(); i++)
    s[i]--;
}
int main() {
  std::string s("PROBA");
  UmanjiString(s);
  std::cout << s;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 35 */
#include <iostream>
#include <string>
void IzbaciRazmakePovecajSlova(std::string &s) {
  for (char &c : s)
    c = toupper(c);
  for (int i = 0; i < s.length(); i++) {
    while (s[i] == ' ')s.erase(s.begin() + i);
    while (s[i] != ' ' && i < s.length())i++;
  }
  if (s[s.length() - 1] == ' ')s.pop_back();
}
int main() {
  std::string s("  ovo je string  ");
  IzbaciRazmakePovecajSlova(s);
  std::cout << "\"" << s << "\"";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 36 */
#include <iostream>
#include <string>
void ROT13(std::string &s) {
  for (int i = 0; i < s.length(); i++) {
    if (tolower(s[i]) >= 'a' && tolower(s[i]) <= 'm')s[i] += 13;
    else if (tolower(s[i]) >= 'n' && tolower(s[i]) <= 'z')s[i] -= 13;
    else continue;
  }
}
int main() {
  std::string s("ovo je ROT13");
  ROT13(s);
  std::cout << "\"" << s << "\"";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 37 */
#include <iostream>
#include <string>
void PrvoSlovo(std::string &s) {
  for (int i = 0; i < s.length(); i++) {
    while (s[i] == ' ' && i < s.length())i++;
    bool prvo_slovo = false;
    while (s[i] != ' ' && i < s.length()) {
      if (!prvo_slovo)
        if (s[i] >= 'a' && s[i] <= 'z')s[i] = toupper(s[i]);
      i++;
      prvo_slovo = true;
    }
  }
}
int main() {
  std::string s(" Dobio sam 25 maraka Danas   ");
  PrvoSlovo(s);
  std::cout << "\"" << s << "\"";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 38 */
#include <iostream>
#include <vector>
void IstaParnost(std::vector<int>&vek) {
  for (int i = 0; i < vek.size(); i++) {
    int num = vek[i];
    int broj_parnih = 0, broj_neparnih = 0, broj_cifara = 0;
    while (num) {
      int cifra = num % 10;
      if (cifra % 2)broj_neparnih++;
      else broj_parnih++;
      num /= 10;
      broj_cifara++;
    }
    if (broj_parnih == broj_cifara || broj_neparnih == broj_cifara) {
      for (int j = i + 1; j < vek.size(); j++)
        vek[j - 1] = vek[j];
      vek.resize(vek.size() - 1);
      i--;
    }
  }
}
int main() {
  std::vector<int>vek{351, 452, 736, 2806, 912};
  IstaParnost(vek); //452, 736 i 912
  for (int i : vek)std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 39 */
#include <iostream>
#include <string>
void DodajRazmake(std::string &s, int n) {
  std::string str;
  for (int i = 0; i < s.length(); i++) {
    str += s[i];
    for (int j = 0; j < n; j++)
      str += ' ';
  }
  s = str;
}
int main() {
  std::string s = "lopta";
  DodajRazmake(s, 2);
  std::cout << "\"" << s << "\"";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 40 */
#include <iostream>
#include <vector>
void DodajSuprotne(std::vector<int> &vek) {
  int n = vek.size();
  for (int i = 0; i < n; i++)
    vek.insert(vek.begin() + 2 * i + 1, -vek[2 * i]);
}
int main() {
  std::vector<int>vek;
  int n, x;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> x;
    vek.push_back(x);
  }
  DodajSuprotne(vek);
  for (int i : vek)std::cout << i << " ";
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 41 */
#include <iostream>
#include <vector>
#include <complex>
void KompleksniVektor(std::vector<std::complex<double>>&vek,
                      std::vector<double>&a, std::vector<double>&b) {
  for (int i = 0; i < vek.size(); i++) {
    a.push_back(abs(vek[i]));
    b.push_back(arg(vek[i]));
  }
}
int main() {
  std::vector<std::complex<double>>vek;
  for (int i = 0; i < 3; i++)
  {
    std::complex<double>temp(i + 1, i + 2);
    vek.push_back(temp);
  }
  std::vector<double>a, b;
  KompleksniVektor(vek, a, b);
  for (double i : a)std::cout << i << " ";
  std::cout << std::endl;
  for (double i : b)std::cout << i << " ";
}

/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 43 */
#include <iostream>
template<typename tipPOK, typename tipEL>
void MinMaxGeneric(tipPOK pocetak, tipPOK kraj,
                   tipEL &najveci, tipEL &najmanji) {
  najveci = *pocetak;
  najmanji = *pocetak;
  while (pocetak != kraj) {
    if (*pocetak > najveci)najveci = *pocetak;
    if (*pocetak < najmanji)najmanji = *pocetak;
    pocetak++;
  }

}
int main() {
  int niz[] {1, 2, 3, 4, 5}, a, b;
  MinMaxGeneric(niz, niz + 5, a, b);
  for (int i : niz)std::cout << i << " ";
  std::cout << a << " " << b;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 45 */
#include <iostream>
template<typename tip>
int LokalniMaksimum(tip *niz, int n) {
  int broj = 0;
  for (int i = 0; i < n; i++)
    if (niz[i] > niz[i - 1] && niz[i] > niz[i - 2] && i >= 2)broj++;
  return broj;
}
int main() {
  int niz[] {1, 2, 3, 4, 5};
  std::cout << LokalniMaksimum(niz, 5);
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 46 */
#include <iostream>
template<typename tip>
void Razvrstaj(tip *niz1, int &n1, tip *niz2, int &n2, tip *niz3, int &n3,
               tip min, tip max ) {
  for (int i = 0; i < n1; i++)
  {
    if (niz1[i] >= min && niz1[i] <= max)
      niz2[n2++] = niz1[i];
    else
      niz3[n3++] = niz1[i];
  }
}
int main() {
  int niz1[5] {1, 2, 3, 4, 5}, niz2[20] {7, 8, 9}, niz3[20] {9, 9};
  int min = 2, max = 4, n1 = 5, n2 = 3, n3 = 2;
  Razvrstaj(niz1, n1, niz2, n2, niz3, n3, min, max);
  for (int i = 0; i < n2; i++)
    std::cout << niz2[i] << " ";
  std::cout << std::endl;
  for (int i = 0; i < n3; i++)
    std::cout << niz3[i] << " ";
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 50 */
#include <iostream>
#include <vector>
template<typename tip>
int MostCommon(std::vector<tip>vek)
{
  int max_count = 0;
  tip most_common;
  for (int i = 0; i < vek.size(); i++)
  {
    int count = 0;
    for (int j = 0; j < vek.size(); j++)
      if (vek[i] == vek[j])count++;
    if (count > max_count)
    {
      max_count = count;
      most_common = vek[i];
    }
  }
  return most_common;
}
int main()
{
  std::vector<int>vek{3, 8, 2, 5, 4, 2, 3, 8, 5, 1, 8, 2, 7, 8, 2};
  std::cout << MostCommon(vek);
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 51 */
#include <iostream>
#include <vector>
template<typename tip>
void UkoliNadprosjecne(std::vector<tip>&vek)
{
    double suma=0,aritmeticka;
    for(int i=0; i<vek.size(); i++)
    suma+=vek[i];
    aritmeticka=suma/vek.size();
    for(int i=0;i<vek.size();i++)
        if(vek[i]>aritmeticka){
        for(int j=i+1;j<vek.size();j++)
        vek[j-1]=vek[j];
        vek.resize(vek.size()-1);
        i--;}
}
int main()
{
    std::vector<double>vek{7.43, 13.5, 7.11, 2.3, 10.3, -5.12, 
      6.12, 4.39, 5.01, 6.3,0};
    UkoliNadprosjecne(vek);
   for(double i:vek)std::cout<<i<<" ";
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 54 */
#include <iostream>
#include <vector>
template<typename tip>
void UkoliInterval(std::vector<tip>&vek, tip min, tip max)
{
    for(int i=0;i<vek.size();i++)
        if(vek[i]>=min&&vek[i]<=max){
        for(int j=i+1;j<vek.size();j++)
        vek[j-1]=vek[j];
        vek.resize(vek.size()-1);
        i--;}
}
int main()
{
    std::vector<double>vek{3, 8, 5, 6, 1, 4, 9, 7, 2, 2, 6, 
    4, 9, 1, 4, 8, 3, 6, 5};
    UkoliInterval(vek, 3.,9.);
   for(double i:vek)std::cout<<i<<" ";
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 55 */
#include <iostream>
#include <vector>
template<typename tip>
std::vector<std::vector<tip>> KnockerovProdukt
(std::vector<tip>a, std::vector<tip>b)
{
    std::vector<std::vector<tip>>mat(a.size(),std::vector<tip>(b.size()));
    for(int i=0;i<a.size();i++)
        for(int j=0;j<b.size();j++)
        mat[i][j]=(a[i]*b[j]);
        return mat;
}
int main()
{
    for(auto i:KnockerovProdukt<int>({1,2,3},{4,5,6})){
        for(auto j:i)
            std::cout<<j<<" ";
    std::cout<<std::endl;
        }
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 56 */
#include <iostream>
#include <vector>
template<typename tip>
int OdrediOsnovniPeriod(std::vector<tip>vektor)
{
    int p = 0;
    for (int i = 1; !p && i < vektor.size(); i++)
    {
        int j = 0;
        while (j < vektor.size() - i && vektor[j] == vektor[j + i]) j++;
        if ( j + i == vektor.size() ) p = i;
    }
    return p;
}
int main()
{
    std::vector<double>vektor{/*5, 9, 7, 2, 5, 9, 7, 2, 5, 9, 7*/};
    int n,x;
    std::cin>>n;
    for(int i=0;i<n;i++){
        std::cin>>x;
        vektor.push_back(x);
    };
    std::cout<<OdrediOsnovniPeriod(vektor);
    return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 57 */
#include <iostream>
#include <vector>
template<typename tip>
void NajmanjiNajveci(tip *niz, int n, int &min, int &max)
{
    int broj_istih=0;
    for(int i=1;i<n;i++)
    if(niz[i]==niz[0])broj_istih++;
    if(broj_istih==n-1)throw std::logic_error("Svi isti");
    min=niz[0];max=niz[0];
    for(int i=0;i<n;i++){
        if(niz[i]<min)min=niz[i];
    if(niz[i]>max)max=niz[i];}
}
int main()
{
    int niz[5]{1,2,3,4,5},min,max;
    NajmanjiNajveci(niz,5,min,max);
    std::cout<<min<<" "<<max;
    return 0;
}
/*-----------------------------------------------*/
/* ZSR4 - ZADATAK 58 */
#include <iostream>
#include <vector>
template<typename tip>
bool Simetrican(std::vector<tip>vek)
{
    int vel=vek.size();
    std::vector<tip>temp;
        for(int i=0;i<vel/2;i++)
            temp.push_back(vek[i]);
        int j=0;
        for(int i=vel-1;i>vel/2;i--)
            if(vek[i]!=temp[j++])return false;
    return true;
}
int main()
{
    std::cout<<Simetrican<int>({3,5,8,4,5,8,8,5,4,8,5,3});

    return 0;
}
/*-----------------------------------------------*/























