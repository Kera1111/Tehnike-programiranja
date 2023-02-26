//TP 2021/2022: Zadaća 4, Zadatak 2
#include <cstddef>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <tuple>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>

double PI=std::atan(1)*4;
long double E=1e-10;
int broj_presjecanja=0;
int j=0;
int broj_napravljenih=0;

class NepreklapajucaKugla{
    double x,y,z,r;
    NepreklapajucaKugla* prethodna=nullptr;
    static NepreklapajucaKugla* posljednja;
    void ProvjeriR(double r){
        if(r<0) throw std::domain_error("Ilegalan poluprecnik");
    }
    void ProvjeriPreklapanje(double x, double y, double z, double r,bool unos){
        bool izvana=true,identicne=true,koncentricne=true,iznutra=true,sadrzi=true,sijeku=false;
        double C1C2=0,r_zbir=0,abs_r_razlika=0,r_razlika=0;
        for(auto it=posljednja;it!=nullptr;it=it->prethodna){
            if(it==this) {goto preskok;}
            izvana=false;
            identicne=false;
            koncentricne=false;
            iznutra=false;
            sadrzi=true;
            sijeku=false;
            C1C2=sqrt(pow(it->x-x,2)+pow(it->y-y,2)+pow(it->z-z,2));
            r_zbir=r+it->r;
            abs_r_razlika=fabs(r-it->r);
            r_razlika=0;
            if(r>it->r) r_razlika=r-it->r; else r_razlika=it->r-r;
            
            //dodirivanje izvana
            if(fabs(r_zbir-C1C2)<E*(fabs(r_zbir)+fabs(C1C2))){
                izvana=true;
            }
            //Ako se dodiruju iznutra
            if(fabs(abs_r_razlika-C1C2)<E*(fabs(abs_r_razlika)+fabs(C1C2))){
                iznutra=true;
            }
            //Ako su koncentricne
            if(fabs(x-it->x)<E*(fabs(x)+fabs(it->x)) && fabs(y-it->y)<E*(fabs(y)+fabs(it->y)) && fabs(z-it->z)<E*(fabs(z)+fabs(it->z))){
                koncentricne=true;
            }
            //Ako su identicne
            if(fabs(it->r-r)<E*(fabs(it->r)+fabs(r)) && fabs(x-it->x)<E*(fabs(x)+fabs(it->x)) && fabs(y-it->y)<E*(fabs(y)+fabs(it->y)) && fabs(z-it->z)<E*(fabs(z)+fabs(it->z))){
                identicne=true;
            }
            //Ako jedna sadrzi drugu
            if(r_razlika<C1C2){
                sadrzi=false;
            }
            //Ako se sijeku
            if(C1C2<r_zbir || fabs(C1C2-r_zbir)<E*(fabs(C1C2)+fabs(r_zbir))){
                sijeku=true;
            }

            if(sijeku==true || sadrzi==true || koncentricne==true || iznutra==true || identicne==true || izvana==true){
                if(unos==true){
                    posljednja=this->prethodna;
                    this->prethodna=nullptr;
                    throw std::logic_error("Nedozvoljeno preklapanje");
                }
                else{
                    throw std::logic_error("Nedozvoljeno preklapanje");
                }
            }
            preskok:;
        }
    }
    public:
    NepreklapajucaKugla (const NepreklapajucaKugla& k)=delete;
    NepreklapajucaKugla operator=(const NepreklapajucaKugla& k)=delete;
    explicit NepreklapajucaKugla(double r = 0){
        try{ProvjeriR(r);}catch(...){throw;}
        if(broj_napravljenih==0){
            posljednja=this;
        }
        if(broj_napravljenih>0){
            prethodna=posljednja;
            posljednja=this;
        }
        if(broj_napravljenih>0)try{ProvjeriPreklapanje(x=0,y=0,z=0,r,true);}catch(...){throw;}
        NepreklapajucaKugla::r=r;
        x=0; y=0; z=0;
        broj_napravljenih++;
    }
    NepreklapajucaKugla(double x, double y, double z, double r = 0){
        try{ProvjeriR(r);}catch(...){throw;}
        if(broj_napravljenih==0){
            posljednja=this;
        }
        if(broj_napravljenih>0){
            prethodna=posljednja;
            posljednja=this;
        }
        if(broj_napravljenih>0)try{ProvjeriPreklapanje(x,y,z,r,true);}catch(...){throw;}
        NepreklapajucaKugla::r=r;
        NepreklapajucaKugla::x=x; NepreklapajucaKugla::y=y; NepreklapajucaKugla::z=z;
        broj_napravljenih++;
    }
    explicit NepreklapajucaKugla(const std::tuple<double, double, double> &centar, double r = 0){
        try{ProvjeriR(r);}catch(...){throw;}
        if(broj_napravljenih==0){
            posljednja=this;
        }
        if(broj_napravljenih>0){
            prethodna=posljednja;
            posljednja=this;
        }
        if(broj_napravljenih>0)try{ProvjeriPreklapanje(std::get<0>(centar),std::get<1>(centar),std::get<2>(centar),r,true);}catch(...){throw;}
        NepreklapajucaKugla::r=r;
        x=std::get<0>(centar); y=std::get<1>(centar); z=std::get<2>(centar);
        broj_napravljenih++;
    }
    double DajX() const{
        return x;
    }
    double DajY() const{
        return y;
    }
    double DajZ() const{
        return z;
    }
    std::tuple<double, double, double> DajCentar() const{
        std::tuple<double, double, double> centar(DajX(),DajY(),DajZ());
        return centar;
    }
    double DajPoluprecnik() const{
        return r;
    }
    double DajPovrsinu() const{
        return pow(r,2)*PI*4;
    }
    double DajZapreminu() const{
        return pow(r,3)*PI*4./3;
    }
    NepreklapajucaKugla &PostaviX(double x){
        if(broj_napravljenih>1)try{ProvjeriPreklapanje(x,y,z,r,false);}catch(...){throw;}        
        NepreklapajucaKugla::x=x;
        return *this;
    }
    NepreklapajucaKugla &PostaviY(double y){
        if(broj_napravljenih>1)try{ProvjeriPreklapanje(x,y,z,r,false);}catch(...){throw;}
        NepreklapajucaKugla::y=y;
        return *this;
    }
    NepreklapajucaKugla &PostaviZ(double z){
        if(broj_napravljenih>1)try{ProvjeriPreklapanje(x,y,z,r,false);}catch(...){throw;}
        NepreklapajucaKugla::z=z;
        return *this;
    }
    NepreklapajucaKugla &PostaviCentar(double x, double y, double z){
        if(broj_napravljenih>1)try{ProvjeriPreklapanje(x,y,z,r,false);}catch(...){throw;}
        NepreklapajucaKugla::x=x;
        NepreklapajucaKugla::y=y;
        NepreklapajucaKugla::z=z;
        return *this;
    }
    NepreklapajucaKugla &PostaviCentar(const std::tuple<double, double, double> &centar){
        if(broj_napravljenih>1)try{ProvjeriPreklapanje(std::get<0>(centar),std::get<1>(centar),std::get<2>(centar),r,false);}catch(...){throw;}
        x=std::get<0>(centar); y=std::get<1>(centar); z=std::get<2>(centar);
        return *this;
    }
    NepreklapajucaKugla &PostaviPoluprecnik(double r){
        try{ProvjeriR(r);}catch(...){throw;}
        if(broj_napravljenih>1)try{ProvjeriPreklapanje(x,y,z,r,false);}catch(...){throw;}
        NepreklapajucaKugla::r=r;
        return *this;
    }
    ~NepreklapajucaKugla(){
        auto pok(posljednja);
        if(pok==this){
            posljednja=this->prethodna;
            this->prethodna=nullptr;
        }
        else{
            while(pok->prethodna!=this) pok=pok->prethodna;
            pok->prethodna=this->prethodna;
        }
    }
    void Ispisi() const{
        std::cout<<"{("<<x<<","<<y<<","<<z<<"),"<<r<<"}"<<std::endl;
    }
    void Transliraj(double delta_x, double delta_y, double delta_z){
        x+=delta_x; y+=delta_y; z+=delta_z;
        if(broj_napravljenih>1)try{ProvjeriPreklapanje(x,y,z,r,false);}catch(...){
            x-=delta_x; y-=delta_y; z-=delta_z;
            throw;}
    }
    bool DaLiSadrzi(const NepreklapajucaKugla &k) const{
        double duzina1=r-k.r,duzina2=sqrt(pow(k.x-x,2)+pow(k.y-y,2)+pow(k.z-z,2));
        if(duzina1<duzina2) return true;
        return false;
    }
    friend double RastojanjeCentara(const NepreklapajucaKugla &k1, const NepreklapajucaKugla &k2);
};

