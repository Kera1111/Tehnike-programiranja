/*
    TP 16/17 (LV 7, Zadatak 10)
        Autotestove pisao Elmir Hodzic. Sva pitanja,
        prijave gresaka i sugestije slati na mail
        ehodzic3@etf.unsa.ba

        Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <algorithm>
#include <functional>
#include <iostream>

std::function<int(int)> IteriranaFunkcija(int fun(int), int broj) {
    
  std::function<int(int)> funkcija(fun);//deklarisem da je jednaka funkciji iz maina
  if(broj<=0){
        return funkcija;
}
  for (int i = 0; i < broj - 1; i++)//rekurzivno se ponavlja sve dok ne izvrsi se n-1 puta (broj puta koliko zelimo), n-1 a ne n zato sto smo vec prije for petlje deklarisali je jednom 
    funkcija = [funkcija, fun](int broj) { return funkcija(fun(broj)); };
  return funkcija;
}
int main() {
  auto funkc = IteriranaFunkcija([](int broj) { return 2 * broj; }, 3)(2);
  std::cout << funkc;
  return 0;
}