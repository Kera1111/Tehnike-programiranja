//TP 2021/2022: LV 14, Zadatak 2
#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <vector>
#include <type_traits>
#include <stdexcept>
#include <iterator>

class Spremnik {
    protected:
        char naziv[200];
        double tezina;
    public:
        Spremnik(const char* ime, double tezina):tezina(tezina){ std::strcpy(naziv,ime); }
        double DajTezinu() const { return tezina; }
        virtual double DajUkupnuTezinu() const = 0;
        virtual void Ispisi() const = 0;
        virtual ~Spremnik()=default;
        virtual Spremnik* DajKopiju() const = 0;      
};

class Sanduk : public Spremnik {
        int brojStvari;
        double tezinaStvari;
    public:
        Sanduk(double tezina, const char* naziv, int brojStvari, double tezinaStvari): Spremnik(naziv, tezina), brojStvari(brojStvari), tezinaStvari(tezinaStvari){}
        double DajUkupnuTezinu() const override { return DajTezinu()+brojStvari*tezinaStvari; }
        void Ispisi() const override { std::cout<<"Vrsta spremnika: Sanduk"<<std::endl<<"Sadrzaj: "<<Spremnik::naziv<<std::endl<<"Vlastita tezina: "<<Spremnik::DajTezinu()<<" kg"<<std::endl<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;}
        Spremnik *DajKopiju() const override { return new Sanduk(*this); }
};

class Bure : public Spremnik {
        double tezinaTecnosti;
    public:
        Bure(double tezina, const char* naziv, double tezinaTecnosti): Spremnik(naziv, tezina), tezinaTecnosti(tezinaTecnosti){}
        double DajUkupnuTezinu() const override { return DajTezinu()+tezinaTecnosti; }
        void Ispisi() const override { std::cout<<"Vrsta spremnika: Bure"<<std::endl<<"Sadrzaj: "<<Spremnik::naziv<<std::endl<<"Vlastita tezina: "<<Spremnik::DajTezinu()<<" kg"<<std::endl<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;}
        Spremnik *DajKopiju() const override { return new Bure(*this); }
};

class Skladiste {
    int maxBroj, brojSpremnika;
    Spremnik** spremnici; 
    void Testiraj() const { if(brojSpremnika==maxBroj)throw std::domain_error("Popunjeno skladiste"); }
    public:
        explicit Skladiste(int maxBroj) : maxBroj(maxBroj), brojSpremnika(0), spremnici(new Spremnik*[maxBroj]{}) {}
        ~Skladiste() { 
           {
            if(spremnici==nullptr) return;
        }
            for (int i=0;i<maxBroj;i++) delete spremnici[i]; delete[] spremnici; }
        Skladiste(const Skladiste &s);
        Skladiste(Skladiste &&s);
        Skladiste& operator =(const Skladiste &s);
        Skladiste& operator =(Skladiste &&s);
        void DodajSanduk(double tezina, const char* naziv, int brojStvari, double tezinaStvari){
            Testiraj();
            spremnici[brojSpremnika++]= new Sanduk(tezina, naziv, brojStvari, tezinaStvari);
        }
        void DodajBure(double tezina, const char *naziv, double tezinaTecnosti){
            Testiraj();
            spremnici[brojSpremnika++]= new Bure(tezina, naziv, tezinaTecnosti); 
        }
        Spremnik& DajNajtezi(){
            if(brojSpremnika==0) throw std::range_error("Skladiste je prazno");
            return **std::max_element(spremnici, spremnici+brojSpremnika, 
            [](Spremnik *s1, Spremnik *s2){
                return (s1->DajTezinu()<s2->DajTezinu());
            });
        }
        Spremnik& DajNajlaksi(){
            if(brojSpremnika==0) throw std::range_error("Skladiste je prazno");
            return **std::min_element(spremnici, spremnici+brojSpremnika, 
            [](Spremnik *s1, Spremnik *s2){
                return (s1->DajTezinu()<s2->DajTezinu());
            });
        }
        int BrojPreteskih(int broj) const {
            int brojPreteskih = 0;
            for(int i=0; i<brojSpremnika; i++) if(spremnici[i]->DajUkupnuTezinu()>broj) brojPreteskih++;
            return brojPreteskih;
        }
        void IzlistajSkladiste()  const{
            std::vector<Spremnik*> pomocni;
            std::copy(spremnici, spremnici+brojSpremnika, std::back_inserter(pomocni));
            std::sort(pomocni.begin(), pomocni.end(), 
            [](Spremnik* s1, Spremnik *s2){
                return s1->DajUkupnuTezinu()>s2->DajUkupnuTezinu();
            });
            std::for_each(pomocni.begin(),pomocni.end(), [](Spremnik *s1){ s1->Ispisi();});
        }
        void UcitajIzDatoteke(const std::string& s);
};

