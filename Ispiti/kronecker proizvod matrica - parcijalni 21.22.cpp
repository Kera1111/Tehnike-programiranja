/*
PARCIJALNI 2021/2022 - kronecker genericki

Kroneckerov (ili tenzorski) proizvod dva vektora i (u matematičkom smilslu) čiji su koeficijenti
, i = 1, 2,...,m i

, j = 1,2,...,n, u oznaci ⊗ , predstavlja matricu formata m × n čiji su elementi
(to je zapravo “tablica množenja” formirana od elemenata ova dva vektora). Napišite generičku
funkciju koja kao svoje parametre prihvata vektore i , pri čemu oni mogu biti smješteni u bilo
kojem kontejnerskom tipu podataka koji podržava indeksiranje i funkciju “size” (npr. mogu biti
smješteni u vektoru, ili u deku), pri čemu se tipovi kontejnera u kojima su smješteni elementi vektora
i mogu razlikovati. Čak je dopušteno da se razlikuju i tipovi elemenata u ova dva kontejnera
(recimo, prvi parametar može biti dek cijelih brojeva, a drugi vektor realnih brojeva). Funkcija treba
da dinamički alocira matricu koju će popuniti elementima Kroneckerovog proizvoda vektora koji su
proslijeđeni kao parametri, i da vrati kao rezultat dvojni pokazivač pomoću kojeg se može pristupiti
elementima tako kreirane matrice. Tip elemenata matrice je onakav kakav je potreban da se smjesti
rezultat množenja elemenata iz ova dva vektora (npr. ako sadrži cijele a realne brojeve, matrica
treba sadržavati realne brojeve, jer se množenjem cijelog sa realnim brojem dobija realni broj).
Alokaciju treba izvesti postupkom kontinualne alokacije. U slučaju da alokacija ne uspije, treba baciti
izuzetak tipa “logic_error” uz prateći tekst “Alokacija nije uspjela”. Funkcija ne smije uzrokovati
curenje memorije ni pod kakvim okolnostima. Demonstrirajte napisanu funkciju u isječku programa
u kojem ćete kreirati Kroneckerov proizvod dva fiksna vektora cijelih brojeva, ispisati elemente
kreiranog Kroneckerovog proizvoda na ekran, i na kraju osloboditi svu alociranu memoriju.
*/

// RJEŠENJE :

#include <iostream>
#include <deque>
#include <vector>

template <typename t1, typename t2>
auto KroneckerGeneric(t1 a, t2 b){
    using tipObjekta = typename std::decay<decltype(a[0]*b[0])>::type;
    auto **mat = new tipObjekta*[a.size()]{};
    try{
        mat[0] = new tipObjekta[a.size()*b.size()]{};
        for(int i=1; i<a.size(); i++){
            mat[i] = mat[i-1] + b.size()+3;
        }
    }catch(...){
        delete[] mat[0]; delete[] mat;
        throw std::logic_error("Alokacija nije uspjela");
    }
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < b.size(); j++)
            mat[i][j] = a[i] * b[j];
    return mat;
}

int main() {
    int **mat;
    std::vector<int>a{1, 2, 3};
    std::deque<int>b{1, 2, 3, 4};
    try {
        mat = KroneckerGeneric(a, b);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++)std::cout << mat[i][j] << " ";
            std::cout << std::endl;
        }
        delete[] mat[0]; delete[] mat;
    } catch (const std::logic_error &e) {
        std::cout << e.what();
    }
    return 0;
}
