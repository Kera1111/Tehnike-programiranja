/*
PARCIJALNI 2021/2022 - zajednicki elementi genericka fja dva vektora istog tipa

Napišite generičku funkciju “ZajednickiElementi” koja prima dva parametra koji su vektori sa
proizvoljnim ali istim tipom elemenata. Funkcija treba da kao rezultat vrati novi vektor koji se sastoji
od elemenata koji se javljaju i u jednom i u drugom vektoru (drugim riječima, treba formirati presjek
skupova čiji su elementi pohranjeni u vektorima koji su zadani kao parametri). Pored toga, u vektoru
koji je vraćen kao rezultat iz funkcije svi elementi treba da budu različiti (odnosno, elemente koji se
ponavljaju ne treba prepisivati više puta). Poredak brojeva pohranjenih u rezultatu nije bitan.
Napisanu funkciju demonstrirajte na isječku programa u kojem se nalazi presjek dva vektora čiji su
elementi stringovi, sa fiksno zadanim sadržajem (po vlastitom izboru).
*/

// RJEŠENJE :

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

template <typename tip>
std::vector<tip> ZajednickiElementi(const std::vector<tip> &v1, const std::vector<tip> &v2){
    std::set<tip> s;
    for(int i=0; i<v1.size(); i++){
        for(int j=0; j<v2.size(); j++){
            if(v1.at(i)==v2.at(j)){
                s.insert(v1.at(i));
                break;
            }
        }
    }
    std::vector<tip> rez(s.size());
    std::copy(s.begin(), s.end(), rez.begin());
    return rez;
}

int main(){
    std::vector<int> v1 = {1,2,3,4,5,6};
    std::vector<int> v2 = {3,4,5,6,7,8,9};
    for(const auto &el: ZajednickiElementi(v1,v2)) std::cout<<el<<" ";
    return 0;
}