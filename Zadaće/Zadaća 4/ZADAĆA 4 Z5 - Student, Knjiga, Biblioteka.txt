//TP 2021/2022: Zadaća 4, Zadatak 5
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <stdexcept>
#include <algorithm>
#include <string>

using namespace std;

struct Student {
    string ime, prezime, adresa, telefon;
    int broj_indeksa, godina_studija;
    
    Student(string ime, string prezime, string adresa, string telefon, int broj_indeksa, int godina_studija): 
    ime(ime), prezime(prezime), adresa(adresa), telefon(telefon), broj_indeksa(broj_indeksa), godina_studija(godina_studija){}
    Student(){};
    string DajIme() const { return ime; }
    string DajPrezime() const { return prezime; }
    string DajAdresu() const { return adresa; }
    string DajTelefon() const { return telefon; }
    int DajBrojIndeksa() const { return broj_indeksa; }
    int DajGodinuStudija() const { return godina_studija; }
    // bool operator ==(const Student &s);
    void IspisiJednogStudenta();
};
/*
moze se i sa ovim uraditi pa porediti u PrikaziZaduzenja bez broja indeksa vec samo preko studenta al eto
bool Student::operator ==(const Student &s){
    if(s.DajIme()!=ime) return false;
    if(s.DajPrezime()!=prezime) return false;
    if(s.DajAdresu()!=adresa) return false;
    if(s.DajTelefon()!=telefon) return false;
    if(s.DajBrojIndeksa()!=broj_indeksa) return false;
    if(s.DajGodinuStudija()!=godina_studija) return false;
    return true;
}
*/

void Student::IspisiJednogStudenta(){
    cout<<"Indeks: "<<broj_indeksa<<endl;
    cout<<"Godina studija: "<<godina_studija<<endl;
    cout<<"Ime i prezime: "<<ime<<" "<<prezime<<endl;
    cout<<"Adresa: "<<adresa<<endl;
    cout<<"Telefon: "<<telefon<<endl;
}

class Knjiga {
        string naslov, imePisca, zanr;
        int godina_izdavanja;
        Student* zaduzeni;
    public:
        Knjiga(){}
        Knjiga(string naslov, string imePisca, string zanr, int godina_izdavanja)
        : naslov(naslov), imePisca(imePisca), zanr(zanr), godina_izdavanja(godina_izdavanja), zaduzeni(nullptr){}
        string DajNaslov() const { return naslov; }
        string DajAutora() const { return imePisca; }
        string DajZanr() const { return zanr; }
        int DajGodinuIzdavanja() const { return godina_izdavanja; }
        void ZaduziKnjigu(Student &k) { zaduzeni = &k; }
        void RazduziKnjigu() { zaduzeni = nullptr; }
        bool DaLiJeZaduzena() { if(zaduzeni){return true;} return false; }
        Student &DajKodKogaJe() const { 
            if(!zaduzeni){
                throw domain_error("Knjiga nije zaduzena");
            }
            return *zaduzeni; 
            }
        Student *DajPokKodKogaJe() const { return zaduzeni; }
        void IspisiJednuKnjigu();
};

void Knjiga::IspisiJednuKnjigu(){
    cout<<"Stanje: ";if(DaLiJeZaduzena()) cout<<"ZADUŽENA"; else cout<<"NA STANJU";cout<<endl;
    cout<<"Naslov: "<<naslov<<endl;
    cout<<"Ime pisca: "<<imePisca<<endl;
    cout<<"Zanr: "<<zanr<<endl;
    cout<<"Godina izdavanja: "<<godina_izdavanja<<endl;
}

class Biblioteka {
        map<int, Student*> studenti;
        map<int,Knjiga*> knjige;
    public:
        Biblioteka(){}
        Biblioteka(const Biblioteka &b);
        Biblioteka(Biblioteka &&b);
        ~Biblioteka();
        Biblioteka &operator =(const Biblioteka &b);
        Biblioteka &operator =(Biblioteka &&b);
        void RegistrirajNovogStudenta(int indeksKorisnika, string ime, string prezime, int godina_studija, string adresa, string telefon);
        void RegistrirajNovuKnjigu(int brojKnjige, string naslov, string imePisca, string zanr, int godinaIzdavanja);
        Student &NadjiStudenta(int indeksKorisnika);
        Knjiga &NadjiKnjigu(int brojKnjige);
        void IzlistajStudente() const;
        void IzlistajKnjige() const;
        void ZaduziKnjigu(int brojKnjige, int indeksKorisnika);
        void RazduziKnjigu(int brojKnjige);
        void PrikaziZaduzenja(int indeksKorisnika) const;
};

