// TP 2021/2022: LV 4, Zadatak 5
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename NekiTip>

NekiTip Presjek(NekiTip v1, NekiTip v2) {

  NekiTip v3;
  int vel1 = v1.size();
  int vel2 = v2.size();

  /*
  v1 = {3,7,2,6,3,4,8,1,6,5};
  v2 = {4,9,5,9,7,0,4,6};
  v3 = Presjek(v1, v2);
  */

  for (int i = 0; i < vel1; i++) {
    for (int j = i; j < vel1 - 1; j++) {
      if (v1.at(i) == v1.at(j + 1)) {
        for (int k = j + 1; k < vel1 - 1; k++) {
          v1.at(k) = v1.at(k + 1);
        }
        vel1--;
        j--;
      }
    }
  }

  /*
  i=0 j=0 k=/  v1(i)=3  v1.(j+1)=7  v1.(k)=/ vel1=10
  i=0 j=1 k=/  v1(i)=3  v1.(j+1)=2  v1.(k)=/ vel1=10
  i=0 j=2 k=/  v1(i)=3  v1.(j+1)=6  v1.(k)=/ vel1=10
  i=0 j=3 k=4  v1(i)=3  v1.(j+1)=3  v1.(k)=3 vel1=9   obrisali smo 3 iz vektora
  ...
  obrisat ce se i 6 jer se ponavljaju u vektoru a necemo vise puta neke stvari
  ispitivati

  v1 = {3,7,2,6,3,4,8,1,6,5} --> {3,7,2,6,4,8,1,5,5,5} (pretvori se sve sto smo
  sklonili viska u zadnji broj sto se pojavio)
  */

  for (int i = 0; i < vel2; i++) {
    for (int j = i; j < vel2 - 1; j++) {
      if (v2.at(i) == v2.at(j + 1)) {
        for (int k = j + 1; k < vel2 - 1; k++) {
          v2.at(k) = v2.at(k + 1);
        }
        vel2--;
        j--;
      }
    }
  }

  /*
  v2 = {4,9,5,9,7,0,4,6} --> {4,9,5,7,0,6,6,6}
    isto cemo uraditi i za drugi vektor
  */

  for (int i = 0; i < vel1; i++) {
    for (int j = 0; j < vel2; j++) {
      if (v1.at(i) == v2.at(j)) {
        v3.push_back(v1.at(i));
      }
    }
  }

  /*
  u trecoj for petlji vec gledamo presjek ova dva vektora i ako ima istih
clanova spasava se u v3 
v1={3,7,2,6,4,8,1,5,5,5} v2={4,9,5,7,0,6,6,6}
v3={7,6,4,5}
  */

  return v3;
}

int main() {
  cout << "Test za realne brojeve..." << endl;
  cout << "Unesite broj elemenata prvog vektora: ";
  int a;
  cin >> a;
  vector<double> v1;
  cout << "Unesite elemente prvog vektora: ";
  for (int i = 0; i < a; i++) {
    double clan;
    cin >> clan;
    v1.push_back(clan);
  }
  cout << "Unesite broj elemenata drugog vektora: ";
  int b;
  cin >> b;
  vector<double> v2;
  cout << "Unesite elemente drugog vektora: ";
  for (int i = 0; i < b; i++) {
    double clan;
    cin >> clan;
    v2.push_back(clan);
  }

  auto v3(Presjek(v1, v2));
  int vel3 = v3.size();
  cout << "Zajednicki elementi su: ";
  for (int i = 0; i < vel3; i++) {
    cout << v3.at(i) << " ";
  }

  cout << endl;

  cout << endl << "Test za stringove..." << endl;
  cout << "Unesite broj elemenata prvog vektora: ";
  int c;
  cin >> c;
  vector<string> s1;
  cout << "Unesite elemente prvog vektora (ENTER nakon svakog unosa):";
  for (int i = 0; i < c + 1; i++) {
    string sclan;
    getline(cin, sclan);
    s1.push_back(sclan);
  }
  cout << endl << "Unesite broj elemenata drugog vektora: ";
  int d;
  cin >> d;
  vector<string> s2;
  cout << "Unesite elemente drugog vektora (ENTER nakon svakog unosa): ";
  for (int i = 0; i < d + 1; i++) {
    string sclan2;
    getline(cin, sclan2);
    s2.push_back(sclan2);
  }

  auto s3(Presjek(s1, s2));
  int svel3 = s3.size();
  cout << endl << "Zajednicki elementi su: ";
  for (int i = 0; i < svel3; i++) {
    cout << s3.at(i) << " ";
  }
  return 0;
}
