//TP 2021/2022: LV 8, Zadatak 6
#include <iostream>
#include <cmath>

template<typename TipElemenata>
struct Cvor {
    TipElemenata element;
    Cvor<TipElemenata> *veza;
};

template <typename TipElemenata> Cvor<TipElemenata> *KreirajPovezanuListu(TipElemenata zavrsni);

template <typename TipElemenata> int BrojElemenata(Cvor<TipElemenata> *pocetak);

template <typename TipElemenata> TipElemenata SumaElemenata(Cvor<TipElemenata> *pocetak);

template <typename TipElemenata> int BrojVecihOd(Cvor<TipElemenata> *pocetak, TipElemenata prag);

template <typename TipElemenata> void UnistiListu(Cvor<TipElemenata> *pocetak);

template <typename TipElemenata> void UnistiListuRekurzivno(Cvor<TipElemenata> *pocetak);

int main ()
{
    std::cout<<"Unesite slijed brojeva (0 za kraj): ";
    Cvor <double> *a = KreirajPovezanuListu(0.);
    double aritmetickaSredina = SumaElemenata(a) / BrojElemenata(a);
    std::cout<<"U slijedu ima "<<BrojVecihOd(a, aritmetickaSredina)<<" brojeva vecih od njihove aritmeticke sredine";
    UnistiListuRekurzivno(a);
	return 0;
}

template <typename TipElemenata> 
Cvor<TipElemenata> *KreirajPovezanuListu(TipElemenata zavrsni){

    Cvor<TipElemenata> *pocetak = nullptr, *prethodni;
    for(;;){
        TipElemenata x;
        std::cin>>x;
        if(x==zavrsni) break;
        Cvor<TipElemenata> *novi = new Cvor<TipElemenata>{x,nullptr};
        if(!pocetak) pocetak = novi;
        else prethodni->veza = novi;
        prethodni = novi;
    }
    return pocetak;

}

template <typename TipElemenata> 
int BrojElemenata(Cvor<TipElemenata> *pocetak){
    int brElemenata = 0;
    for(auto x = pocetak; x!=nullptr; x = x->veza){
        brElemenata++;
    }
    return brElemenata;
}

template <typename TipElemenata> 
TipElemenata SumaElemenata(Cvor<TipElemenata> *pocetak){
    TipElemenata SumaElemenata{};
    for(auto x = pocetak; x!=nullptr; x = x->veza){
        SumaElemenata+=x->element;
    }
    return SumaElemenata;
}

template <typename TipElemenata> 
int BrojVecihOd(Cvor<TipElemenata> *pocetak, TipElemenata prag){
    int brojac = 0;
    for(auto x = pocetak; x!=nullptr; x = x->veza){
        if(x->element > prag) brojac++;
    }
    return brojac;
}

template <typename TipElemenata> 
void UnistiListu(Cvor<TipElemenata> *pocetak){
    if(!pocetak) return;
    int n = BrojElemenata(pocetak);
    while(n!=1){
        auto p = pocetak;
        for(int i=0; i<n-1; i++){
            p = p->veza;
        }
        delete p;
        n--;
    }
    delete pocetak;
}

template <typename TipElemenata> 
void UnistiListuRekurzivno(Cvor<TipElemenata> *pocetak){
    if(pocetak) UnistiListuRekurzivno(pocetak->veza);
    delete pocetak;
}