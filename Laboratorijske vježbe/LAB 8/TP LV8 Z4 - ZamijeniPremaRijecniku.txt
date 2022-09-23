//TP 2021/2022: LV 8, Zadatak 4
#include <iostream>
#include <cmath>
#include <map>
#include <cctype>//zbg isalpha

typedef std::map<std::string, std::string> Rjecnik;

std::string ZamijeniPremaRjecniku(const std::string &s, const Rjecnik &mapa){
    std::string rezultat;
    for(int i=0; i<s.length(); i++){
        if(isalpha(s.at(i))){
            std::string temp;
            for(; s.at(i)!=' ' && i<s.length()-1; i++) temp.push_back(s.at(i));
            auto Nadjen = mapa.find(temp);
            if(Nadjen != mapa.end()){
                for(auto p = Nadjen->second.begin(); p != Nadjen->second.end(); p++){
                    rezultat.push_back(*p);
                }    
            }else{
                    for(auto p = temp.begin(); p!=temp.end(); p++){
                        rezultat.push_back(*p);
                    }
                }
        }   
    rezultat.push_back(s.at(i));
    }
return rezultat;
}

int main ()
{
    std::map<std::string, std::string> rjecnik 
    { 
        {"jabuka", "apple"}, 
        {"da", "yes"}, 
        {"kako", "how"}, 
        {"ne", "no"}, 
        {"majmun", "monkey"}, 
        {"mart", "ozujak"},
        {"maj", "svibanj"}, 
        {"jul", "srpanj"}
    };

    std::cout << ZamijeniPremaRjecniku("davor martic ima sestre maju i juliju", rjecnik) << std::endl;
	return 0;
}
