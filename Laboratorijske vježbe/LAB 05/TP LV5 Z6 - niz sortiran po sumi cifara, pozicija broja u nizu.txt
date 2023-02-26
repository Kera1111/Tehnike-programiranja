/* 
    TP 2018/2019: LV 5, Zadatak 6
	
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
#include <algorithm>
#include <vector>

using namespace std;

void SumaCifara(int &suma, int x){
    if(x==0){
        return;
    }
    suma+=abs(x%10);
    SumaCifara(suma,x/=10);//rekurzija jer sto da ne, djelim svaki put s 10 i dodam na original sumu 
}//ne moze int SumaCifara jer moram deklarisat na pocetku suma=0; pa bi onda svaki put se vratila suma na 0

bool PoredjenjeSumaCifara(int a, int b){
    int sumaA=0,sumaB=0;
    SumaCifara(sumaA,a);
    SumaCifara(sumaB,b);
    if(sumaA==sumaB){
        return a<b;
    }
    return sumaA<sumaB;
}

void Unos(int &x) { cin >> x; }

void Ispis(int &x) { cout << x << " "; }

int main ()
{
    int brElemenata;
    cout<<"Unesite broj elemenata: ";
    cin>>brElemenata;

    vector<int> a(brElemenata);
    cout<<"Unesite elemente: ";
    for_each(a.begin(), a.end(), Unos);
	
    sort(a.begin(),a.end(),PoredjenjeSumaCifara);

    cout<<"Niz sortiran po sumi cifara glasi: ";
    for_each(a.begin(), a.end(), Ispis);

    int broj;
    cout<<endl<<"Unesite broj koji trazite: ";
    cin>>broj;
    if(!binary_search(a.begin(),a.end(),broj,PoredjenjeSumaCifara)){
        cout<<"Trazeni broj ne nalazi se u nizu!"<<endl;
    }else{
        vector<int>::iterator pozicija=find(a.begin(),a.end(), broj);
        cout<<"Trazeni broj nalazi se na poziciji "<< pozicija-a.begin();
    }

    return 0;
}
DRUGA VERZIJA KODA TJ NOVA
/* 
    TP 2018/2019: LV 5, Zadatak 6
	
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
#include <algorithm>
#include <vector>

using namespace std;

void SumaCifara(int &suma, int x){
    if(x==0){
        return;
    }
    suma+=abs(x%10);
    SumaCifara(suma,x/=10);//rekurzija jer sto da ne, djelim svaki put s 10 i dodam na original sumu 
}//ne moze int SumaCifara jer moram deklarisat na pocetku suma=0; pa bi onda svaki put se vratila suma na 0

bool PoredjenjeSumaCifara(int a, int b){
    int sumaA=0,sumaB=0;
    SumaCifara(sumaA,a);//dodijelim vrijednost sumaA
    SumaCifara(sumaB,b);//dodijelim vrijednost sumaB
    if(sumaA==sumaB){
        return a<b;
    }
    return sumaA<sumaB;
}

void Unos(int &x) { cin >> x; }

void Ispis(int &x) { cout << x << " "; }

int main ()
{
    int brElemenata;
    cout<<"Unesite broj elemenata: ";
    cin>>brElemenata;

    vector<int> a(brElemenata);
    cout<<"Unesite elemente: ";
    for_each(a.begin(), a.end(), Unos);
	
    sort(a.begin(),a.end(),PoredjenjeSumaCifara);

    cout<<"Niz sortiran po sumi cifara glasi: ";
    for_each(a.begin(), a.end(), Ispis);
	//da bi binary search radio niz mora biti sortiran!
// tkd standardno sortiranje je po velicini al posto je ovo prema sumi cifara mora se i to kao dodatni parametar proslijedit u fju
    int broj;
    cout<<endl<<"Unesite broj koji trazite: ";
    cin>>broj;
    auto pozicija=lower_bound(a.begin(),a.end(),broj,PoredjenjeSumaCifara);//inace kaze emir kOpic da ako nema tog broja sto trazi vraca prvi veci 
    if(*pozicija==broj){
        /*
        vector<int>::iterator pozicija=find(a.begin(),a.end(), broj);
        moze ovako al eto postavka ne da :(
ovo je dosta sporije btw jer radi dvaput binarno trazenje
        */
        cout<<"Trazeni broj nalazi se na poziciji "<< pozicija-a.begin();//mora ici -a.begin() jer ako se nalazi npr a.begin na 100 u memoriji a ovo je 104 pozicija
//da bi nasla sto mi treba onda ide 104-100=4to mjesto 
        
    }else{
        cout<<"Trazeni broj ne nalazi se u nizu!"<<endl;
    }
    return 0;
}