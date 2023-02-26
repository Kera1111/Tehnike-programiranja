/* 
    TP 2018/2019: LV 6, Zadatak 3
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <iostream>
#include <new>
#include <stdexcept>

using namespace std;

int **KreirajTrougao(int n){//vraca se matrica zato treba **

    if(n<=0) throw domain_error("Broj redova mora biti pozitivan");
    int **p= nullptr;//pokazivac na pokazivac jer nam treba matrica
    try{
        p = new int* [n] {};//napravila redove
        try{//morali smo maksuz razdvojeno praviti redove i kolone
            for(int i=0; i<n; i++){
                p[i] = new int[2*i+1];//napravila kolone
            }
            for(int i=0; i<n; i++){//redovi
                for(int j=0; j<2*i+1; j++){//kolone
                    p[i][j] = abs(i-j) +1;//upisali elemente
                }
            }
        }catch(...){
            for(int i=0; i<n; i++) delete[] p[i];
            throw bad_alloc();
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

        for(int i=0; i<n; i++){
            delete[] matrica[i];
        }
        delete[] matrica;
    }catch(domain_error izuzetak){
        cout<<"Izuzetak: "<<izuzetak.what();;
    }catch(bad_alloc){
        cout<<"Izuzetak: Nedovoljno memorije!";
    }    
	return 0;
}