//TP 2021/2022: Zadaća 5, Zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
#include <iterator>
#include <functional>

using namespace std;

class Berza {
        int minCijena, maxCijena;
        vector<int> registrovano;
    public:    
        Berza(int minCijena, int maxCijena){
            Berza::minCijena = minCijena;
            Berza::maxCijena = maxCijena;
            if(minCijena < 0 || maxCijena < 0) throw range_error("Ilegalne granicne cijene"); 
        }

        explicit Berza(int maxCijena){
            Berza::minCijena = 0;
            Berza::maxCijena = maxCijena;
            if(maxCijena<0) throw range_error("Ilegalne granicne cijene");
        }

        void RegistrirajCijenu(int cijena){
            if(cijena<minCijena || cijena>maxCijena) throw range_error("Ilegalna cijena");
            registrovano.push_back(cijena);
        }

        int DajBrojRegistriranihCijena() const{
            return registrovano.size();
        }

        void BrisiSve(){
            registrovano.clear();
        }

        int DajMinimalnuCijenu() const{
            if(registrovano.empty()) throw range_error("Nema registriranih cijena");
            return *min_element(registrovano.begin(), registrovano.end());
        }

        int DajMaksimalnuCijenu() const{
            if(registrovano.empty()) throw range_error("Nema registriranih cijena");
            return *max_element(registrovano.begin(), registrovano.end());
        }

        bool operator !() const{
            return registrovano.empty();
        }

        int DajBrojCijenaVecihOd(int cijena) const{
            if(registrovano.empty()) throw range_error("Nema registriranih cijena");
            return count_if(registrovano.begin(), registrovano.end(), bind(greater<int>(), placeholders::_1, cijena));
        }

        void Ispisi() const{
            vector<double> temp(registrovano.begin(), registrovano.end());
            sort(temp.begin(), temp.end(), greater<int>());
            transform(temp.begin(), temp.end(), 
            ostream_iterator<double>(cout<<setprecision(2)<<fixed, "\n"), bind(divides<double>(), placeholders::_1, 100.));
        }

        int operator [] (int indeks) const{
            if(indeks<1 || indeks>registrovano.size()) throw range_error("Neispravan indeks");
            return registrovano[indeks-1];
        }

        Berza& operator ++(){
            if(find_if(registrovano.begin(), registrovano.end(), 
            bind(greater<int>(), placeholders::_1, maxCijena-100))!=registrovano.end()) 
            throw range_error("Prekoracen dozvoljeni opseg cijena");
            transform(registrovano.begin(), registrovano.end(), registrovano.begin(), 
            bind(plus<int>(), placeholders::_1, 100));
            return *this;
        }

        Berza operator ++(int){
            if(find_if(registrovano.begin(), registrovano.end(), 
            bind(greater<int>(), placeholders::_1, maxCijena-100))!=registrovano.end()) 
            throw range_error("Prekoracen dozvoljeni opseg cijena");
            transform(registrovano.begin(), registrovano.end(), registrovano.begin(), 
            bind(plus<int>(), placeholders::_1, 100));
            return *this;
        }

        Berza &operator --(){
            if(find_if(registrovano.begin(), registrovano.end(), 
            bind(less<int>(), placeholders::_1, minCijena+100))!=registrovano.end()) 
            throw range_error("Prekoracen dozvoljeni opseg cijena");
            transform(registrovano.begin(), registrovano.end(), registrovano.begin(), 
            bind(minus<int>(), placeholders::_1, 100));
            return *this;
        }

        Berza operator --(int){
            if(find_if(registrovano.begin(), registrovano.end(), 
            bind(less<int>(), placeholders::_1, minCijena+100))!=registrovano.end()) 
            throw range_error("Prekoracen dozvoljeni opseg cijena");
            transform(registrovano.begin(), registrovano.end(), registrovano.begin(), 
            bind(minus<int>(), placeholders::_1, 100));
            return *this;
        }

        Berza operator -() const{
            Berza rez(*this);
            transform(rez.registrovano.begin(), rez.registrovano.end(), rez.registrovano.begin(),
            bind(minus<int>(), rez.maxCijena+rez.minCijena, placeholders::_1));
            return rez;
        }

        Berza& operator +=(int x){
            return *this = *this + x;
        }

        Berza& operator -=(int x){
            return *this = *this - x;
        }

        Berza& operator -=(const Berza& x){
            return *this = *this - x;
        }
        friend Berza operator + (Berza&x, int y);
        friend Berza operator + (int x, const Berza& y);
        friend Berza operator - (Berza x, int y);
        friend Berza operator - (int, Berza);
        friend Berza operator - (Berza, Berza);
        friend bool operator == (const Berza&, const Berza&);
        friend bool operator != (const Berza&, const Berza&);
};


Berza operator + (Berza &x, int y){
    if(find_if(x.registrovano.begin(), x.registrovano.end(), 
    bind(greater<int>(), placeholders::_1, x.maxCijena+y))!=x.registrovano.end()) 
    throw domain_error("Prekoracen dozvoljeni opseg cijena");
    transform(x.registrovano.begin(), x.registrovano.end(),
                    x.registrovano.begin(), bind(plus<int>(), placeholders::_1, y));
    return x;
}

Berza operator + (int x, const Berza& y){
    return x+y;
}

Berza operator - (Berza x, int y){
     if(find_if(x.registrovano.begin(), x.registrovano.end(), 
    bind(less<int>(), placeholders::_1, x.minCijena-y))!=x.registrovano.end()) 
    throw domain_error("Prekoracen dozvoljeni opseg cijena");
    transform(x.registrovano.begin(), x.registrovano.end(),
                    x.registrovano.begin(), bind(minus<int>(), placeholders::_1, y));
    return x;
}

Berza operator - (int y, Berza x){
    if(find_if(x.registrovano.begin(), x.registrovano.end(), 
    bind(less<int>(), y-x.minCijena, placeholders::_1))!=x.registrovano.end()) 
    throw domain_error("Prekoracen dozvoljeni opseg cijena");
    if(find_if(x.registrovano.begin(), x.registrovano.end(), 
    bind(greater<int>(), y-x.maxCijena, placeholders::_1))!=x.registrovano.end()) 
    throw domain_error("Prekoracen dozvoljeni opseg cijena");
    transform(x.registrovano.begin(), x.registrovano.end(),
                    x.registrovano.begin(), bind(minus<int>(), y, placeholders::_1));
    return x;
}

Berza operator - (Berza x, Berza y){
    if(x.registrovano.size()!=y.registrovano.size() 
    || x.maxCijena!=y.maxCijena 
    || x.minCijena!=y.minCijena ) throw domain_error("Nesaglasni operandi");
    transform(x.registrovano.begin(), x.registrovano.end(),
                    y.registrovano.begin(), x.registrovano.end(), minus<int>());
    if(find_if(x.registrovano.begin(), x.registrovano.end(), 
    bind(less<int>(), placeholders::_1, x.minCijena))!=x.registrovano.end())
    throw domain_error("Prekoracen dozvoljeni opseg cijena");
    return x;
}

bool operator == (const Berza& x, const Berza& y){
    return x.maxCijena == y.maxCijena && x.minCijena == y.minCijena
    && x.registrovano.size() ==y.registrovano.size() 
    && equal(x.registrovano.begin(), x.registrovano.end(), y.registrovano.begin());
}

bool operator != (const Berza& x, const Berza& y){
    return !(x==y);
}

int main ()
{
	return 0;
}