Biblioteka::Biblioteka(const Biblioteka &b){
    for(auto it=(b.studenti).begin(); it!=(b.studenti).end(); it++){
        studenti.insert(make_pair(it->first, new Student(*(it->second))));
    }
    for(auto it=(b.knjige).begin(); it!=(b.knjige).end(); it++){
        knjige.insert(make_pair(it->first, new Knjiga(*(it->second))));
    }
}

Biblioteka::Biblioteka(Biblioteka &&b){
    for(auto it=(b.studenti).begin(); it!=(b.studenti).end(); it++){
        studenti.insert(make_pair(it->first, it->second));
        it->second = nullptr;
    }
     for(auto it=(b.knjige).begin(); it!=(b.knjige).end(); it++){
        knjige.insert(make_pair(it->first, it->second));
        it->second = nullptr;
    }
}

Biblioteka::~Biblioteka(){
    for(auto it=studenti.begin(); it!=studenti.end(); it++){
        delete it->second;
    }  
    for(auto it=knjige.begin(); it!=knjige.end(); it++) {
        delete it->second;
    }
}

Biblioteka &Biblioteka::operator =(Biblioteka &&b){
    if(this!=&b){
        for(auto it=studenti.begin(); it!=studenti.end(); it++){
        delete it->second;
    }  
    for(auto it=knjige.begin(); it!=knjige.end(); it++) {
        delete it->second;
    }
        for(auto it=(b.studenti).begin(); it!=(b.studenti).end(); it++){
        studenti.insert(make_pair(it->first, it->second));
        it->second = nullptr;
    }
     for(auto it=(b.knjige).begin(); it!=(b.knjige).end(); it++){
        knjige.insert(make_pair(it->first, it->second));
        it->second = nullptr;
    }
    }
    return *this;
}

Biblioteka &Biblioteka::operator =(const Biblioteka &b){
    if(this!=&b){
        for(auto it=studenti.begin(); it!=studenti.end(); it++){
        delete it->second;
    }  
    for(auto it=knjige.begin(); it!=knjige.end(); it++) {
        delete it->second;
    }
    for(auto it=(b.studenti).begin(); it!=(b.studenti).end(); it++){
        studenti.insert(make_pair(it->first, new Student(
            (it->second)->DajIme(),
            (it->second)->DajPrezime(),
            (it->second)->DajAdresu(),
            (it->second)->DajTelefon(),
            (it->second)->DajBrojIndeksa(),
            (it->second)->DajGodinuStudija())));
    }
    for(auto it=(b.knjige).begin(); it!=(b.knjige).end(); it++){
        knjige.insert(make_pair(it->first, new Knjiga(
            (it->second)->DajNaslov(),
            (it->second)->DajAutora(),
            (it->second)->DajZanr(),
            (it->second)->DajGodinuIzdavanja()
        )));
        if((*(it->second)).DaLiJeZaduzena()){
            Student s((*(it->second)).DajKodKogaJe());
            for(auto it1=(b.studenti).begin();it1!=(b.studenti).end(); it++){
                if(s.DajBrojIndeksa()==(it1->second)->DajBrojIndeksa()){
                    ZaduziKnjigu(it->first, it->first);
                    break;
                }
            }
        }
    }
    }
    return *this;
}

void Biblioteka::RegistrirajNovogStudenta(int indeksKorisnika, string ime, string prezime, int godina_studija, string adresa, string telefon){
    auto it(studenti.find(indeksKorisnika));
    if(it!=studenti.end()) throw logic_error("Vec postoji student s tim brojem indeksa");
    studenti.insert(make_pair(indeksKorisnika, new Student(ime,prezime,adresa,telefon,indeksKorisnika,godina_studija)));
}

void Biblioteka::RegistrirajNovuKnjigu(int brojKnjige, string naslov, string imePisca, string zanr, int godinaIzdavanja){
     auto it(knjige.find(brojKnjige));
    if(it!=knjige.end()) throw logic_error("Knjiga s tim evidencijskim brojem vec postoji");
    knjige.insert(make_pair(brojKnjige, new Knjiga(naslov, imePisca, zanr, godinaIzdavanja)));
}

Student &Biblioteka::NadjiStudenta(int indeksKorisnika){
    auto it(studenti.find(indeksKorisnika));
    if(it==studenti.end()) throw logic_error("Student nije nadjen");
    Student &s(*(it->second));
    return s;
}

Knjiga &Biblioteka::NadjiKnjigu(int brojKnjige){
    auto it(knjige.find(brojKnjige));
    if(it==knjige.end()) throw logic_error("Knjiga nije nadjena");
    Knjiga &k(*(it->second));
    return k;
}

