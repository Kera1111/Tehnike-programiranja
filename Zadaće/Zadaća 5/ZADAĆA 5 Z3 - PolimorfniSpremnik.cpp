//TP 2021/2022: Zadaća 5, Zadatak 4
#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <vector>
#include <type_traits>
#include <stdexcept>
#include <iterator>
#include <string>
#include <memory>

using namespace std;

class Spremnik {
    protected:
        string ime;
        double tezina;
    public:
        friend class PolimorfniSpremnik;
        Spremnik(double tezinaSpremnika, string naziv):tezina(tezinaSpremnika),ime(naziv){}
        double DajTezinu() const { return tezina; }
        virtual double DajUkupnuTezinu() const = 0;
        virtual void Ispisi() const = 0;
        virtual ~Spremnik() = default;
        virtual Spremnik* DajKopiju() const = 0;      
};

class Sanduk : public Spremnik {
        vector<double> tezine;
    public:
        Sanduk(double tezina, string ime, vector<double> tezine): Spremnik(tezina, ime), tezine(tezine){}
        double DajUkupnuTezinu() const override { 
            double tezinaSanduka = DajTezinu();
            for(int i=0; i<tezine.size(); i++){
                tezinaSanduka+=tezine[i];
            }
            return tezinaSanduka;//ukupna tezina
        }
        
        void Ispisi() const override { 
            cout<<"Vrsta spremnika: Sanduk"<<endl
            <<"Sadrzaj: "<<ime<<endl;
            cout<<"Tezine predmeta: ";
            for(int i=0; i<tezine.size(); i++) cout<<tezine[i]<<" ";
            cout<<" (kg)"<<endl
            <<"Vlastita tezina: "<<DajTezinu()<<" (kg)"<<endl
            <<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)"<<endl;
        }
        
        Sanduk *DajKopiju() const override { return new Sanduk(*this); }
};

class Bure : public Spremnik {
        double specTezina, zapremina;
    public:
        Bure(double tezina, string naziv, double specTezina, double zapremina): Spremnik(tezina, naziv), specTezina(specTezina), zapremina(zapremina){}
        double DajUkupnuTezinu() const override { return DajTezinu()+(specTezina*zapremina)/1000; }
        void Ispisi() const override { 
            cout<<"Vrsta spremnika: Bure"<<endl
            <<"Sadrzaj: "<<ime<<endl
            <<"Vlastita tezina: "<<DajTezinu()<<" (kg)"<<endl
            <<"Specificna tezina tecnosti: "<<specTezina<<" (kg/m^3)"<<endl
            <<"Zapremina tecnosti: "<<zapremina<<" (l)"<<endl
            <<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)"<<endl;}
        Bure *DajKopiju() const override { return new Bure(*this); }
};

class Vreca : public Spremnik {
    double tezinaPraha;
    public:
        Vreca(double tezina, string ime, double tezinaPraha): Spremnik(tezina, ime), tezinaPraha(tezinaPraha){}
        double DajUkupnuTezinu() const override { return DajTezinu()+tezinaPraha; }
        Vreca *DajKopiju() const override { return new Vreca(*this); }
        void Ispisi() const override { 
            cout<<"Vrsta spremnika: Vreca"<<endl
            <<"Sadrzaj: "<<ime<<endl
            <<"Vlastita tezina: "<<DajTezinu()<<" (kg)"<<endl
            <<"Tezina pohranjene materije: "<<tezinaPraha<<" (kg)"<<endl
            <<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)"<<endl;
        }
};