Skladiste::Skladiste(const Skladiste &s):maxBroj(s.maxBroj), brojSpremnika(s.brojSpremnika), spremnici(new Spremnik*[s.maxBroj]{}){
    try{
        for(int i=0; i<s.brojSpremnika; i++) spremnici[i] = s.spremnici[i]->DajKopiju();
    }catch(...){
        for(int i=0; i<s.brojSpremnika; i++) delete spremnici[i];
        delete[] spremnici;
        throw;
    }
}

Skladiste::Skladiste(Skladiste &&s):maxBroj(s.maxBroj), brojSpremnika(s.brojSpremnika), spremnici(s.spremnici){
    s.spremnici = nullptr;
}

Skladiste& Skladiste::operator =(const Skladiste &s){
    Spremnik** novi = new Spremnik *[s.maxBroj]{};
    try{
        for(int i=0; i<s.brojSpremnika; i++) novi[i]=s.spremnici[i]->DajKopiju();
        for(int i=0; i<brojSpremnika; i++) delete spremnici[i];
        delete[] spremnici;
        brojSpremnika = s.brojSpremnika; 
        maxBroj = s.maxBroj;
        spremnici = novi;
    }catch(...){
        for(int i=0; i<s.brojSpremnika; i++){
            delete novi[i];
        }
        delete[] novi;
        throw;
    }
    return *this;
}

Skladiste& Skladiste::operator =(Skladiste &&s){
    std::swap(spremnici, s.spremnici);
    std::swap(maxBroj, s.maxBroj);
    std::swap(brojSpremnika, s.brojSpremnika);
    return *this;
}

void Skladiste::UcitajIzDatoteke(const std::string &s){
    std::ifstream datoteka(s);
    if(!datoteka) throw std::logic_error("Trazena datoteka ne postoji");
    for(int i=0; i<brojSpremnika; i++) delete spremnici[i];
    delete[] spremnici;
    std::string redDatoteke;
    int brojac = 0;
    while(std::getline(datoteka, redDatoteke)) brojac++;
    datoteka.clear();
    datoteka.seekg(0);
    maxBroj = brojac/2;
    spremnici = new Spremnik*[maxBroj]{};
    brojSpremnika = 0;
    char znak1, znak2;
    char ime[200];
    while(datoteka>>znak1 && datoteka.get(znak2) && datoteka.getline(ime, sizeof ime)){
        if(znak1=='S'){
            double tezinaSanduka, tezinaPredmeta;
            int brojSanduka;
            datoteka>>tezinaSanduka>>brojSanduka>>tezinaPredmeta;
            if(!datoteka) throw std::logic_error("Datoteka sadrzi besmislene podatke");
            spremnici[brojSpremnika++]=new Sanduk(tezinaSanduka,ime,brojSanduka,tezinaPredmeta);
            datoteka.ignore(10,'\n');
        }else if(znak1=='B'){
            double tezinaBureta, tezinaTecnosti;
            datoteka>>tezinaBureta>>tezinaTecnosti;
            if(!datoteka) throw std::logic_error("Datoteka sadrzi besmislene podatke");
            spremnici[brojSpremnika++]=new Bure(tezinaBureta,ime,tezinaTecnosti);
            datoteka.ignore(10,'\n');
        }else throw std::logic_error("Datoteka sadrzi besmislene podatke");
    }
    if(datoteka.bad()) throw std::logic_error("Problemi pri citanju datoteke");
}

int main ()
{
	return 0;
}
