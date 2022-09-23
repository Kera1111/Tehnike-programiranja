/* 
    TP 16/17 (LV 13, Zadatak 2)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <string>
#include <stdexcept>

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

int main ()
{
	return 0;
}