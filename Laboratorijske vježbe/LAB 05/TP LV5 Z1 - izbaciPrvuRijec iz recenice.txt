/*
    TP 2018/2019: LV 5, Zadatak 1

        Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
        mozete slati na mail nslamnik1@etf.unsa.ba.

        NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
                          da se koristi indeksiranje niz[i] ili simulacija
   indeksiranja npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.

                          To ce tutori rucno pregledati u toku tutorijala te ako
                          student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se
   da za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <iostream>

using namespace std;

int main() {
  char recenica[1000];//receno je u postavci da se ne smiju koristit stringovi pa ovako se mora unos raditi
  cout << "Unesite recenicu: ";
  cin.getline(recenica, sizeof(recenica), '\n');

  char *pok = recenica;
  //*pok uslov je ako je validan unos tj dok nije \0
  while (*pok && *pok == ' ')
    pok++; // preskacemo pocetne razmake
  while (*pok && *pok != ' ')
    pok++; // preskacemo prvu rijec
  while (*pok && *pok == ' ')
    pok++; // preskacemo razmake prije druge rijeci
  /* Ispis recenice bez prve rijeci: */
  cout << "Recenica bez prve rijeci glasi: " << pok << endl;

  return 0;
}
