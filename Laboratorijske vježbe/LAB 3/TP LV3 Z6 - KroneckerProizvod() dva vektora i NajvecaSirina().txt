// TP 2021/2022: LV 3, Zadatak 6
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Matrica;
typedef vector<int> Vektor;
//ovo typedef koristim da ne bi morala svaki put pisat tu duzu verziju 

Matrica NapraviMatricu(int a, int b) { return Matrica(a, Vektor(b)); }

int NajvecaSirina(Matrica matricica) {
  int max(0), brojac(0), i, j;
  for (i = 0; i < matricica.size(); i++) {
    for (j = 0; j < matricica[i].size(); j++) { 
/*svaka matrica u c++ se sastoji od u sustini jednog vektora, koji se sastoji od n elemenata,
svaki taj element se moze sastojati od m clanova
zbog toga da bi se pristupilo kolko ima kolona/redova stavlja se matricica[i].size*/
      brojac = 0;
      if (matricica[i][j] < 0) {//ako je neg broj pa da uzmem i minus u obzir za sirinu
        brojac++;
      }
      int x = abs(matricica[i][j]);
      while (x != 0) {//izbrojim cifre svakog clana 
        x /= 10;
        brojac++;
      }
      if (max < brojac) //vidim koji brojac ce dati najveci broj, te time i najvecu potrebnu sirinu
        max = brojac;
    }
  }
  return max;
}

Matrica KroneckerovProizvod(Vektor a, Vektor b) {
  auto kronerka(NapraviMatricu(a.size(), b.size()));//pravimo je na osnovu a i b vektora, zbog velicina njihovih
  int i, j;
  for (i = 0; i < a.size(); i++) {
    for (j = 0; j < b.size(); j++) {
      kronerka[i][j] = a[i] * b[j];
    }
  }
  return kronerka;
}

int main() {
  int m, n, element, i, j;
  Vektor a;
  Vektor b;
  cout << "Unesite broj elemenata prvog vektora: ";
  cin >> m;
  cout << "Unesite elemente prvog vektora: ";
  for (i = 0; i < m; i++) {
    cin >> element;
    a.push_back(element);
  }
  cout << "Unesite broj elemenata drugog vektora: ";
  cin >> n;
  cout << "Unesite elemente drugog vektora: ";
  for (int i = 0; i < n; i++) {
    cin >> element;
    b.push_back(element);
  }

  Matrica konacno(KroneckerovProizvod(a, b));

  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      cout << setw(NajvecaSirina(konacno) + 1) << right << konacno[i][j];
    }
    cout << endl;
  }

  return 0;
}