/* 
    TP 2018/2019: LV 5, Zadatak 5
	
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
#include <iomanip>
#include <cmath>

using namespace std;

double TrapeznoPravilo(double (*f) (double), double a, double b, int n) {//prosljedjuje se fja pa mora pokazivac, formule uvrstene i tjt 
    double suma=0;
    int i=1;
    while(i<n){ // racunanje sume
        suma += f (a + ( (b - a) / n) * i);
        i++;
    }  
    // racunanje integrala:
    return (b - a) / double (n) * ( f (a) * 0.5 + f (b) * 0.5 + suma);  
}
 
int main()
{
    const double pi=4*atan(1);
    cout << "Unesite broj podintervala: ";
    int broj;
    cin >> broj;
    cout<<"Za taj broj podintervala priblizne vrijednosti integrala iznose:"<<endl;//dobro dodju lambda fje jer samo jedan parametar ce se mijenjat tj fja sinx,xxx,1/x, ostalo su konstante

    cout << "- Za funkciju sin x na intervalu (0,pi): " <<fixed<<setprecision(5)<< TrapeznoPravilo ([] (double x) {return sin (x);} , 0, pi, broj)<<endl;
    cout << "- Za funkciju x^3 na intervalu (0,10): "  <<fixed<<setprecision(2)<< TrapeznoPravilo ([] (double x) {return x * x * x;} , 0, 10, broj)<<endl;
    cout << "- Za funkciju 1/x na intervalu (1,2): "   <<fixed<<setprecision(5) << TrapeznoPravilo ([] (double x) {return 1 / x;}, 1, 2, broj) << endl;
 
    return 0;
}