class Skladiste {
    vector<shared_ptr<Spremnik>> vektor;
    public:
        explicit Skladiste() {}
        Skladiste(const Skladiste &s);
        Skladiste(Skladiste &&s);
        Skladiste& operator =(const Skladiste &s);
        Skladiste& operator =(Skladiste &&s);
        Spremnik *DodajSanduk(double tezina, string ime, vector<double> tezine)
        {
            Sanduk *pomocni = new Sanduk(tezina, ime, tezine);
            vektor.push_back(shared_ptr<Spremnik>(pomocni));
            return pomocni;
        }
        Spremnik *DodajBure(double tezina, string ime, double specTezina, double zapremina)
        {
            Bure *pomocni = new Bure(tezina, ime, specTezina, zapremina);
            vektor.push_back(shared_ptr<Spremnik>(pomocni));
            return pomocni;
        }
        Spremnik *DodajVrecu(double tezina, string ime, double tezinaPraha)
        {
            Vreca *pomocni = new Vreca(tezina, ime, tezinaPraha);
            vektor.push_back(shared_ptr<Spremnik>(pomocni));
            return pomocni;
        }
        Spremnik *DodajSpremnik(Spremnik* pok, bool jest)
        {
            if(jest){
                Spremnik *pomocni = pok->DajKopiju(); delete pok;
                vektor.push_back(shared_ptr<Spremnik>(pomocni));
                return pomocni;
            }else{
                Spremnik *pomocni = pok->DajKopiju();
                vektor.push_back(shared_ptr<Spremnik>(pomocni));
                return pomocni;
            }
        }
        Spremnik& DajNajtezi(){
            if(vektor.size()==0) throw std::range_error("Skladiste je prazno");
            auto it = max_element(vektor.begin(), vektor.end(), 
            [](shared_ptr<Spremnik> s1, shared_ptr<Spremnik> s2){
                return (s1->DajTezinu()<s2->DajTezinu());
            });
            return **it;
        }
        Spremnik& DajNajlaksi(){
            if(vektor.size()==0) throw std::range_error("Skladiste je prazno");
            auto it = min_element(vektor.begin(), vektor.end(), 
            [](shared_ptr<Spremnik> s1, shared_ptr<Spremnik> s2){
                return (s1->DajTezinu()<s2->DajTezinu());
            });
            return **it;
        }
        int BrojPreteskih(int broj) const {
            return count_if(vektor.begin(), vektor.end(),[broj](shared_ptr<Spremnik> p1){
                if(p1->DajUkupnuTezinu()>broj) return true;
                return false;
            });
        }
        void IzlistajSkladiste()  const{
            auto kopija = vektor;
            sort(kopija.begin(), kopija.end(), [](shared_ptr<Spremnik> p1, shared_ptr<Spremnik> p2){
                return p1->DajUkupnuTezinu()>p2->DajUkupnuTezinu();
            });
            for(auto x : kopija) x->Ispisi();
        }
        void UcitajIzDatoteke(string ime);
        void BrisiSpremnik(Spremnik *m)
        {
            for(int i=0; i<vektor.size(); i++){
                if(m==vektor[i].get()){
                    vektor.erase(vektor.begin()+i);
                    break;
                }
            }
        }
};

Skladiste::Skladiste(const Skladiste &s){
   for(auto x : s.vektor){
       vektor.push_back(shared_ptr<Spremnik>(x->DajKopiju()));
   }
}

Skladiste::Skladiste(Skladiste &&s){
   swap(vektor, s.vektor);
   s.vektor.resize(0);
}

Skladiste& Skladiste::operator =(const Skladiste &s){
    for(auto x : vektor) x = nullptr;
    vektor.resize(0);
    for(auto x : s.vektor){
        vektor.push_back(shared_ptr<Spremnik>(x->DajKopiju()));
    }
    return *this;
}

Skladiste& Skladiste::operator =(Skladiste &&s){ 
    swap(vektor, s.vektor);
    return *this;
}

