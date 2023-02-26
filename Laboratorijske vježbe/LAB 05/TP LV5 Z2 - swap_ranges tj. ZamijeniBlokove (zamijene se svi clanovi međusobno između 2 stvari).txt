/*
    TP 2018/2019: LV 5, Zadatak 2

        Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
        mozete slati na mail nslamnik1@etf.unsa.ba.

        NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
                          da se koristi indeksiranje niz[i] ili simulacija
   indeksiranja npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.

                          To ce tutori rucno pregledati u toku tutorijala te ako
                          student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se
   da za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

template <typename nekiTip, typename nekiDrugiTip>

auto RazmijeniBlokove(nekiTip p1, nekiTip p2, nekiDrugiTip p3) {
	//koristimo onaj najobicniji algoritam za sortiranje niza samo sto ovdje koristimo da bi prebacili iz jednog u drugi i da bi to uradili potrebna nam je neka temp
//varijabla da bi smjestili privremeno vrijednosti jednog vektora/niza
  while (p1 != p2) {
    auto temp = *p1;
    *p1 = *p3;
    *p3 = temp;

    p1++;
    p3++;
  }
  return p3;
}

template <typename nekiTip> void ispis(nekiTip pocetak, nekiTip kraj) {
  while (pocetak != kraj) {
    cout << *pocetak++ << " ";
  }
}

int main() {

  vector<int> v1{1, 2, 3, 4, 5, 6};
  int niz[5]{56, 235, 12, 521, 9};
  /*
  swap_ranges() - swap all elements of two sequences
  */
  RazmijeniBlokove(v1.begin(), v1.end(), &niz[0]);od pocetka do kraja vektora koristi vrijednosti od niza i zamijeni im vrijednosti
  ispis(v1.begin(), v1.end());
  cout << endl;
  ispis(niz, niz + 5);
}