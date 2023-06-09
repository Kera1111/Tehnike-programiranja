//PARCIJALNI 2021/2022 - koje su greške u programu

// RJEŠENJE :

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <algorithm>
#include <cmath>

int main() {
    std::list<double> a{1, 4, 2, 5, 3}; std::queue<int> q{3, 4, 2, 5}; // ne moze se ovako inicijalizirati queue, on moze samo sa nekim drugim kontejnerskim tipom ili sa njegovim ugradjenim fjama dodati clanove
    std::sort(a.begin(), a.end()); for(double x : a) std::cout << a << " "; //sort nema fju kriterija, ne mozemo sa rasponskom for petljom raspisati kolekciju
    auto f = [](double (*g)(int)) { return g(1); }; //lambda(anonimne) fje tj. nemaju naziva, nema nigdje predeclared fje g da bi se mogla pozvati
    std::cout << f([a](int x){ return *a.begin() + x; });//a.begin() je iterator, ne postoji *a.begin()
    auto h = [](int &x) { return x + 2 }; std::cout << h(std::sqrt(2));//fali poslije x+2 ;, opet lambde nemaju naziva
    double *p = std::find(a.begin(), a.end(), 2); std::cout << *p;//vraća iterator, a ne obični pokazivač
    for(int x : q) std::cout << x << " "; return 0;// ne moze se sa iteratorima niti for loop proci kroz queue
}