/* 
    TP 16/17 (LV 11, Zadatak 5)
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
#include <vector>
#include <memory>

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
    //Tim** timovi;
    std::vector<std::shared_ptr<Tim>> timovi;
    static bool PronadjiTim(const char* ime_tima);
    public:
      explicit Liga(){};
      explicit Liga(std::initializer_list<Tim> lista_timova) : timovi(lista_timova.size()){
          for(int i=0; i<timovi.size(); i++){
              timovi[i] = std::make_shared<Tim> (lista_timova.begin()[i]);
                   } 
               }
               //operator dodjele moze se naknadno koristit lupam 2 vektora hos da su jednaki onda koristis ovaj operator, a ako hoces da inicijalizujes tj kopiras onda koristis konstruktor
      Liga(const Liga &l);
      Liga(Liga &&l);
      Liga &operator =(const Liga &l);
      Liga &operator =(Liga &&l);
      void DodajNoviTim(const char ime_tima[]);
      void RegistrirajUtakmicu(const char tim1[], const char tim2[],
                               int rezultat_1, int rezultat_2);
      void IspisiTabelu();
};

        static bool f(std::shared_ptr<const Tim> tim1, std::shared_ptr<const Tim> tim2){
            if(tim1->DajBrojPoena() > tim2->DajBrojPoena()){
                return tim1->DajBrojPoena() >tim2->DajBrojPoena();
            }
else if(tim1->DajBrojPoena() ==tim2->DajBrojPoena()){
     if(tim1->DajGolRazliku() > tim2->DajGolRazliku()) return tim1-> DajGolRazliku() >tim2->DajGolRazliku();
     if(tim1->DajGolRazliku() ==tim2->DajGolRazliku()){
         std::string s1(tim1->DajImeTima()), s2(tim2->DajImeTima()); 
         return s1 < s2;
     }
}
return tim1->DajBrojPoena() >tim2->DajBrojPoena();
        }
/*
        Liga::Liga(): timovi(nullptr){
            AlocirajNiz(max_br_timova);
        }
*/
/*
        Liga::Liga(const std::initializer_list<Tim> lista_timova):timovi.size()lista_timova.size()), timovi(nullptr){
            int brojac = 0;
            try{
                for(const auto &x: lista_timova) timovi[brojac++] = new Tim(x);
                //timovi = new Tim*[broj_timova];
                //for(int i=0; i<broj_timova; i++) timovi[i]=nullptr;
                //for(auto &x: lista_timova) timovi[brojac++]=new Tim(x);
            }catch(...){
                OcistiTimove();
                throw;
            }
        }
*/
/*
        Liga::~Liga(){
            //if(timovi==nullptr) return;
            for(int i=0; i<timovi.size(); i++) delete timovi[i];
            //delete[] timovi;
        }
*/
/*
        Liga::Liga(const Liga &l): broj_timova(l.broj_timova), max_br_timova(l.max_br_timova, timovi(nullptr){
            AlocirajNiz(max_br_timova);
            try{
                for(int i=0; i<broj_timova; i++) this->timovi[i] = new Tim(*l.timovi[i]);
            }catch(...){
                OcistiTimove();
                throw;
            }
        }
*/
     Liga::Liga(const Liga &l){
         timovi.resize((l.timovi).size());
         for(int i=0; i < (l.timovi).size(); i++)   
            timovi[i] = std::make_shared<Tim>(*l.timovi[i]);
     }
/*
        Liga::Liga(Liga &&l): timovi(nullptr){
            //uzimamo podatke od objekta koji uskoro "umire" (l.timovi)
            timovi = l.timovi;
            l.timovi = nullptr;
            l.broj_timova = 0;
        }
*/
Liga::Liga(Liga &&l) : timovi(l.timovi) {
    (l.timovi).resize(0);
}

