/*
PARCIJALNI 2021/2022 iz vektora ubaci u novi rezultantni vektor sve kubove brojeva

Napišite funkciju koja prihvata vektor cijelih brojeva (tipa "int"), a koja kao rezultat vraća vektor
logičkih vrijednosti iste dimenzije, pri čemu je i-ti element vektora koji se vraća kao rezultat logička
vrijednost “tačno” ukoliko se i-ti element ulaznog vektora moža prikazati kao kub nekog prirodnog
broja (recimo 216 = 6

), a “netačno” u suprotnom. U slučaju da je neki od elemenata vektora
negativan, treba baciti izuzetak tipa "domain_error" sa proizvoljnim tekstom. Napišite i kratki isječak
programa u kojem ćete testirati napisanu funkciju sa fiksnim vektorom od 10 proizvoljnih elemenata
tipa "int", pri čemu ćete ispisati elemente vraćenog vektora odvojene razmakom. Obavezno predvidite
hvatanje eventualno bačenih izuzetaka.
*/

// RJEŠENJE:

#include <iostream>
#include <vector>
#include <cmath>

std::vector<bool> kubBroja(const std::vector<int> &v){
    std::vector<bool> rezultat;
    for(int i : v){
        if(i<0) throw std::domain_error("Element vektora je negativan!");
        if(pow(int(round(pow(i,1./3))),3)==i) rezultat.push_back(true); else rezultat.push_back(false);
    }
    return rezultat;
}

int main() {

    int n;
    std::cout<<"Unesite velicinu vektora: ";
    std::cin>>n;

    std::cout<<"Unesite elemente vektora: ";
    std::vector<int> A;
    for(int i=0; i<n; i++){
        int element;
        std::cin>>element;
        A.push_back(element);
    }

    try{
        auto rez = kubBroja(A);
        std::cout<<"U novom vektoru elementi su true ili false u zavisnosti da li se element ulaznog vektora moze predstaviti kao kub nekog prirodnog broja."<<std::endl;
        std::cout<<"Elementi novog vektora su: "<<std::endl;
        for(auto x: rez) std::cout<<std::boolalpha<<x<<" ";
    }catch(std::range_error &e){
        std::cout<<e.what()<<std::endl;
    }

    return 0;
}