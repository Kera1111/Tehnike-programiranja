// TP 2021/2022: Zadaća 1, Zadatak 1

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

typedef vector<int> Vektor;
// ovo typedef koristim da ne bi morala svaki put pisat tu duzu verziju

int CiklickaPermutacija(Vektor a, Vektor b) {

  int pomak = -1;
  //specijalni slucajevi
  if (a.size() != b.size())  return -1; //ako im velicina nije ista onda -1
  else if (a == b) { // ako su dva identicna vektora onda 0
    pomak = 0;
    return pomak;
  }

  bool imajuGaObaVektora = false; // ako se ne nadje broj iz a u b onda odma return -1

  for (int i = 0; i < b.size(); i++) {   // prolazim kroz prvi vektor
    for (int j = 0; j < a.size(); j++) { // prolazim kroz drugi vektor
      if (b.at(i) == a.at(j)) { 
        /*ako su isti clanovi na odredjenim pozicijama,  potrebno je ispitati jos da li su isti na svim narednim da bi bile ciklicke permutacije jedan drugog*/
        imajuGaObaVektora = true; 
        // pocinjem ispitivati od clana koji je isti
        int x=i+1;
        int y=j+1;
        while(x<b.size() && y<a.size()){
            if (a.at(y) != b.at(x)){
              imajuGaObaVektora=0; // nisu isti clanovi
              break;
            }
            x++;
            y++;
        }
        if(imajuGaObaVektora){
          pomak=j;
          break;
        } 
      }
    }
    break;
  }
  return pomak;
}

int main() {

  Vektor a, b;
  int element;
  cout << "Prva sekvenca: ";
  while (cin >> element) {
    a.push_back(element);
  }

  cin.clear();//moramo ocistiti tok da bi se unijelo i za drugi niz
  cin.ignore(10000, '\n');

  cout << "Druga sekvenca: ";
  while (cin >> element) {
    b.push_back(element);
  }

  int pomak = CiklickaPermutacija(a, b);

  if (pomak == -1) cout << "Druga sekvenca nije ciklicka permutacija prve.";
  else cout << "Druga sekvenca je ciklicka permutacija prve s pomakom " <<pomak<<".";
  return 0;
}