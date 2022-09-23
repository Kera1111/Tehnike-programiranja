/*
    TP 2018/2019: ===TITLE===

        Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
        mozete slati na mail nslamnik1@etf.unsa.ba.

        NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
                          da se koristi indeksiranje dek[i] ili simulacija
   indeksiranja npr. *(dek + i); dalje, da su zabranjene for petlje i slicno.

                          To ce tutori rucno pregledati u toku tutorijala te ako
                          student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se
   da za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>

using namespace std;

bool JelPotpunKvadrat(int x) { return sqrt(x) == int(sqrt(x)); }

bool BrojCifara(int x, int y) {
  x = abs(x);
  y = abs(y);
  return log10(x) < log10(y);
}

bool Trocifren(double n) {
  n = abs(n);
  if (log10(n) >= 2 && log10(n) < 3)
    return true;
  else
    return false;
}

void Unos(int &x) { cin >> x; }

void Ispis(int &x) { cout << x << " "; }
int minCifre = 10;

int main() {

  int n;
  cout << "Unesite broj elemenata: ";
  cin >> n;
  deque<int> dek(n);
  cout << "Unesite elemente: ";

  for_each(dek.begin(), dek.end(), [](int &x) { cin >> x; });//sve isto samo s lambda fjama a one se koriste kad se samo jednom koriste u sustini
//tj kad su nam samo potrebne jednom nema potrebe da ih gore pravimo pa dolje pozivamo

  cout << "Najveci element deka je " << *max_element(dek.begin(), dek.end())//kad je deque u pitanju mora se vako pisat pocetak i kraj deka
       << endl;

  cout << "Najmanji element deka se pojavljuje "
       << count(dek.begin(), dek.end(), *min_element(dek.begin(), dek.end()))
       << " puta u deku" << endl;

  cout << "U deku ima "
       << count_if(dek.begin(), dek.end(),
                   [](int x) { return sqrt(x) == int(sqrt(x)); })//lambda fje se sastoje od uglastih zagrada onda parametar (int x) a unutar viticastih sta se radi
       << " brojeva koji su potpuni kvadrati" << endl;

  for_each(dek.begin(), dek.end(), [](int x) {//"void" lambda fja gdje smanjujemo najvecu mogucu vrijednost cifara za int dok ne dodjemo do minCifre
    int temp = int(log10(abs(x))) + 1;
    if (temp < minCifre)
      minCifre = temp;
  });

  cout << "Prvi element sa najmanjim brojem cifara je "
       << *find_if(dek.begin(), dek.end(),
                   [](int x) { return int(log10(abs(x))) + 1 == minCifre; })
       << endl;

  cout << "Elementi koji nisu trocifreni su: ";
  deque<int> novi(n);
  deque<int>::iterator kraj =
      remove_copy_if(dek.begin(), dek.end(), novi.begin(),
                     [](int x) { return int(log10(abs(x))) + 1 == 3; });
  for_each(novi.begin(), kraj, [](int x) { cout << x << " "; });
}