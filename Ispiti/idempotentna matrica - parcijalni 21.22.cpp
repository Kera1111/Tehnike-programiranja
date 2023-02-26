/*
PARCIJALNI ISPIT 2021/2022 - idempotentna matrica 

Za kvadratnu matricu kažemo da je idempotentna ukoliko vrijedi A^2 = A, pri čemu je A^2 matrični produkt matrice sa samom sobom (tj.
A^2 = A×A). Napravite funkciju koja kao parametar prima matricu organiziranu kao vektor vektôrā realnih brojeva,
a koja vraća logičku vrijednost “tačno” ili “netačno” ovisno da li je parametar idempotentna matrica ili ne (ovo drugo uključuje i slučaj kada matrica nije
kvadratna, ili kad parametar uopće nema ispravnu formu matrice). Za punu količinu poena u funkciji nije dozvoljeno koristiti ikakve pomoćne kontejnerske tipove podataka. 
*/

// RJEŠENJE : 

#include <iostream>
#include <vector>

bool Idempotentna(const std::vector<std::vector<double>> &a) {
    int velicina = a[0].size();
    for (int i = 1; i < a.size(); i++) if (a.size() != velicina || a[i].size() != velicina) return false;
    for (int i = 0; i < velicina; i++)
        for (int j = 0; j < velicina; j++) {
            double proizvod = 0;
            for (int k = 0; k < velicina; k++)
                proizvod += a[i][k] * a[k][j];
            if (a[i][j] != proizvod) return false;
        }
    return true;
}
int main()
{
    std::vector<std::vector<double>>a{
            {3, -6},
            {1, -2},
    };
    std::cout << Idempotentna(a) << std::endl;
    return 0;
}