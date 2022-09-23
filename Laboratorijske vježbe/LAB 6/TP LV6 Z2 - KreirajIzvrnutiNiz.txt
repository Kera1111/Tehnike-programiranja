/* 
    TP 2018/2019: LV 6, Zadatak 2
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <iostream>
#include <new>
#include <type_traits>
#include <vector>
using namespace std;

template<typename nekiTip>
auto KreirajIzvrnutiNiz(nekiTip pocetak, nekiTip kraj) -> typename remove_reference <decltype(*pocetak)>::type*{
    //auto jer ne znamo tip sto vraca fja
    //istog su tipa pocetak i kraj
    //decltype da bi odredila naknadno sta vraca jer ne zna samo auto sta ce ga vratit pa mora ovo se dodat, a ovo remove reference sklanja referencu sa pokazivaca
    try{
    typename remove_reference<decltype(*pocetak)>::type* novi = {};
    nekiTip temp = pocetak;

    int brElemenata = 0;
    while(temp != kraj){
        brElemenata++;
        temp++;
    } 
    
    novi = new typename remove_reference<decltype(*pocetak)>::type[brElemenata];
    //opet ne znamo koji ce tip vratit pa nam treba ovo s decltype
    
    for(int i=brElemenata-1; i>=0; i--){//odzada dodavala na ovaj novi
        novi[i] = *pocetak++;
    }
    return novi;

    }catch(bad_alloc){//ako si nasao belaj nastavi program i baci izuzetak
        throw;
    }
}

int main ()
{
    int n;
    try{
        cout<<"Koliko zelite elemenata: ";
        cin>>n;
        vector<double> v;
        v.resize(n);
        cout<<"Unesite elemente: ";
        for(int i=0;i<n;i++){
            double temp; 
            cin>>temp; 
            v.push_back(temp);
        }

        cout<<"Kreirani niz: ";
        auto p(KreirajIzvrnutiNiz(v.begin(), v.end()));
        for(int i=0; i<n; i++){
            cout<<p[i]<<" ";
        }
        delete[] p;
    }
    catch(bad_alloc){
        cout<<"Nedovoljno memorije!"<<endl;
    }

	return 0;
}