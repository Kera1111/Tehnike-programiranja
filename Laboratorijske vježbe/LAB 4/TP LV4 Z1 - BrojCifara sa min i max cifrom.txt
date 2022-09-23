// TP 2021/2022: LV 4, Zadatak 1
#include <cmath>
#include <iostream>

using namespace std;

/*
trazimo min i max cifru i brCifara od nekog broja
naci cemo min tako sto poredimo svaku cifru sa 9 i smanjujemo sve dok ne dodjemo
do najmanje, analogno i za max krecemo od 0 i spasavamo vece cifre sve dok ne
naidjemo na najvecu dok provjeravamo ovo sve brojac se povecava za brCifara
*/

int Cifre(long long int n, int &c_min, int &c_max) {
  c_max = 0;
  c_min = 9;
  int brojCifara = 0, cifra;

  /*
  postoji poseban slucaj kada je n=0 tada ima samo jednu cifru ali je ujedno i
  min i max jednak 0, za jednocifrene brojeve isto izlazi max=min=cifri
  brCifara=1
  */

  if (n == 0) {
    brojCifara = 1;
    c_min = 0;
    c_max = 0;
  }

  /*
npr. -345
  */

  while (n != 0) {
    cifra = n % 10; //-345%10=-5,  34%10=4,  3%10=3
    if (cifra < 0)
      cifra *= (-1);    //-5-->5,  /  , /
    if (cifra <= c_min) // 5<9 da, 4<5 da, 3<4 da
      c_min = cifra;
    if (cifra >= c_max) // 5>0 da, 4>5 ne, 3>5 ne
      c_max = cifra;
    brojCifara++; // 1,2,3
    n /= 10;      // 345/10=34,34/10=3,3/10=0
  }
  return brojCifara; // 3    max=5, min=3
}

int main() {

  long long int n;
  int mini, maxi;

  cout << "Unesite broj: ";
  cin >> n;
  int e = Cifre(n, mini, maxi);
  cout << "Broj " << n << " ima " << e << " cifara, najveca je " << maxi
       << " a najmanja " << mini << "." << endl;

  return 0;
}
