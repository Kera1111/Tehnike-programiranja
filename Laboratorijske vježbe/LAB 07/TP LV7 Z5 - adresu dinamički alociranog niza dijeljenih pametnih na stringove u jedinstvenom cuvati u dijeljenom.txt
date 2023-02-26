/* 
    TP 16/17 (LV 7, Zadatak 5)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/

/*
Izmijenite prethodni program tako što ćete adresu dinamički alociranog niza dijeljenih pametnih 
pokazivača na stringove umjesto u jedinstvenom pametnom pokazivaču čuvati također u dijeljenom
pametnom pokazivaču. Vodite računa da ovo, sve dok ne zaživi C++17 standard, nosi i izvjesne 
komplikacije. Prvo, ukoliko želimo da dijeljeni pametni pokazivač pokazuje na dinamički alocirani niz, 
neophodno je zadati i funkciju koja se poziva kada dođe vrijeme za brisanje objekta (tzv. custom 
deleter), s obzirom da podrazumijevani način brisanja nije adekvatan. Drugo, takvi pametni 
pokazivači ne mogu se neposredno indeksirati, nego je neophodna njihova konverzija u “glupe”
pokazivače da bismo mogli koristiti indeksaciju
*/

#include <algorithm>
#include <cstring> //zbg strlen
#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>

int main() {
  int brRecenica;
  std::cout << "Koliko zelite recenica: ";
  std::cin >> brRecenica;
  std::cin.ignore(10000, '\n'); // ocisti

  try {
    std::cout << "Unesite recenice:" << std::endl;
    std::shared_ptr<std::shared_ptr<std::string>> recenice (new std::shared_ptr<std::string>[brRecenica], [](auto *recenice){delete[] recenice;});
    // unos
    for (int i = 0; i < brRecenica; i++) {
        recenice.get()[i] = std::make_shared<std::string>();
        std::getline(std::cin, *(recenice.get()[i]));
      }
      // sortiranje
      std::sort(&recenice.get()[0], &recenice.get()[brRecenica-1]+1, [](auto a, auto b) {
        return *b > *a;
      }); // provjeri ko je veci i prema tom kriteriju sortiraj
      //mora se prvo dereferencirati zato ne moze ici recenice, recenice+brRecenica
      //moram dodati +1 poslije &recenice[brRecenica-1] ako hocu da i zadnju sortira

      // ispis
      std::cout << "Sortirane recenice:" << std::endl;
      for (int i = 0; i < brRecenica; i++) {
        std::cout << *recenice.get()[i] << std::endl;
      }
    } catch (std::bad_alloc) {
    std::cout << "Problemi s memorijom!" << std::endl;
    //nema delete jer
    //Jednom kada svi shared_ptr objekti koji dijele vlasništvo nad pokazivačem otpuste ovo vlasništvo, upravljani objekt se briše (obično pozivanjem ::delete, ali se prilikom konstrukcije može navesti drugačiji alat za brisanje).
  }
  return 0;
}