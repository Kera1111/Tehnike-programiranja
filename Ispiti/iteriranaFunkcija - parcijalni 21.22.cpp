/*
PARCIJALNI 2021/2022 - iterirana funkcija

Napišite funkciju “IteriranaFunkcija” koja kao parametar prima neku funkciju f koja prima cijeli
broj i vraća cijeli broj kao rezultat, te prirodan broj n. Ova funkcija kao rezultat treba vratiti novu
funkciju (nazovimo je g) takvu da vrijedi da je g(x) = f
( )
(x) = f(f(f(... f(x)...))), gdje se funkcija f
primjenjuje na argument n puta uzastopno. Recimo, ukoliko je “f” neka funkcija koja prima i vraća
cjelobrojnu vrijednost, tada izraz “IteriranaFunkcija(f, 5)(2)” treba da proizvede isti rezultat kao i
izraz “f(f(f(f(f(2)))))”. Napisanu funkciju iskoristite u programu u kojem ćete izračunati koliko
iznosi vrijednost izraza f(f(f(f(f(f(0)))))) za funkciju f(x) = 3 x −5, ali da pri tome ne kreirate
nikakvu imenovanu funkciju.
*/

// RJEŠENJE : 

#include <iostream>
#include <functional>

std::function<int(int)> IteriranaFunkcija(const std::function<int(int)> &f, int n){
    std::function<int(int)> g=f;
    for (int i = 1; i < n; i++) g = [g, f](int x){ return g(f(x)) ;};
    return g;
}

int main(){
    std::cout<<IteriranaFunkcija([]( int x){ return 3*x-5;} , 5)(2);
}