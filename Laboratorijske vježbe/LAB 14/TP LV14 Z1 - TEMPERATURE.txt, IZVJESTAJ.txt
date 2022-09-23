//TP 2021/2022: LV 14, Zadatak 1
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

struct Datum{
    int dan, mjesec, godina;  
};
 
struct Temperatura{
    Datum date;
    std::string ime;
    double prosjecna, minTemp, maxTemp;
    std::vector<int> izmjereno; 
};

bool Sortiranje(Temperatura t1, Temperatura t2){
        if(t1.date.godina < t2.date.godina) return true;
        else if(t1.date.godina == t2.date.godina){
            if(t1.date.mjesec < t2.date.mjesec) return true;
            else if(t1.date.mjesec == t2.date.mjesec){
                if(t1.date.dan < t2.date.dan) return true;
                else if(t1.date.dan == t2.date.dan){
                    if(t1.prosjecna<t2.prosjecna) return true;
                }
                }
        }else return false;
        return false;
}

int main ()
{
    ifstream ulazni_tok("TEMPERATURE.TXT");
    if(!ulazni_tok) {cout << "Datoteka TEMPERATURE.TXT ne postoji!" <<endl; return 0;}

    vector<Temperatura> tempVektor;
    while(1){
        int d, m, g; double zbir = 0;
        string naziv;
        vector<int> temp;
        char znak1, znak2;
        ulazni_tok>>d>>znak1>>m>>znak2>>g;
        if(!ulazni_tok) break;
        ulazni_tok.ignore(10000,'\n');
        std::getline(ulazni_tok, naziv);
        char provjeriti;
        while(1){
            int tempy;
            char zarez ='.', minus='.';
            if(ulazni_tok.peek()=='-') ulazni_tok>>minus;
            ulazni_tok>>tempy;
            zarez = ulazni_tok.get();
            if(minus=='-') tempy*=-1;
            zbir+=tempy;
            temp.push_back(tempy);
            if(zarez!=',') break;
        }

    Temperatura temperatura;
    temperatura.date.dan=d;
    temperatura.date.mjesec=m;
    temperatura.date.godina=g;
    temperatura.ime=naziv;
    temperatura.izmjereno = temp;
    temperatura.prosjecna = zbir/temp.size();
    temperatura.minTemp = *min_element(temp.begin(), temp.end());
    temperatura.maxTemp = *max_element(temp.begin(), temp.end());
    
    tempVektor.push_back(temperatura);
    }
    if(!ulazni_tok.eof()) cout<<"Problemi pri citanju datoteke TEMPERATURE.TXT"<<endl;

    sort(tempVektor.begin(), tempVektor.end(),Sortiranje);

    ofstream izlaz("IZVJESTAJ.TXT");

    for(int k=0; k<tempVektor.size(); k++){
        izlaz<<tempVektor.at(k).ime<<endl;
        for(int i=0; i<tempVektor.at(k).ime.size(); i++) izlaz<<"-";
        izlaz<<endl;
        izlaz<<"Datum mjerenja: "<<fixed<<setprecision(0)<<tempVektor.at(k).date.dan<<"/"<<tempVektor.at(k).date.mjesec<<"/"<<tempVektor.at(k).date.godina<<endl;
        izlaz<<"Minimalna temperatura: "<<tempVektor.at(k).minTemp<<endl;
        izlaz<<"Maksimalna temperatura: "<<tempVektor.at(k).maxTemp<<endl;
        izlaz<<"Prosjecna temperatura: "<<fixed<<setprecision(2)<<tempVektor.at(k).prosjecna<<endl;
        izlaz<<endl;	
    }
    return 0;
    
}