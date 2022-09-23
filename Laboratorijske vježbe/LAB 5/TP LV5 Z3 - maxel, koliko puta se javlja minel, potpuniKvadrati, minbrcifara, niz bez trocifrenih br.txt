/* 
    TP 2018/2019: ===TITLE===
	
	Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
	mozete slati na mail nslamnik1@etf.unsa.ba.
	
	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.
			  
			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

bool JelPotpunKvadrat(int x){
    return sqrt(x)== int(sqrt(x));
}

bool BrojCifara(int x, int y){
    x=abs(x);
    y=abs(y);
    return log10(x)+1<log10(y)+1;
}

bool Trocifren(double n){
    n=abs(n);
    if(log10(n)>=2 && log10(n)<3) return true;
    else return false;
}

void Unos(int &x){
    cin>>x;
}

void Ispis(int &x){
    cout<<x<<" ";
}

int main(){

    const int maxBrElemenata=1000;
    int n;
    int niz[maxBrElemenata];
    
    cout<<"Unesite broj elemenata (max. 1000): ";
    cin>>n;
    
    cout<<"Unesite elemente: ";//posto ne smijemo koristit one petlje uzmemo iz algorithma biblioteke for_each i onda unesemo u niz preko pokazivaca jer ne mozemo
//direkt koristit pristup elementima sa niz[i] sto zahtjeva petlju pa smo ovako morali
    int *p=niz;
    for_each(p,p+n,Unos);

    cout<<"Najveci element niza je "<<*max_element(niz, niz+n)<<endl;//fja provjeri od pocetka do kraja niza koji je max

    cout<<"Najmanji element niza se pojavljuje "<<count(niz,niz+n,*min_element(niz, niz+n))<<" puta u nizu"<<endl;//izbroj koliko puta se javlja od pocetka do kraja niza min element 
//(treci parametar je uvijek taj na osnovu kojeg se gleda da li element ispunjava uslov u tom rangeu koji se postavi

    cout<<"U nizu ima "<<count_if(niz,niz+n,JelPotpunKvadrat)<<" brojeva koji su potpuni kvadrati"<<endl;//razlika izmedju count if i count je sto count postoji samo jedan element i on je vec određen fjom min_element 
// dok count if moze ih postojati vise za koje je ispunjen uslov

    cout<<"Prvi element sa najmanjim brojem cifara je "<<*min_element(niz,niz+n,BrojCifara)<<endl;

    cout<<"Elementi koji nisu trocifreni su: ";
    int novi[1000];
    
    int *konacno = remove_copy_if(niz,niz+n,novi,Trocifren);//napravi kopiju niza u novi i u njega ubaci samo one sto nisu trocifreni
    for_each(novi,konacno,Ispis);//ispisi novi 



}