// TP 2021/2022: LV 3, Zadatak 8
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>


using namespace std;

string IzdvojiRijec(string words, int n) {
  int brojac(0), provjera(0), i(0);
  string rijec;
  if (n < 1) {
    throw range_error(
        "IZUZETAK: Pogresan redni broj rijeci!"); // ne postoji 0.ta ili
                                                  // negativni redni br rijeci
  }
  for (i = 0; i < words.size(); i++) { // Ja sam Hana (n=1),(n=3)
    if (words[i] != ' ' && i == 0) {   // br=1, ne udje u petlju
      brojac++;
    } else if (words[i] != ' ' && i != 0 && words[i - 1] == ' ') {
      brojac++;
    }
    if (brojac == n) { // odgovara ulazi, nastavlja dalje dok ne dodje do 3
      while (words[i] != ' ' && i < words.size()) {
        rijec.push_back(
            words[i]); // J naletilo ali mora do kraja popuniti tu rijec, kada
                       // dodje brojac=3 onda napuni rijec H do kraja tj do Hana
        i++;
      }
      provjera = 1;
      break;
    }
  }
  if (!provjera)
    throw range_error(
        "IZUZETAK: Pogresan redni broj rijeci!"); // ako sluc naleti neka greska
                                                  // da nije nasao tu rijec

  return rijec;
}

int main() {

  int n;
  string rijec, words;
  cout << "Unesite redni broj rijeci: ";
  cin >> n;
  cout << "Unesite recenicu: ";
  cin >> ws; // da skloni bjeline na pocetku iz toka
  getline(cin, words);

  try {
    rijec = IzdvojiRijec(words, n);
  } catch (range_error izuzetak) {
    cout << izuzetak.what() << endl; // ako se ne uhvati kakav error izbaci
                                     // rijec, a ako da e onda error poruka
    return 0;
  }

  cout << "Rijec na poziciji " << n << " je " << rijec;

  return 0;
}