double RastojanjeCentara(const NepreklapajucaKugla &k1, const NepreklapajucaKugla &k2){
    return sqrt(pow(k2.x-k1.x,2)+pow(k2.y-k1.y,2)+pow(k2.z-k1.z,2));
}


NepreklapajucaKugla* NepreklapajucaKugla::posljednja(nullptr);

int main ()
{
    int n;
    std::cout<<"Unesite broj kugli: "; 
    pocetak:;
    std::cin>>n;
    if(n<1){
        std::cout<<"Neispravan broj kugli, unesite ponovo! ";
        goto pocetak;
    }
    std::vector<std::shared_ptr<NepreklapajucaKugla>> v(n);
    for(int i=0;i<n;i++){
        unos:;
        std::cout<<"Unesite centar za "<<i+1<<". kuglu: ";
        double x,y,z;
        unos_centra:;
        std::cin>>x>>y>>z;
        if(!std::cin){
            std::cout<<"Neispravan centar, unesite ponovo: ";
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            goto unos_centra;
        }
        std::cin.ignore(1000,'\n');
        std::cout<<"Unesite poluprecnik: ";
        unos_poluprecnika:;
        double r;
        std::cin>>r;
        if(!std::cin){
            std::cout<<"Neispravan poluprecnik, unesite ponovo: ";
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            goto unos_poluprecnika;
        }
        std::cin.ignore(1000,'\n');
        try{
            v.at(i)=std::shared_ptr<NepreklapajucaKugla>(new NepreklapajucaKugla(x,y,z,r));;
        }
        catch(std::domain_error error){
            std::cout<<"Neispravan poluprecnik, unesite ponovo: ";
            goto unos_poluprecnika;
        }
        catch(std::logic_error error){
            std::cout<<error.what()<<std::endl;
            goto unos;
        }
    }
    std::sort(v.begin(),v.end(),[](std::shared_ptr<NepreklapajucaKugla> k1,std::shared_ptr<NepreklapajucaKugla> k2){
        if(k1->DajPovrsinu()>k2->DajPovrsinu()) return false;
        else if(fabs(k1->DajPovrsinu()-k2->DajPovrsinu())<E*(fabs(k1->DajPovrsinu())+fabs(k2->DajPovrsinu()))){
            if(sqrt(pow(k1->DajX(),2)+pow(k1->DajY(),2)+pow(k2->DajZ(),2))<sqrt(pow(k2->DajX(),2)+pow(k2->DajY(),2)+pow(k2->DajZ(),2))) return true;
            return false;
        }
        return true;
    });
    std::cout<<"Kugle nakon obavljenog sortiranja: ";
    std::for_each(v.begin(),v.end(),[](std::shared_ptr<NepreklapajucaKugla> k){
        k->Ispisi();
    });
	return 0;
}