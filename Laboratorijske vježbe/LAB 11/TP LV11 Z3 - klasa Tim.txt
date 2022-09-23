/* 
    TP 16/17 (LV 11, Zadatak 3)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <iomanip>
#include <cstring>//zbg strlen
#include <stdexcept>

class Tim{
    char ime_tima[20];
    int broj_datih;
    int broj_primljenih;
    int broj_odigranih;
    int broj_nerijesenih;
    int broj_pobjeda;
    int broj_poraza;
    int broj_poena;
    public:
        
        Tim(const char ime[]){
            if(strlen(ime)>19) throw std::range_error("Predugacko ime tima");
            else std::strcpy(Tim::ime_tima, ime);
            broj_datih=0;
            broj_primljenih=0;
            broj_odigranih=0;
            broj_nerijesenih=0;
            broj_pobjeda=0;
            broj_poraza=0;
            broj_poena=0;
        }
        
        void ObradiUtakmicu(int broj_datih, int broj_primljenih){
            if(broj_datih<0 || broj_primljenih<0) throw std::range_error("Neispravan broj golova");
            broj_odigranih++;
            this->broj_datih+=broj_datih;
            this->broj_primljenih+=broj_primljenih;
            if(broj_datih>broj_primljenih){
                broj_pobjeda++;
                broj_poena+=3;
            }else{
                if(broj_datih==broj_primljenih){
                    broj_nerijesenih++;
                    broj_poena++;
                }else broj_poraza++;
            }
        }
        
        const char *DajImeTima() const{
            return ime_tima;
        }
        
        int DajBrojPoena() const{
            return broj_poena;
        }
        
        int DajGolRazliku() const{
            return broj_datih-broj_primljenih;
        }
        
        void IspisiPodatke() const{
            std::cout<<std::setw(20)<<std::left<<DajImeTima()<<std::setw(4)<<std::right<<Tim::broj_odigranih<<std::setw(4)<<std::right<<Tim::broj_pobjeda<<std::setw(4)<<std::right<<Tim::broj_nerijesenih<<std::setw(4)<<std::right<<Tim::broj_poraza<<std::setw(4)<<std::right<<Tim::broj_datih<<std::setw(4)<<std::right<<Tim::broj_primljenih<<std::setw(4)<<std::right<<DajBrojPoena()<<std::endl;
        }

};

int main ()
{
	return 0;
}