void Skladiste::UcitajIzDatoteke(string s){
    ifstream datoteka(s);
    if(!datoteka) throw logic_error("Trazena datoteka ne postoji");
    
    string naziv;
    char znak;
    double tezina;
    while(1){;
        znak = datoteka.get();
        if(!datoteka) break;
        getline(datoteka, naziv);
        if(znak=='S'){
            int brpred;
            double tezina;
            vector<double> tezine;
            datoteka>>tezina>>brpred;
            for(int i=0; i<brpred; i++){
                double element;
                datoteka>>element;
                if(!datoteka && !datoteka.eof() && !datoteka.bad()) throw logic_error("Datoteka sadrzi besmislene podatke");
                tezine.push_back(element);
            }
            DodajSanduk(tezina,naziv,tezine);
        }else if(znak=='B'){
            double specTezina, zapremina;
            datoteka>>specTezina>>zapremina;
            if(!datoteka && !datoteka.eof() && !datoteka.bad()) throw logic_error("Datoteka sadrzi besmislene podatke");
            DodajBure(tezina, naziv, specTezina, zapremina);
        }else if(znak=='V'){
            double tezinaPraha;
            datoteka>>tezinaPraha;
            if(!datoteka && !datoteka.eof() && !datoteka.bad()) throw logic_error("Datoteka sadrzi besmislene podatke");
            DodajVrecu(tezina, naziv, tezinaPraha);
        }    
    if(datoteka.bad()) throw logic_error("Problemi pri citanju datoteke");
    else if(!datoteka.eof() && !datoteka.bad()) throw logic_error("Datoteka sadrzi besmislene podatke");
}
}

class PolimorfniSpremnik {
        Spremnik *s;
        void TestirajUnos() const{
            if(!s) throw logic_error("Nespecificiran spremnik");
        }
    public:
        PolimorfniSpremnik() : s(nullptr){}
        ~PolimorfniSpremnik(){delete s;}
        PolimorfniSpremnik(const PolimorfniSpremnik &p){s=p.s->DajKopiju();}
        PolimorfniSpremnik(PolimorfniSpremnik &&p){s=p.s; p.s=nullptr;}
        PolimorfniSpremnik &operator =(const PolimorfniSpremnik &p);
        PolimorfniSpremnik &operator =(PolimorfniSpremnik &&p){swap(s,p.s); return *this;}
        PolimorfniSpremnik(const Spremnik &spremnik){
            s=spremnik.DajKopiju();
        }
        /*
        PolimorfniSpremnik(const Sanduk &sa){s=sa.DajKopiju();}
        PolimorfniSpremnik(Sanduk &&sa){s=sa.DajKopiju();}
        PolimorfniSpremnik(const Vreca &v){s=v.DajKopiju();}
        PolimorfniSpremnik(Vreca &&v){s=v.DajKopiju();}
        PolimorfniSpremnik(const Bure &b){s=b.DajKopiju();}
        PolimorfniSpremnik(Bure &&b){s=b.DajKopiju();}
        */

        double DajTezinu() const { TestirajUnos(); return s->tezina;}
        double DajUkupnuTezinu() const { TestirajUnos(); return s->DajUkupnuTezinu();}
        void Ispisi() const { TestirajUnos(); s->Ispisi();}
};

int main ()
{
    try{
        PolimorfniSpremnik s1(Bure(5,"Benzin", 930, 70)); // s1 je bure
        PolimorfniSpremnik s2, s3; // s2 i s3 su nespecificirani
        s2 = Sanduk(3, "Tepsije", {0.5, 0.8, 0.6, 0.5}); // s2 je sada sanduk
        s3 = Vreca(0.4, "Brasno", 30); // a s3 vreca
        std::cout << s1.DajTezinu() << std::endl;
        std::cout << s2.DajUkupnuTezinu() << std::endl;
        s3.Ispisi();
        s1 = s2; // sad je i s1 sanduk...
        s1.Ispisi(); 
    }catch(logic_error &e){
        cout<<e.what()<<endl;
    }
    
	return 0;
}

PolimorfniSpremnik &PolimorfniSpremnik::operator =(const PolimorfniSpremnik &p){
    Spremnik *noviProstor = nullptr;
    if(p.s) noviProstor = p.s->DajKopiju();
    delete s;
    s=noviProstor;
    return *this;
}