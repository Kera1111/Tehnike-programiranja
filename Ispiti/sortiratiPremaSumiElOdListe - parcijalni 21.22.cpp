/*
PARCIJALNI 2021/2022 sortirati vektor po sumi elemenata u listama rastuci

Neka je “v” neki vektor čiji su elementi liste cijelih brojeva (tj. tipa “std::vector<std::list<int>>”).
Napišite isječak programa u kojima ćete pozivom bibliotečke funkcije “sort” uz odgovarajuću funkciju
kriterija implementiranu kao lambda funkciju sortirati ovaj vektor u rastući poredak po sumi
elemenata u listama, tj. tako da u njemu liste sa manjom sumom elemenata dolaze prije listi sa većom
sumom elemenata (elementi unutar svake od listi ostaju u istom redoslijedu u kakvom su bili i prije
sotriranja). Po obavljenom sortiranju, treba ispisati sortirani vektor tako da se svaka lista ispisuje u
posebnom redu, pri čemu se elementi unutar jedne liste međusobno razdvajaju jednim razmakom.
*/

// RJEŠENJE:

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

int sumaListe(const std::list<int>& l){
    int suma = 0;
    for(int it : l) suma+=it;
    return suma;
}

int main() {

    std::vector<std::list<int>> v = {{1,2,3},{5},{4,7,9}};
    sort(v.begin(), v.end(),
         [](const std::list<int> &l1, const std::list<int> &l2){return sumaListe(l1)< sumaListe(l2);});
    for(const auto& lista: v){
        for(auto el: lista) std::cout<<el<<" ";
        std::cout<<std::endl;
    }

    return 0;
}

