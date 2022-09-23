/* 
    TP 16/17 (LV 7, Zadatak 7)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <algorithm>
#include <set>
#include <string>

template<typename nekiTip>
std::set<nekiTip> Unija(std::set<nekiTip> a, std::set<nekiTip> b){
    std::set<nekiTip> unija;
    //ubacim prvo a, pa b, ako hocu da zadrzim duplikate koristim multiset, ali ovdje nema belaja oko toga, jer set ne stavlja ih ako ga vec ima
    for(auto x: a) unija.insert(x);
    for(auto x: b) unija.insert(x);
    return unija;
}

template<typename nekiTip>
std::set<nekiTip> Presjek(std::set<nekiTip> a, std::set<nekiTip> b){
    std::set<nekiTip> presjek;
    //ubacim a i prvo provjerim ima li ga i u b, ako ima onda dodaj taj clan, ako nema ne dodaji nista
    for(auto x: a)
        if(std::binary_search(b.begin(),b.end(),x)) presjek.insert(x);
    return presjek;
}

int main ()
{
    //btw set automatski sortira 
    std::set<std::string> s1 ={"hana","hanna","joj"};
    std::set<std::string> s2 ={"hana","jabuka","cokolada"};
    for(auto x: Unija(s1,s2)) std::cout<<x<<" ";
    std::cout<<std::endl;
    for(auto x: Presjek(s1,s2)) std::cout<<x<<" ";
	return 0;
}