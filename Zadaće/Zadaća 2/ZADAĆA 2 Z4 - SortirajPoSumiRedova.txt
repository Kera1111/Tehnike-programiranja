// TP 2021/2022: Zadaća 2, Zadatak 4
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Matrica;

template <typename nekiTip>
bool Kriterij(vector<nekiTip> prvired, vector<nekiTip> drugired) {

  nekiTip suma1 = nekiTip();
  nekiTip suma2 = nekiTip();

  for (auto clan : prvired) {
    suma1 += clan;
  }
  for (auto clan : drugired) {
    suma2 += clan;
  }

  if (suma1 == suma2)
    return prvired < drugired;

  return suma2 < suma1;
}

void OcistiTok(){
    cin.clear();
    cin.ignore(10000, '\n');
}

template <typename nekiTip>
void SortirajPoSumiRedova(vector<vector<nekiTip>> &matrica) {
  sort(matrica.begin(), matrica.end(), Kriterij<nekiTip>);
}

int main() {
  Matrica mat;
  double br = 0;
  cout << "Unesi elemente (* za kraj reda, * na pocetku reda za kraj unosa):"
       << endl;
  int vel = 0;
  while (1) {
    mat.resize(vel + 1);
    while (1) {
      cin >> br;
      if (!cin) {
        OcistiTok();
        break;
      }
      mat.at(vel).push_back(br);
    }
    if (mat.at(vel).size() == 0)
      break;
    vel++;
  }

  cout << "Matrica nakon sortiranja:" << endl;
  SortirajPoSumiRedova(mat);
  for (auto red: mat) {
    for (auto kolona: red) {
      cout << kolona << " ";
    }
    cout << endl;
  }

  return 0;
}
