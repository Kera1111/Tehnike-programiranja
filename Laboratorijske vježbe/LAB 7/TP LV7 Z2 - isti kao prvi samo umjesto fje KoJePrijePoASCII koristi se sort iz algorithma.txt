/* 
    TP 16/17 (LV 7, Zadatak 2)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/

/*
Izmijenite prethodni program, ali tako što ćete umjesto ručnog sortiranja koristiti funkciju “sort” iz 
biblioteke “algorithm”, uz pogodnu funkciju kriterija implementiranu kao lambda funkcija.
*/

#include <iostream>
#include <cstring> //zbg strlen
#include <stdexcept>
#include <algorithm>

int main() {
  int brRecenica;
  std::cout << "Koliko zelite recenica: ";
  std::cin >> brRecenica;
  std::cin.ignore(10000, '\n'); // ocisti

  char **recenice(nullptr);
  try {
    std::cout << "Unesite recenice:"<<std::endl;
    recenice = new char *[brRecenica];
    for(int i=0; i<brRecenica; i++) recenice[i]=nullptr;
    //unos
    try{
    for(int i=0; i<brRecenica; i++){
        char trenutna[1000];
        std::cin.getline(trenutna, sizeof trenutna);
        
        recenice[i] = new char[std::strlen(trenutna)+1];
        
        std::strcpy(recenice[i], trenutna);
    }
    //sortiranje
    std::sort(recenice, recenice+brRecenica,[](auto a,auto b){return std::strcmp(a,b)<0;});
    //ispis
    std::cout<<"Sortirane recenice: "<<std::endl;
    for(int i=0; i<brRecenica; i++){
        std::cout<<recenice[i]<<std::endl;
    }
    //brisanje alociranog da ne dodje do curenja memorije
    for(int i=0; i<brRecenica; i++)
        delete[] recenice[i];
    delete[] recenice;
    }catch(...){
            std::cout << "Problemi s memorijom!" << std::endl;
            for(int i=0; i<brRecenica; i++)
                delete[] recenice[i];
            delete[] recenice;
            }
  } catch (std::bad_alloc) {
    std::cout << "Problemi s memorijom!" << std::endl;
    delete[] recenice;
}
  return 0;
}