/* 
    TP 16/17 (LV 12, Zadatak 2)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <set>

template <typename nekiTip>
std::set<nekiTip> &operator *=(std::set<nekiTip> &skup1, std::set<nekiTip> skup2)
{
    std::set<nekiTip> novi;

    typename std::set<nekiTip>::iterator it1(skup1.begin()), it2(skup1.end());
    while(it1 != it2){
        if(skup2.find(*it1) != skup2.end()){
            novi.insert(*it1);
        }
        it1++;
    }
    skup1 = novi;
    return skup1;
}

template <typename nekiTip>
std::set<nekiTip> &operator +=(std::set<nekiTip> &skup1, std::set<nekiTip> skup2){
    std::set<nekiTip> novi;

    typename std::set<nekiTip>::iterator it1(skup1.begin()), it2(skup1.end());
    typename std::set<nekiTip>::iterator it21(skup2.begin()), it22(skup2.end());

    while(it1 != it2){
        novi.insert(*it1);
        it1++;
    }
    while(it21 != it22){
        novi.insert(*it21);
        it21++;
    }
    skup1 = novi;
    return skup1;

}

template <typename nekiTip>
std::ostream &operator <<(std::ostream &ispis, std::set<nekiTip> s)
{
    ispis<<'{';
    auto i2 = s.begin();

    if(s.size()==0) return ispis<<'}';

    for(auto i=0; i<s.size()-1; i++) ispis<<*i2++<<',';
    ispis<<*i2<<'}';
    return ispis;
}

template <typename nekiTip>
std::set<nekiTip> operator *(std::set<nekiTip> &skup1, std::set<nekiTip> skup2)
{
    std::set<nekiTip> novi (skup1 *= skup2);
    return novi;
}

template <typename nekiTip>
std::set<nekiTip> operator +(std::set<nekiTip> skup1, std::set<nekiTip> skup2)
{
    std::set<nekiTip> novi (skup1 += skup2);
    return novi;
}

template <typename nekiTip, typename nekiDrugiTip>
std::set<std::pair<nekiTip, nekiDrugiTip>> operator %(std::set<nekiTip> skup1, std::set<nekiDrugiTip> skup2)
{
    std::set<std::pair<nekiTip, nekiDrugiTip>> novi;

    typename std::set<nekiTip>::iterator it1(skup1.begin()), it2(skup1.end());
    typename std::set<nekiDrugiTip>::iterator it21(skup2.begin()), it22(skup2.end());

    while(it1 != it2){
        while(it21 != it22){
            novi.insert({*it1, *it21});
            it21++;
        }
        it21 = skup2.begin();
        it1++;
    }

    return novi;
}

template <typename nekiTip, typename nekiDrugiTip>
std::ostream &operator <<(std::ostream &ispis, std::set<std::pair<nekiTip, nekiDrugiTip>> s)
{
   ispis<<'{';
    auto i2 = s.begin();

    if(s.size()==0) return ispis<<'}';

    for(auto i=0; i<s.size()-1; i++){
        ispis<<'('<<i2->first<<','<<i2->second<<')'<<',';
        i2++;
    }
    ispis<<'('<<i2->first<<','<<i2->second<<')'<<'}';
    return ispis;
}

int main ()
{
	return 0;
}