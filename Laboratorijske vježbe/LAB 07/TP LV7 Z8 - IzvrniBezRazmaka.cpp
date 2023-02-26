/* 
    TP 16/17 (LV 7, Zadatak 8)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <string>
#include <algorithm>

std::string IzvrniBezRazmaka(std::string s){
    std::string rez;
    std::remove_copy(s.rbegin(),s.rend(),std::back_inserter(rez),' ');
    return rez;
}
/*od kraja do pocetka ubaci s u rez ali skloni viska razmake, te back inserta u rez */
int main ()
{
    std::cout<<IzvrniBezRazmaka("jes dobar    zadatak");
	return 0;
}