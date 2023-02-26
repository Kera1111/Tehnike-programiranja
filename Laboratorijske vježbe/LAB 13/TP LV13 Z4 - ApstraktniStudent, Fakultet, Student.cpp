/* 
    TP 16/17 (LV 13, Zadatak 4)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>

using namespace std;

class ApstraktniStudent {
        string ime, prezime;
        int index, bpi;
        double prosjek;
    public:
        virtual ~ApstraktniStudent() {}
        ApstraktniStudent(string ime, string prezime, int index):ime(ime), prezime(prezime), index(index), bpi(0), prosjek(5) {}
        string DajIme() const {
            return ime;
        }
        string DajPrezime()  const {
            return prezime;
        }
        int DajBrojIndeksa() const {
            return index;
        }
        int DajBrojPolozenih() const {
            return bpi;
        }
        double DajProsjek() const {
            return prosjek;
        }
        void RegistrirajIspit(int ocjena){
            if(ocjena>=5 && ocjena<=10){
                if(ocjena!=5){
                    double suma = prosjek*bpi;
                    bpi++;
                    suma+=ocjena;
                    prosjek = suma/bpi;
                }
            }else throw domain_error("Neispravna ocjena");
        }
        void PonistiOcjene() {
            bpi = 0;
            prosjek = 5;
        }
        virtual void IspisiPodatke() const = 0;
        virtual ApstraktniStudent *DajKopiju() const = 0;
};

class StudentBachelor : public ApstraktniStudent {
    public: 
        StudentBachelor(string ime, string prezime, int index): ApstraktniStudent(ime, prezime, index){}
        void IspisiPodatke() const {
            cout<<"Student bachelor studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<","<<endl<<"ima prosjek "<<DajProsjek()<<"."<<endl;
        }
        StudentBachelor *DajKopiju() const {
            return new StudentBachelor(*this);
        }
};

class StudentMaster : public ApstraktniStudent {
        int zavrsio;
    public:
        StudentMaster(string ime, string prezime, int index, int god): ApstraktniStudent(ime, prezime, index), zavrsio(god){}
        StudentMaster *DajKopiju() const {
            return new StudentMaster(*this);
        }
        void IspisiPodatke() const {
            cout<<"Student master studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<","<<endl<<"zavrsio bachelor studij godine "<<zavrsio<<",ima prosjek "<<DajProsjek()<<"."<<endl;
        }
};

class Fakultet {
    vector<ApstraktniStudent*> v;
    bool jel(int indeks){
        for(int i=0; i<v.size(); i++){
            if(v[i]->DajBrojIndeksa()==indeks) return false;
        }
        return true;
    }
    public:
        Fakultet(){}
        ~Fakultet(){
            for(int i=0; i<v.size(); i++){
                delete v[i];
                v[i]=nullptr;
            }
        }
        Fakultet(const Fakultet &k): v(k.v){
            for(int i=0; k.v.size(); i++){
                v[i]=k.v[i]->DajKopiju();
            }
        }
        Fakultet &operator =(const Fakultet &k){
            vector<ApstraktniStudent*> novi(k.v.size());
            try{
                for(int i=0; i<novi.size(); i++){
                    novi[i]=k.v[i]->DajKopiju();
                }
            }catch(...) {throw;}
            for(int i=0; i<v.size(); i++){
                delete v[i];
                v[i]= nullptr;
            }
            v = novi;
            return *this;
        }
        Fakultet(Fakultet &&k):v(k.v.size()){
            for(int i=0; i<v.size(); i++) delete v[i];
            v.resize(k.v.size());
            try{
                for(int i=0; i<v.size(); i++){
                    v[i]=k.v[i]->DajKopiju();
                }
            }catch(...){ throw; } 
            for(int i=0; i<k.v.size(); i++){
                delete k.v[i];
                k.v[i]= nullptr;
            }
            k.v.resize(0);
        }
        Fakultet &operator =(Fakultet &&k){
             for(int i=0; i<v.size(); i++) delete v[i];
            v.resize(k.v.size());
            try{
                for(int i=0; i<v.size(); i++){
                    v[i]=k.v[i]->DajKopiju();
                }
            }catch(...){
                throw;
            } 
            for(int i=0; i<k.v.size(); i++){
                delete k.v[i];
                k.v[i]= nullptr;
            }
            k.v.resize(0);
            return *this;
        }
        void UpisiStudenta(string ime, string prezime, int indeks){
            if(!jel(indeks)) throw logic_error("Student sa zadanim brojem indeksa vec postoji");
            ApstraktniStudent *pok = new StudentBachelor(ime, prezime, indeks);
            v.push_back(pok);
        }
        void UpisiStudenta(string ime, string prezime, int indeks, int godina){
            if(!jel(indeks)) throw logic_error("Student sa zadanim brojem indeksa vec postoji");
            ApstraktniStudent *pok = new StudentMaster(ime, prezime, indeks, godina);
            v.push_back(pok);
        }
        void ObrisiStudenta(int indeks){
            if(jel(indeks)) throw logic_error("Student sa zadanim brojem indeksa ne postoji");
            int poz=0;
            for(int i=0; i<v.size(); i++){
                if(v[i]->DajBrojIndeksa()==indeks) {
                    delete v[i]; poz=i; break;
                }
                v.erase(v.begin(), v.begin()+poz+1);
            }
        }
        const ApstraktniStudent &operator [](int indeks) const {
            bool jel(true);
            for(int i=0; i<v.size(); i++){
                if(v[i]->DajBrojIndeksa()==indeks) jel=false;
            }
            if(jel) throw logic_error("Student sa zadanim brojem indeksa ne postoji");
            for(int i=0; i<v.size(); i++){
                if(v[i]->DajBrojIndeksa()==indeks) return *v[i];
            }
            return *v[0];
        }
        ApstraktniStudent &operator [](int indeks){
            if(jel(indeks)) throw logic_error("Student sa zadanim brojem indeksa ne postoji");
            for(int i=0; i<v.size(); i++){
                if(v[i]->DajBrojIndeksa()==indeks) return *v[i];
            }
            return *v[0];
        }
        void IspisiSveStudente() const {
            auto novi = v; 
            sort(novi.begin(), novi.end(), [](ApstraktniStudent* pok1, ApstraktniStudent* pok2){
                if(pok1->DajProsjek() == pok2->DajProsjek()) return pok1->DajBrojIndeksa() < pok2->DajBrojIndeksa();
		        return pok1->DajProsjek() > pok2->DajProsjek();
            });
            for(int i=0; i<novi.size(); i++){ novi[i]->IspisiPodatke();}
        }
};

class Student{
    ApstraktniStudent *p;
    public:
        Student(){p=nullptr;}
        ~Student(){delete p; p=nullptr;}
        Student(const Student &s){
            if(!s.p) p=nullptr;
            else p=s.p->DajKopiju();
        }
        Student(Student &&s){
            p=s.p;
            s.p=nullptr;
        }
        string DajIme() const{
            return p->DajIme();
        }
        string DajPrezime() const{
            return p->DajPrezime();
        }
        int DajBrojPolozenih() const{
            return p->DajBrojPolozenih();
        }
        int DajBrojIndeksa() const{
            return p->DajBrojIndeksa();
        }
        double DajProsjek() const{
            return p->DajProsjek();
        }
        void RegistrirajIspit(int ocjena){
            p->RegistrirajIspit(ocjena);
        }
        void PonistiOcjene(){
            p->PonistiOcjene();
        }
        void IspisiPodatke(){
            p->IspisiPodatke();
        }
        Student &operator =(const Student &s){
            ApstraktniStudent *pNovi(nullptr);
            if(s.p!=nullptr) pNovi = s.p->DajKopiju();
            delete p;
            p=pNovi;
            return *this;
        }
        Student &operator =(Student &&s){
            swap(p,s.p);
            return *this;
        }
        Student(const ApstraktniStudent &s):p(s.DajKopiju()){}
};

int main ()
{
	return 0;
}