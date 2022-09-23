/* 
    TP 16/17 (LV 7, Zadatak 4)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/

/*
Izmijenite prethodni program tako što ćete adrese dinamički alociranih objekata tipa “string” 
umjesto u običnim pokazivačima čuvati u dijeljenim pametnim pokazivačima, dok ćete adresu
dinamički alociranog niza takvih pokazivača čuvati u odgovarajućem jedinstvenom pametnom
pokazivaču (jedinstveni pametni pokazivač je ovdje odabran zbog činjenice da je pogodniji za
čuvanje adresa dinamički alociranih nizova, a svakako neće više različitih pokazivača pokazivati na
ovaj dinamički alocirani niz). Savjet: iskoristite “typedef” ili “using” deklaraciju da uvedete 
prikladno ime za tip dijeljenih pametnih pokazivača na stringove, inače ćete imati vrlo glomazne i 
nečitke konstrukcije. Također, na jednom mjestu će Vam vjerovatno trebat i konverzija pametnih u 
“glupe” pokazivače
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
    std::unique_ptr<std::shared_ptr<std::string>[]> recenice (new std::shared_ptr<std::string>[brRecenica]);
    // unos
    for (int i = 0; i < brRecenica; i++) {
        recenice[i] = std::make_shared<std::string>();
        std::getline(std::cin, *recenice[i]);
      }
      // sortiranje
      std::sort(&recenice[0], &recenice[brRecenica-1]+1, [](auto a, auto b) {
        return *b > *a;
      }); // provjeri ko je veci i prema tom kriteriju sortiraj
      //mora se prvo dereferencirati zato ne moze ici recenice, recenice+brRecenica
      //moram dodati +1 poslije &recenice[brRecenica-1] ako hocu da i zadnju sortira

      // ispis
      std::cout << "Sortirane recenice:" << std::endl;
      for (int i = 0; i < brRecenica; i++) {
        std::cout << *recenice[i] << std::endl;
      }
    } catch (std::bad_alloc) {
    std::cout << "Problemi s memorijom!" << std::endl;
    //nema delete jer
    //unique_ptr objects automatically delete the object they manage (using a deleter) as soon as they themselves are destroyed, or as soon as their value changes either by an assignment operation or by an explicit call to unique_ptr::reset.
  }
  return 0;
}