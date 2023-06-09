/*
PARCIJALNI 2021/2022 - polinom

Napravite funkciju “Polinom” koja kao parametar prima vektor realnih brojeva koji predstavljaju
koeficijente nekog polinoma (prvi element vektora je slobodni član, drugi element je član uz prvi
stepen promjenljive polinoma, i tako dalje ka rastućim stepenima promjenljive polinoma), a koja kao
rezultat vraća funkciju koja računa vrijednost tog polinoma u tački koja se zadaje kao argument te
funkcije. Na primjer, isječak programa
auto poli = Polinom({2, 3, 0, −1, 4});
std::cout << poli(5);
treba da ispiše broj 2392, jer je 2 + 3 ∙ 5 + 0 ∙ 5 − 1 ∙ 5 + 4 ∙ 5 = 2392.
*/

// RJEŠENJE :

#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

std::function<double(double)> Polinom(const std::vector<double>& a){
    return [a](double x){
        double suma=0;
        for(int i=0;i<a.size();i++)
            suma+=(a.at(i)*pow(x,i));
        return suma;
    };
}
int main(){
    std::cout<<Polinom({1,2,3,4})(5)<<std::endl;
    return 0;
}