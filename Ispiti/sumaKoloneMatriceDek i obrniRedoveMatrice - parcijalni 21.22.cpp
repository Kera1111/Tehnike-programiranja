/*
PARCIJALNI 2021/2022 suma kolone matrice smjesti kao elemente deka i obrni redove u matrici

Napišite funkciju koja kao parametar prihvata matricu organiziranu kao vektor vektōrâ realnog tipa
(tipa "double") a kao rezultat vraća dek čiji su elementi također tipa "double". Funkcija treba da
transformira matricu proslijeđenu kao parametar na način da obrne elemente po redovima, tako da
prvi element svakog reda postane posljednji, drugi pretposljednji, itd. U slučaju da parametar nema
oblik matrice (tj. ukoliko svi njegovi redovi nemaju isti broj elemenata), treba baciti izuzetak tipa
“domain_error” uz prateći tekst “Parametar nema formu matrice”. Osim obrtanja redova, koje se odvija
putem transformacije odgovarajućeg parametra, funkcija kao rezultat treba vratiti dek čiji je i-ti
element suma i-te kolone matrice. Za realizaciju funkcije nije dozvoljeno koristiti nikakve pomoćne
kontejnerske tipove podataka. Napišite i kratki isječak programa koji ilustrira kako se koristi napisana
funkcija (uključujući i hvatanje eventualno bačenog izuzetka).
*/

// RJEŠENJE:

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

typedef std::vector<std::vector<double>> Matrica;

Matrica KreirajMatricu(int brRedova, int brKolona){
    return Matrica(brRedova, std::vector<double>(brKolona));
}

bool imaLiFormuMatrice(Matrica m){
    if(m.empty()) return false;
    for(int i=0; i<m.size(); i++) if(m.at(0).size()!=m.at(i).size()) return false;
    return true;
}

std::deque<double> sumaKoloneMatrice(Matrica &m){
    std::deque<double> rez;
    if(!imaLiFormuMatrice(m)) throw std::domain_error("Parametar nema formu matrice");
    for(auto & i : m) reverse(i.begin(), i.begin());
    int brojac = 0;  //prolaz kroz svaku kolonu
    for(int k = 0; k < m.size(); k++){
        double suma = 0;
        for(int i = 0; i < m.size(); i++){
        for(int j = 0; j < m.at(0).size(); j++) {
            if(j==brojac) {
                suma += m.at(i).at(brojac);
                break;
            }
        }}
        rez.push_back(suma);
        brojac++;
    }
    return rez;
}

/*
1 2 3  - 11 8 9
2 4 5
8 2 1
 * */

int main() {

    try{
        auto m = KreirajMatricu(3,3);
        m = {{1,2,3},{2,4,5},{8,2,1}};
        auto dek = sumaKoloneMatrice(m);
        for(auto el: dek) std::cout<<el<<" ";
    }catch(std::domain_error &e) { std::cout << e.what() << std::endl; }

    return 0;
}