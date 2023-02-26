/* 
    TP 16/17 (LV 13, Zadatak 1)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cmath>
#include <vector>
#include <memory>
#include <stdexcept>

using namespace std;

const double pi = 4*atan(1);

class Lik {
    public:
        virtual void IspisiSpecificnosti() const = 0;
        virtual double DajObim() const = 0;
        virtual double DajPovrsinu() const = 0;
        virtual ~Lik() {}
        virtual void Ispisi() const {}
};

class Krug : public Lik {
        double poluprecnik;
    public:
        Krug(double x){
            if(x<=0) throw domain_error("Neispravni parametri");
            poluprecnik = x;
        }
        void IspisiSpecificnosti() const {
            cout<<"Krug poluprecnika "<<poluprecnik<<endl;
        }
        void Ispisi() const {
            IspisiSpecificnosti();
            cout<<"Obim: "<<DajObim()<<" Povrsina: "<<DajPovrsinu()<<endl;
        }
        double DajObim() const {
            return 2*poluprecnik*pi;
        }
        double DajPovrsinu() const {
            return poluprecnik * poluprecnik * pi;
        }
};

class Pravougaonik : public Lik {
        double a, b;
    public:
        Pravougaonik(double x, double y){
            if(x<=0 || y<=0) throw domain_error("Neispravni parametri");
            a=x;
            b=y;
        }
        void IspisiSpecificnosti() const {
            cout<<"Pravougaonik sa stranicama duzine "<<a<<" i "<<b<<endl;
        }
        void Ispisi() const {
            IspisiSpecificnosti();
            cout<<"Obim: "<<DajObim()<<" Povrsina: "<<DajPovrsinu()<<endl;
        }
        double DajObim() const {
            return 2*(a+b);
        }
        double DajPovrsinu() const {
            return a*b;
        }
};

class Trougao : public Lik {
        double x,y,z;
    public:
        Trougao(double a, double b, double c){
            bool jel(a>0 && b>0 && c>0 && ((a+b)>c && (a+c)>b && (b+c)>a));
            if(!jel) throw domain_error("Neispravni parametri");
            x=a;
            y=b;
            z=c;
        }
        void IspisiSpecificnosti() const {
            cout<<"Trougao sa stranicama duzine "<<x<<", "<<y<<" i "<<z<<endl;
        }
        void Ispisi() const {
            IspisiSpecificnosti();
            cout<<"Obim: "<<DajObim()<<" Povrsina: "<<DajPovrsinu()<<endl;
        }
        double DajObim() const {
            return (x+y+z);
        }
        double DajPovrsinu() const {
            double s = (DajObim()/2);
            return sqrt(s*(s-x)*(s-y)*(s-z));
        }
};

int main ()
{
    int n;
    cout<<"Koliko zelite likova: ";
    cin>>n;
    vector<shared_ptr<Lik>> v(n);
    for(int i=0; i<n; ){
        try{
            cin.ignore(1000, '\n');
            cout<<"Lik "<<i+1<<": ";
            char c;
            c = cin.get();
            double x,y,z,br;
            switch(c){
                case 'K':
                    cin>>br;
                    if(!cin || cin.peek()!='\n'){
                        cout<<"Pogresni podaci, ponovite unos!"<<endl;
                        continue;
                        }
                        v[i] = make_shared<Krug>(Krug(br));
                        i++;
                        break;
                case 'P':
                    char e;
                    cin>>x>>e>>y;
                    if(!cin || cin.peek()!='\n'){
                        cout<<"Pogresni podaci, ponovite unos!"<<endl;
                        continue;}
                        v[i] = make_shared<Pravougaonik>(Pravougaonik(x,y));
                        i++;
                        break;
                    
                case 'T':
                    char r;
                    cin>>x>>r>>y>>r>>z;
                    if(!cin || cin.peek()!='\n'){
                        cout<<"Pogresni podaci, ponovite unos!"<<endl;
                        continue;}
                        v[i] = make_shared<Trougao>(Trougao(x,y,z));
                        i++;
                        break;
                    
                default:
                    cout<<"Pogresni podaci, ponovite unos!"<<endl;
                    break;
            }
        }catch(domain_error &e){
                cout<<"Pogresni podaci, ponovite unos!"<<endl;
            }
    }
    cout<<endl;
    for(auto x : v) x->Ispisi();
	return 0;
}