Liga &Liga::operator =(const Liga &l){
           /* if(max_br_timova!=l.max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
            *
            if(&l==this){
            for(int i=0; i<broj_timova; i++) delete timovi[i];
            broj_timova=l.broj_timova;
            try{
                for(int i=0; i<broj_timova; i++) timovi[i] = new Tim(*l.timovi[i]);
            }catch(...){
                OcistiTimove();
                throw;
            }}*/
            timovi.resize((l.timovi).size());
            if(&l != this){
                for(int i=0; i<(l.timovi).size(); i++){
                    timovi[i] = std::make_shared<Tim>(*l.timovi[i]);
                }
            }
            return *this;
        }

        Liga &Liga::operator =(Liga &&l){
            /*if(max_br_timova!=l.max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
            if(&l==this){
                OcistiTimove();
                timovi=l.timovi;
                broj_timova=l.broj_timova;
                l.timovi=nullptr;
                l.broj_timova=0;
            */
            timovi.resize((l.timovi).size());
            if(&l != this){
                timovi = l.timovi;
                (l.timovi).resize(0);
        }
            return *this;
        }

void Liga::DodajNoviTim(const char ime_tima[]){
           /* if(broj_timova==max_br_timova) throw std::range_error("Liga popunjena");
            if(PronadjiTim(ime_tima)!=-1) throw std::logic_error("Tim vec postoji");
            if(std::strlen(ime_tima)>19) throw std::logic_error("Predugacko ime tima");
            try{
                timovi[broj_timova++]= new Tim(ime_tima);
            }catch(std::bad_alloc){
                broj_timova--;
                throw std::domain_error("Neuspjesno dodavanje tima u ligu");
            }catch(...){
                broj_timova--;
                throw;
            }
        }
*/
if(strlen(ime_tima) >=20) throw std::range_error("Predugacko ime tima");
for(int i=0; i<timovi.size(); i++){
    if(!strcmp(ime_tima,timovi[i]->DajImeTima())) throw std::logic_error("Tim vec postoji");
}
timovi.push_back( std::make_shared<Tim>(ime_tima) );
}

void Liga::RegistrirajUtakmicu(const char tim1[], const char tim2[], 
        int rezultat_1, int rezultat_2){
            /*if(PronadjiTim(tim1)==-1 || PronadjiTim(tim2)==-1) throw std::domain_error("Tim nije nadjen");
            timovi[PronadjiTim(tim1)]->ObradiUtakmicu(rezultat_1, rezultat_2);
            timovi[PronadjiTim(tim2)]->ObradiUtakmicu(rezultat_2, rezultat_1);
        }
*/
       int i, j;
       for( i=0; i<timovi.size(); i++){
              if( !strcmp(tim1, timovi[i]->DajImeTima()) ) break;
       }
       for( j=0;j<timovi.size(); j++){
           if( !strcmp(tim2, timovi[j]->DajImeTima()) ) break;
       }
    if(i == timovi.size() || j==timovi.size()) throw std::logic_error("Tim nije nadjen");
    if(rezultat_1<0 || rezultat_2<0) throw std::range_error("Neispravan broj golova");
timovi[i]->ObradiUtakmicu(rezultat_1, rezultat_2);
timovi[j]->ObradiUtakmicu(rezultat_2, rezultat_1);
        }


void Liga::IspisiTabelu(){
            /*std::sort(timovi, timovi+broj_timova, [](Tim *a, Tim *b){
                if(a->DajBrojPoena()==b->DajBrojPoena()){
                    return a->DajGolRazliku()>b->DajGolRazliku();
                return a->DajBrojPoena()>b->DajBrojPoena();    
            });
            for(int i=0; i<broj_timova; i++) timovi[i]->IspisiPodatke();
        */
       std::sort(timovi.begin(), timovi.end(), f);
       for(int i=0; i<timovi.size(); i++){
           timovi[i]->IspisiPodatke(); 
        }
}

int main ()
{
    
	return 0;
}
