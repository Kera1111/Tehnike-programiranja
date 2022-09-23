// TP 2021/2022: LV 3, Zadatak 7
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> PascalovTrougao(int n) {

  if (n < 0){
    throw domain_error("Broj redova ne smije biti negativan");
  }

  vector<vector<int>> matrica(n);
  int i, j;

  if (n == 0) {
    matrica.resize(0);
    return matrica;
  }
  
  for (i = 0; i < n; i++) {
    matrica[i].resize(i + 1);
  }
  
  for (i = 0; i < n; i++) {
    for (j = 0; j < i + 1; j++) {
      if (j == 0 || i == j)
        matrica[i][j] = 1;
      else
        matrica[i][j] = matrica[i - 1][j] + matrica[i - 1][j - 1];
    }
  }
  return matrica;
}

int main() {
  int n;

  cout << "Unesite broj redova: " << endl;
  cin >> n;
  vector<vector<int>> ispis = PascalovTrougao(n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i + 1; j++) {
      cout << ispis[i][j] << " ";
    }
    cout << "\n";
  }
  return 0;
}
