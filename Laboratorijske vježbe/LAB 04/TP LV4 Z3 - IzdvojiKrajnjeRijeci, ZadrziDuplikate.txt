// TP 2021/2022: LV 4, Zadatak 3
#include <cctype>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void IzdvojiKrajnjeRijeci(vector<string> rijeci, string &prva, string &zadnja) {

  string prazni;

  if (rijeci.size()==0) {
    prva = prazni;
    zadnja = prazni;
  } else {
    string prvarijec = rijeci.at(0);
    string zadnjarijec = rijeci.at(0);
    for (int i = 0; i < rijeci.size(); i++) {
      string novi;
      novi = rijeci.at(i);
      for (int i = 0; i < prvarijec.size(); i++) {
        if (prvarijec.at(i) >= 'a' && prvarijec.at(i) <= 'z') {
          prvarijec.at(i) = toupper(prvarijec.at(i));
        }
      }
      for (int i = 0; i < zadnjarijec.size(); i++) {
        if (zadnjarijec.at(i) >= 'a' && zadnjarijec.at(i) <= 'z') {
          zadnjarijec.at(i) = toupper(zadnjarijec.at(i));
        }
      }
      for (int i = 0; i < novi.size(); i++) {
        if (novi.at(i) >= 'a' && novi.at(i) <= 'z') {
          novi.at(i) = toupper(novi.at(i));
        }
      }
      if (novi <= prvarijec) {
        prvarijec = rijeci.at(i);
        prva = rijeci.at(i);
      }
      if (novi >= zadnjarijec) {
        zadnjarijec = rijeci.at(i);
        zadnja = rijeci.at(i);
      }
    }
  }
}

void ZadrziDuplikate(vector<string> &rijeci) {

    vector<string> konacni;
    for(int i=0;i<rijeci.size();i++){
        for(int j=i+1;j<rijeci.size();j++){
        bool duplikat=false;
        for(int k=0;k<konacni.size();k++){
            if(rijeci.at(i)==konacni.at(k)) duplikat=true;
        }
        if(rijeci.at(i)==rijeci.at(j) && !duplikat) konacni.push_back(rijeci.at(i));
        }
    }
    rijeci=konacni;
}

int main() {
  int n;
  vector<string> rijeci;
  string prva, zadnja;
  cout << "Koliko zelite unijeti rijeci: ";
  cin >> n;
  cout << "Unesite rijeci: ";
  for (int i = 0; i < n; i++) {
    string rijec;
    cin >> rijec;
    rijeci.push_back(rijec);
  }

  IzdvojiKrajnjeRijeci(rijeci, prva, zadnja);

  cout << endl;
  cout << "Prva rijec po abecednom poretku je: " << prva << endl;
  cout << "Posljednja rijec po abecednom poretku je: " << zadnja << endl;
  cout << "Rijeci koje se ponavljaju su: ";

  ZadrziDuplikate(rijeci);

  for (string x : rijeci) {
    cout << x << " ";
  }

  return 0;
}