void Biblioteka::IzlistajStudente() const {
    for(auto it=studenti.begin(); it!=studenti.end(); it++){
        cout<<"Broj indeksa: "<<it->first<<endl;
        cout<<"Ime i prezime: "<<(it->second)->DajIme()<<" "<<(it->second)->DajPrezime()<<endl;
        cout<<"Godina studija: "<<(it->second)->DajGodinuStudija()<<endl;
        cout<<"Adresa: "<<(it->second)->DajAdresu()<<endl;
        cout<<"Broj telefona: "<<(it->second)->DajTelefon()<<endl;
        cout<<endl;
    }
}

void Biblioteka::IzlistajKnjige() const {
    for(auto it=knjige.begin(); it!=knjige.end(); it++){
        cout<<"Evidencijski broj: "<<it->first<<endl;
        cout<<"Naslov: "<<(it->second)->DajNaslov()<<endl;
        cout<<"Pisac: "<<(it->second)->DajAutora()<<endl;
        cout<<"Zanr: "<<(it->second)->DajZanr()<<endl;
        cout<<"Godina izdavanja: "<<(it->second)->DajGodinuIzdavanja()<<endl;
        if((it->second)->DaLiJeZaduzena()) cout<<"Zaduzena kod studenta: "<<((it->second)->DajKodKogaJe()).DajIme()<<" "<<((it->second)->DajKodKogaJe()).DajPrezime()<<" ("<<((it->second)->DajKodKogaJe()).DajBrojIndeksa()<<")"<<endl;
        cout<<endl;
    }
}

void Biblioteka::ZaduziKnjigu(int brojKnjige, int indeksKorisnika){

    auto it(knjige.find(brojKnjige));
    if(it==knjige.end()) throw logic_error("Knjiga nije nadjena");

    auto it1(studenti.find(indeksKorisnika));
    if(it1==studenti.end()) throw logic_error("Student nije nadjen");

    if((it->second)->DaLiJeZaduzena()) throw logic_error("Knjiga vec zaduzena");

    (*(it->second)).ZaduziKnjigu(NadjiStudenta(indeksKorisnika));

}

void Biblioteka::RazduziKnjigu(int brojKnjige){
    auto it(knjige.find(brojKnjige));
    if(it==knjige.end()) throw logic_error("Knjiga nije nadjena");
    if(!((it->second)->DaLiJeZaduzena())) throw logic_error("Knjiga nije zaduzena");
    (*(it->second)).RazduziKnjigu();
}

void Biblioteka::PrikaziZaduzenja(int indeksKorisnika) const {

    auto it(studenti.find(indeksKorisnika));
    if(it==studenti.end()) throw logic_error("Student nije nadjen");

    bool temp = false;
    Student s(*(it->second));
    auto it2(knjige.begin());
    while(it2!=knjige.end()){
        if((it2->second)->DaLiJeZaduzena()){
            if(((it2->second)->DajKodKogaJe().DajBrojIndeksa)()==s.DajBrojIndeksa()){
                temp = true;
                break;
            }
        }
        it2++;
    }
    
    for(auto it1=knjige.begin(); it1!=knjige.end(); it1++){
        if((it1->second)->DaLiJeZaduzena()){
            temp=true;
            if(((it1->second)->DajKodKogaJe().DajBrojIndeksa)()==s.DajBrojIndeksa()){
                cout<<"Evidencijski broj: "<<it1->first<<endl;
                cout<<"Naslov: "<<(it1->second)->DajNaslov()<<endl;
                cout<<"Pisac: "<<(it1->second)->DajAutora()<<endl;
                cout<<"Zanr: "<<(it1->second)->DajZanr()<<endl;
                cout<<"Godina izdavanja: "<<(it1->second)->DajGodinuIzdavanja()<<endl;
            }
        }
    }
    if(!temp) cout<<"Nema zaduzenja za tog studenta!";
}

