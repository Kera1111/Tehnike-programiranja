/* 
    TP 16/17 (LV 7, Zadatak 6)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/

#include <iostream>
#include <list>

template <typename nekiTip>
void SortirajListu(std::list<nekiTip> &lista){
    for(auto i=lista.begin(); i!=lista.end(); i++){//sortiraj od pocetka do kraja
        for(auto j=i; j!=lista.end(); j++){//provjeri od trenutnog do kraja jel ispunjava uslov
            if(*i>*j){
                auto temp=*j;
                *j=*i;
                *i=temp;
            }
        }
    }
}

int main ()
{
    int n;
    std::cout<<"Koliko ima elemenata: ";
    std::cin>>n;
    std::list<int> lista;
    std::cout<<"Unesite elemente: ";
    for(int i=0; i<n; i++){
        int temp;
        std::cin>>temp;
        lista.push_back(temp);
    }
    std::cout<<"Sortirana lista: ";
    SortirajListu(lista);
    for(auto x: lista){
        std::cout<<x<<" ";
    }
	return 0;
}