/*
    TP 2018/2019: LV 6, Zadatak 1

        Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja
        i sugestije saljite na mail: khodzic2@etf.unsa.ba

        Napomene: testovi su konacni tek pred tutorijal
                          za krsenje zabrana dobiva se 0 bodova za zadatak

*/

#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <limits> //treba mi zbog numeric_limits, jer daje range tipa podataka
#include <new>
#include <stdexcept>


using namespace std;

template <typename nekiTip> nekiTip *GenerirajStepeneDvojke(int n) {

  if (n <= 0)
    throw domain_error("Broj elemenata mora biti pozitivan");

  nekiTip *niz(nullptr); // stavljam da nekiTip pokazivaca pokazuju na nista tj nullptr

  try {
    niz = new nekiTip[n]; // vrsenje alokacije
  } catch (...) {
    throw runtime_error("Alokacija nije uspjela");
  }

  nekiTip broj = 1;
  for (int i = 0; i < n; i++) { // mora do n ici bez ukljucujuci ga jer ce se u obratnom desiti
              // integer overflow, ali kako u fja radi 2^n on tehnicki ce moci
              // izdrzat samo do pola tako da poslije pola baci error
    if (i != n - 1 && broj >= numeric_limits<nekiTip>::max() / 2) { // ako je doslo do pola a nije ni do zadnjeg dosao
                         // clana onda ce doci do overflowa u sljedecem koraku pa
                         // da mi na vrijeme obustavimo to
      delete[] niz;
      throw overflow_error("Prekoracen dozvoljeni opseg");
    }
    niz[i] = broj;
    broj *= 2; // ne moze pow(2,i) ako se ne raspise fino jer opet dodje do
               // integer overflowa
  }
  return niz;
}

int main() {
  cout << "Koliko zelite elemenata: ";
  int n;
  cin >> n;
  unsigned long int *a; // sustinski moze i auto a kao deklaracija, ali onda bi
                        // morala incijalizovat, al nema potrebe jer svaki
                        // autotest ima svoj main pa ce on tamo dodat vrijednost,
                        // ja mogu za jedan konkretan raspisat(unsigned long int)
  try {
    a = GenerirajStepeneDvojke<unsigned long int>(n);
  } catch (exception &izuzetak) {
    cout << "Izuzetak: " << izuzetak.what();
    return 0;
  }
  for (int i = 0; i < n; i++) {
    cout << fixed << setprecision(0) << a[i] << " ";
  }
  delete[] a; // da ne curi memorija brisi sve iako moderni kompajleri
              // automatski brisu poslije svakog izvrsenja programa
  return 0;
}