/* 
    TP 2018/2019: LV 6, Zadatak 4
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <iostream>
#include <new>
#include <stdexcept>

using namespace std;

int **KreirajTrougao(int n){

    if(n<=0) throw domain_error("Broj redova mora biti pozitivan");
    int **p= nullptr;
    try{
        p = new int *[n] {};
        try{
            p[0] = new int[n*n]; //posto je kontinualno mogu odjednom napraviti redove i kolone, nulti red smo popunili sa dinamickim nizom 
            
            for(int i=1; i<n; i++){//
                p[i] = p[i-1] + 2*(i-1) +1;
            }

            for(int i=0; i<n; i++){
                for(int j=0; j<2*i+1; j++){
                    p[i][j] = abs(i-j) +1;
                }
            }
            
        }catch(...){
            delete[] p[0];
            throw;
        }
    }catch(...){
        delete[] p;
        throw;
    }
    return p;
}

int main ()
{
   
    try{
        cout<<"Koliko zelite redova: ";
        int n;
        cin>>n;   
        auto matrica = KreirajTrougao(n); 

        for(int i=0; i<n; i++){
            cout<<endl;
            for(int j=0; j<2*i+1; j++){
                cout<<matrica[i][j]<<" ";
            }
        }
    //kod fragmentirano razbacano je po memoriji (kreirani redovi)
        delete[] matrica[0];//brise se nulti red 
        delete[] matrica;
    }catch(bad_alloc){
        cout<<"Izuzetak: Nedovoljno memorije!";
    }catch(domain_error izuzetak){
        cout<<"Izuzetak: "<<izuzetak.what();
    }
	return 0;
}