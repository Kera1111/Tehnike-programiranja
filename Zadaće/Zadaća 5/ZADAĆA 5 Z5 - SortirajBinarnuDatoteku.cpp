//TP 2021/2022: Zadaća 5, Zadatak 6
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
#include <iterator>
#include <functional>
#include <fstream>

using namespace std;


template <typename TipElemenata>
void SortirajBinarnuDatoteku(const char imeDatoteke[], function<bool(TipElemenata, TipElemenata)> kriterij = less<TipElemenata>()){
    if(!fstream(imeDatoteke)) throw logic_error("Datoteka ne postoji");
}

int main(){
    return 0;
}