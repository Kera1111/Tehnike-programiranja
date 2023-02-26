/*
PARCIJALNI 2021/2022 - pomnozi stek sa brojem 

Napišite funkciju koja kao jedan parametar prima neki stek realnih brojeva, a kao drugi parametar 
neki realni broj. Funkcija kao rezultat treba da vrati novi stek realnih brojeva čiji su elementi 
jednaki elementima izvornog steka pomnoženi sa zadanim brojem. Na primjer, ukoliko se u steku 
koji je proslijeđen kao parametar nalaze brojevi 2, 5, 3 i 4 (tim redom), i ukoliko se kao drugi 
parametar proslijedi broj 3, stek vraćen kao rezultat treba da sadrži brojeve 6, 15, 9 i 12 (tim redom). 
Podsjetimo se da je stek kontejnerska struktura koja ne podržava ništa drugo osim operacija “push” 
(dodaj novi element na vrh steka), “top” (daj element koji je na vrhu steka), “pop” (ukloni element 
sa vrha steka), “size” (daj broj elemenata u steku) i “empty” (daj informaciju da li je stek prazan ili 
ne). Za realizaciju ove funkcije ne smijete koristiti nikakvu pomoćnu funkciju, osim eventualno 
jednog pomoćnog steka ukoliko smatrate da Vam je potreban
*/

// RJEŠENJE :

#include <stack>
#include <iostream>

std::stack<double> mnoziStekSaBrojem(std::stack<double> &s, double broj){
    std::stack<double> novi;
    while(!s.empty()){
        novi.push(s.top()*broj);
        s.pop();
    }
    return novi;
}

int main(){
    std::stack<double> s; s.push(1); s.push(2); s.push(3); s.push(4); s.push(5);
    auto rez = mnoziStekSaBrojem(s,5);
    while(!rez.empty()){std::cout<<rez.top()<<" "; rez.pop();}
}