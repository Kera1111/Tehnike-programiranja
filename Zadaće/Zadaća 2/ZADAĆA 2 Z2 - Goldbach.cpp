// TP 2021/2022: Zadaća 2, Zadatak 2
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

vector<int> Sundaram(long long int n) {

  vector<int> prosti;
  vector<bool> markirani(n, false);
    int j=1;
  // skloni sve brojeve oblika i+j+2ij u spisku brojeva od 1 do n
  for (int i = 1; i <= j; i++) {
    for (j = i; i + j + 2 * i * j < n; j++) {
      markirani.at(i + j + 2 * i * j) = true;
    }
  }

  prosti.push_back(2); // 2 je prost broj al drugaciji od ostalih prostih pa
                       // moramo njega maksuz ubaciti

  // kako i algoritam kaze, sad ubacimo one sto nisu markirani u niz prostih
  for (int i = 1; i < n; i++) {
    if (markirani.at(i) == false) {
      prosti.push_back(2 * i + 1);
    }
  }

  return prosti;
}

void Goldbach(int n, int &p, int &q) {

  auto prosti(Sundaram(n));

  // specijalni slucajevi ako je manji il jednaki od 2
  if (n <= 2) {
    throw logic_error("Rastava ne postoji");
  }
  p = 0;
  q = 0;
  for (int i = 0; prosti.at(i) <= prosti.size(); i++) {
    // nadji razliku tako sto oduzmes n od trenutnog prostog
    // jer tehnicki kako hoce od nas da nadjemo sto manji broj kao jedan
    // sabirak, onda cemo to postici ovako najlakse tj naleti na prvi prosti sto
    // se javi i nadji samo njegov drugi sabirak i tjt
    int razlika = n - prosti.at(i);

    // ako je i ta razlika prost broj e onda si nasao sve sto ti treba
    if (binary_search(prosti.begin(), prosti.end(), razlika)) {
      // raspisi
      p = prosti.at(i);
      q = razlika;
      return;
    }
  }

  if (!p && !q) {
    throw logic_error("Rastava ne postoji");
  }
}

int main() {
  /*
  da bi rjesila ovaj zadatak, koristit cu Sundaramovo sito.
  Ono predstavlja algoritam da bi se našli svi prosti brojevi do nekog broja.
  Počinje sa listom cijelih brojeva od 1 do n. Iz ove liste, uklanja sve brojeve
  u obliku i + j + 2ij gdje: i i j su prirodni brojevi 1<=i<=j te i+j+2ij<=n
  ostali brojevi se udvostruce, povecaju dajuci listu neparnim brojevima
  tj prostim ispod 2n+2
  */
  int n, p, q;
  try {
    cout << "Unesi broj: ";
    cin >> n;
    Goldbach(n, p, q);
    cout << endl << n << " je zbir prostih brojeva " << p << " i " << q << endl;
  } catch (logic_error izuzetak) {
    cout << endl << n << " nije zbir dva prosta broja!" << endl;
  }

  return 0;
}
