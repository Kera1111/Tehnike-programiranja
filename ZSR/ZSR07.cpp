/*-----------------------------------------------*/
/* ZSR7 - ZADATAK 18 */
#include <iostream>
#include <vector>
#include <list>
template<typename tip>
bool DaLiJeSimetricna(std::list<tip>a) {
  int n = a.size();
  auto p = a.begin(), q = a.end();
  q--;
  for (int i = 0; i < n / 2; i++)
    if (*p++ != *q--)return false;
  return true;
}
int main() {
  std::list<int>a{3, 5, 8, 4, 5, 8, 6, 8, 5, 4, 8, 5, 3};
  std::cout << DaLiJeSimetricna(a);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR7 - ZADATAK 19 */
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
template<typename tip, typename T>
void KumulativnaSuma(tip poc, tip kraj, T b) {
  using tip_objekta = typename std::decay<decltype(*poc)>::type;
  tip_objekta suma = 0;
  while (poc != kraj) {
    suma += *poc;
    *b = suma;
    b++;
    poc++;
  }
}
int main() {
  std::list<int>a{1, 2, 3, 4, 5};
  std::vector<int>b;
  KumulativnaSuma(a.begin(), a.end(), std::back_inserter(b));
  for (int i : b)std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR7 - ZADATAK 20 */
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
template<typename tip>
auto SkalarniProizvod(tip poc, tip kraj, tip b) {
  using tip_objekta = typename std::decay<decltype(*poc)>::type;
  tip_objekta suma = 0;
  while (poc != kraj) {
    suma += (*poc**b);
    b++;
    poc++;
  }
  return suma;
}
int main() {
  std::list<int>a{1, 2, 3};
  std::list<int>b{3, 2, 1};
  std::cout << SkalarniProizvod(a.begin(), a.end(), b.begin());

  return 0;
}
/*-----------------------------------------------*/
/* ZSR7 - ZADATAK 21 */
#include <iostream>
#include <string>
#include <iterator>
#include <set>
template<typename tip, typename T>
T KopirajBezDuplikata(tip poc, tip kraj, T b) {
  using tip_objekta = typename std::decay<decltype(*poc)>::type;
  std::set<tip_objekta>s;
  for (; poc != kraj; poc++) {
    if (s.count(*poc) != 0)
      continue;
    *b++ = *poc;
    s.insert(*poc);
  }
  return b;
}
int main() {
  std::string a = "abc defabcd ghidef";
  std::string b;
  KopirajBezDuplikata(a.begin(), a.end(), std::back_inserter(b));
  std::cout << b;
  return 0;
}
/*-----------------------------------------------*/
/* ZSR7 - ZADATAK 22 */
#include <iostream>
#include <deque>
#include <iterator>
template<typename T1, typename T2, typename T3, typename T>
auto PopuniPoKriteriju(T1 p1, T1 p2, T2 p3, T3 p4, T f) {
  using tip_objekta = typename std::decay<decltype(*p1)>::type;
  tip_objekta suma = 0;
  while (p1 != p2) {
    suma += (*p1);
    *p3++ = f(*p1++);
  }
  return suma;
}
int main() {
  std::deque<int>a{1, 2, 3}, b;
  std::cout << PopuniPoKriteriju(a.begin(), a.end(), std::front_inserter(b), b.end(), [](int x) {return x * x;});
  auto it = b.begin();
  while (it != b.end())
    std::cout << *it++ << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR7 - ZADATAK 23 */
#include <iostream>
#include <deque>
#include <iterator>
template<typename T1, typename T2, typename T3, typename T>
auto PopuniPoKriteriju(T1 p1, T1 p2, T2 p3, T3 p4, T f) {
  using tip_objekta = typename std::decay<decltype(*p1)>::type;
  tip_objekta proizvod = 1;
  while (p1 != p2) {
    proizvod *= (*p1);
    *p3++ = f(*p1++);
  }
  return proizvod;
}
int main() {
  std::deque<int>a{1, 2, 3}, b;
  std::cout << PopuniPoKriteriju(a.begin(), a.end(), std::front_inserter(b), b.end(), [](int x) {return x * x * x;});
  auto it = b.begin();
  while (it != b.end())
    std::cout << *it++ << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR7 - ZADATAK 24 */
#include <iostream>
#include <list>
int PeriodListe(std::list<int>l) {
  int n = l.size();
  int p = 0;
  auto st = l.begin();
  while (n) {
    int count = 0;
    auto it = st;
    while (it != l.end()) {
      auto t = it;
      for (int j = 0; j < n; j++)
        t++;
      if (*it == *t)count++;
      it++;
    }
    if (count == l.size() - 1)p = n;
    n--;
  }
  return p;
}
int main() {
  std::list<int>l{5, 9, 7, 2, 5, 9, 7, 2, 5, 9, 7};
  std::cout << PeriodListe(l);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR7 - ZADATAK 25 */
#include <iostream>
#include <list>
#include <iterator>
template<typename T1, typename T2>
auto PrekopirajSimetricno(T1 p1, T1 p2, T2 p3) {
  T1 p = p1;
  while (p != p2) {
    *p3++ = *p++;
  }
  while (p != p1) {
    *p3++ = *--p;
  }
  return p3;
}
int main() {
  std::list<int>l, a;
  int x;
  for (int i = 0; i < 3; i++) {
    std::cin >> x;
    l.push_back(x);
  }
  PrekopirajSimetricno(l.begin(), l.end(), std::back_inserter(a));
  std::list<int>::iterator it = a.begin();
  while (it != a.end())
    std::cout << *it++ << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR7 - ZADATAK 26 */
#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <iterator>
int main() {
  std::list<std::string>l{"abc", "qwertzui", "def", "123456789"}, q;
  std::transform(l.begin(), l.end(), std::back_inserter(q), [](std::string & s) {
    int broj = 0;
    for (char c : s)
      if (toupper(c) >= 'A' && toupper(c) <= 'Z' || c >= '0' && c <= '9')
        broj++;
    if (broj > 7)s.clear();
    return s;
  });
  auto it = l.begin();
  while (it != l.end()) {
    if ((*it).size())std::cout << "\"" << *it << "\"" << std::endl; it++;
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR7 - ZADATAK 27 */
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
int main() {
  std::vector<std::list<int>>a{{3, 4}, {1, 2, 9}};
  std::sort(a.begin(), a.end(), [](std::list<int>a, std::list<int>b) {
    auto it = a.begin();
    int suma_a = 0, suma_b = 0;
    while (it != a.end())
      suma_a += (*it++);
    it = b.begin();
    while (it != b.end())
      suma_b += (*it++);
    return suma_a > suma_b;
  });
  for (auto i : a) {
    for (auto j : i)std::cout << j << " ";
    std::cout << std::endl;
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR7 - ZADATAK 28 */
#include <iostream>
#include <list>
#include <deque>
#include <algorithm>
int main() {
  std::deque<std::list<int>>a{{3, 4}, {1, 2, 9, 8}};
  std::sort(a.begin(), a.end(), [](std::list<int>a, std::list<int>b) {
    auto it = a.begin();
    int parni_a = 0, parni_b = 0;
    while (it != a.end())
      if ((*it++) % 2 == 0)parni_a++;
    it = b.begin();
    while (it != b.end())
      if ((*it++) % 2 == 0)parni_b++;
    return parni_a > parni_b;
  });
  for (auto i : a) {
    for (auto j : i)std::cout << j << " ";
    std::cout << std::endl;
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR7 - ZADATAK 29 */
#include <iostream>
#include <set>
template<typename tip>
std::set<tip>SimetricnaRazlika(std::set<tip>a, std::set<tip>b) {
  std::set<tip>c;
  auto it = a.begin();
  while (it != a.end()) {
    auto t = b.begin();
    bool nema_ga = true;
    while (t != b.end())
      if (*t++ == *it)nema_ga = false;
    if (nema_ga)c.insert(*it);
    it++;
  }
  it = b.begin();
  while (it != b.end()) {
    auto t = a.begin();
    bool nema_ga = true;
    while (t != a.end())
      if (*t++ == *it)nema_ga = false;
    if (nema_ga)c.insert(*it);
    it++;
  }
  return c;
}
int main() {
  std::set<int>a{1, 2, 3}, b{4, 2, 5, 3};
  std::set<int>c = SimetricnaRazlika(a, b);
  for (int i : c)std::cout << i << " ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR7 - ZADATAK 30 */
#include <iostream>
#include <stack>
std::stack<double>StekPomnozi(std::stack<double>a, int n){
std::stack<double>c;
while(!a.empty()){
    c.push(a.top()*n);
    a.pop();
}
return c;
}
int main(){
    std::stack<double>a;
    a.push(2); a.push(5); a.push(3); a.push(4);
    std::stack<double>c=StekPomnozi(a,3);
    while(!c.empty()){
        std::cout<<c.top()<<" ";c.pop();}
  return 0;
}
/*-----------------------------------------------*/
/* ZSR7 - ZADATAK 31 */
#include <iostream>
#include <string>
#include <stack>
std::stack<std::string> VratiStek(std::stack<std::string>a, std::string s) {
  std::stack<std::string>b;
  while(!a.empty()){
        std::string str=a.top();
        str+=s;
        b.push(str);
    a.pop();
  }
  return b;
}

int main() {
  std::stack<std::string>a,b;
  a.push("a"); a.push("b"); a.push("c");
  b=VratiStek(a,"xyz");
  while(!b.empty()){
    std::cout<<b.top()<<" ";
    b.pop();
  }
  return 0;
}
/*-----------------------------------------------*/
/* ZSR7 - ZADATAK 32 */
#include <iostream>
#include <vector>
template<typename tip, typename F>
tip Mapa(tip kontejner, F f){
tip a(kontejner.size());
for(int i=0;i<kontejner.size();i++)
    a[i]=f(kontejner[i]);
return a;
}
int main() {
    std::vector<int>a{1,2,3,4,5};
  std::vector<int>b=Mapa(a, [](int x){return x*x;});
  for(int i:b)std::cout<<i<<" ";
  return 0;
}
/*-----------------------------------------------*/
/* ZSR7 - ZADATAK 33 */
#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
std::function<double(double)> Polinom(std::vector<double>a){
return [a](double x){
    double suma=0;
for(int i=0;i<a.size();i++)
    suma+=(a[i]*pow(x,i));
    return suma;
};
}
int main() {
   auto poli = Polinom({3, 5, 0, 4, 1});
std::cout << poli(2);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR7 - ZADATAK 34 */
#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
std::function<double(double)> RacionalnaFunkcija(std::vector<double>a, std::vector<double>b){
return [a,b](double x){
    double brojnik=0,nazivnik=0;
for(int i=0;i<a.size();i++)
    brojnik+=(a[i]*pow(x,i));
    for(int i=0;i<b.size();i++)
    nazivnik+=(b[i]*pow(x,i));
    return brojnik/nazivnik;
};
}
int main() {
   auto rac = RacionalnaFunkcija({1,3,2}, {3,-2});
std::cout << rac(10);
  return 0;
}
/*-----------------------------------------------*/
/* ZSR7 - ZADATAK 35 */
#include <iostream>
#include <vector>
#include <list>
std::list<double> FunkcijaPomak(double f(double), double xmin, double xmax, double dx){
std::list<double>l;
for(int i=0;i<xmax;i++)
    l.push_back(f(xmin+i*dx));
    l.push_back(f(xmax));
return l;
}
int main() {
    for(double i:FunkcijaPomak([](double x){return 3*x*x-5;}, 0,10,0.1))
        std::cout<<i<<" "<<"\n";
  return 0;
}
/*-----------------------------------------------*/