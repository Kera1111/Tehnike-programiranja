//TP 2021/2022: Zadaća 1, Zadatak 3
#include <iostream>
#include <cmath>
#include <vector>

/*
Dva polja (v1, k1) i (v2, k2) se nalaze 
u istoj vrsti ako je v1 = v2, 
u istoj koloni ako je k1 = k2, 
na istoj dijagonali ako je |v1 - v2| = |k1 - k2| (tj. ako je
horizontalno rastojanje ta dva polja jednako vertikalnom).
*/

using namespace std;
typedef vector<vector<bool>> matrica;

bool DaLiSeDameNapadaju(matrica ploca){

    int maxred=0;
    int brojRedova=ploca.size();

    for(int i=0;i<brojRedova;i++){
        if(ploca.at(i).size()>maxred)
        maxred=ploca.at(i).size();
    }

    for(int i=0;i<brojRedova;i++){
        ploca.at(i).resize(maxred,false);
    }

    for(int i=0;i<ploca.size();i++){
        for(int j=0;j<ploca.at(i).size();j++){
            
            if(ploca.at(i).at(j)){
                for(int x=i;x<ploca.size();x++){
                    for(int y=j;y<ploca.at(i).size();y++){
                        if(ploca.at(x).at(y)==ploca.at(i).at(j) && y!=j && x==i) return true;
                        if(ploca.at(x).at(y)==ploca.at(i).at(j) && x!=i && y==j) return true;
                        if(ploca.at(x).at(y)==ploca.at(i).at(j) && abs(x-i)==abs(y-j) && x!=i && y!=j) return true;
                    }
                }
            }


        }
    }
    return false;
}


int main ()
{

    cout<<"Unesite opis sahovske ploce:"<<endl;
    cout<<"(Q za kraljicu, bilo sta drugo za prazno polje, ENTER naprazno za kraj unosa):"<<endl;
    matrica ploca;
    int max_duzina=0,i=0;
    while(1){
        string red;
        getline(cin,red);
        if(red.length()==0) break;
        if(max_duzina<red.length()) max_duzina=red.length();

        ploca.resize(i+1,vector<bool>(max_duzina,false));
        for(int j=0;j<red.length();j++){
            if(red.at(j)=='Q') ploca.at(i).at(j)=true;
            else ploca.at(i).at(j)=false;
        }
        i++;
    }
    if(DaLiSeDameNapadaju(ploca)){
        cout<<"Dame se medjusobno napadaju."<<endl;
    }
    else{
        cout<<"Dame se medjusobno ne napadaju."<<endl;
    }
	return 0;
}
