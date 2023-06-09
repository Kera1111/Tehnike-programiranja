/*
PARCIJALNI 2021/2022 2PAC i U2, 120 studenata... (izdvoji brojeve u stringu)

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
#include <string>
#include <vector>

std::vector<int> BrojeviUStringu(std::string s){
    std::vector<int> vek;
    for (int i = 0; i < s.length(); i++) {
        std::string rijec;
        while (s[i] == ' ' && i < s.length()) i++;
        while (s[i] != ' ' && i < s.length()) rijec += s[i++];
        int j = 0;
        while (rijec[j] >= '0' && rijec[j] <= '9') j++;
        std::string znakovi = ".,;!?";
        // provjera znaka nakon broja
        for (char k : znakovi)
            if (rijec[j] == k || rijec[j] == '\0') {
                vek.push_back(std::stoi(rijec));
                break;
            }
    }
    return vek;
}
int main()
{
    std::string s;
    std::getline(std::cin, s);
    for (int i : BrojeviUStringu(s))
        std::cout << i << " ";
    return 0;
}