/*
PARCIJALNI 2021/2022 - podblok od bloka 

Napišite generičku funkciju koja prima 4 parametra od kojih prva dva omeđuju jedan blok podataka a
druga dva drugi blok podataka. Ovi parametri mogu biti bilo pokazivači bilo iteratori, pri čemu su
prva dva istog tipa i druga dva također istog tipa, ali tipovi prva dva parametra i druga dva parametra
ne moraju biti isti. Ova funkcija treba da pronađe da li se drugi blok nalazi kao podblok u prvom
bloku (npr. blok {3, 5,2} nalazi se kao podblok u bloku {1, 7, 3, 5,2,6}). Ukoliko se nalazi, funkcija kao
rezultat vraća pokazivač/iterator na mjesto u prvom bloku na kojem se drugi blok nalazi kao podblok.
Ukoliko se traženi blok nalazi na više mjesta kao podblok u prvom bloku, treba vratiti mjesto njegovog
prvog pronalaska. Konačno, ukoliko traženi blok nije nađen kao podblok u prvom bloku, treba vratiti
pokazivač/iterator koji pokazuje tačno iza kraja prvog bloka. Napišite i kratki isječak programa u
kojem ćete demonstrirati kako se koristi napisana funkcija na dva fiksna niza stringova.
*/

// RJEŠENJE :

#include <iostream>
#include <vector>
 
template <typename tip1, typename tip2>
tip1 Podblok(tip1 poc1, tip1 kraj1, tip2 poc2, tip2 kraj2){
    int brojac = 0, duzinaPodbloka = std::distance(poc2, kraj2);
    tip1 pocetak; tip2 p = poc2;
    while(poc1!=kraj1){
        if(*poc1==*poc2){
            if(brojac == 0) pocetak = poc1;
            brojac++; poc1++; poc2++;
            if(brojac == duzinaPodbloka) break;
        }else{
            brojac=0;
            poc1++;
            poc2 = p;
        }
    }
    return pocetak;
}
int main()
{
    std::vector<int> n{1, 7, 3, 5, 2, 6}, m{3, 5, 2};
    std::vector<int>::iterator pocetak = Podblok(n.begin(), n.end(), m.begin(), m.end());
    while (pocetak != n.end()) std::cout << *pocetak++ << " ";
    return 0;
}
