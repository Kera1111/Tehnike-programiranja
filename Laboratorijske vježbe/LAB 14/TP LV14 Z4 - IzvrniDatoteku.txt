//TP 2021/2022: LV 14, Zadatak 4
#include <iostream>
#include <cmath>
#include <fstream>

void IzvrniDatoteku(const char imeDatoteke[])
{
    std::fstream datoteka(imeDatoteke, std::ios::in | std::ios::out | std::ios::binary);
    if(!datoteka) throw std::logic_error("Datoteka ne postoji");
    datoteka.seekg(0, std::ios::end);
    int duzina = datoteka.tellg();
    int brojElemenata = duzina/sizeof(double);
    for(int i=0; i<(brojElemenata+1)/2; i++){
        datoteka.seekp(0);
        double br1, br2;
        datoteka.seekg(int(i*sizeof(double)));
        datoteka.read(reinterpret_cast<char*>(&br1), sizeof br1);
        datoteka.seekg(-int((i+1)*sizeof(double)), std::ios::end);
        datoteka.read(reinterpret_cast<char*>(&br2), sizeof br2);
        datoteka.seekp(int(i*sizeof(double)));
        datoteka.write(reinterpret_cast<char*>(&br2), sizeof br2);
        datoteka.seekp(-int((i+1)*sizeof(double)), std::ios::end);
        datoteka.write(reinterpret_cast<char*>(&br1), sizeof br1);
        datoteka.seekg(0);
    }
    if(!datoteka) throw std::logic_error("Problemi pri citanju datoteke");
}

int main ()
{
	return 0;
}
