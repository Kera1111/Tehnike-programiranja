/*
PARCIJALNI 2021/2022 - odredi tipove podataka 

Data je generička funkcija
template <typename NekiTip>
auto F(NekiTip t) -> decltype(&t) {
return new NekiTip(t);
}
Odredite kojeg će tipa biti varijabla “x” u svakoj od sljedećih deklaracija:
*/

// RJEŠENJE :

#include <iostream>
#include <vector>
#include <deque>

template <typename NekiTip>
auto F(NekiTip t) -> decltype(&t) {
    return new NekiTip(t);
}

int main()
{
    // auto x = F(3); int*
    // auto x = F<float>(3); float*
    // auto x = F(3.); double*
    // auto x = F('3'); char*
    // auto x = F<int>('3'); int*
    // auto x = F("3"); const char**
    // auto x = F("333"); const char**
    // auto x = F(.3); double*
    // auto x = F<std::string>("3"); string*
    return 0;
}