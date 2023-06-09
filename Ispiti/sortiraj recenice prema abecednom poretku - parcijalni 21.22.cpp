/*
PARCIJALNI 2021/2022 - sortiraj recenice u abecednom poretku

Napišite program koji traži od korisnika da unese niz rečenica, pri čemu se broj rečenica prethodno
unosi sa tastature. Za svaku unesenu rečenicu dinamički alocirajte prostor, uz vođenje evidencije o
adresi svake alocirane rečenice u dinamičkom nizu pokazivača na početke svake od rečenica. Nakon
toga, treba ispisati unesene rečenice sortirane u abecedni poredak (tačnije rečeno, u rastući poredak
po ASCII kodovima). Za sortiranje koristite funkciju “sort” uz pogodno definiranu funkciju kriterija.
*/

// RJEŠENJE :

#include <iostream>
#include <algorithm>
#include <cstring>

bool VecaPoASCII(const char *r1,const char *r2)
{
    return std::strcmp(r1,r2)<0;
    //strcmp vraća kao rezultat
    //neku vrijednost manju od nule
    //ukoliko je prvi niz ispred drugog po abecednom poretku
}
int main ()
{
    char **p=nullptr;
    try{
        std::cout<<"Koliko zelite recenica: ";
        int n;
        std::cin>>n;
        std::cin.ignore(100000,'\n'); //ciscenje spremnika zbog nul...
        std::cout<<"Unesite recenice:"<<std::endl;
        p=new char*[n];//alokacija pokazivaca na zeljeni broj recenica
        for(int i=0;i<n;i++){
            char pomocni[1000];
            std::cin.getline(pomocni,sizeof pomocni);//unos niza charova max 1000
            p[i]=new char[std::strlen(pomocni)+1]; //+1 zbog nul granicnika//alokacija svake recenice
            std::strcpy(p[i],pomocni);//kopiranje niza charova u pokazivac na niz charova
        }

        std::sort(p, p+n, VecaPoASCII);

        std::cout<<"Sortirane recenice:"<<std::endl;
        for(int i=0;i<n;i++) std::cout<< p [i] <<std::endl;

        for(int i=0;i<n;i++) delete[] p[i];
        delete[] p;
    }catch(...){
        delete[] p;
        std::cout<<"Problemi s memorijom!";
    }
    return 0;
}