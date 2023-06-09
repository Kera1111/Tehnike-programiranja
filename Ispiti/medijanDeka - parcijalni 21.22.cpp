/*
PARCIJALNI 2021/2022 - medijan deka

Neka je dat slijed brojeva , , ..., koji se sastoji od neparnog broja elemenata (tj. n je neparan
broj). Za neki element tog slijeda kažemo da je njegov medijan ukoliko postoji podjednako mnogo
elemenata u tom slijedu koji su veći ili jednaki od njega i koji su manji ili jednaki od njega (tj. koji bi
se, u slučaju da slijed sortiramo, našao tačno na sredini sortiranog slijeda). Inače, definicija medijana
se može proširiti i za slijedove sa parnim brojem elemenata, ali to nas u ovom zadatku ne zanima.
Napravite funkciju koja kao parametar prima dek cijelih brojeva koji sadrži slijed čiji medijan
tražimo, a koja kao rezultat vraća nađeni medijan. Pri tome funkcija ne smije vršiti sortiranje deka, niti
koristi pomoćne kontejnerske tipove podataka. Možete pretpostaviti da će dek imati neparan broj
elemenata (i tu pretpostavku ne trebate provjeravati u funkciji). Međutim, trebate odgovoriti na
pitanje šta će Vaša funkcija (koju ste napisali) vratiti kao rezultat ukoliko joj se ponudi dek koji ima
paran broj elemenata (odgovor na ovo pitanje nosi 0.5 poena).
*/

// RJEŠENJE :

#include <iostream>
#include <vector>
#include <deque>

int MedijanDeka(std::deque<int> &a){
    for(int i=0; i<a.size(); i++){
        int brVecih = 0, brManjih = 0;
        for(int j=0; j<a.size(); j++){
            if(a.at(j)!=a.at(i)){
                if(a.at(j)>a.at(i)) brVecih++;
                else brManjih++;
            }
        }
        if(brVecih==brManjih) return a.at(i);
    }
    return 0;
}

int main()
{
    std::deque<int>a{3, 5, 2, 1, 4, 8, 12};
    std::cout << MedijanDeka(a);
    /* Ako se unese paran broj elemenata deka, funkcija će vratiti broj 0
    kao medijan jer niti jedan elemenat deka neće imati jednak broj
    većih i manjih od sebe */
    return 0;
}
