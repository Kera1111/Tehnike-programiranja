/*
PARCIJALNI 2021/2022 PopuniPoKriteriju(p1,p2,p3,p4,f) 

Napišite generičku funkciju “PopuniPoKriteriju” koja prihvata pet parametara , , , i f.
Parametri i omeđuju jedan blok podataka i mogu biti pokazivači ili iteratori, ali oba su istog
tipa, dok parametar (također pokazivač ili iterator) pokazuje na početak nekog odredišnog bloka.
Tip ne mora biti isti kao tip odnosno . Funkcija “PopuniPoKriteriju” treba da na svaki
element prvog bloka primijeni transformacionu funkciju f (koja prima jedan argument) i da rezultate
transformacije upiše u drugi blok (pri čemu se pretpostavlja da u njemu ima dovoljno mjesta da
primi sve rezultate). U parametar treba smjestiti pokazivač odnosno iterator koji pokazuje tačno
iza posljednjeg elementa odredišnog bloka. Sama funkcija treba da kao rezultat vrati sumu svih
elemenata u izvornom bloku. Za iteratore se podrazumijeva da podržavaju samo osnovni skup operacija
koje moraju podržavati svi iteratori. Napisanu funkciju demonstrirajte u kratkom isječku programa
gdje se sa tastature unosi neki vektor cijelih brojeva, a zatim se pozivom napisane funkcije popunjava
neki dek kvadratima elemenata tog vektora, ali u obrnutom poretku elemenata. Na primjer, za
elemente vektora 1, 2 i 3, kreirani dek treba redom da sadrži 9, 4 i 1 (kao rezultat funkcije vraća se 6).
Korištenje umetača je dozvoljeno i poželjno.
*/

// RJEŠENJE: 

#include <iostream>
#include <vector>
#include <deque>

constexpr double kvadriraj(double x) {
    return x*x;
}

constexpr double kubiraj(double x) {
    return x*x*x;
}

template <typename IterTip_1, typename IterTip_2, typename tip>
auto PopuniPoKriteriju(IterTip_1 p1, IterTip_1 p2, IterTip_2 p3, IterTip_2 p4, tip f(tip)) {

    IterTip_1 pom1 = p1;
    IterTip_2 pom = p3;

    auto suma(0);
    while (p1!=p2) {
        suma+=*p1;
        p1++;
    }

    p1 = pom1;

    while(pom1!=p2) {
        *pom = f(*pom1);
        pom1++;
        pom++;
    }
    return suma;
}

int main ()
{
    std::vector<int> v{1,2,3};
    std::deque<int> dek(5);
    double zbir = PopuniPoKriteriju(v.rbegin(), v.rend(), dek.begin(), dek.end(),  kvadriraj);

    std::cout << zbir << std::endl;

    auto it = dek.begin();
    while(it!=dek.end())
        std::cout << *it++ << " ";

    return 0;
}