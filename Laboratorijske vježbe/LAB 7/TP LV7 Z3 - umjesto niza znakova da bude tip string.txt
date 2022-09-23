/*
    TP 16/17 (LV 7, Zadatak 3)
        Autotestove pisao Elmir Hodzic. Sva pitanja,
        prijave gresaka i sugestije slati na mail
        ehodzic3@etf.unsa.ba

        Vrsit ce se provjera na prepisivanje tutorijala.
*/

/*
Izmijenite prethodni program (dakle, program iz Zadatka 2), tako što ćete rečenice umjesto u 
dinamički alociranim nizovima znakova čuvati u dinamički alociranim objektima tipa “string”. 
Također uklonite ograničenje da rečenice mogu biti duge najviše 1000 znakova
*/

#include <algorithm>
#include <cstring> //zbg strlen
#include <iostream>
#include <stdexcept>
#include <string>


int main() {
  int brRecenica;
  std::cout << "Koliko zelite recenica: ";
  std::cin >> brRecenica;
  std::cin.ignore(10000, '\n'); // ocisti

  std::string **recenice(nullptr);
  try {
    std::cout << "Unesite recenice:" << std::endl;
    recenice = new std::string *[brRecenica] {
    }; // jer imam [] za new, u deleteu moram brisat sa [] (u pitanju je niz)
    // unos
    try {
      for (int i = 0; i < brRecenica; i++) {
        recenice[i] = new std::string;
        std::getline(std::cin, *recenice[i]);
      }
      // sortiranje
      std::sort(recenice, recenice + brRecenica, [](auto a, auto b) {
        return *b > *a;
      }); // provjeri ko je veci i prema tom kriteriju sortiraj

      // ispis
      std::cout << "Sortirane recenice: " << std::endl;
      for (int i = 0; i < brRecenica; i++) {
        std::cout << *recenice[i] << std::endl;
      }
      // brisanje alociranog da ne dodje do curenja memorije
      for (int i = 0; i < brRecenica; i++)
        delete recenice[i];
      delete[] recenice;
    } catch (...) {
      for (int i = 0; i < brRecenica; i++)
        delete recenice[i];
      delete[] recenice;
      throw;
    }
  } catch (std::bad_alloc) {
    std::cout << "Problemi s memorijom!" << std::endl;
  }
  return 0;
}