// TP 2021/2022: LV 4, Zadatak 4
#include <cmath>
#include <iostream>
#include <string>

using namespace std;
template <typename NekiTip>

/*
prvi parametar ispisuje tekst prompta "pitanja", drugi ispise gresku ako se
javi, treci unosi broj

ako se ne unese broj ili ako nije sljedeci karakter koji je unesen razmak onda
nek se unosi jos peek koristimo da bi racunar vidio sta je sljedeci char al da
ga samo virne, ne da ga mijenja koristi il slicno

ako je uneseno kako treba nek prestane unos i nek se ocisti tok i sve sto je
dotad bilo uneseno

ako nije uneseno kako treba ispisi gresku da ne valja mu unos, nek ga ponovi, a
mi cemo ocistit tok za njega
*/

void UnosBroja(string prompt, string txtgreske, NekiTip &broj) {
  cout << prompt;
  while (!(cin >> broj) || cin.peek() != '\n') {
    cin >> broj;
    if (cin) {
      cin.ignore(10000, '\n');
      return;
    }
    cout << txtgreske << endl;
    cin.clear();
    cin.ignore(10000, '\n');
    cout << prompt;
  }
}

int main() {
  double x, rez = 1;
  int n;
  UnosBroja("Unesite bazu: ", "Neispravan unos, pokusajte ponovo...\n", x);
  UnosBroja("Unesite cjelobrojni eksponent: ",
            "Neispravan unos, pokusajte ponovo...\n", n);

  /*
  posto ne daju nam da koristimo pow(x,n) onda koristimo for petlju do abs(n) i
  mnozimo rez n puta sa bazom x, ako je n negativan to znaci da uzimamo
  reciprocnu vrijednost pa za to moramo posebnu petlju
  */

  for (int i = 0; i < abs(n); i++) {
    rez *= x;
  }
  if (n < 0) {
    rez = 1 / rez;
  }

  cout << endl << x << " na " << n << " iznosi " << rez << endl;

  return 0;
}
