/* 
    TP 16/17 (LV 11, Zadatak 4)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <iomanip>
#include <cstring> //zbg strlen
#include <new>
#include <stdexcept>
#include <algorithm> //zbg sort

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

class Liga{
    int broj_timova;
    const int max_br_timova;
    Tim** timovi;
    void AlocirajNiz(int br){
        timovi = nullptr;
        try{
            timovi = new Tim*[br];
        }catch(...){
            OcistiTimove();
            throw;
        }
    }
    void OcistiTimove(){
        if(timovi==nullptr) return;
        for(int i=0; i<broj_timova; i++){
            delete timovi[i];
            delete[] timovi;
        }
    }
    int PronadjiTim(const char* ime_tima) const {
        for(int i=0; i<broj_timova; i++){
            if(std::strcmp(ime_tima, timovi[i]->DajImeTima())==0) return i;
        }
        return -1;
    }
    public:

        explicit Liga(int velicina_lige):broj_timova(0),max_br_timova(velicina_lige), timovi(nullptr){
            AlocirajNiz(max_br_timova);
        }

        explicit Liga(std::initializer_list<Tim> lista_timova):broj_timova(lista_timova.size()), max_br_timova(lista_timova.size()), timovi(nullptr){
            int brojac = 0;
            try{
                timovi = new Tim*[broj_timova];
                for(int i=0; i<broj_timova; i++) timovi[i]=nullptr;
                for(auto &x: lista_timova) timovi[brojac++]=new Tim(x);
            }catch(...){
                OcistiTimove();
                throw;
            }
        }

        ~Liga(){
            if(timovi==nullptr) return;
            for(int i=0; i<broj_timova; i++) delete timovi[i];
            delete[] timovi;
        }

        Liga(const Liga &l): broj_timova(l.broj_timova), max_br_timova(l.broj_timova), timovi(nullptr){
            AlocirajNiz(max_br_timova);
            try{
                for(int i=0; i<broj_timova; i++) this->timovi[i] = new Tim(*l.timovi[i]);
            }catch(...){
                OcistiTimove();
                throw;
            }
        }

        Liga(Liga &&l):broj_timova(l.broj_timova), max_br_timova(l.broj_timova), timovi(nullptr){
            timovi = l.timovi;
            l.timovi = nullptr;
        }

        Liga &operator =(const Liga &l){
            if(max_br_timova!=l.max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
            if(&l==this) return *this;
            for(int i=0; i<broj_timova; i++) delete timovi[i];
            broj_timova=l.broj_timova;
            try{
                for(int i=0; i<broj_timova; i++) timovi[i] = new Tim(*l.timovi[i]);
            }catch(...){
                OcistiTimove();
                throw;
            }
            return *this;
        }

        Liga &operator =(Liga &&l){
            if(max_br_timova!=l.max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
            if(&l==this) return *this;
            timovi=l.timovi;
            broj_timova=l.broj_timova;
            l.timovi=nullptr;
            return *this;
        }

        void DodajNoviTim(const char ime_tima[]){
            if(broj_timova==max_br_timova) throw std::range_error("Liga popunjena");
            if(PronadjiTim(ime_tima)!=-1) throw std::logic_error("Tim vec postoji");
            if(std::strlen(ime_tima)>19) throw std::logic_error("Predugacko ime tima");
            try{
                timovi[broj_timova++]= new Tim(ime_tima);
            }catch(std::bad_alloc){
                broj_timova--;
                throw std::logic_error("Neuspjesno dodavanje tima u ligu");
            }catch(...){
                broj_timova--;
                throw;
            }
        }

        void RegistrirajUtakmicu(const char tim1[], const char tim2[], 
        int rezultat_1, int rezultat_2){
            if(PronadjiTim(tim1)==-1 || PronadjiTim(tim2)==-1) throw std::logic_error("Tim nije nadjen");
            timovi[PronadjiTim(tim1)]->ObradiUtakmicu(rezultat_1, rezultat_2);
            timovi[PronadjiTim(tim2)]->ObradiUtakmicu(rezultat_2, rezultat_1);
        }

        void IspisiTabelu(){
            std::sort(timovi, timovi+broj_timova, [](Tim *a, Tim *b){
                if(a->DajBrojPoena()==b->DajBrojPoena()){
                    if(a->DajGolRazliku()==b->DajGolRazliku()){
                    return std::strcmp(a->DajImeTima(), b->DajImeTima())<0;
                }else{
                    return a->DajGolRazliku()>b->DajGolRazliku();
                }}else{
                    return a->DajBrojPoena()>b->DajBrojPoena();
                }
            });
            for(int i=0; i<broj_timova; i++) timovi[i]->IspisiPodatke();
        }
};


int main ()
{
	return 0;
}