int main ()
{
    cout<<"STUDENTSKA BIBLIOTEKA ETF"<<endl<<endl;

    cout<<"Unesite odgovarajući broj za izvršenje komande"<<endl;
    cout<<"Legenda:"<<endl;
    cout <<"0 - prekid"<<endl
        <<"1- registrovanje novog studenta"<<endl
        <<"2 - registrovanje nove knjige"<<endl
        <<"3 - pronaći studenta"<<endl
        <<"4 - pronaći knjigu"<<endl
        <<"5 - prikaz svih studenata"<<endl
        <<"6 - prikaz svih knjiga"<<endl
        <<"7 - zaduživanje knjige"<<endl
        <<"8 - razduživanje knjige"<<endl
        <<"9 - prikaz svih zaduženja"<<endl
        <<"10 - motivacijska poruka dana"<<endl;

    Biblioteka b;
    
    while(1){
        int komanda;
        cin>>komanda;
        switch(komanda){
            case 0: break;
            case 1:
                try{
                    cout<<"Unesite ime i prezime, indeks, godinu studija, adresu stanovanja i broj telefona novog studenta:"<<endl;
                    int indeksKorisnika, godina_studija;
                    string ime, prezime, adresa, telefon;
                    cin>>ime>>prezime>>indeksKorisnika>>godina_studija>>adresa>>telefon;
                    b.RegistrirajNovogStudenta(indeksKorisnika, ime, prezime, godina_studija, adresa, telefon);
                    b.IzlistajStudente();
                }catch(domain_error &e){
                    cout<<e.what()<<endl;
                }
                break;
            case 2:
            try{
                cout<<"Unesite evidencijski broj, naslov, ime pisca, zanr i godinu izdavanja:"<<endl;
                    int brojKnjige, godinaIzdavanja;
                    string naslov, imePisca, zanr;
                    cin>>brojKnjige>>naslov>>imePisca>>zanr>>godinaIzdavanja;
                    b.RegistrirajNovuKnjigu(brojKnjige, naslov, imePisca, zanr, godinaIzdavanja);
                    b.IzlistajKnjige();
            }catch(domain_error &e){
                    cout<<e.what()<<endl;
            }
                break;
            case 3:
                try{
                cout<<"Unesite broj indeksa studentsa kojeg želite pronaći:"<<endl;
                    int indeksKorisnika;
                    cin>>indeksKorisnika;
                    b.NadjiStudenta(indeksKorisnika).IspisiJednogStudenta();
                }catch(domain_error &e){
                    cout<<e.what()<<endl;
                }
                break;
            case 4:
                try{
                cout<<"Unesite broj knjige koje želite pronaći:"<<endl;
                    int brojKnjige;
                    cin>>brojKnjige;
                    b.NadjiKnjigu(brojKnjige).IspisiJednuKnjigu();
                }catch(domain_error &e){
                    cout<<e.what()<<endl;
                }
                break;
            case 5:
                 try{
                    b.IzlistajStudente();
                }catch(domain_error &e){
                    cout<<e.what()<<endl;
                }
                break;
            case 6:
                try{
                    b.IzlistajKnjige();
                }catch(domain_error &e){
                    cout<<e.what()<<endl;
                }
                break;
            case 7:
                try{
                    cout<<"Unesite indeks studenta koji zadužuje knjigu, a zatim i evidencijski broj knjige koja se zadužuje:"<<endl;
                    int indeksKorisnika, brojKnjige;
                    cin>>indeksKorisnika>>brojKnjige;
                    b.ZaduziKnjigu(brojKnjige, indeksKorisnika);
                    cout<<"Knjiga: "<<endl;
                    b.NadjiKnjigu(brojKnjige).IspisiJednuKnjigu();
                    cout<<"Knjiga je uspješno zadužena kod studenta sa brojem indeksa "<<indeksKorisnika<<endl;
                    b.NadjiKnjigu(brojKnjige).DajKodKogaJe().IspisiJednogStudenta();
                }catch(domain_error &e){
                    cout<<e.what()<<endl;
                }
                break;
            case 8:
                try{
                    cout<<"Unesite evidencijski broj knjige koju želite razdužiti: "<<endl;
                    int brojKnjige;
                    cin>>brojKnjige;
                    b.RazduziKnjigu(brojKnjige);
                    b.IzlistajKnjige();
                }catch(domain_error &e){
                    cout<<e.what()<<endl;
                }
                break;
            case 9:
                try{
                    cout<<"Unesite broj indeksa kako bi prikazali sva zaduženja: ";
                    int indeksKorisnika;
                    cin>>indeksKorisnika;
                    cout<<"Spisak svih zaduženja studenta: "<<endl;
                    b.PrikaziZaduzenja(indeksKorisnika);
                }catch(domain_error &e){
                    cout<<e.what()<<endl;
                }
                break;
            case 10:{
                int random = rand()%3;
                if(random==0) cout<<"Nikad ne odustaj";
                else if(random==1) cout<<"Samo polako, nebo strpljive voli <3";
                else cout<<"Pokaži da možeš i hoćeš :)";
                break;}
            default: 
                cout<<"Pogriješili ste broj komande.";
                break;
        }
    }

	return 0;
}
