// TP 2021/2022: LV 4, Zadatak 2
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

void IzvrniString(string &s) {//mora se staviti & jer je u pitanju pokazivac ne mozemo pokazati na njegovu adresu bez ovog znaka

  /*
  posto treba da se izvrne idemo do sredine stringa i onda koristimo algoritam
  za sortiranje, pomocnu varijablu da bi zadrzali vrijednost jedne strane i
  zamjenimo im mjesta samo

  jabuka = akubaj (j<->a, a<->k, b<->u)
  */

  char temp;//koristimo temp varijablu za najobicniji, najcesci algoritam za sortiranje
  for (int i = 0; i < s.size() / 2; i++) {//petlja kod koje prolazimo kroz citav string
    temp = s.at(i);//spasavamo privremeno vrijednost stringa i 
    s.at(i) = s.at(s.size() - i - 1);//dodjeljujemo vrijednost od zadnjeg mjesta ka naprijed
    s.at(s.size() - i - 1) = temp;// tj ucinimo jedan po jedan swap kako prolazimo kroz petlju
  }
}

int main() {
  string str;
  cout << "Unesi string: ";
  getline(cin, str);//unosimo string sa getline
  IzvrniString(str);//primjenimo void fju da izvrsi izmjene nad stringom
  cout << "Izvrnuti string je: " << str;//ispis
  return 0;
}
