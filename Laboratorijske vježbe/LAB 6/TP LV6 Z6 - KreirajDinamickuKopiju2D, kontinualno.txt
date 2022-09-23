/* 
    TP 2018/2019: LV 6, Zadatak 6
	
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

template<typename NekiTip> 
auto KreirajDinamickuKopiju2D(NekiTip matrica)->remove_reference_t<decltype(matrica.at(0).at(0))>**{
    remove_reference_t<decltype(matrica.at(0).at(0))> **p(nullptr);

    int BrElemenata = 0;
    for(int i=0; i<matrica.size(); i++){
        for(int j=0; j< matrica.at(i).size(); j++){
            BrElemenata++;
        }
    }

    try{
        p = new remove_reference_t<decltype(matrica.at(0).at(0))> *[matrica.size()];//napravi niz pokazivaca
        p[0] = new remove_reference_t<decltype(matrica.at(0).at(0))> [BrElemenata];//stavi sve u jedan red

        for(int i=1; i<matrica.size(); i++){
            p[i] = p[i-1] + matrica.at(i-1).size();//razdvoji fino redove jer je prije sve bilo u jednom 
        }

        for(int i=0; i<matrica.size(); i++){
            for(int j=0; j<matrica.at(i).size(); j++){
                p[i][j] = matrica.at(i).at(j);//upisi elemente
            }
        }

    }catch(...){
        delete[] p;
        throw bad_alloc();
    }

    return p;

}

int main ()
{
    try{
        int n;
        vector<deque<int>> matrica;
        cout<<"Unesite broj redova kvadratne matrice: ";
        cin>>n;

        matrica.resize(n);
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
        delete[] p[0];
        delete[] p;
    }catch(...){
        cout<<"Nedovoljno memorije";
    }
	return 0;
}