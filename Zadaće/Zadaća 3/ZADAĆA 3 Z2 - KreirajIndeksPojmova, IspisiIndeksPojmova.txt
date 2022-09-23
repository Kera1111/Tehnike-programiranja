//TP 2021/2022: Zadaća 3, Zadatak 2
#include <cctype>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <stdexcept>
#include <string>

bool DaLiJeRijec(char s){
    
    if((s >= 'A' && s <= 'Z') || (s >='a' && s <='z') || (s>='0' && s<='9')) return true;

    return false;

}

std::map<std::string, std::set<int>> KreirajIndeksPojmova(std::string s){
    
    std::map<std::string, std::set<int>> mapa;
    
    for(int i=0; i<s.length(); i++){
        int pozicija = 0;
        if(DaLiJeRijec(s[i])){
            for(int j=i;;j++){
                if(!DaLiJeRijec(s[j])) break;
                pozicija++;
            }
            std::string novi = s.substr(i,pozicija);
            std::transform(novi.begin(), novi.end(), novi.begin(), ::tolower);
            if(novi.empty()) continue;

            if(mapa.find(novi)==mapa.end()) mapa[novi].insert(i);
            else mapa.find(novi)->second.insert(i);

            i+=novi.length()-1;
        }
    }

return mapa;

}

void IspisiIndeksPojmova(std::map<std::string, std::set<int>> mapa){
    std::for_each(mapa.begin(), mapa.end(), [](std::pair<std::string, std::set<int>> e){
        std::cout<<e.first<<": ";
        int i=0;
        for(auto it = e.second.begin(); it != e.second.end(); it++, i++){
            if(i == e.second.size()-1) std::cout<<*it;
            else std::cout<<*it<<",";
        }
        std::cout<<std::endl;
        /*
        std::for_each(e.second.begin(), e.second.end(), [](int el){
            std::cout<<el<<",";
        });
        ne mogu ovako jer mi zarez ce se ispisati i za zadnji clan
        */
    });
}

std::set<int> PretraziIndeksPojmova(std::string s, std::map<std::string, std::set<int>> mapa){
    /*
    if(mapa.find(s)==mapa.end()) throw std::logic_error("Pojam nije nadjen");
    return mapa.find(s)->second;
    ovako bi moglo da nema testa za case insensitive
    */
    for(auto it=mapa.begin(); it!=mapa.end(); it++){
        std::string prvi = s;
        std::transform(prvi.begin(), prvi.end(), prvi.begin(), ::tolower);
        std::string drugi = it->first;
        std::transform(drugi.begin(), drugi.end(), drugi.begin(), ::tolower);
        if(prvi==drugi) return mapa[it->first];
    }
    throw std::logic_error("Pojam nije nadjen");
}

int main ()
{
    std::cout<<"Unesite tekst: ";
    std::string s;
    std::getline(std::cin, s);
    auto mapa = KreirajIndeksPojmova(s);
    IspisiIndeksPojmova(mapa);
    while(1){
        std::cout<<std::endl;
        std::cout<<"Unesite rijec: ";
        std::string rijec;
        std::getline(std::cin, rijec);
        if(rijec==".") break;
        try{
            auto e = PretraziIndeksPojmova(rijec,mapa);
            int i=0; 
            for(auto it = e.begin(); it != e.end(); it++, i++)
            {
                
                std::cout<<*it<<" ";
            }
        }catch(...){
            std::cout<<"Unesena rijec nije nadjena!";
        }
    }
    
	return 0;
}
