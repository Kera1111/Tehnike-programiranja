/* 
    TP 2018/2019: LV 6, Zadatak 5
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <iostream>
#include <type_traits>
#include <deque>
#include <vector>

using namespace std;

template <typename nekiTip>
auto KreirajDinamickuKopiju2D(nekiTip matrica)->remove_reference_t<decltype(matrica.at(0).at(0))>**{
  remove_reference_t<decltype(matrica.at(0).at(0))> **pok;
  try {
    pok = new remove_reference_t<decltype(matrica.at(0).at(0))> *[matrica.size()];//napravi redove
    try {
      for (int i = 0; i < matrica.size(); i++) {
        pok[i] = new remove_reference_t<decltype(
            matrica.at(0).at(0))>[matrica.at(i).size()];//napravi kolone
      }

      for (int i = 0; i < matrica.size(); i++) {
        for (int j = 0; j < matrica.at(i).size(); j++) {
          pok[i][j] = matrica.at(i).at(j);//upisi elemente
        }
      }

    } catch (...) {
      for (int i = 0; i < matrica.size(); i++)
        delete[] pok[i];
      throw bad_alloc();
    }
  } catch (...) {
    delete[] pok;
    throw bad_alloc();
  }
  return pok;
}

int main ()
{
    try{
        int n;

        cout<<"Unesite broj redova kvadratne matrice: ";
        cin>>n;

        vector<deque<int>> matrica(n);
        for(auto &x : matrica) x.resize(n);

        cout<<"Unesite elemente matrice: ";
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                cin>>matrica.at(i).at(j);
            }
        }

        auto p (KreirajDinamickuKopiju2D(matrica));
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                cout<<p[i][j]<<" ";
            }
            cout<<endl;
        }
        for(int i=0; i<n; i++) delete[] p[i];
        delete[] p;
    }catch(...){
        cout<<"Nedovoljno memorije";
    }
	return 0;
}