//TP 2021/2022: LV 14, Zadatak 3
#include <iostream>
#include <iomanip>
#include <cstring> //zbg strlen
#include <new>
#include <stdexcept>
#include <algorithm> //zbg sort
#include <string>
#include <cstdlib>
#include <fstream>

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
    int max_br_timova;
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
        void ObrisiSve()
        {
            for(int i=0; i<broj_timova; i++) delete timovi[i];
            broj_timova=0;
        }
        void SacuvajStanje(std::string datoteka)
        {
            std::ofstream izlaz(datoteka, std::ios::binary);
            if(!izlaz) throw std::logic_error("Problemi pri upisu u datoteku");
            izlaz.write(reinterpret_cast<char*>(&max_br_timova), sizeof(max_br_timova));
            izlaz.write(reinterpret_cast<char*>(&broj_timova), sizeof(broj_timova));
            for(int i=0; i<broj_timova; i++) izlaz.write(reinterpret_cast<char*>(timovi[i]), sizeof(Tim));
            if(!izlaz) throw std::logic_error("Problemi pri upisu u datoteku");
        }
        void AzurirajIzDatoteke(std::string datoteka)
        {
            std::ifstream ulaz(datoteka);
            if(!ulaz) throw std::logic_error("Datoteka ne postoji");
            std::string s1, s2;
            for(;;){
                std::getline(ulaz, s1);
                std::getline(ulaz, s2);
                int r1, r2;
                char x;
                ulaz>>r1>>x>>r2;
                if(!ulaz.eof()) ulaz.get();
                if(s1.size()>20 || s2.size()>20 || (!ulaz && !ulaz.eof()) || x!=':'){
                    throw std::logic_error("Problemi pri citanju datoteke");
                }
                try{
                    RegistrirajUtakmicu(s1.c_str(), s2.c_str(), r1, r2);
                }catch(...){
                    throw std::logic_error("Problemi pri citanju datoteke");
                }
                if(ulaz.eof()) break;
            }
        }

        Liga(std::string datoteka): max_br_timova(0)
        {
            std::ifstream ulaz(datoteka, std::ios::binary);
            if(!ulaz) throw std::logic_error("Datoteka ne postoji");
            ulaz.read(reinterpret_cast<char *>(&max_br_timova), sizeof(max_br_timova));
            ulaz.read(reinterpret_cast<char *>(&broj_timova), sizeof(broj_timova));
            if(!ulaz) throw std::logic_error("Problemi pri citanju datoteke");
            if(max_br_timova<broj_timova) throw std::logic_error("Datoteka sadrzi fatalne greske");
            timovi = new Tim*[broj_timova];
            for(int i=0; i<broj_timova; i++){
                try{
                    timovi[i] = new Tim("FK Sarajevo");
                    ulaz.read(reinterpret_cast<char *>(timovi[i]), sizeof(Tim));
                }catch(...){
                    for(int j=0; j<i; j++) delete timovi[i];
                    delete[] timovi;
                    throw std::bad_alloc();
                }
                if(!ulaz) throw std::logic_error("Problemi pri citanju datoteke");
            }
        }
};


int main ()
{
	return 0;
}