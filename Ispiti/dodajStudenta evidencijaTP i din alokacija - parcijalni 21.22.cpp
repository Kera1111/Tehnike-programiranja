/*
PARCIJALNI 2021/2022 - evidencija TP din alokacija dodat studenta

Predmetni nastavnik vodi evidenciju o svim studentima koji pohađaju kurs “Tehnike programiranja”.
Radi efikasnije manipulacije sa studentima, imena svih studenata se čuvaju u dinamički alociranim
objektima tipa “string” (svaki student u posebnom objektu), a adrese tih dinamički alociranih objekata
čuvaju se u nizu pokazivača koji je također dinamički alociran. Neki od tih pokazivača su neiskorišteni,
tj. postavljeni su na nul-pokazivač (to obično nastaje kada se neki od studenata ispiše). Napišite
funkciju za dodavanje novog studenta u evidenciju. Prvi parametar je pokazivač koji pokazuje na
opisani niz pokazivača, drugi parametar je ukupan broj pokazivača u tom nizu, dok je treći parametar
string koji predstavlja ime koje se dodaje. Dodavanje se obavlja ovako. Dinamički se alocira novi string,
koji je kopija stringa proslijeđenog kao parametar. Ukoliko u nizu postoji neki nul-pokazivač, njemu se
dodjeljuje adresa novokreiranog stringa, i dodavanje je gotovo. Ukoliko ne postoji niti jedan nul-
pokazivač, dinamički se alocira novi niz pokazivača čija je veličina za 10 elemenata veća od trenutnog
broja pokazivača, svi pokazivači iz starog niza se kopiraju u novi, “višak” pokazivača se postavlja na nul-
pokazivače, prvom nul-pokazivaču dodjeljuje adresa novokreiranog stringa, nakon čega se stari niz
pokazivača briše a prvi parametar funkcije se ažurira da pokazuje na novi niz pokazivača. Ukoliko neka
od alokacija ne uspije, treba baciti izuzetak tipa “logic_error” uz prateći tekst “Nedovoljno memorije”,
pazeći da ni u kom slučaju ne dođe do cirenja memorije, niti da budu izgubljeni podaci koji već postoje.
*/

// RJEŠENJE:

#include <iostream>
#include <vector>
#include <string>

void EvidencijaTP(std::string** &mat, int brPokazivaca, std::string noviStudent){
    auto* ucenik = new std::string{};
    *ucenik = noviStudent;
    bool imaMjesta = false;
    for(int i=0; i<brPokazivaca; i++){
        if(mat[i]==nullptr){ mat[i]=ucenik; imaMjesta = true; }
    }
    if(!imaMjesta){
        try{
            auto** novaMat = new std::string*[brPokazivaca+10]{};
            for(int i=0; i<brPokazivaca; i++) novaMat[i] = mat[i];
            novaMat[brPokazivaca]=ucenik;
            delete[] mat;
            mat = novaMat;
        }catch(...){ throw std::logic_error("Nedovoljno memorije"); }
    }
}

int main(){
    int vel = 3;
    auto** rez = new std::string*[vel]{};
    for(int i=0; i<vel; i++) rez[i] = new std::string{};
    *rez[0]="abc", *rez[1]="bdd", *rez[2]="bgm"; vel++;
    try{
        EvidencijaTP(rez, vel, "joj");
        for(int i=0; i<vel; i++) std::cout<<*rez[i]<<" ";
        for(int i=0; i<vel; i++){delete rez[i];} delete[] rez;
    }catch(std::logic_error &e){
        std::cout<<e.what()<<std::endl;
    }

}