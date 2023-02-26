/*
    TP 2018/2019: LV 5, Zadatak 7

        Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
        mozete slati na mail nslamnik1@etf.unsa.ba.

        NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
                          da se koristi indeksiranje niz[i] ili simulacija
   indeksiranja npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.

                          To ce tutori rucno pregledati u toku tutorijala te ako
                          student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se
   da za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <deque>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename neki>
void Suma(neki pocetak, neki kraj, decltype(*pocetak) suma) {
  if (pocetak == kraj)
    return;
  suma += *pocetak;
  Suma(++pocetak, kraj,
       suma); // rekurzivna jer prolazim kroz to nesto i idem do kraja a sve se
              // to dodaje na sumu, a prolazim tako sto povecam pocetak svaki put
              // i to prvo logicno ++pocetak a ne pocetak++ jer parametar hocu da
              // mi bude prihvacen kao sljedeci clan kako treba a ne da ga poveca
              // a uzme stari
}

template <typename neki>
auto SumaBloka(neki pocetak, neki kraj) -> decltype(*pocetak + *pocetak) {

  if (pocetak == kraj)//ako je prazan
    throw range_error("Blok je prazan");
  if (kraj - pocetak == 1)//ako ima samo jedna stvar
    return *pocetak;

  decltype(*pocetak + *pocetak) suma = *pocetak + *(pocetak + 1);
  pocetak += 2;
  Suma(pocetak, kraj, suma);
  return suma;
}

int main() {
  std::vector<double> v{-95, 25, 333, 96, 6, 12, 1, 2, 35, 0};
  std::cout << "Suma bloka je: " << SumaBloka(v.begin(), v.end());
  return 0;
}

DRUGA VERZIJA KODA (PUNO BOLJA)

/*
    TP 2018/2019: LV 5, Zadatak 7

        Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
        mozete slati na mail nslamnik1@etf.unsa.ba.

        NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
                          da se koristi indeksiranje niz[i] ili simulacija
   indeksiranja npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.

                          To ce tutori rucno pregledati u toku tutorijala te ako
                          student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se
   da za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <deque>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename neki>
auto SumaBloka(neki pocetak, neki kraj) -> decltype(*pocetak + *pocetak) {//treba genericka fja ne znamo koji ce tip varijable biti, auto nam treba da bi odredili
//povratni tip fje al nam treba i decltype da odredimo tip promjenjive (koristim *pocetak+*pocetak jer ne moze samo *pocetak)
*pocetak nije l vrijednost vec referenca na cjelobrojni objekat pa ovako kad sabiramo dva pokazivaca znamo koji je tip promjenjive a i tip povratne vrijednosti SumaBloka

  if (pocetak == kraj)//ako je prazan
    throw range_error("Blok je prazan");
  if (kraj - pocetak == 1)//ako ima samo jedna stvar
    return *pocetak;

  decltype(*pocetak + *pocetak) suma(*pocetak);//suma je inicijalizovana sa vrijednoscu pocetka tkd while petljom samo nadodamo sve sto preostane 
  while(++pocetak!=kraj){
      suma+=*pocetak;
  }  
  return suma;
}

int main() {
  std::vector<double> v{-95, 25, 333, 96, 6, 12, 1, 2, 35, 0};
  std::cout << "Suma bloka je: " << SumaBloka(v.begin(), v.end());
  return 0;
}